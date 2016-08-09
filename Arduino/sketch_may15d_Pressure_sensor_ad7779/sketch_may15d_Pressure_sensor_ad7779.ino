/*
Pressure sensor system

This system shows how to log data from a analog sensor and log 
data into an SD card using the SD library.Also use an external 
24 bits ADC
   
created  20 June 2013
by Danny   
*/

#include <SPI.h>
//#include <SD.h>
//#include <LiquidCrystal.h>
#include <Wire.h>
#include "rgb_lcd.h"


//NodeMCU
const int RESET_PIN                 = 16;//D0
const int ALERT_PIN                 =  5;//D1
const int DRDY_PIN                  =  4;//D2
const int ADCCS                     = 15;
const int START_PIN                 =  0;//D0

//const int SDA_PIN                   =  0;
//const int CLK_PIN                   =  2;

//const int SDCS = 4;
//const int ADCCS = 10;

//Intel Edison
//const int RESET_PIN                 = 0;//16;//D0
//const int ALERT_PIN                 = 1;//17;//D1
//const int DRDY_PIN                  = 2;//18;//D2
//const int ADCCS                     =  10;

//const int RESET_PIN                 = 16;//D0
//const int ALERT_PIN                 = 17;//D1
//const int DRDY_PIN                  = 18;//D2
//const int SDA_PIN                   =  0;
//const int CLK_PIN                   =  2;
//const int SDCS = 4;
//const int ADCCS = 10;
//const int ADCCS                     =  16;//2;


const int GENERAL_USER_CONFIG_1_REG = 0x011;
const int GENERAL_USER_CONFIG_2_REG = 0x012;
const int GENERAL_USER_CONFIG_3_REG = 0x013;
const int DOUT_FORMAT_REG           = 0x014;
const int ADC_MUX_CONFIG_REG        = 0x015;

const int BUFFER_CONFIG_1_REG       = 0x019;
const int BUFFER_CONFIG_2_REG       = 0x01A;

const int CH0_ERR_REG_REG           = 0x04C;
const int CH1_ERR_REG_REG           = 0x04D;
const int CH2_ERR_REG_REG           = 0x04E;
const int CH3_ERR_REG_REG           = 0x04F;
const int CH4_ERR_REG_REG           = 0x050;
const int CH5_ERR_REG_REG           = 0x051;
const int CH6_ERR_REG_REG           = 0x052;
const int CH7_ERR_REG_REG           = 0x053;
const int CH0_1_SAT_ERR_REG         = 0x054;
const int CH2_3_SAT_ERR_REG         = 0x055;
const int CH4_5_SAT_ERR_REG         = 0x056;
const int CH6_7_SAT_ERR_REG         = 0x057;
const int CHX_ERR_REG_EN_REG        = 0x058;
const int GEN_ERR_REG_1_REG         = 0x059;
const int GEN_ERR_REG_1_EN_REG      = 0x05A;
const int GEN_ERR_REG_2_REG         = 0x05B;
const int GEN_ERR_REG_2_EN_REG      = 0x05C;
const int STATUS_REG_1_REG          = 0x05D;
const int STATUS_REG_2_REG          = 0x05E;
const int STATUS_REG_3_REG          = 0x05F;
const int SRC_N_MSB_REG             = 0x060;
const int SRC_N_LSB_REG             = 0x061;
const int SRC_IF_MSB_REG            = 0x062;
const int SRC_IF_LSB_REG            = 0x063;
const int SRC_UPDATE_REG            = 0x064;




int alert;
int reset;
int drdy;



rgb_lcd lcd;
uint8_t char_cel[8] = {
  B00111, B00101, B00111, B00000, B00000, B00000, B00000
};


double pressureValue0 = 0;
double pressureValue1 = 0;
double pressureValue2 = 0;
double pressureValue3 = 0;
//const int fs=3;
//const int fs=3;
//const int fs=250;
//const int fs=250000;
//const int fs=2000;
//const int fs=16000;
//const int fs=256;
const int fs=50;
//LiquidCrystal lcd(12, 11, 6, 5, 3, 2);
//byte command11 = B01001000;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01010100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01111000;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
byte command11 = B01001000;//GENERAL_USER_CONFIG_1 0x011
/*
7 ALL_CH_DIS_MCLK_EN If all Σ-Δ channels are disabled, setting this bit high allows DCLK to
continue toggling.
 0x0 R/W
6 POWERMODE Power Mode.
 0x0 R/W
 0 Low power (1/4).
 1 High resolution.
5 PDB_VCM Power Down VCM Buffer. Active low. 
 0x1 R/W
4 PDB_REFOUT_BUF Power Down Internal Reference Output Buffer. Active low. 
 0x0 R/W
3 PDB_SAR Power Down SAR. Active low. 
 0x0 R/W
2 PDB_RC_OSC Power Down Signal for Internal Oscillator. Active low. 
 0x1 R/W
[1:0] SOFT_RESET Soft Reset
 0x0 R/W
 00 No effect
 01 No effect
 10 2nd write
 11 1st write
 */
//byte command12 = B00011111;//GENERAL_USER_CONFIG_2 0x012
byte command12 = B00011001;//GENERAL_USER_CONFIG_2 0x012
//byte command12 = B00011111;//GENERAL_USER_CONFIG_2 0x012
//byte command12 = B00001001;//GENERAL_USER_CONFIG_2 0x012
/*
[7:6] RESERVED Reserved. 
 0x0 R/W
5 SAR_DIAG_MODE_EN Sets SPI Interface to Read Back SAR Result on SDO. 
 0x0 R/W
[4:3] SDO_DRIVE_STR SDO Drive Strength. 
 0x1 R/W
 00 Nominal.
 01 Strong.
 10 Weak.
 11 Extra strong.
[2:1] DOUT_DRIVE_STR DOUTx Drive Strength.
 0x0 R/W
 00 Nominal.
 01 Strong.
 10 Weak.
 11 Extra strong.
0 SPI_SYNC SYNC Pulse Generated Through SPI.
 0x1 R/W
 0 This signal is AND’ed with the value on the START pin in the control module and generates a pulse in the SYNC_IN pin.
 1 This bit is AND’ed with the value on START pin in the control module.
 */
byte command13  = B10000000;//GENERAL_USER_CONFIG_3 0x013
byte command13_spi = B10010000;//GENERAL_USER_CONFIG_3 0x013
/*
[7:6] CONVST_DEGLITCH_DIS Disable deglitching of CONVST_SAR pin
 0x2 R/W
 00 Reserved.
 01 Reserved.
 10 CONVST_SAR Deglitch 1.5 MCLK.
 11 No deglitch circuit.
5 RESERVED Reserved. 
 0x0 R/W
4 SPI_SLAVE_MODE_EN Enable to SPI slave mode to read back ADC on SDO 
 0x0 R/W
[3:2] RESERVED Reserved. 
 0x0 R/W
1 RESERVED Reserved. 
 0x0 R/W
0 CLK_QUAL_DIS Disables the clock qualifier check if the user requires to use an MCLK
signal <265 kHz. 
 0x0 R/W
 */
byte command14 = B00000000;//DOUT_FORMAT 0x014
/*
[7:6] DOUT_FORMAT Data Out Format.
 0x0 R/W
 00 4 DOUT lines
 01 2 DOUT lines
 10 1 DOUT lines
 11 1 DOUT lines
5 DOUT_HEADER_FORMAT DOUT Header Format
 0x1 R/W
 0 Status header
 1 CRC header
4 RESERVED Reserved.
 0x0 R/W
[3:1] DCLK_CLK_DIV Divide MCLK
 0x0 R/W
0 RESERVED Reserved.
 0x0 R/W
 */
//byte command15 = B10011000;//ADC_MUX_CONFIG 0x015
//byte command15 = B01011000;//ADC_MUX_CONFIG 0x015
byte command15 = B00001100;//ADC_MUX_CONFIG 0x015
//byte command15 = B01100000;//ADC_MUX_CONFIG 0x015
/*
[7:6] REF_MUX_CTRL SD ADC Reference Mux
 0x0 R/W
 00 External reference REFx+/REFx−
 01 Internal reference.
 10 External supply AVDD1x/AVSSx.
 11 External reference REFx−/REFx+.
[5:2] MTR_MUX_CTRL SD ADC Meter Mux
 0x0 R/W
 0010 280 mV
 0011 External reference REFx+/REFx−
 0100 External reference REFx−/REFx+
 0101 External reference REFx−/REFx−
 0110 Internal reference +/−
 0111 Internal reference −/+
 1000 Internal reference +/+
 1001 External reference REFx+/REFx+
[1:0] RESERVED Reserved.
 0x0 R/W
 */

//byte command19 = B00011000;//BUFFER_CONFIG_1 0x019
byte command19 = B00000000;//BUFFER_CONFIG_1 0x019
/*
[7:5] RESERVED Reserved 0x0 R/W
4 REF_BUF_POS_EN Reference Buffer Positive Enable 0x1 R/W
3 REF_BUF_NEG_EN Reference Buffer Negative Enable 0x1 R/W
[2:0] RESERVED Reserved 0x0 R/W
*/

//byte command1A = B11000000;//BUFFER_CONFIG_2 0x01A
byte command1A = B00000000;//BUFFER_CONFIG_2 0x01A
/*
7 REFBUFP_PREQ Reference Buffer Positive Precharge Enable 0x1 R/W
6 REFBUFN_PREQ Reference Buffer Negative Precharge Enable 0x1 R/W
[5:3] RESERVED Reserved. 0x0 R/W
2 PDB_ALDO1_OVRDRV AREG1CAP Overdrive Enable 0x0 R/W
1 PDB_ALDO2_OVRDRV AREG2CAP Overdrive Enable 0x0 R/W
0 PDB_DLDO_OVRDRV DREGCAP Overdrive Enable 0x0 R/W
*/

//CH0_ERR_REG 0x04C
/*
[7:5] RESERVED Reserved 0x0 R/W
4 CH0_ERR_AINM_UV Channel 0—AIN1− Undervoltage Error 0x0 R
3 CH0_ERR_AINM_OV Channel 0—AIN1− Overvoltage Error 0x0 R
2 CH0_ERR_AINP_UV Channel 0—AIN1+ Undervoltage Error 0x0 R
1 CH0_ERR_AINP_OV Channel 0—AIN1+ Overvoltage Error 0x0 R
0 CH0_ERR_REF_DET Channel 0—Reference Detect Error 0x0 R
*/
//CH0_1_SAT_ERR 0x054
/*
5 CH1_ERR_MOD_SAT Channel 1—Modulator Output Saturation Error 0x0 R
4 CH1_ERR_FILTER_SAT Channel 1—Filter result has exceeded a reasonable level, before offset and
gain calibration has been applied 0x0 R
3 CH1_ERR_OUTPUT_SAT Channel 1—ADC conversion has exceeded limits and has been clamped 0x0 R
2 CH0_ERR_MOD_SAT Channel 0—Modulator Output Saturation Error 0x0 R
1 CH0_ERR_FILTER_SAT Channel 0—Filter result has exceeded a reasonable level, before offset and
gain calibration has been applied 0x0 R
0 CH0_ERR_OUTPUT_SAT Channel 0—ADC conversion has exceeded limits and has been clamped 0x0 R
*/

byte command58 = B11111111;//CHX_ERR_REG_EN 0x058
//byte command58 = B00000000;//CHX_ERR_REG_EN 0x058
/*
7 OUTPUT_SAT_TEST_EN ADC Conversion Error Test Enable 0x1 R/W
6 FILTER_SAT_TEST_EN Filter Saturation Test Enable 0x1 R/W
5 MOD_SAT_TEST_EN Enable Error Flag for Modulator Saturation 0x1 R/W
4 AINM_UV_TEST_EN AINx− Undervoltage Test Enable 0x1 R/W
3 AINM_OV_TEST_EN AINx− Overvoltage Test Enable 0x1 R/W
2 AINP_UV_TEST_EN AINx+ Undervoltage Test Enable 0x1 R/W
1 AINP_OV_TEST_EN AINx+ Overvoltage Test Enable 0x1 R/W
0 REF_DET_TEST_EN Reference Detect Test Enable 0x0 R/W
*/

//GEN_ERR_REG_1 0x059
/*
5 MEMMAP_CRC_ERR A CRC of the memory map contents is run periodically to check for errors 0x0 R
4 ROM_CRC_ERR A CRC of the fuse contents is run periodically to check for errors in the fuses 0x0 R
3 SPI_CLK_COUNT_ERR SPI clock counter error 0x0 R
2 SPI_INVALID_READ_ERR SPI invalid read address 0x0 R
1 SPI_INVALID_WRITE_ERR SPI invalid write address 0x0 R
0 SPI_CRC_ERR SPI CRC error 0x0 R
*/
//byte command5A = B11111110;//GEN_ERR_REG_1_EN 0x05A
byte command5A = B11111110;//GEN_ERR_REG_1_EN 0x05A
/*
5 MEMMAP_CRC_TEST_EN Memory Map CRC Test Enable 0x1 R/W
4 ROM_CRC_TEST_EN Fuse CRC Test Enable 0x1 R/W
3 SPI_CLK_COUNT_TEST_EN SPI Clock Counter Test Enable 0x1 R/W
2 SPI_INVALID_READ_TEST_EN SPI Invalid Read Address Test Enable 0x1 R/W
1 SPI_INVALID_WRITE_TEST_EN SPI Invalid Write Address Test Enable 0x1 R/W
0 SPI_CRC_TEST_EN SPI CRC Error Test Enable 0x0 R/W
*/
//GEN_ERR_REG_2 0x05B
/*
5 RESET_DETECTED Reset Detected 0x0 R
4 EXT_MCLK_SWITCH_ERR Clock Not Switched Over 0x0 R
2 ALDO1_PSM_ERR AREG1CAP Power Supply Error 0x0 R
1 ALDO2_PSM_ERR AREG2CAP Power Supply Error 0x0 R
0 DLDO_PSM_ERR DREGCAP Power Supply Error 0x0 R
*/
byte command5C = B00111100;//GEN_ERR_REG_2_EN 0x05C
/*
5 RESET_DETECT_EN Reset Detect Enable 0x1 R/W
4 RESERVED Reserved 0x1 R/W
[3:2] LDO_PSM_TEST_EN LDO PSM Test EN 0x3 R/W
 0 00—no power supply monitor test enabled.
 1 01—run power supply monitor test on AREGxCAP
 10 10—run power supply monitor test on DREGCAP
 11 11—run power supply monitor test on all LDOs
[1:0] LDO_PSM_TRIP_TEST_EN LDO PSM Trip Test Enable 0x0 R/W
 0 00—no trip detect test enabled
 1 01—run trip detect test on AREG1CAP
 10 10—run trip detect test on AREG2CAP
 11 11—run trip detect test on DREGCAP
*/
//STATUS_REG_1 0x05D
/*
5 CHIP_ERROR Set this bit high if any error bit is high 0x0 R
4 ERR_LOC_CH4 An error specific to CH4_ERR_REG is active 0x0 R
3 ERR_LOC_CH3 An error specific to CH3_ERR_REG is active 0x0 R
2 ERR_LOC_CH2 An error specific to CH2_ERR_REG is active 0x0 R
1 ERR_LOC_CH1 An error specific to CH1_ERR_REG is active 0x0 R
0 ERR_LOC_CH0 An error specific to CH0_ERR_REG is active 0x0 R
*/
//STATUS_REG_2 0x05E
/*
5 CHIP_ERROR Set high if any error bit is high 0x0 R
4 ERR_LOC_GEN2 An error specific to GEN_ERR_REG_2 is active 0x0 R
3 ERR_LOC_GEN1 An error specific to GEN_ERR_REG_1 is active 0x0 R
2 ERR_LOC_CH7 An error specific to CH7_ERR_REG is active 0x0 R
1 ERR_LOC_CH6 An error specific to CH6_ERR_REG is active 0x0 R
0 ERR_LOC_CH5 An error specific to CH5_ERR_REG is active 0x0 R
*/
//STATUS_REG_3 0x05F
/*
5 CHIP_ERROR Set high if any error bit is high. 0x0 R
4 INIT_COMPLETE Fuse initialization is complete. Device is ready to receive commands. 0x0 R
3 ERR_LOC_SAT_CH6_7 An error specific to CH6_7_SAT_ERR register is active. 0x0 R
2 ERR_LOC_SAT_CH4_5 An error specific to CH4_5_SAT_ERR register is active. 0x0 R
1 ERR_LOC_SAT_CH2_3 An error specific to CH2_3_SAT_ERR register is active. 0x0 R
0 ERR_LOC_SAT_CH0_1 An error specific to CH0_1_SAT_ERR register is active. 0x0 R
*/

//byte command60 = B00000000;//SRC_N_MSB 0x060
byte command60 = B00001111;//SRC_N_MSB 0x060
/*
[3:0] SRC_N_ALL[11:8] SRC N Combined 0x0 R/W
*/
//byte command61 = B00000000;//SRC_N_LSB 0x061
byte command61 = B11111111;//SRC_N_LSB 0x061
/*
[7:0] SRC_N_ALL[0:7] SRC N Combined 0x0 R/W
*/
byte command62 = B11111111;//SRC_IF_MSB 0x062
//byte command62 = B00000000;//SRC_IF_MSB 0x062
/*
[7:0] SRC_N_ALL[15:8] SRC IF All 0x0 R/W
*/
byte command63 = B11111111;//SRC_IF_LSB 0x063
//byte command63 = B00000000;//SRC_IF_LSB 0x063
/*
[7:0] SRC_N_ALL[7:0] SRC IF All 0x0 R/W
*/

byte command64 = B00000000;//SRC_UPDATE 0x064
byte command64_update = B00000001;//SRC_UPDATE 0x064
/*
7 SRC_LOAD_SOURCE Selects which option to load an SRC update 0x0 R/W
0 SRC_LOAD_UPDATE Asserts bit to load SRC registers into SRC 0x0 R/W
*/


byte  CH0_ERR_REG;
byte  CH1_ERR_REG;
byte  CH2_ERR_REG;
byte  CH3_ERR_REG;
byte  CH4_ERR_REG;
byte  CH5_ERR_REG;
byte  CH6_ERR_REG;
byte  CH7_ERR_REG;
byte  CH0_1_SAT_ERR;
byte  CH2_3_SAT_ERR;
byte  CH4_5_SAT_ERR;
byte  CH6_7_SAT_ERR;
byte  GEN_ERR_REG_1;
byte  GEN_ERR_REG_2;
byte  STATUS_REG_1;
byte  STATUS_REG_2;
byte  STATUS_REG_3;

int GENERAL_USER_CONFIG_1;
int GENERAL_USER_CONFIG_2;
int GENERAL_USER_CONFIG_3;
int DOUT_FORMAT;
int ADC_MUX_CONFIG;

int BUFFER_CONFIG_1;
int BUFFER_CONFIG_2;

int CHX_ERR_REG_EN;
int GEN_ERR_REG_1_EN;
int GEN_ERR_REG_2_EN;
int SRC_N_MSB;
int SRC_N_LSB;
int SRC_IF_MSB;
int SRC_IF_LSB;
int SRC_UPDATE;

//const long int speedMaximum = 14000000;
const long int speedMaximum = 30000000;
//const long int dataOrder = LSBFIRST;
const long int dataOrder = MSBFIRST;
const long int dataMode = SPI_MODE0;
//const long int dataMode = SPI_MODE2;


const int OUTPUT_TO_PROCESSING                 = 0x001;
const int OUTPUT_TO_CONSOLE_CHANNEL_DATA       = 0x002;
const int OUTPUT_TO_CONSOLE_CHANNEL_STATISTICS = 0x003;

const int OUTPUT_TYPE = 0x003;


uint32_t ui32Buffer;
uint16_t ui16Buffer;
uint8_t aui8Buffer[2];
uint8_t aui8inRegisterBuffer[4];
uint8_t aui8outRegisterBuffer[4];
uint8_t sizeRegisterBuffer = 4;

void set_register(int bregister, byte bcommand)
{
    delayMicroseconds(500);
  digitalWrite(ADCCS, LOW);
  SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));
  ui16Buffer = ((bregister & 0xff) * (1 << 8)) + (bcommand & 0xff);
  SPI.transfer16(ui16Buffer);

//  ui32Buffer = ((bregister & 0xff) * (1 << 8)) + (bcommand & 0xff);
//  SPI.transfer(&ui32Buffer,2);

/*  aui8outRegisterBuffer[1] = (bregister & 0xff);
  aui8outRegisterBuffer[0] = (bcommand & 0xff);
  SPI.transferBytes(aui8outRegisterBuffer,aui8inRegisterBuffer,sizeRegisterBuffer);*/
  
//  SPI.transfer(bregister);
//  SPI.transfer(bcommand);
  SPI.endTransaction();
  digitalWrite(ADCCS, HIGH);
    delayMicroseconds(500);
}

byte get_register(int bregister)
{
  byte bdata;
    delayMicroseconds(500);
  digitalWrite(ADCCS, LOW);
  SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));
  ui16Buffer = (((0x80) + (bregister & 0xff)) * (1 << 8));
  ui16Buffer = SPI.transfer16(ui16Buffer);
  bdata=(ui16Buffer & 0xff);

//  ui32Buffer = (((0x80) + (bregister & 0xff)) * (1 << 8));
//  ui32Buffer = SPI.transfer(&ui32Buffer,2);
//  bdata=(ui32Buffer & 0xff);

/*  aui8outRegisterBuffer[1] = (0x80) + (bregister & 0xff);
  aui8outRegisterBuffer[0] = 0;
  SPI.transferBytes(aui8outRegisterBuffer,aui8inRegisterBuffer,sizeRegisterBuffer);
  bdata=aui8inRegisterBuffer[1];*/
  
////  SPI.transfer(bregister);
//  bdata=SPI.transfer(0);
//  bdata=SPI.transfer(0);
  SPI.endTransaction();
  digitalWrite(ADCCS, HIGH);
    delayMicroseconds(500);
  return bdata;
}

/*void set_register16(int bregister, int bcommand)
{
    delayMicroseconds(500);
  SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));
  digitalWrite(ADCCS, LOW);
  SPI.transfer(bregister);
  SPI.transfer(bcommand);
  digitalWrite(ADCCS, HIGH);
  SPI.endTransaction();
    delayMicroseconds(500);
}

int get_register16(int bregister)
{
  int bdata;
    delayMicroseconds(500);
  SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));
  digitalWrite(ADCCS, LOW);
  SPI.transfer(bregister);
  SPI.transfer(0);
  bdata=SPI.transfer(0);
  digitalWrite(ADCCS, HIGH);
  SPI.endTransaction();
    delayMicroseconds(500);
}*/


void setup()
{

//  Serial.begin(9600);
  Serial.begin(115200);
//  Serial.begin(250000);
//  Serial.begin(921600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
//    Serial.println("Init...");


//  lcd.setCursor(0, 0);
//  lcd.print("SOLDER STATION");
//  lcd.setCursor(0, 1);
//  lcd.print("ver. 0.5");

  pinMode(ALERT_PIN, INPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(DRDY_PIN, INPUT);
  pinMode(START_PIN, OUTPUT);

  pinMode(ADCCS, OUTPUT);
//  pinMode(SDCS, OUTPUT);
  digitalWrite(ADCCS, HIGH);
//  digitalWrite(SDCS, HIGH);
  SPI.begin();

//  SPI.setClockDivider(SPI_CLOCK_DIV2);
//  SPI.setClockDivider(SPI_CLOCK_DIV4);
//  SPI.setClockDivider(SPI_CLOCK_DIV8);
//  SPI.setClockDivider(SPI_CLOCK_DIV16);
//  SPI.setClockDivider(SPI_CLOCK_DIV32);
//  SPI.setClockDivider(SPI_CLOCK_DIV64);
//  SPI.setClockDivider(SPI_CLOCK_DIV128);



/*  Wire.begin(SDA_PIN,CLK_PIN);
  lcd.begin(16, 2);
  lcd.createChar(1, char_cel);*/

  SPI.setBitOrder(dataOrder);

/*  digitalWrite(START_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(START_PIN, HIGH);
    delayMicroseconds(500);
  digitalWrite(START_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(START_PIN, HIGH);
    delayMicroseconds(500);

  digitalWrite(RESET_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, HIGH);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, HIGH);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, LOW);
    delayMicroseconds(500);*/
  digitalWrite(RESET_PIN, HIGH);
    delayMicroseconds(500);

  set_register(GENERAL_USER_CONFIG_1_REG,command11);
  GENERAL_USER_CONFIG_1=get_register(GENERAL_USER_CONFIG_1_REG);
  set_register(GENERAL_USER_CONFIG_2_REG,command12);
  GENERAL_USER_CONFIG_2=get_register(GENERAL_USER_CONFIG_2_REG);
  set_register(GENERAL_USER_CONFIG_3_REG,command13);
  GENERAL_USER_CONFIG_3=get_register(GENERAL_USER_CONFIG_3_REG);
  set_register(DOUT_FORMAT_REG,command14);
  DOUT_FORMAT=get_register(DOUT_FORMAT_REG);
  set_register(ADC_MUX_CONFIG_REG,command15);
  ADC_MUX_CONFIG=get_register(ADC_MUX_CONFIG_REG);
  
  set_register(BUFFER_CONFIG_1_REG,command19);
  BUFFER_CONFIG_1=get_register(BUFFER_CONFIG_1_REG);
  set_register(BUFFER_CONFIG_2_REG,command1A);
  BUFFER_CONFIG_2=get_register(BUFFER_CONFIG_2_REG);
  
  set_register(CHX_ERR_REG_EN_REG,command58);
  CHX_ERR_REG_EN=get_register(CHX_ERR_REG_EN_REG);
  set_register(GEN_ERR_REG_1_EN_REG,command5A);
  GEN_ERR_REG_1_EN=get_register(GEN_ERR_REG_1_EN_REG);
  set_register(GEN_ERR_REG_2_EN_REG,command5C);
  GEN_ERR_REG_2_EN=get_register(GEN_ERR_REG_2_EN_REG);
  set_register(SRC_N_MSB_REG,command60);
  SRC_N_MSB=get_register(SRC_N_MSB_REG);
  set_register(SRC_N_LSB_REG,command61);
  SRC_N_LSB=get_register(SRC_N_LSB_REG);
  set_register(SRC_IF_MSB_REG,command62);
  SRC_IF_MSB=get_register(SRC_IF_MSB_REG);
  set_register(SRC_IF_LSB_REG,command63);
  SRC_IF_LSB=get_register(SRC_IF_LSB_REG);
  set_register(SRC_UPDATE_REG,command64);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);
  set_register(SRC_UPDATE_REG,command64_update);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);
  set_register(SRC_UPDATE_REG,command64);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);

    Serial.println("");    
    Serial.println("GENERAL_USER_CONFIG_1; GENERAL_USER_CONFIG_2; GENERAL_USER_CONFIG_3; DOUT_FORMAT; ADC_MUX_CONFIG;");    
    print_binary(GENERAL_USER_CONFIG_1,8);    Serial.print(";");
    print_binary(GENERAL_USER_CONFIG_2,8);    Serial.print(";");
    print_binary(GENERAL_USER_CONFIG_3,8);    Serial.print(";");
    print_binary(DOUT_FORMAT,8);              Serial.print(";");
    print_binary(ADC_MUX_CONFIG,8);           Serial.print(";");
    Serial.println("");    
    print_binary(command11,8);    Serial.print(";");
    print_binary(command12,8);    Serial.print(";");
    print_binary(command13,8);    Serial.print(";");
    print_binary(command14,8);    Serial.print(";");
    print_binary(command15,8);    Serial.print(";");
    Serial.println("");   
    Serial.println("CHX_ERR_REG_EN; GEN_ERR_REG_1_EN; GEN_ERR_REG_2_EN;");    
    print_binary(CHX_ERR_REG_EN,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_1_EN,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_2_EN,8);    Serial.print(";");
    Serial.println("");    
    print_binary(command58,8);    Serial.print(";");
    print_binary(command5A,8);    Serial.print(";");
    print_binary(command5C,8);    Serial.print(";");
    Serial.println("");   
    Serial.println("SRC_N_MSB; SRC_N_LSB; SRC_IF_MSB; SRC_IF_LSB; SRC_UPDATE;");   
    print_binary(SRC_N_MSB,8);    Serial.print(";");
    print_binary(SRC_N_LSB,8);    Serial.print(";");
    print_binary(SRC_IF_MSB,8);    Serial.print(";");
    print_binary(SRC_IF_LSB,8);    Serial.print(";");
    print_binary(SRC_UPDATE,8);    Serial.print(";");
    Serial.println("");    
    print_binary(command60,8);    Serial.print(";");
    print_binary(command61,8);    Serial.print(";");
    print_binary(command62,8);    Serial.print(";");
    print_binary(command63,8);    Serial.print(";");
    print_binary(command64,8);    Serial.print(";");
    Serial.println("");   
    

    delayMicroseconds(500);

  digitalWrite(RESET_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, HIGH);
    delayMicroseconds(500);


  CH0_ERR_REG=get_register(CH0_ERR_REG_REG);
  CH1_ERR_REG=get_register(CH1_ERR_REG_REG);
  CH2_ERR_REG=get_register(CH2_ERR_REG_REG);
  CH3_ERR_REG=get_register(CH3_ERR_REG_REG);
  CH4_ERR_REG=get_register(CH4_ERR_REG_REG);
  CH5_ERR_REG=get_register(CH5_ERR_REG_REG);
  CH6_ERR_REG=get_register(CH6_ERR_REG_REG);
  CH7_ERR_REG=get_register(CH7_ERR_REG_REG);
  CH0_1_SAT_ERR=get_register(CH0_1_SAT_ERR_REG);
  CH2_3_SAT_ERR=get_register(CH2_3_SAT_ERR_REG);
  CH4_5_SAT_ERR=get_register(CH4_5_SAT_ERR_REG);
  CH6_7_SAT_ERR=get_register(CH6_7_SAT_ERR_REG);
  GEN_ERR_REG_1=get_register(GEN_ERR_REG_1_REG);
  GEN_ERR_REG_2=get_register(GEN_ERR_REG_2_REG);
  STATUS_REG_1=get_register(STATUS_REG_1_REG);
  STATUS_REG_2=get_register(STATUS_REG_2_REG);
  STATUS_REG_3=get_register(STATUS_REG_3_REG);

    Serial.println("");    
    Serial.println("CH0-7_ERR_REG;");    

    print_binary(CH0_ERR_REG,8);    Serial.print(";");
    print_binary(CH1_ERR_REG,8);    Serial.print(";");
    print_binary(CH2_ERR_REG,8);    Serial.print(";");
    print_binary(CH3_ERR_REG,8);    Serial.print(";");
    print_binary(CH4_ERR_REG,8);    Serial.print(";");
    print_binary(CH5_ERR_REG,8);    Serial.print(";");
    print_binary(CH6_ERR_REG,8);    Serial.print(";");
    print_binary(CH7_ERR_REG,8);    Serial.print(";");
    Serial.println("");    
    Serial.println("CH0_1-6_7_SAT_ERR; GEN_ERR_REG_1-2;STATUS_REG_1-3;");    
    print_binary(CH0_1_SAT_ERR,8);    Serial.print(";");
    print_binary(CH2_3_SAT_ERR,8);    Serial.print(";");
    print_binary(CH4_5_SAT_ERR,8);    Serial.print(";");
    print_binary(CH6_7_SAT_ERR,8);    Serial.print(";");
    Serial.print(" ");    
    print_binary(GEN_ERR_REG_1,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_2,8);    Serial.print(";");
    print_binary(STATUS_REG_1,8);    Serial.print(";");
    print_binary(STATUS_REG_2,8);    Serial.print(";");
    print_binary(STATUS_REG_3,8);    Serial.print(";");
    Serial.println("");    

/*    lcd.setCursor(0, 0);
    lcd.print(GEN_ERR_REG_1);
    lcd.setCursor(8, 0);
    lcd.print(GEN_ERR_REG_2);
    lcd.setCursor(0, 1);
    lcd.print(STATUS_REG_1);
    lcd.setCursor(5, 1);
    lcd.print(STATUS_REG_2);
    lcd.setCursor(10, 1);
    lcd.print(STATUS_REG_3);*/

  set_register(GENERAL_USER_CONFIG_3_REG,command13_spi);
    

/*  Serial.print("Initializing SD card...");
  if (!SD.begin(SDCS)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");*/

//    Serial.println("Init done.");
  
}

float volt0;
float volt1;
float volt2;
float volt3;
float volt4;
float volt5;
float volt6;
float volt7;
float v_ref=2.48;          // Reference Voltage, 5.0 Volt for LT1021 or 3.0 for LP2950-3
long int ltw0 = 0;         // ADC Data ling int
long int ltw1 = 0;
long int ltw2 = 0;
long int ltw3 = 0;  
long int ltw4 = 0;  
long int ltw5 = 0;  
long int ltw6 = 0;  
long int ltw7 = 0;  
long int cnt;                  // counter
byte b0;                  //
char st1[20];             // float voltage text
byte hdr0;                  
byte hdr1;                  
byte hdr2;                  
byte hdr3;                  
byte hdr4;                  
byte hdr5;                  
byte hdr6;                  
byte hdr7;                  

byte b00;
byte b01;
byte b02;
byte b03;
byte b04;
byte b05;
byte b06;
byte b07;
byte b08;
byte b09;
byte b10;
byte b11;
byte b12;
byte b13;
byte b14;
byte b15;
byte b16;
byte b17;
byte b18;
byte b19;
byte b20;
byte b21;
byte b22;
byte b23;
byte b24;
byte b25;
byte b26;
byte b27;
byte b28;
byte b29;
byte b30;
byte b31;

byte b32;
byte b33;
byte b34;
byte b35;
byte b36;
byte b37;
byte b38;
byte b39;
byte b40;
byte b41;
byte b42;
byte b43;
byte b44;
byte b45;
byte b46;
byte b47;
int skipped=0;

long int c0 = 0;         
long int c1 = 0;
long int c2 = 0;
long int c3 = 0;  
long int c4 = 0;  
long int c5 = 0;  
long int c6 = 0;  
long int c7 = 0;  

uint8_t aui8inDataBuffer[4*8];
uint8_t aui8outDataBuffer[4*8];
uint8_t sizeDataBuffer = 4*8;

void loop()
{

/*    lcd.setCursor(0, 0);
    lcd.print(GEN_ERR_REG_1);
    lcd.setCursor(8, 0);
    lcd.print(GEN_ERR_REG_2);
    lcd.setCursor(0, 1);
    lcd.print(STATUS_REG_1);
    lcd.setCursor(5, 1);
    lcd.print(STATUS_REG_2);
    lcd.setCursor(10, 1);
    lcd.print(STATUS_REG_3);*/

/*    delay(1000/fs);

if(0)*/
{
  
/*
  lcd.print("0:");
  lcd.setCursor(9, 0);
  lcd.print("1:");
  lcd.setCursor(0, 1);
  lcd.print("2:");
  lcd.setCursor(9, 1);
  lcd.print("3:");
    */

/*  digitalWrite(ADCCS, LOW);
    delayMicroseconds(100);
    digitalWrite(ADCCS, HIGH);      
    delayMicroseconds(400000);
  digitalWrite(ADCCS, LOW);
    delayMicroseconds(100);
    digitalWrite(ADCCS, HIGH);      
    delayMicroseconds(400000);*/
  digitalWrite(ADCCS, LOW);
int drdy_pin=digitalRead(DRDY_PIN);
int miso=digitalRead(MISO);
  if (drdy_pin == LOW) {   // ADC Converter ready ?
  if (miso == LOW) {   // ADC Converter ready ?
    ltw0=0;
    ltw1=0;
    ltw2=0;
    ltw3=0;
    ltw4=0;
    ltw5=0;
    ltw6=0;
    ltw7=0;
    SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));

  SPI.transferBytes(aui8outDataBuffer,aui8inDataBuffer,sizeDataBuffer);
  b00=aui8inDataBuffer[0];
  b01=aui8inDataBuffer[1];
  b02=aui8inDataBuffer[2];
  b03=aui8inDataBuffer[3];
  b04=aui8inDataBuffer[4];
  b05=aui8inDataBuffer[5];
  b06=aui8inDataBuffer[6];
  b07=aui8inDataBuffer[7];
  b08=aui8inDataBuffer[8];
  b09=aui8inDataBuffer[9];
  b10=aui8inDataBuffer[10];
  b11=aui8inDataBuffer[11];
  b12=aui8inDataBuffer[12];
  b13=aui8inDataBuffer[13];
  b14=aui8inDataBuffer[14];
  b15=aui8inDataBuffer[15];
  b16=aui8inDataBuffer[16];
  b17=aui8inDataBuffer[17];
  b18=aui8inDataBuffer[18];
  b19=aui8inDataBuffer[19];
  b20=aui8inDataBuffer[20];
  b21=aui8inDataBuffer[21];
  b22=aui8inDataBuffer[22];
  b23=aui8inDataBuffer[23];
  b24=aui8inDataBuffer[24];
  b25=aui8inDataBuffer[25];
  b26=aui8inDataBuffer[26];
  b27=aui8inDataBuffer[27];
  b28=aui8inDataBuffer[28];
  b29=aui8inDataBuffer[29];
  b30=aui8inDataBuffer[30];
  b31=aui8inDataBuffer[31];

/*//    SPI.transfer(B11110000);
    b0=SPI.transfer(0);
    b00=b0;
    hdr0 = b0;
    b0=SPI.transfer(0);
    b01=b0;
    ltw0 |= b0;
    ltw0 <<= 8;
    b0=SPI.transfer(0);
    b02=b0;
    ltw0 |= b0;
    ltw0 <<= 8;
    b0=SPI.transfer(0);
    b03=b0;
    ltw0 |= b0;   

    b0=SPI.transfer(0);
    b04=b0;
    hdr1 = b0;
    b0=SPI.transfer(0);
    b05=b0;
    ltw1 |= b0;
    ltw1 <<= 8;
    b0=SPI.transfer(0);
    b06=b0;
    ltw1 |= b0;
    ltw1 <<= 8;
    b0=SPI.transfer(0);
    b07=b0;
    ltw1 |= b0;   

    b0=SPI.transfer(0);
    b08=b0;
    hdr2 = b0;
    b0=SPI.transfer(0);
    b09=b0;
    ltw2 |= b0;
    ltw2 <<= 8;
    b0=SPI.transfer(0);
    b10=b0;
    ltw2 |= b0;
    ltw2 <<= 8;
    b0=SPI.transfer(0);
    b11=b0;
    ltw2 |= b0;   

    b0=SPI.transfer(0);
    b12=b0;
    hdr3 = b0;
    b0=SPI.transfer(0);
    b13=b0;
    ltw3 |= b0;
    ltw3 <<= 8;
    b0=SPI.transfer(0);
    b14=b0;
    ltw3 |= b0;
    ltw3 <<= 8;
    b0=SPI.transfer(0);
    b15=b0;
    ltw3 |= b0;   

    b0=SPI.transfer(0);
    b16=b0;
    hdr4 = b0;
    b0=SPI.transfer(0);
    b17=b0;
    ltw4 |= b0;
    ltw4 <<= 8;
    b0=SPI.transfer(0);
    b18=b0;
    ltw4 |= b0;
    ltw4 <<= 8;
    b0=SPI.transfer(0);
    b19=b0;
    ltw4 |= b0;   

    b0=SPI.transfer(0);
    b20=b0;
    hdr5 = b0;
    b0=SPI.transfer(0);
    b21=b0;
    ltw5 |= b0;
    ltw5 <<= 8;
    b0=SPI.transfer(0);
    b22=b0;
    ltw5 |= b0;
    ltw5 <<= 8;
    b0=SPI.transfer(0);
    b23=b0;
    ltw5 |= b0;   

    b0=SPI.transfer(0);
    b24=b0;
    hdr6 = b0;
    b0=SPI.transfer(0);
    b25=b0;
    ltw6 |= b0;
    ltw6 <<= 8;
    b0=SPI.transfer(0);
    b26=b0;
    ltw6 |= b0;
    ltw6 <<= 8;
    b0=SPI.transfer(0);
    b27=b0;
    ltw6 |= b0;   

    b0=SPI.transfer(0);
    b28=b0;
    hdr7 = b0;
    b0=SPI.transfer(0);
    b29=b0;
    ltw7 |= b0;
    ltw7 <<= 8;
    b0=SPI.transfer(0);
    b30=b0;
    ltw7 |= b0;
    ltw7 <<= 8;
    b0=SPI.transfer(0);
    b31=b0;
    ltw7 |= b0;   */

/*    b0=SPI.transfer(0);    b32=b0;
    b0=SPI.transfer(0);    b33=b0;
    b0=SPI.transfer(0);    b34=b0;
    b0=SPI.transfer(0);    b35=b0;
    b0=SPI.transfer(0);    b36=b0;
    b0=SPI.transfer(0);    b37=b0;
    b0=SPI.transfer(0);    b38=b0;
    b0=SPI.transfer(0);    b39=b0;
    b0=SPI.transfer(0);    b40=b0;
    b0=SPI.transfer(0);    b41=b0;
    b0=SPI.transfer(0);    b42=b0;
    b0=SPI.transfer(0);    b43=b0;
    b0=SPI.transfer(0);    b44=b0;
    b0=SPI.transfer(0);    b45=b0;
    b0=SPI.transfer(0);    b46=b0;
    b0=SPI.transfer(0);    b47=b0;*/
    
    SPI.endTransaction();
    delayMicroseconds(1);

    digitalWrite(ADCCS, HIGH);      
    delayMicroseconds(1);


//if((b00|B00000000)&&(b04|B00010000)&&(b08|B00100000)&&(b12|B00110000)&&
//   (b16|B01000000)&&(b20|B01010000)&&(b24|B01100000)&&(b28|B01110000)){


if(
  (((b00>=B10000000)&&(b00<B10010000))||((b00>=B00000000)&&(b00<B00010000)))
  )
  {
    c0++;
if(
  (((b04>=B10010000)&&(b04<B10100000))||((b04>=B00010000)&&(b04<B00100000)))
  )
  {
    c1++;
if(
  (((b08>=B10100000)&&(b08<B10110000))||((b08>=B00100000)&&(b08<B00110000)))
  )
  {
    c2++;
if(
  (((b12>=B10110000)&&(b12<B11000000))||((b12>=B00110000)&&(b12<B01000000)))
  )
  {
    c3++;
if(
  (((b16>=B11000000)&&(b16<B11010000))||((b16>=B01000000)&&(b16<B01010000)))
  )
  {
    c4++;
if(
  (((b20>=B11010000)&&(b20<B11100000))||((b20>=B01010000)&&(b20<B01100000)))
  )
  {
    c5++;
if(
  (((b24>=B11100000)&&(b24<B11110000))||((b24>=B01100000)&&(b24<B01110000)))
  )
  {
    c6++;
if(
  (((b28>=B11110000)&&(b28<=B11111111))||((b28>=B01110000)&&(b28<=B01111111)))
  )
  {
    c7++;
  }
  }
  }
  }
  }
  }
  }
  }
  
    Serial.print(100*(float)c0/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c1/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c2/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c3/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c4/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c5/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c6/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.print(100*(float)c7/(c0+c1+c2+c3+c4+c5+c6+c7),6);    Serial.print("; ");
    Serial.println("");
  
/*    Serial.print(c0);    Serial.print("; ");
    Serial.print(c1);    Serial.print("; ");
    Serial.print(c2);    Serial.print("; ");
    Serial.print(c3);    Serial.print("; ");
    Serial.print(c4);    Serial.print("; ");
    Serial.print(c5);    Serial.print("; ");
    Serial.print(c6);    Serial.print("; ");
    Serial.print(c7);    Serial.print("; ");
    Serial.println("");*/
    
    
//if(false)

/*if(
//    (((b00==B10000000))||((b00==B00000000)))
//  &&(((b04==B10100000))||((b04==B00100000)))
    (((b00>=B10000000)&&(b00<B10010000))||((b00>=B00000000)&&(b00<B00010000)))
  &&(((b04>=B10010000)&&(b04<B10100000))||((b04>=B00010000)&&(b04<B00100000)))
  &&(((b08>=B10100000)&&(b08<B10110000))||((b08>=B00100000)&&(b08<B00110000)))
  &&(((b12>=B10110000)&&(b12<B11000000))||((b12>=B00110000)&&(b12<B01000000)))
  &&(((b16>=B11000000)&&(b16<B11010000))||((b16>=B01000000)&&(b16<B01010000)))
  &&(((b20>=B11010000)&&(b20<B11100000))||((b20>=B01010000)&&(b20<B01100000)))
  &&(((b24>=B11100000)&&(b24<B11110000))||((b24>=B01100000)&&(b24<B01110000)))
  &&(((b28>=B11110000)&&(b28<B11111111))||((b28>=B01110000)&&(b28<B01111111)))
  )*/
  
//if((b28>=B11110000))
{

/*  Serial.write( 0xff ); 
  Serial.write( 0xfe ); 
  Serial.write( 0xfd ); 
  Serial.write( b00 & 0xff );                                            
  Serial.write( b01 & 0xff );                                            
  Serial.write( b02 & 0xff );                                            
  Serial.write( b03 & 0xff );*/

/*  Serial.write( 0xff ); 
  Serial.write( 0xfe ); 
  Serial.write( 0xfd ); 
  Serial.write( b08 & 0xff );                                            
  Serial.write( b09 & 0xff );                                            
  Serial.write( b10 & 0xff );                                            
  Serial.write( b11 & 0xff );*/
  
/*  Serial.write( b05 & 0xff );                                            
  Serial.write( b06 & 0xff );                                            
  Serial.write( b07 & 0xff );*/
/*  Serial.write( b09 & 0xff );                                            
  Serial.write( b10 & 0xff );                                            
  Serial.write( b11 & 0xff );*/
/*  Serial.write( b29 & 0xff );                                            
  Serial.write( b30 & 0xff );                                            
  Serial.write( b31 & 0xff );*/
  
/*    print_binary(b00,8);    Serial.print(";");
    print_hex(b01,8);    Serial.print(";");
    print_hex(b02,8);    Serial.print(";");
    print_hex(b03,8);    Serial.print(";");
    print_binary(b04,8);    Serial.print(";");
    print_hex(b05,8);    Serial.print(";");
    print_hex(b06,8);    Serial.print(";");
    print_hex(b07,8);    Serial.print(";");
    print_binary(b08,8);    Serial.print(";");
    print_hex(b09,8);    Serial.print(";");
    print_hex(b10,8);    Serial.print(";");
    print_hex(b11,8);    Serial.print(";");
    print_binary(b12,8);    Serial.print(";");
    print_hex(b13,8);    Serial.print(";");
    print_hex(b14,8);    Serial.print(";");
    print_hex(b15,8);    Serial.print(";");
    print_binary(b16,8);    Serial.print(";");
    print_hex(b17,8);    Serial.print(";");
    print_hex(b18,8);    Serial.print(";");
    print_hex(b19,8);    Serial.print(";");
    print_binary(b20,8);    Serial.print(";");
    print_hex(b21,8);    Serial.print(";");
    print_hex(b22,8);    Serial.print(";");
    print_hex(b23,8);    Serial.print(";");
    print_binary(b24,8);    Serial.print(";");
    print_hex(b25,8);    Serial.print(";");
    print_hex(b26,8);    Serial.print(";");
    print_hex(b27,8);    Serial.print(";");
    print_binary(b28,8);    Serial.print(";");
    print_hex(b29,8);    Serial.print(";");
    print_hex(b30,8);    Serial.print(";");
    print_hex(b31,8);    Serial.print(";");
    print_hex(skipped,16);    Serial.print(";");
    skipped=0;
    Serial.println("");*/
    
//    Serial.print(";  ");
/*    print_hex(b32,8);    Serial.print(";");
    print_hex(b33,8);    Serial.print(";");
    print_hex(b34,8);    Serial.print(";");
    print_hex(b35,8);    Serial.print(";");
    print_hex(b36,8);    Serial.print(";");
    print_hex(b37,8);    Serial.print(";");
    print_hex(b38,8);    Serial.print(";");
    print_hex(b39,8);    Serial.print(";");
    print_hex(b40,8);    Serial.print(";");
    print_hex(b41,8);    Serial.print(";");
    print_hex(b42,8);    Serial.print(";");
    print_hex(b43,8);    Serial.print(";");
    print_hex(b44,8);    Serial.print(";");
    print_hex(b45,8);    Serial.print(";");
    print_hex(b46,8);    Serial.print(";");
    print_hex(b47,8);    Serial.print(";");*/
/*if((b00==B10000000)&&(b04==B10010000)&&(b08==B10100000)&&(b12==B10110000)&&
   (b16==B11000000)&&(b20==B11010000)&&(b24==B11100000)&&(b28==B11110000)){
    Serial.print("!!!!!!!!!!!!!!!;");
}*/
//    Serial.println(";  ");
//} else {
//  skipped++;
}
/*    volt0 = ltw0 * v_ref*0.88*2/ 16777216; 
    volt1 = ltw1 * v_ref*0.88*2 / 16777216; 
    volt2 = ltw2 * v_ref*0.88*2 / 16777216; 
    volt3 = ltw3 * v_ref*0.88*2/ 16777216; 
    volt4 = ltw4 * v_ref*0.88*2/ 16777216; 
    volt5 = ltw5 * v_ref*0.88*2/ 16777216; 
    volt6 = ltw6 * v_ref*0.88*2/ 16777216; 
    volt7 = ltw7 * v_ref*0.88*2/ 16777216; 
    pressureValue0=(volt0-0.205)/0.01845;
    pressureValue1=(volt1-0.205)/0.01845;
    pressureValue2=(volt2-0.205)/0.01845;
    pressureValue3=(volt3-0.205)/0.01845;*/
//    Serial.println("ADC Converter ready");


  }
  }


  digitalWrite(ADCCS, HIGH);    
//  digitalWrite(SDCS, LOW);

/*  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(pressureValue0);
    lcd.setCursor(2, 0);
    lcd.print(pressureValue0);
    lcd.setCursor(11, 0);
    lcd.print(pressureValue1);
    lcd.setCursor(2, 1);
    lcd.print(pressureValue2);
    lcd.setCursor(11, 1);
    lcd.print(pressureValue3);
  */  
/*    lcd.setCursor(0, 0);
    lcd.print(volt0,6);
    lcd.setCursor(8, 0);
    lcd.print(volt1,6);
    lcd.setCursor(0, 1);
    lcd.print(volt2,6);
    lcd.setCursor(8, 1);
    lcd.print(volt3,6);*/


/*    lcd.setCursor(0, 0);
    lcd.print(ltw0);
  ovrflw=digitalRead(OVRFLW_PIN);
  fault=digitalRead(FAULT_PIN);
    lcd.setCursor(0, 1);
    lcd.print(ovrflw);
    lcd.setCursor(8, 1);
    lcd.print(fault);*/
  
/*    // print to the serial port too:
    Serial.print(cnt++);
    Serial.print(";  ");*/

/*
 
   512  0000 0000 0000 0010 0000 0000
  1536  0000 0000 0000 0110 0000 0000
 34304  0000 0000 1000 0110 0000 0000
 38912  0000 0000 1001 1000 0000 0000
 42496  0000 0000 1010 0110 0000 0000
 44544  0000 0000 1010 1110 0000 0000
 46592  0000 0000 1011 0110 0000 0000
 
 */
    
/*    Serial.print(ltw0);           // print voltage as floating number
    Serial.print("; ");
    Serial.print(ltw1);
    Serial.print("; ");
    Serial.print(ltw2);
    Serial.print("; ");
    Serial.print(ltw3);
    Serial.print("; ");
    Serial.print(ltw4);
    Serial.print("; ");
    Serial.print(ltw5);
    Serial.print("; ");
    Serial.print(ltw6);
    Serial.print("; ");
    Serial.print(ltw7);
    Serial.print("; ");*/
    
/*    Serial.print(volt0,6);           // print voltage as floating number
    Serial.print("; ");
    Serial.print(volt1,6);
    Serial.print("; ");
    Serial.print(volt2,6);
    Serial.print("; ");
    Serial.print(volt3,6);
    Serial.print("; ");
    Serial.print(volt4,6);
    Serial.print("; ");
    Serial.print(volt5,6);
    Serial.print("; ");
    Serial.print(volt6,6);
    Serial.print("; ");
    Serial.print(volt7,6);
    Serial.print("; ");*/

/*
  Status Header Output
7 Alert
 This bit is set high if any of the enabled diagnostic functions have detected an error, including an
 external clock not detected, a memory map bit flip, or an internal CRC error. This bit is not channel specific.
 The bit clears if the error is no longer present.
6:4 CH_ID_[2:0]
 These bits indicate which ADC channel the following conversion data came from (see Table 32).
3 RESET_DETECTED
 This bit indicates if a reset condition occurs. This bit is not channel specific.
2 MODULATOR_SATURATE
 This bit indicates that the modulator output 20 consecutive 0s or 1s. The bit resets automatically after
 the error is no longer present.
1 FILTER_SATURATE
 This bit indicates that the filter output is out of bounds. The bit resets automatically after the error is
 no longer present.
0 AIN_OV_UVERROR
 This bit indicates that there is an AINx± overvoltage/undervoltage condition on the inputs. This bit is
 set until the appropriate register is read back and the error is no longer present.

8388608; 8388608; 8388608; 8388608; 8388608; 8388608; 8388608; 8388608; 
1000 0000 0000 0000 0000 0000

136 1000 1000
153 1001 1001
160 1010 0000
153 1001 1001
160 1010 0000
168 1010 1000
153 1001 1001
160 1010 0000

   2  0000 0010   2932
   6  0000 0110   7072
  15  0000 1111    183
 134  1000 0110  39363
 
 150  1001 0110
 152  1001 1000  85431
 154  1001 1010    177
 156  1001 1100      1
 158  1001 1110    174
 
 166  1010 0110   2357
 174  1010 1110  71976
 
 182  1011 0110    452


  67  0100 0011      3
  76  0100 1100     10
  87  0101 0111      8

   512  0000 0000 0000 0010 0000 0000
  1536  0000 0000 0000 0110 0000 0000
 34304  0000 0000 1000 0110 0000 0000
 38912  0000 0000 1001 1000 0000 0000
 42496  0000 0000 1010 0110 0000 0000
 44544  0000 0000 1010 1110 0000 0000
 46592  0000 0000 1011 0110 0000 0000

 */

    
/*    Serial.print(hdr0);
    Serial.print("; ");
    Serial.print(hdr1);
    Serial.print("; ");
    Serial.print(hdr2);
    Serial.print("; ");
    Serial.print(hdr3);
    Serial.print("; ");
    Serial.print(hdr4);
    Serial.print("; ");
    Serial.print(hdr5);
    Serial.print("; ");
    Serial.print(hdr6);
    Serial.print("; ");
    Serial.print(hdr7);
    Serial.print("; ");*/
    
/*    // print to the serial port too:
    Serial.print(cnt++);
    Serial.print(";  ");
    Serial.print(ltw0,6);           // print voltage as floating number
    Serial.print("; ");
    Serial.print(ltw1,6);
    Serial.print("; ");
    Serial.print(ltw2,6);
    Serial.print("; ");
    Serial.print(ltw3,6);
    Serial.print("; ");
    Serial.print(ltw4,6);
    Serial.print("; ");
    Serial.print(ltw5,6);
    Serial.print("; ");
    Serial.print(ltw6,6);
    Serial.print("; ");
    Serial.print(ltw7,6);
    Serial.print("; ");
  //  Serial.print(ltw0);
  //  Serial.print("; ");
    //Serial.print(pressureValue);  */

/*  alert=digitalRead(ALERT_PIN);
  drdy=digitalRead(DRDY_PIN);
    Serial.print(alert);
    Serial.print("; ");
    Serial.print(drdy);
    Serial.print("; ");
    Serial.print(drdy_pin);
    Serial.print("; ");
    Serial.print(miso);
    Serial.print("; ");
    Serial.println("  "); */   

//  lcd.setCursor(0, 0);
//    lcd.print(cnt);
//  lcd.setCursor(8, 0);
//    lcd.print(volt0,6);           // print voltage as floating number
//  lcd.setCursor(0, 1);
//    lcd.print(volt1,6);
//  lcd.setCursor(8, 1);
//    lcd.print(volt2,6);
//    lcd.print(volt3,6);
 

//    dataFile.close();
//    delayMicroseconds(10);
    delayMicroseconds(1000000/fs);
//    delay(1000/fs);
//    lcd.clear();
/*  }  
  else {
    Serial.println("error opening datalog.txt");
  } */
//  digitalWrite(SDCS, HIGH);
} 
}

byte SPI_read()
{
  return SPI.transfer(0x00);
}




void print_binary(int v, int num_places)
{
    int mask=0, n;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask;  // truncate v to specified number of places

    while(num_places)
    {

        if (v & (0x0001 << num_places-1))
        {
             Serial.print("1");
        }
        else
        {
             Serial.print("0");
        }

        --num_places;
        if(((num_places%4) == 0) && (num_places != 0))
        {
            Serial.print("_");
        }
    }
}

void print_hex(int v, int num_places)
{
    int mask=0, n, num_nibbles, digit;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask; // truncate v to specified number of places

    num_nibbles = num_places / 4;
    if ((num_places % 4) != 0)
    {
        ++num_nibbles;
    }

    do
    {
        digit = ((v >> (num_nibbles-1) * 4)) & 0x0f;
        Serial.print(digit, HEX);
    } while(--num_nibbles);

}

