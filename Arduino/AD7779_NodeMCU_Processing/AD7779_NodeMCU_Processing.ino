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
//#include <Wire.h>
//#include "rgb_lcd.h"

//int text=0;
//int text=2;//data `
int text=3;//crc
int telnet = 0;
int serial = 0;
int processing = 0;

int openbci = 0;
int streamingMode = 0;

//const int fs=3;
//const int fs=3;
//const int fs=256;
//const int fs=250000;
//const int fs=2000;
const int fs=16000;
//const int fs=256;
//const int fs=50;

//const int SERIAL_SPEED = 921600;
//const int SERIAL_SPEED = 921600;
const int SERIAL_SPEED = 115200;
//  Serial.begin(9600);
//  Serial.begin(115200);
//  Serial.begin(250000);
//  Serial.begin(921600);

//const long int speedMaximum = 14000000;
//const long int speedMaximum = 2000000;
//const long int speedMaximum = 200;
const long int speedMaximum = 30000000;
//const long int dataOrder = LSBFIRST;
const long int dataOrder = MSBFIRST;
const long int dataMode = SPI_MODE0;
//const long int dataMode = SPI_MODE2;

//NodeMCU
const int RESET_PIN                 = 16;//D0
//const int ALERT_PIN                 =  5;//D1
//const int DRDY_PIN                  =  4;//D2
const int ADCCS                     = 15;
//const int START_PIN                 =  0;//D0
//const int ALERT_PIN                 =  5;//D1
const int DRDY_PIN                  =  4;//D2
//const int ADCCS                     = 15;
const int START_PIN                 =  0;//D3

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
const int GLOBAL_MUX_CONFIG_REG     = 0x016;

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



//rgb_lcd lcd;
//uint8_t char_cel[8] = {
//  B00111, B00101, B00111, B00000, B00000, B00000, B00000
//};


double pressureValue0 = 0;
double pressureValue1 = 0;
double pressureValue2 = 0;
double pressureValue3 = 0;


//LiquidCrystal lcd(12, 11, 6, 5, 3, 2);
//byte command11 = B01001000;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01010100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01111000;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01110100;//GENERAL_USER_CONFIG_1 0x011
//byte command11 = B01001000;//GENERAL_USER_CONFIG_1 0x011
byte command11 = B01100100;//GENERAL_USER_CONFIG_1 0x011
byte command11_soft_reset = B01100111;//GENERAL_USER_CONFIG_1 0x011
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
byte command12_sar = B00111001;//GENERAL_USER_CONFIG_2 0x012
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
//byte command14 = B00000000;//DOUT_FORMAT 0x014
byte command14 = B00100000;//DOUT_FORMAT 0x014
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
//byte command15 = B01100000;//ADC_MUX_CONFIG 0x015
//byte command15 = B00001100;//ADC_MUX_CONFIG 0x015
byte command15 = B00000000;//ADC_MUX_CONFIG 0x015
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

byte command16 = B00000000;//GLOBAL_MUX_CTRL 0x016
/*
[7:3] GLOBAL_MUX_CTRL Global SAR Diagnostics Mux Control. 0x0 R/W
 00000 AUXAIN+/AUXAIN−.
 00001 DV BE /AVSSx.
 00010 REF1+/REF1−.
 10011 REF2+/REF2−.
 10100 REF_OUT/AVSSx.
 10101 VCM/AVSSx.
 10110 AREG1CAP/AVSSx.
 10111 AREG2CAP/AVSSx.
 11000 DREGCAP/DGND.
 11001 AVDD1A/AVSSx.
 11010 AVDD1B/AVSSx.
 11011 AVDD2A/AVSSx.
 11100 AVDD2B/AVSSx.
 11101 IOVDD/DGND.
 11110 AVDD4/AVSSx.
 11111 DGND/AVSS1A.
 10000 DGND/AVSS1B.
 10001 DGND/AVSSx.
 10010 AVDD4/AVSSx.
 10011 REF1+/AVSSx.
 10100 REF2+/AVSSx.
 10101 AVDD4/AVSSx. Attenuated.
[2:0] RESERVED Reserved. 0x0 R/W
*/

//byte command19 = B00000000;//BUFFER_CONFIG_1 0x019
//byte command19 = B00011000;//BUFFER_CONFIG_1 0x019
byte command19 = B00111000;//BUFFER_CONFIG_1 0x019
/*
[7:5] RESERVED Reserved 0x0 R/W
4 REF_BUF_POS_EN Reference Buffer Positive Enable 0x1 R/W
3 REF_BUF_NEG_EN Reference Buffer Negative Enable 0x1 R/W
[2:0] RESERVED Reserved 0x0 R/W
*/

byte command1A = B11000000;//BUFFER_CONFIG_2 0x01A
//byte command1A = B00000000;//BUFFER_CONFIG_2 0x01A
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

//byte command58 = B00000000;//CHX_ERR_REG_EN 0x058
//byte command58 = B11111111;//CHX_ERR_REG_EN 0x058
byte command58 = B11111110;//CHX_ERR_REG_EN 0x058
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
byte command5A = B11111110;//GEN_ERR_REG_1_EN 0x05A
//byte command5A = B11111111;//GEN_ERR_REG_1_EN 0x05A
byte command5A_crc = B11111111;//GEN_ERR_REG_1_EN 0x05A

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
int GLOBAL_MUX_CONFIG;

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



const int OUTPUT_TO_PROCESSING                 = 0x000;
const int OUTPUT_TO_CONSOLE_CHANNEL_DATA       = 0x002;
const int OUTPUT_TO_CONSOLE_CHANNEL_STATISTICS = 0x003;

const int OUTPUT_TYPE = OUTPUT_TO_PROCESSING;


uint32_t ui32Buffer;
uint16_t ui16Buffer;
uint8_t aui8Buffer[2];
uint8_t aui8inRegisterBuffer[3];
uint8_t aui8outRegisterBuffer[3];
uint8_t sizeRegisterBuffer = 3;
uint8_t ui8RegisterCRC;

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

byte get_register_crc(int bregister)
{
  byte bdata;
    delayMicroseconds(500);
  digitalWrite(ADCCS, LOW);
  SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));
//  ui16Buffer = (((0x80) + (bregister & 0xff)) * (1 << 8));
//  ui16Buffer = SPI.transfer16(ui16Buffer);
//  bdata=(ui16Buffer & 0xff);

//  ui32Buffer = (((0x80) + (bregister & 0xff)) * (1 << 8));
//  ui32Buffer = SPI.transfer(&ui32Buffer,2);
//  bdata=(ui32Buffer & 0xff);

  aui8outRegisterBuffer[2] = (0x80) + (bregister & 0xff);
  aui8outRegisterBuffer[1] = 0;
  aui8outRegisterBuffer[0] = 0;
  SPI.transferBytes(aui8outRegisterBuffer,aui8inRegisterBuffer,sizeRegisterBuffer);
  bdata=aui8inRegisterBuffer[1];
  ui8RegisterCRC=aui8inRegisterBuffer[0];
////  SPI.transfer(bregister);
//  bdata=SPI.transfer(0);
//  bdata=SPI.transfer(0);
  SPI.endTransaction();
  digitalWrite(ADCCS, HIGH);
    delayMicroseconds(500);
  return bdata;
}

void set_register_crc(int bregister, byte bcommand)
{
    delayMicroseconds(500);
  digitalWrite(ADCCS, LOW);
  SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));
//  ui16Buffer = ((bregister & 0xff) * (1 << 8)) + (bcommand & 0xff);
//  SPI.transfer16(ui16Buffer);

//  ui32Buffer = ((bregister & 0xff) * (1 << 8)) + (bcommand & 0xff);
//  SPI.transfer(&ui32Buffer,2);

  aui8outRegisterBuffer[1] = (bregister & 0xff);
  aui8outRegisterBuffer[0] = (bcommand & 0xff);
  SPI.transferBytes(aui8outRegisterBuffer,aui8inRegisterBuffer,sizeRegisterBuffer);
  
//  SPI.transfer(bregister);
//  SPI.transfer(bcommand);
  SPI.endTransaction();
  digitalWrite(ADCCS, HIGH);
    delayMicroseconds(500);
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

uint8_t aui8_6b[6] = {0,1,2,3,4,5};
uint8_t aui8_7b[7] = {0,1,2,3,4,5,6};
uint8_t aui8_8b[8] = {0,1,2,3,4,5,6,7};
uint8_t aui8_8b_[8] = {1,2,3,4,5,6,7,8};

uint8_t crc8da_(uint8_t *data, uint8_t data_size)
{
//  Serial.println("");   
//  for(int16_t byte_in_data = data_size - 1; byte_in_data >= 0; byte_in_data--) 
//  {
//    print_binary(data[byte_in_data],8);    Serial.print(";");
//  }
//  Serial.println("");   
  for(int16_t bit_in_data = data_size * 8 - 1; bit_in_data >= 7; bit_in_data--) 
//  for(int16_t bit_in_data = data_size * 8 - 1; bit_in_data >= 8; bit_in_data--) 
  {
//    uint16_t bit_in_leftmost_byte_in_data = bit_in_data / 8;
//    uint16_t leftmost_byte_in_data = bit_in_data / 8;
    if(data[bit_in_data / 8] & (1 << (bit_in_data % 8)))
    {
//      if(bit_in_data == 8)
      if(bit_in_data == 7)
      {
        if(data[0]<0x83)
        {
          return data[0];
        }
      }
      data[bit_in_data / 8] = data[bit_in_data / 8] ^ (1 << (bit_in_data % 8));
      data[(bit_in_data - 6) / 8] = data[(bit_in_data - 6) / 8] ^ (1 << ((bit_in_data - 6) % 8));
      data[(bit_in_data - 7) / 8] = data[(bit_in_data - 7) / 8] ^ (1 << ((bit_in_data - 7) % 8));
//      data[(bit_in_data - 8) / 8] = data[(bit_in_data - 8) / 8] ^ (1 << ((bit_in_data - 8) % 8));
    }
//    for(int16_t byte_in_data = data_size - 1; byte_in_data >= 0; byte_in_data--) 
//    {
//      print_binary(data[byte_in_data],8);    Serial.print(";");
//    }
//    Serial.println("");   
  }
  return data[0];
}

uint8_t crc8da(uint8_t *data, uint8_t data_size)
{
//  Serial.println("");   
//  for(int16_t byte_in_data = 0; byte_in_data < data_size; byte_in_data++) 
//  {
//    print_binary(data[byte_in_data],8);    Serial.print(";");
//  }
//  Serial.println("");   
//  data[0] = data[0] ^ 0xff;
//  for(int16_t byte_in_data = 0; byte_in_data < data_size; byte_in_data++) 
//  {
//    print_binary(data[byte_in_data],8);    Serial.print(";");
//  }
//  Serial.println("");   
  for(int16_t bit_in_data = (data_size * 8 - 1); bit_in_data >= (9 - 1); bit_in_data--) 
  {
//    uint16_t bit_in_leftmost_byte_in_data = bit_in_data / 8;
//    uint16_t leftmost_byte_in_data = bit_in_data / 8;
    if(data[((data_size * 8 - 1) - bit_in_data) / 8] & (1 << (bit_in_data % 8)))
    {
      if(bit_in_data == (9 - 1))
      {
        if(data[(data_size - 1)] < 0x07)
        {
          return data[(data_size - 1)];
        }
      }
      data[(((data_size * 8 - 1) - (bit_in_data - 0))) / 8] =
       data[(((data_size * 8 - 1) - (bit_in_data - 0))) / 8] ^ (1 << ((bit_in_data - 0) % 8));
      data[(((data_size * 8 - 1) - (bit_in_data - 6))) / 8] = 
       data[(((data_size * 8 - 1) - (bit_in_data - 6))) / 8] ^ (1 << ((bit_in_data - 6) % 8));
      data[(((data_size * 8 - 1) - (bit_in_data - 7))) / 8] = 
       data[(((data_size * 8 - 1) - (bit_in_data - 7))) / 8] ^ (1 << ((bit_in_data - 7) % 8));
      data[(((data_size * 8 - 1) - (bit_in_data - 8))) / 8] = 
       data[(((data_size * 8 - 1) - (bit_in_data - 8))) / 8] ^ (1 << ((bit_in_data - 8) % 8));
    }
//    for(int16_t byte_in_data = 0; byte_in_data < data_size; byte_in_data++) 
//    {
//      print_binary(data[byte_in_data],8);    Serial.print(";");
//    }
//    Serial.println("");   
  }
  return data[(data_size - 1)];
}

uint8_t crc8da_7(const uint8_t *addr)
{
/*  aui8_7b[6]=((addr[4] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  aui8_7b[5]=addr[7];
  aui8_7b[4]=addr[6];
  aui8_7b[3]=addr[5];
  aui8_7b[2]=addr[3];
  aui8_7b[1]=addr[2];
  aui8_7b[0]=addr[1];
  return crc8da(aui8_7b,7);*/

/*  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=addr[3];
  aui8_7b[2]=addr[2];
  aui8_7b[1]=addr[1];
  aui8_7b[0]=0xff;
  return crc8da(aui8_7b,7);*/

/*  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[2]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[1]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[0]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  return crc8da(aui8_7b,7);*/

  aui8_8b_[0]=((addr[0] & 0xf0)) | ((addr[1] & 0xf0) >> 4);
  aui8_8b_[0] = aui8_8b_[0] ^ 0xff;
  aui8_8b_[1]=((addr[1] & 0x0f) << 4) | ((addr[2] & 0xf0) >> 4);
  aui8_8b_[2]=((addr[2] & 0x0f) << 4) | ((addr[3] & 0xf0) >> 4);
  aui8_8b_[3]=((addr[3] & 0x0f) << 4) | ((addr[4] & 0xf0) >> 4);
  aui8_8b_[4]=addr[5];
  aui8_8b_[5]=addr[6];
  aui8_8b_[6]=addr[7];
  aui8_8b_[7]=0x00;
  return crc8da(aui8_8b_,8);
//  return crc8ccitt(aui8_8b_,8);
  

//  aui8_8b[7]=addr[7];
/*  aui8_7b[6]=addr[6];
  aui8_7b[5]=addr[5];
  aui8_7b[4]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[3]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[2]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[1]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  aui8_7b[0]=0xff;
  return crc8da(aui8_7b,7);*/

/*  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[2]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[1]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[0]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  return crc8da(aui8_7b,7);*/
}

uint8_t crc8_01;
uint8_t crc8_23;
uint8_t crc8_45;
uint8_t crc8_67;


/*#include <ESP8266WiFi.h>

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 1
const char* ssid = "Broadcom_nf";
const char* password = "";
//const char* ssid = "MGTS_GPON_8877";
//const char* password = "6f6ea853";

//WiFiServer server(23);
WiFiServer server(1337);
WiFiClient serverClients[MAX_SRV_CLIENTS];*/



void initial_setup()
{

  GENERAL_USER_CONFIG_1=get_register(GENERAL_USER_CONFIG_1_REG);
  GENERAL_USER_CONFIG_2=get_register(GENERAL_USER_CONFIG_2_REG);
  GENERAL_USER_CONFIG_3=get_register(GENERAL_USER_CONFIG_3_REG);
  DOUT_FORMAT=get_register(DOUT_FORMAT_REG);
  ADC_MUX_CONFIG=get_register(ADC_MUX_CONFIG_REG);
  
  BUFFER_CONFIG_1=get_register(BUFFER_CONFIG_1_REG);
  BUFFER_CONFIG_2=get_register(BUFFER_CONFIG_2_REG);
  
  CHX_ERR_REG_EN=get_register(CHX_ERR_REG_EN_REG);
  GEN_ERR_REG_1_EN=get_register(GEN_ERR_REG_1_EN_REG);
  GEN_ERR_REG_1_EN=get_register(GEN_ERR_REG_1_EN_REG);
  GEN_ERR_REG_2_EN=get_register(GEN_ERR_REG_2_EN_REG);
  SRC_N_MSB=get_register(SRC_N_MSB_REG);
  SRC_N_LSB=get_register(SRC_N_LSB_REG);
  SRC_IF_MSB=get_register(SRC_IF_MSB_REG);
  SRC_IF_LSB=get_register(SRC_IF_LSB_REG);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);

if (text)
{

    Serial.println("");    
    Serial.println("GENERAL_USER_CONFIG_1; GENERAL_USER_CONFIG_2; GENERAL_USER_CONFIG_3; DOUT_FORMAT; ADC_MUX_CONFIG;");    
    print_binary(GENERAL_USER_CONFIG_1,8);    Serial.print(";");
    print_binary(GENERAL_USER_CONFIG_2,8);    Serial.print(";");
    print_binary(GENERAL_USER_CONFIG_3,8);    Serial.print(";");
    print_binary(DOUT_FORMAT,8);              Serial.print(";");
    print_binary(ADC_MUX_CONFIG,8);           Serial.print(";");
    Serial.println("");   
    Serial.println("BUFFER_CONFIG_1; BUFFER_CONFIG_2;");    
    print_binary(BUFFER_CONFIG_1,8);    Serial.print(";");
    print_binary(BUFFER_CONFIG_2,8);    Serial.print(";");
    Serial.println("");   
    Serial.println("CHX_ERR_REG_EN; GEN_ERR_REG_1_EN; GEN_ERR_REG_2_EN;");    
    print_binary(CHX_ERR_REG_EN,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_1_EN,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_2_EN,8);    Serial.print(";");
    Serial.println("");   
    Serial.println("SRC_N_MSB; SRC_N_LSB; SRC_IF_MSB; SRC_IF_LSB; SRC_UPDATE;");   
    print_binary(SRC_N_MSB,8);    Serial.print(";");
    print_binary(SRC_N_LSB,8);    Serial.print(";");
    print_binary(SRC_IF_MSB,8);    Serial.print(";");
    print_binary(SRC_IF_LSB,8);    Serial.print(";");
    print_binary(SRC_UPDATE,8);    Serial.print(";");
    Serial.println("");   

}//text

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
//  set_register(GEN_ERR_REG_1_EN_REG,command5A_crc);
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

if (text)
{

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
    Serial.println("BUFFER_CONFIG_1; BUFFER_CONFIG_2;");    
    print_binary(BUFFER_CONFIG_1,8);    Serial.print(";");
    print_binary(BUFFER_CONFIG_2,8);    Serial.print(";");
    Serial.println("");    
    print_binary(command19,8);    Serial.print(";");
    print_binary(command1A,8);    Serial.print(";");
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

}//text
}

void setup()
{

  Serial.begin(SERIAL_SPEED);
//  Serial.begin(9600);
//  Serial.begin(115200);
//  Serial.begin(250000);
//  Serial.begin(921600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
//    Serial.println("Init...");


/*  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());*/


/*if(telnet)
{

//  Serial1.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if(i == 21){
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  server.begin();
  server.setNoDelay(true);
  
  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
//  Serial.println(" 23' to connect");
  Serial.println(" 1337' to connect");

}//telnet*/

if (text)
{

/*  aui8_7b[0]=0;
  aui8_7b[1]=0;
  aui8_7b[2]=0;
  aui8_7b[3]=0;
  aui8_7b[4]=0;
  aui8_7b[5]=B00000110;
//  aui8_8b[5]=aui8_8b[5] ^ 0xff;
  aui8_7b[6]=B01001110;*/

/*  aui8_8b[0]=0;
  aui8_8b[1]=0;
  aui8_8b[2]=0;
  aui8_8b[3]=0;
  aui8_8b[4]=0;
  aui8_8b[5]=B00000110;
//  aui8_8b[5]=aui8_8b[5] ^ 0xff;
  aui8_8b[6]=B01001110;
  aui8_8b[7]=0;*/


 
/*  aui8_7b[6]=0;
  aui8_7b[5]=0;
  aui8_7b[4]=0;
  aui8_7b[3]=0;
  aui8_7b[2]=B00000110;
  aui8_7b[1]=B01001110;
  aui8_7b[0]=0xff;*/

/*  aui8_8b[0]=0xE0;
  aui8_8b[1]=0xD3;
  aui8_8b[2]=0x1C;
  aui8_8b[3]=0x9F;
  aui8_8b[4]=0xD4;
  aui8_8b[5]=0x48;
  aui8_8b[6]=0xE3;
  aui8_8b[7]=0x00;
  
    Serial.println("");   
  print_binary(aui8_8b[0],8);    Serial.print(";");
  print_binary(aui8_8b[1],8);    Serial.print(";");
  print_binary(aui8_8b[2],8);    Serial.print(";");
  print_binary(aui8_8b[3],8);    Serial.print(";");
  print_binary(aui8_8b[4],8);    Serial.print(";");
  print_binary(aui8_8b[5],8);    Serial.print(";");
  print_binary(aui8_8b[6],8);    Serial.print(";");
  print_binary(aui8_8b[7],8);    Serial.print(";");
    Serial.println("");   
  print_hex(aui8_8b[0],8);    Serial.print(";");
  print_hex(aui8_8b[1],8);    Serial.print(";");
  print_hex(aui8_8b[2],8);    Serial.print(";");
  print_hex(aui8_8b[3],8);    Serial.print(";");
  print_hex(aui8_8b[4],8);    Serial.print(";");
  print_hex(aui8_8b[5],8);    Serial.print(";");
  print_hex(aui8_8b[6],8);    Serial.print(";");
  print_hex(aui8_8b[7],8);    Serial.print(";");
    Serial.println("");   

// crc8_01=crc8da(&(aui8_7b[5]),2);
// crc8_01=crc8da(&(aui8_8b[5]),3);
 crc8_01=crc8da(&(aui8_8b[0]),8);*/

//1110_1010;EA;0D;31;C9;1111_0101;F5;D4;48;E3;0000;B3;72;E3;0D;
//E0 D3 1C 9F D4 48 E3
//A5

/*  aui8_8b[0]=0xEA;
  aui8_8b[1]=0x0D;
  aui8_8b[2]=0x31;
  aui8_8b[3]=0xC9;
  aui8_8b[4]=0xF5;
  aui8_8b[5]=0xD4;
  aui8_8b[6]=0x48;
  aui8_8b[7]=0xE3;

    Serial.println("");   
  print_binary(aui8_8b[0],8);    Serial.print(";");
  print_binary(aui8_8b[1],8);    Serial.print(";");
  print_binary(aui8_8b[2],8);    Serial.print(";");
  print_binary(aui8_8b[3],8);    Serial.print(";");
  print_binary(aui8_8b[4],8);    Serial.print(";");
  print_binary(aui8_8b[5],8);    Serial.print(";");
  print_binary(aui8_8b[6],8);    Serial.print(";");
  print_binary(aui8_8b[7],8);    Serial.print(";");
    Serial.println("");   
  print_hex(aui8_8b[0],8);    Serial.print(";");
  print_hex(aui8_8b[1],8);    Serial.print(";");
  print_hex(aui8_8b[2],8);    Serial.print(";");
  print_hex(aui8_8b[3],8);    Serial.print(";");
  print_hex(aui8_8b[4],8);    Serial.print(";");
  print_hex(aui8_8b[5],8);    Serial.print(";");
  print_hex(aui8_8b[6],8);    Serial.print(";");
  print_hex(aui8_8b[7],8);    Serial.print(";");
    Serial.println("");   

 crc8_01=crc8da_7(&(aui8_8b[0]));


  print_binary(crc8_01,8);    Serial.print(";");
    Serial.println("");   
  print_hex(crc8_01,8);    Serial.print(";");
    Serial.println("");*/   

}//text

//  lcd.setCursor(0, 0);
//  lcd.print("SOLDER STATION");
//  lcd.setCursor(0, 1);
//  lcd.print("ver. 0.5");

//  pinMode(ALERT_PIN, INPUT);
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

//  digitalWrite(START_PIN, LOW);
    delayMicroseconds(500);
/*  digitalWrite(START_PIN, HIGH);
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
    delayMicroseconds(500);*/
  digitalWrite(RESET_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, HIGH);
    delayMicroseconds(500);

  initial_setup();

    delayMicroseconds(500);

//  digitalWrite(RESET_PIN, LOW);
//    delayMicroseconds(500);
//  digitalWrite(RESET_PIN, HIGH);
//    delayMicroseconds(500);


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

if (text)
{

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

}//text

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

//  set_register(GENERAL_USER_CONFIG_3_REG,command12_sar);
//  set_register(GENERAL_USER_CONFIG_3_REG,command13_spi);

if(openbci)
{
  Serial.print("$$$");
}

//if(!openbci)
{
  set_register(GENERAL_USER_CONFIG_3_REG,command13_spi);
  set_register(GEN_ERR_REG_1_EN_REG,command5A_crc);
}

/*  Serial.print("Initializing SD card...");
  if (!SD.begin(SDCS)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");*/

//    Serial.println("Init done.");

//  generate_table();
}


void register_settings ()
{

  GENERAL_USER_CONFIG_1=get_register(GENERAL_USER_CONFIG_1_REG);
  GENERAL_USER_CONFIG_2=get_register(GENERAL_USER_CONFIG_2_REG);
  GENERAL_USER_CONFIG_3=get_register(GENERAL_USER_CONFIG_3_REG);
  DOUT_FORMAT=get_register(DOUT_FORMAT_REG);
  ADC_MUX_CONFIG=get_register(ADC_MUX_CONFIG_REG);
  
  BUFFER_CONFIG_1=get_register(BUFFER_CONFIG_1_REG);
  BUFFER_CONFIG_2=get_register(BUFFER_CONFIG_2_REG);
  
  CHX_ERR_REG_EN=get_register(CHX_ERR_REG_EN_REG);
  GEN_ERR_REG_1_EN=get_register(GEN_ERR_REG_1_EN_REG);
  GEN_ERR_REG_2_EN=get_register(GEN_ERR_REG_2_EN_REG);
  SRC_N_MSB=get_register(SRC_N_MSB_REG);
  SRC_N_LSB=get_register(SRC_N_LSB_REG);
  SRC_IF_MSB=get_register(SRC_IF_MSB_REG);
  SRC_IF_LSB=get_register(SRC_IF_LSB_REG);
  SRC_UPDATE=get_register(SRC_UPDATE_REG);

    Serial.println("");    
    Serial.println("GENERAL_USER_CONFIG_1; GENERAL_USER_CONFIG_2; GENERAL_USER_CONFIG_3; DOUT_FORMAT; ADC_MUX_CONFIG;");    
    print_binary(GENERAL_USER_CONFIG_1,8);    Serial.print(";");
    print_binary(GENERAL_USER_CONFIG_2,8);    Serial.print(";");
    print_binary(GENERAL_USER_CONFIG_3,8);    Serial.print(";");
    print_binary(DOUT_FORMAT,8);              Serial.print(";");
    print_binary(ADC_MUX_CONFIG,8);           Serial.print(";");
    Serial.println("");    
    Serial.println("BUFFER_CONFIG_1; BUFFER_CONFIG_2;");    
    print_binary(BUFFER_CONFIG_1,8);    Serial.print(";");
    print_binary(BUFFER_CONFIG_2,8);    Serial.print(";");
    Serial.println("");    
    Serial.println("CHX_ERR_REG_EN; GEN_ERR_REG_1_EN; GEN_ERR_REG_2_EN;");    
    print_binary(CHX_ERR_REG_EN,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_1_EN,8);    Serial.print(";");
    print_binary(GEN_ERR_REG_2_EN,8);    Serial.print(";");
    Serial.println("");   
    Serial.println("SRC_N_MSB; SRC_N_LSB; SRC_IF_MSB; SRC_IF_LSB; SRC_UPDATE;");   
    print_binary(SRC_N_MSB,8);    Serial.print(";");
    print_binary(SRC_N_LSB,8);    Serial.print(";");
    print_binary(SRC_IF_MSB,8);    Serial.print(";");
    print_binary(SRC_IF_LSB,8);    Serial.print(";");
    print_binary(SRC_UPDATE,8);    Serial.print(";");
    Serial.println("");   

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

  Serial.print("$$$");

}//register_settings




/*float volt0;
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
byte hdr7;*/

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

/*byte b32;
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
byte b47;*/
int skipped=0;

long int c00 = 0;         
long int c01 = 0;         
long int c0 = 0;         
long int c1 = 0;
long int c2 = 0;
long int c3 = 0;  
long int c4 = 0;  
long int c5 = 0;  
long int c6 = 0;  
long int c7 = 0;  

uint8_t aui8inDataBuffer[4*8] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1};
uint8_t aui8outDataBuffer[4*8] = {10,11,12,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1};
//uint8_t sizeDataBuffer = 4*2;
//uint8_t sizeDataBuffer = 4*4;
uint8_t sizeDataBuffer = 4*8;

uint8_t ui8SampleNumber=0;

void loop()
{

/*  set_register(GENERAL_USER_CONFIG_1_REG,command11);
  GENERAL_USER_CONFIG_1=get_register(GENERAL_USER_CONFIG_1_REG);
  Serial.println("");    
    Serial.println("GENERAL_USER_CONFIG_1;");    
    print_binary(GENERAL_USER_CONFIG_1,8);    Serial.print(";");
    Serial.println("");    
    print_binary(command11,8);    Serial.print(";");
    Serial.println("");   
  //  initial_setup();*/

 if(openbci)
 {

  if(Serial.available()){
    size_t len = 1;
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);

    if(sbuf[0]=='s') {
      streamingMode = 0;
      set_register(GENERAL_USER_CONFIG_3_REG,command13);
    }
    if(sbuf[0]=='b') {
      streamingMode = 1;
      ui8SampleNumber = 0;
      set_register(GENERAL_USER_CONFIG_3_REG,command13_spi);
    }
    if(sbuf[0]=='v') {
      set_register(GENERAL_USER_CONFIG_1_REG,command11_soft_reset);
    }
    if(sbuf[0]=='?') {
      register_settings();
    }
    if(sbuf[0]=='d') {
//      default_channel_settings();
      Serial.print("defaul settings");
      Serial.println("");
      Serial.print("$$$");
    }
    
  }
 }//openbci

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

//    delay(1000/fs);
//    delayMicroseconds(1000000/fs);
//if(0)

//if(!((openbci) && (!(streamingMode))))

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


//  set_register(ADC_MUX_CONFIG_REG,command15);



    
  digitalWrite(ADCCS, LOW);
int drdy_pin=digitalRead(DRDY_PIN);
int miso=digitalRead(MISO);
//    Serial.print(drdy_pin);    Serial.print("; ");
//    Serial.print(miso);    Serial.print("; ");
//    Serial.println("");
  if (drdy_pin == LOW) {   // ADC Converter ready ?
  if (miso == LOW) {   // ADC Converter ready ?
/*    ltw0=0;
    ltw1=0;
    ltw2=0;
    ltw3=0;
    ltw4=0;
    ltw5=0;
    ltw6=0;
    ltw7=0;*/
    SPI.beginTransaction(SPISettings(speedMaximum, dataOrder, dataMode));

//  SPI.transferBytes(aui8outDataBuffer,aui8inDataBuffer,sizeDataBuffer);

  for(int iBuffer=0;iBuffer<sizeDataBuffer;iBuffer++)
  {
    aui8inDataBuffer[iBuffer]=SPI.transfer(0x00);
//    print_hex(aui8inDataBuffer[iBuffer],8);    Serial.print(";");
  }
//    Serial.println("");
  
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

    
    SPI.endTransaction();
    delayMicroseconds(1);

    digitalWrite(ADCCS, HIGH);      
    delayMicroseconds(1);


//if((b00|B00000000)&&(b04|B00010000)&&(b08|B00100000)&&(b12|B00110000)&&
//   (b16|B01000000)&&(b20|B01010000)&&(b24|B01100000)&&(b28|B01110000)){

if (text==1)
{

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

}//text==1
  
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
//  &&(((b08>=B10100000)&&(b08<B10110000))||((b08>=B00100000)&&(b08<B00110000)))
//  &&(((b12>=B10110000)&&(b12<B11000000))||((b12>=B00110000)&&(b12<B01000000)))
//  &&(((b16>=B11000000)&&(b16<B11010000))||((b16>=B01000000)&&(b16<B01010000)))
//  &&(((b20>=B11010000)&&(b20<B11100000))||((b20>=B01010000)&&(b20<B01100000)))
//  &&(((b24>=B11100000)&&(b24<B11110000))||((b24>=B01100000)&&(b24<B01110000)))
//  &&(((b28>=B11110000)&&(b28<B11111111))||((b28>=B01110000)&&(b28<B01111111)))
  )*/
  
//if((b28>=B11110000))
{

if(!text)
{

 /*if(telnet)
 {







  uint8_t i;
  //check if there are any new clients
  if (server.hasClient()){
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      //find free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected()){
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        Serial.print("New client: "); Serial.print(i);
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
  //check clients for data
  for(i = 0; i < MAX_SRV_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()){
      if(serverClients[i].available()){
        //get data from the telnet client and push it to the UART
        while(serverClients[i].available()) Serial.write(serverClients[i].read());
      }
    }
  }



 crc8_01=crc8da_7(&(aui8inDataBuffer[0]));
// crc8_23=crc8da_7(&(aui8inDataBuffer[8]));
// crc8_45=crc8da_7(&(aui8inDataBuffer[16]));
// crc8_67=crc8da_7(&(aui8inDataBuffer[24]));

  if((!(((byte)crc8_01)-((byte)((b00<<4)|(b04&0x0f)))))
//     &&(!(((byte)crc8_23)-((byte)((b08<<4)|(b12&0x0f)))))
//     &&(!(((byte)crc8_45)-((byte)((b16<<4)|(b20&0x0f)))))
//     &&(!(((byte)crc8_67)-((byte)((b24<<4)|(b28&0x0f)))))
    )
  {   


  //check UART for data
//  if(Serial.available()){
//    size_t len = Serial.available();
//    size_t len = 4;
    size_t len = 2;
    uint8_t sbuf[len];
//    Serial.readBytes(sbuf, len);
//    sbuf[0]=(b01&(1<<8));
//    sbuf[1]=b01^(b01&(1<<8));
//    sbuf[2]=b02;
//    sbuf[3]=b03;
    sbuf[0]=b02;
    sbuf[1]=b03;
    //push UART data to all connected telnet clients
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (serverClients[i] && serverClients[i].connected()){
        serverClients[i].write(sbuf, len);
        delay(1);
//    print_hex(sbuf[0],8);    Serial.print(";");
//    print_hex(sbuf[1],8);    Serial.print(";");
//    print_hex(sbuf[2],8);    Serial.print(";");
//    print_hex(sbuf[3],8);    Serial.print(";");
//    Serial.println("");
      }
    }
//  }

  


  }
  
 } //telnet*/


 if(openbci)
 {


 if(streamingMode)
 {

 crc8_01=crc8da_7(&(aui8inDataBuffer[0]));
 crc8_23=crc8da_7(&(aui8inDataBuffer[8]));
 crc8_45=crc8da_7(&(aui8inDataBuffer[16]));
 crc8_67=crc8da_7(&(aui8inDataBuffer[24]));

  if((!(((byte)crc8_01)-((byte)((b00<<4)|(b04&0x0f)))))
     &&(!(((byte)crc8_23)-((byte)((b08<<4)|(b12&0x0f)))))
     &&(!(((byte)crc8_45)-((byte)((b16<<4)|(b20&0x0f)))))
     &&(!(((byte)crc8_67)-((byte)((b24<<4)|(b28&0x0f)))))
    )
  {   

  Serial.write( 0xA0 ); 
  Serial.write( ui8SampleNumber++ ); 
//  Serial.write( b00 & 0xff );                                            
  Serial.write( b01 & 0xff );                                            
  Serial.write( b02 & 0xff );                                            
  Serial.write( b03 & 0xff );
//  Serial.write( b04 & 0xff );                                            
  Serial.write( b05 & 0xff );                                            
  Serial.write( b06 & 0xff );                                            
  Serial.write( b07 & 0xff );
//  Serial.write( b08 & 0xff );
  Serial.write( b09 & 0xff );
  Serial.write( b10 & 0xff );
  Serial.write( b11 & 0xff );
//  Serial.write( b12 & 0xff );
  Serial.write( b13 & 0xff );
  Serial.write( b14 & 0xff );
  Serial.write( b15 & 0xff );
//  Serial.write( b16 & 0xff );
  Serial.write( b17 & 0xff );
  Serial.write( b18 & 0xff );
  Serial.write( b19 & 0xff );
//  Serial.write( b20 & 0xff );
  Serial.write( b21 & 0xff );
  Serial.write( b22 & 0xff );
  Serial.write( b23 & 0xff );
//  Serial.write( b24 & 0xff );
  Serial.write( b25 & 0xff );
  Serial.write( b26 & 0xff );
  Serial.write( b27 & 0xff );
//  Serial.write( b28 & 0xff );
  Serial.write( b29 & 0xff );
  Serial.write( b30 & 0xff );
  Serial.write( b31 & 0xff );
  Serial.write( 0);
  Serial.write( 0);
  Serial.write( 0);
  Serial.write( 0);
  Serial.write( 0);
  Serial.write( 0);
  Serial.write( 0xC0);

  }
 }//streamingMode
 }//openbci

 if(serial)
 {

 crc8_01=crc8da_7(&(aui8inDataBuffer[0]));
// crc8_23=crc8da_7(&(aui8inDataBuffer[8]));
// crc8_45=crc8da_7(&(aui8inDataBuffer[16]));
// crc8_67=crc8da_7(&(aui8inDataBuffer[24]));

  if((!(((byte)crc8_01)-((byte)((b00<<4)|(b04&0x0f)))))
//     &&(!(((byte)crc8_23)-((byte)((b08<<4)|(b12&0x0f)))))
//     &&(!(((byte)crc8_45)-((byte)((b16<<4)|(b20&0x0f)))))
//     &&(!(((byte)crc8_67)-((byte)((b24<<4)|(b28&0x0f)))))
    )
  {   

/*  Serial.write( 0xff ); 
  Serial.write( 0xfe ); 
  Serial.write( 0xfd ); 
  Serial.write( b00 & 0xff );                                            
  Serial.write( b01 & 0xff );                                            */
  Serial.write( b02 & 0xff );                                            
  Serial.write( b03 & 0xff );
/*  Serial.write( b04 & 0xff );                                            
  Serial.write( b05 & 0xff );                                            
  Serial.write( b06 & 0xff );                                            
  Serial.write( b07 & 0xff );
  Serial.write( b08 & 0xff );
  Serial.write( b09 & 0xff );
  Serial.write( b10 & 0xff );
  Serial.write( b11 & 0xff );
  Serial.write( b12 & 0xff );
  Serial.write( b13 & 0xff );
  Serial.write( b14 & 0xff );
  Serial.write( b15 & 0xff );*/

  }
 }//serial

 if(processing)
 {

/*  Serial.write( 0xff ); 
  Serial.write( 0xfe ); 
  Serial.write( 0xfd ); 
  Serial.write( b08 & 0xff );                                            
  Serial.write( b09 & 0xff );                                            
  Serial.write( b10 & 0xff );                                            
  Serial.write( b11 & 0xff );*/


 crc8_01=crc8da_7(&(aui8inDataBuffer[0]));
// crc8_23=crc8da_7(&(aui8inDataBuffer[8]));
// crc8_45=crc8da_7(&(aui8inDataBuffer[16]));
// crc8_67=crc8da_7(&(aui8inDataBuffer[24]));

  if((!(((byte)crc8_01)-((byte)((b00<<4)|(b04&0x0f)))))
//     &&(!(((byte)crc8_23)-((byte)((b08<<4)|(b12&0x0f)))))
//     &&(!(((byte)crc8_45)-((byte)((b16<<4)|(b20&0x0f)))))
//     &&(!(((byte)crc8_67)-((byte)((b24<<4)|(b28&0x0f)))))
    )
  {   

/*  Serial.write( 0xff ); 
  Serial.write( 0xfe ); 
  Serial.write( 0xfd ); 
  Serial.write( b04 & 0xff );                                            
  Serial.write( b05 & 0xff );                                            
  Serial.write( b06 & 0xff );                                            
  Serial.write( b07 & 0xff );*/

  Serial.write( 0xff ); 
  Serial.write( 0xfe ); 
  Serial.write( 0xfd ); 
  Serial.write( b00 & 0xff );                                            
  Serial.write( b01 & 0xff );                                            
  Serial.write( b02 & 0xff );                                            
  Serial.write( b03 & 0xff );
/*  Serial.write( b04 & 0xff );                                            
  Serial.write( b05 & 0xff );                                            
  Serial.write( b06 & 0xff );                                            
  Serial.write( b07 & 0xff );
  Serial.write( b08 & 0xff );
  Serial.write( b09 & 0xff );
  Serial.write( b10 & 0xff );
  Serial.write( b11 & 0xff );
  Serial.write( b12 & 0xff );
  Serial.write( b13 & 0xff );
  Serial.write( b14 & 0xff );
  Serial.write( b15 & 0xff );*/

  }
  
/*  Serial.write( b05 & 0xff );                                            
  Serial.write( b06 & 0xff );                                            
  Serial.write( b07 & 0xff );*/
/*  Serial.write( b09 & 0xff );                                            
  Serial.write( b10 & 0xff );                                            
  Serial.write( b11 & 0xff );*/
/*  Serial.write( b29 & 0xff );                                            
  Serial.write( b30 & 0xff );                                            
  Serial.write( b31 & 0xff );*/

 }//processing

}//!text



if (text==3)
{
 crc8_01=crc8da_7(&(aui8inDataBuffer[0]));
 crc8_23=crc8da_7(&(aui8inDataBuffer[8]));
 crc8_45=crc8da_7(&(aui8inDataBuffer[16]));
 crc8_67=crc8da_7(&(aui8inDataBuffer[24]));

/*    print_hex(crc8_01,8);    Serial.print(";");
    print_hex(crc8_23,8);    Serial.print(";");
    print_hex(crc8_45,8);    Serial.print(";");
    print_hex(crc8_67,8);    Serial.print(";");
    Serial.println("");

    print_hex(((b00<<4)|(b04&0x0f)),8);    Serial.print(";");
    print_hex(((b08<<4)|(b12&0x0f)),8);    Serial.print(";");
    print_hex(((b16<<4)|(b20&0x0f)),8);    Serial.print(";");
    print_hex(((b24<<4)|(b28&0x0f)),8);    Serial.print(";");
    Serial.println("");*/


  if((!(((byte)crc8_01)-((byte)((b00<<4)|(b04&0x0f)))))
     &&(!(((byte)crc8_23)-((byte)((b08<<4)|(b12&0x0f)))))
     &&(!(((byte)crc8_45)-((byte)((b16<<4)|(b20&0x0f)))))
     &&(!(((byte)crc8_67)-((byte)((b24<<4)|(b28&0x0f))))))
  {   
    c00++;
  }
  c01++;

  if(!(((byte)crc8_01)-((byte)((b00<<4)|(b04&0x0f)))))
  {
    c0++;
  }
  if(!(((byte)crc8_23)-((byte)((b08<<4)|(b12&0x0f)))))
  {
    c1++;
  }
  if(!(((byte)crc8_45)-((byte)((b16<<4)|(b20&0x0f)))))
  {
    c2++;
  }
  if(!(((byte)crc8_67)-((byte)((b24<<4)|(b28&0x0f)))))
  {
    c3++;
  }
  
    Serial.print(100*((float)(c00))/((float)(c01)),6);    Serial.print("; ");
    Serial.print(100*((float)(c0))/((float)(c01)),6);    Serial.print("; ");
    Serial.print(100*((float)(c1))/((float)(c01)),6);    Serial.print("; ");
    Serial.print(100*((float)(c2))/((float)(c01)),6);    Serial.print("; ");
    Serial.print(100*((float)(c3))/((float)(c01)),6);    Serial.print("; ");
//    Serial.print(100*((float)(c0))/((float)(c0+c1+c2+c3)),6);    Serial.print("; ");
//    Serial.print(100*((float)(c1))/((float)(c0+c1+c2+c3)),6);    Serial.print("; ");
//    Serial.print(100*((float)(c2))/((float)(c0+c1+c2+c3)),6);    Serial.print("; ");
//    Serial.print(100*((float)(c3))/((float)(c0+c1+c2+c3)),6);    Serial.print("; ");
    Serial.println("");

}//text==3

if (text==2)
{

//  aui8_6b[0] = b01 & 0xff;
//  aui8_6b[1] = b02 & 0xff;
//  aui8_6b[2] = b03 & 0xff;
//  aui8_6b[3] = b05 & 0xff;
//  aui8_6b[4] = b06 & 0xff;
//  aui8_6b[5] = b07 & 0xff;
//  return crc8ccitt(aui8_6b,6);
//  return crc8(aui8_6b,6);


//    Serial.println(aui8_6b[0]);
//    Serial.println(aui8_6b[1]);
//    aui8_6b[0]=0;

    print_binary(b00,8);    Serial.print(";");
    print_hex(b00,8);    Serial.print(";");
    print_hex(b01,8);    Serial.print(";");
    print_hex(b02,8);    Serial.print(";");
    print_hex(b03,8);    Serial.print(";");
    print_binary(b04,8);    Serial.print(";");
    print_hex(b04,8);    Serial.print(";");
    print_hex(b05,8);    Serial.print(";");
    print_hex(b06,8);    Serial.print(";");
    print_hex(b07,8);    Serial.print(";");
    print_binary(b08,8);    Serial.print(";");
    print_hex(b08,8);    Serial.print(";");
    print_hex(b09,8);    Serial.print(";");
    print_hex(b10,8);    Serial.print(";");
    print_hex(b11,8);    Serial.print(";");
    print_binary(b12,8);    Serial.print(";");
    print_hex(b12,8);    Serial.print(";");
    print_hex(b13,8);    Serial.print(";");
    print_hex(b14,8);    Serial.print(";");
    print_hex(b15,8);    Serial.print(";");
    print_binary(b16,8);    Serial.print(";");
    print_hex(b16,8);    Serial.print(";");
    print_hex(b17,8);    Serial.print(";");
    print_hex(b18,8);    Serial.print(";");
    print_hex(b19,8);    Serial.print(";");
    print_binary(b20,8);    Serial.print(";");
    print_hex(b20,8);    Serial.print(";");
    print_hex(b21,8);    Serial.print(";");
    print_hex(b22,8);    Serial.print(";");
    print_hex(b23,8);    Serial.print(";");
    print_binary(b24,8);    Serial.print(";");
    print_hex(b24,8);    Serial.print(";");
    print_hex(b25,8);    Serial.print(";");
    print_hex(b26,8);    Serial.print(";");
    print_hex(b27,8);    Serial.print(";");
    print_binary(b28,8);    Serial.print(";");
    print_hex(b28,8);    Serial.print(";");
    print_hex(b29,8);    Serial.print(";");
    print_hex(b30,8);    Serial.print(";");
    print_hex(b31,8);    Serial.print(";");
    print_hex(skipped,16);    Serial.print(";");
    skipped=0;

 crc8_01=crc8da_7(&(aui8inDataBuffer[0]));
 crc8_23=crc8da_7(&(aui8inDataBuffer[8]));
 crc8_45=crc8da_7(&(aui8inDataBuffer[16]));
 crc8_67=crc8da_7(&(aui8inDataBuffer[24]));

/* crc8_01=crc8_7(&aui8inDataBuffer[0]);
 crc8_23=crc8_7(&aui8inDataBuffer[9]);
 crc8_45=crc8_7(&aui8inDataBuffer[17]);
 crc8_67=crc8_7(&aui8inDataBuffer[25]);*/

/* crc8_01=crc8ccitt_7(&aui8inDataBuffer[0]);
 crc8_23=crc8ccitt_7(&aui8inDataBuffer[9]);
 crc8_45=crc8ccitt_7(&aui8inDataBuffer[17]);
 crc8_67=crc8ccitt_7(&aui8inDataBuffer[25]);*/

/* crc8_01=crc8ccitt(&aui8inDataBuffer[0],8);
 crc8_23=crc8ccitt(&aui8inDataBuffer[9],8);
 crc8_45=crc8ccitt(&aui8inDataBuffer[17],8);
 crc8_67=crc8ccitt(&aui8inDataBuffer[25],8);*/

/* crc8_01=crc8_7b(b01,b02,b03,b05,b06,b07);
 crc8_23=crc8_7b(b09,b10,b11,b13,b14,b15);
 crc8_45=crc8_7b(b17,b18,b19,b21,b22,b23);
 crc8_67=crc8_7b(b25,b26,b27,b29,b30,b31);*/

/*    print_binary(crc8_01,8);    Serial.print(";");
    print_binary(crc8_23,8);    Serial.print(";");
    print_binary(crc8_45,8);    Serial.print(";");
    print_binary(crc8_67,8);    Serial.print(";");*/
    print_hex(crc8_01,8);    Serial.print(";");
    print_hex(crc8_23,8);    Serial.print(";");
    print_hex(crc8_45,8);    Serial.print(";");
    print_hex(crc8_67,8);    Serial.print(";");

/* crc8_01=crc8ccitt_8b(b01,b02,b03,b05,b06,b07);
 crc8_23=crc8ccitt_8b(b09,b10,b11,b13,b14,b15);
 crc8_45=crc8ccitt_8b(b17,b18,b19,b21,b22,b23);
 crc8_67=crc8ccitt_8b(b25,b26,b27,b29,b30,b31);

    print_binary(crc8_01,8);    Serial.print(";");
    print_binary(crc8_23,8);    Serial.print(";");
    print_binary(crc8_45,8);    Serial.print(";");
    print_binary(crc8_67,8);    Serial.print(";");*/
    Serial.println("");

}//text==2
    
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





/*//ONEWIRE
// CRC-8-CCIT x^8 + x^2 + x + 1
//
// Compute a Dallas Semiconductor 8 bit CRC directly.
// this is much slower, but much smaller, than the lookup table.
//
uint8_t crc8(const uint8_t *addr, uint8_t len)
{
  uint8_t crc = 0;
  
  while (len--) {
    uint8_t inbyte = *addr++;
    for (uint8_t i = 8; i; i--) {
      uint8_t mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) crc ^= 0x83;
//      if (mix) crc ^= 0x07;
//      if (mix) crc ^= 0xE0;
      inbyte >>= 1;
    }
  }
  return crc;
}


//https://www.3dbrew.org/wiki/CRC-8-CCITT
//CRC-8-CCITT is a fast error detection algorithm. It's a standard CRC-8, with polynomial x⁸+x²+x+1.
uint8_t crc8ccitt(const void * data, size_t size);

 uint8_t CRC_TABLE[256] = {
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
    0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
    0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
    0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
    0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
    0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
    0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
    0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
    0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
    0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
    0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
    0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
    0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
    0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
    0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
    0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
    0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
    0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
    0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
    0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
    0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
    0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
    0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
    0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
    0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
    0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
    0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
    0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
    0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
    0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
    0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
    0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

uint8_t crc8ccitt(const void * data, size_t size) {
  uint8_t val = 0;

  uint8_t * pos = (uint8_t *) data;
  uint8_t * end = pos + size;

  while (pos < end) {
    val = CRC_TABLE[val ^ *pos];
    pos++;
  }

  return val;
}

//uint8_t CRCTable[0x100];
uint8_t CRC_Polynom = 0x83;

void generate_table()
{
// CRC_Polynom - значение полинома CRC
// CRCTable[0x100] - таблица
  uint8_t _crc;
  uint8_t x;
  uint8_t y;
     for (x = 0; x < 0x100; x++) {
         _crc = x;
         for (y = 0; y < 8; y++) {
            _crc = (_crc & (1<<7)) ? ((_crc << 1) ^ CRC_Polynom) : (_crc << 1);
        }
        CRC_TABLE[x] = _crc;
     }
}

uint8_t crc8table(const void * data, size_t size) {
  uint8_t val = 0;

  uint8_t * pos = (uint8_t *) data;
  uint8_t * end = pos + size;

  while (pos < end) {
    val = CRC_TABLE[val ^ *pos];
    pos++;
  }

  return val;
}*/

/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Poly  : 0x07    x^8 + x^2 + x^1 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт(127 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
/*unsigned char Crc8(unsigned char *pcBlock, unsigned int len)
{
    unsigned char crc = 0xFF;
    unsigned int i;

    while (len--)
    {
        crc ^= *pcBlock++;

        for (i = 0; i < 8; i++)
            crc = crc & 0x80 ? (crc << 1) ^ 0x07 : crc << 1;
    }

    return crc;
}



uint8_t Crc8_7(const uint8_t *addr)
{
  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[2]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[1]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[0]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  return Crc8(aui8_7b,7);
}
uint8_t crc8_7(const uint8_t *addr)
{
  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[2]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[1]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[0]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  return crc8(aui8_7b,7);
}
uint8_t crc8ccitt_7(const uint8_t *addr)
{
  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[2]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[1]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[0]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  return crc8ccitt(aui8_7b,7);
}
uint8_t crc8table_7(const uint8_t *addr)
{
  aui8_7b[6]=addr[7];
  aui8_7b[5]=addr[6];
  aui8_7b[4]=addr[5];
  aui8_7b[3]=((addr[4] & 0xf0) >> 4) | ((addr[3] & 0x0f) << 4);
  aui8_7b[2]=((addr[3] & 0xf0) >> 4) | ((addr[2] & 0x0f) << 4);
  aui8_7b[1]=((addr[2] & 0xf0) >> 4) | ((addr[1] & 0x0f) << 4);
  aui8_7b[0]=((addr[1] & 0xf0) >> 4) | ((addr[0] & 0xf0));
  return crc8table(aui8_7b,7);
}*/


/*uint8_t crc8_6b(uint8_t ui8_0, uint8_t ui8_1, uint8_t ui8_2, uint8_t ui8_3, uint8_t ui8_4, uint8_t ui8_5)
{
  aui8_6b[0] = ui8_0;
  aui8_6b[1] = ui8_1;
  aui8_6b[2] = ui8_2;
  aui8_6b[3] = ui8_3;
  aui8_6b[4] = ui8_4;
  aui8_6b[5] = ui8_5;
//  return crc8ccitt(aui8_6b,6);
  return crc8(aui8_6b,6);
}
uint8_t crc8ccitt_6b(uint8_t ui8_0, uint8_t ui8_1, uint8_t ui8_2, uint8_t ui8_3, uint8_t ui8_4, uint8_t ui8_5)
{
  aui8_6b[0] = ui8_0;
  aui8_6b[1] = ui8_1;
  aui8_6b[2] = ui8_2;
  aui8_6b[3] = ui8_3;
  aui8_6b[4] = ui8_4;
  aui8_6b[5] = ui8_5;
  return crc8ccitt(aui8_6b,6);
//  return crc8(aui8_6b,6);
}*/

