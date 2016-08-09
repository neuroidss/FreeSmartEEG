/*
Pressure sensor system

This system shows how to log data from a analog sensor and log 
data into an SD card using the SD library.Also use an external 
24 bits ADC
   
created  20 June 2013
by Danny   
*/

#include <SPI.h>

//int text=0;
//int text=2;//data `
int text=3;//crc
int telnet = 0;
int serial = 0;
int processing = 0;

int openbci = 0;
int streamingMode = 0;

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





int alert;
int reset;
int drdy;




double pressureValue0 = 0;
double pressureValue1 = 0;
double pressureValue2 = 0;
double pressureValue3 = 0;
//const int fs=3;
//const int fs=3;
const int fs=256;
//const int fs=250000;
//const int fs=2000;
//const int fs=16000;
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
const long int speedMaximum = 400;
//const long int speedMaximum = 30000000;
//const long int dataOrder = LSBFIRST;
const long int dataOrder = MSBFIRST;
const long int dataMode = SPI_MODE0;
//const long int dataMode = SPI_MODE2;




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

byte command19 = B00011000;//BUFFER_CONFIG_1 0x019
//byte command19 = B00000000;//BUFFER_CONFIG_1 0x019
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
byte command5A = B11111111;//GEN_ERR_REG_1_EN 0x05A
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

//  pinMode(ALERT_PIN, INPUT);
  pinMode(RESET_PIN, OUTPUT);
  pinMode(DRDY_PIN, INPUT);
  pinMode(START_PIN, OUTPUT);

  pinMode(ADCCS, OUTPUT);
//  pinMode(SDCS, OUTPUT);
  digitalWrite(ADCCS, HIGH);
//  digitalWrite(SDCS, HIGH);
  SPI.begin();


  SPI.setBitOrder(dataOrder);

//  digitalWrite(START_PIN, LOW);
//  digitalWrite(START_PIN, HIGH);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, LOW);
    delayMicroseconds(500);
  digitalWrite(RESET_PIN, HIGH);
    delayMicroseconds(500);

}


void loop()
{

  set_register(GENERAL_USER_CONFIG_1_REG,command11);
  GENERAL_USER_CONFIG_1=get_register(GENERAL_USER_CONFIG_1_REG);
  Serial.println("");    
    Serial.println("GENERAL_USER_CONFIG_1;");    
    print_binary(GENERAL_USER_CONFIG_1,8);    Serial.print(";");
    Serial.println("");    
    print_binary(command11,8);    Serial.print(";");
    Serial.println("");   
  //  initial_setup();

    delayMicroseconds(1000000/fs);

}
