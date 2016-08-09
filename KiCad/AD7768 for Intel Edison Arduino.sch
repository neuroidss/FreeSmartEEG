EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:AD7768
LIBS:AD7768 for Intel Edison Arduino-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LP5907 U3
U 1 1 577FE246
P 7600 5900
F 0 "U3" H 7350 6300 60  0000 C CNN
F 1 "LP5907QMFX-3.3Q1" H 7900 6300 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-353" H 7600 5900 60  0001 C CNN
F 3 "" H 7600 5900 60  0000 C CNN
	1    7600 5900
	-1   0    0    1   
$EndComp
$Comp
L LP5907 U2
U 1 1 577FE273
P 5250 5900
F 0 "U2" H 5000 6300 60  0000 C CNN
F 1 "LP5907QMFX-3.3Q1" H 5550 6300 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-353" H 5250 5900 60  0001 C CNN
F 3 "" H 5250 5900 60  0000 C CNN
	1    5250 5900
	-1   0    0    1   
$EndComp
$Comp
L LP5907 U4
U 1 1 577FE314
P 9950 5900
F 0 "U4" H 9700 6300 60  0000 C CNN
F 1 "LP5907QMFX-2.5Q1" H 10250 6300 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-353" H 9950 5900 60  0001 C CNN
F 3 "" H 9950 5900 60  0000 C CNN
	1    9950 5900
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X08 P3
U 1 1 577FE40C
P 1550 3650
F 0 "P3" H 1550 4100 50  0000 C CNN
F 1 "POWER" V 1650 3650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 1550 3650 50  0001 C CNN
F 3 "" H 1550 3650 50  0000 C CNN
	1    1550 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P4
U 1 1 577FE497
P 2750 5450
F 0 "P4" H 2750 5900 50  0000 C CNN
F 1 "DIGITAL(_PWM)" V 2850 5450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 2750 5450 50  0001 C CNN
F 3 "" H 2750 5450 50  0000 C CNN
	1    2750 5450
	1    0    0    1   
$EndComp
$Comp
L CONN_01X10 P1
U 1 1 577FE5A9
P 2750 3650
F 0 "P1" H 2750 4200 50  0000 C CNN
F 1 "DIGITAL(_PWM)" V 2850 3650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 2750 3650 50  0001 C CNN
F 3 "" H 2750 3650 50  0000 C CNN
	1    2750 3650
	1    0    0    1   
$EndComp
$Comp
L CONN_01X06 P5
U 1 1 57800D6E
P 1550 5450
F 0 "P5" H 1550 5800 50  0000 C CNN
F 1 "ANALOG_IN" V 1650 5450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 1550 5450 50  0001 C CNN
F 3 "" H 1550 5450 50  0000 C CNN
	1    1550 5450
	1    0    0    -1  
$EndComp
Text GLabel 1150 4950 0    60   Input ~ 0
A0
Text GLabel 1150 5150 0    60   Input ~ 0
A1
Text GLabel 1150 5350 0    60   Input ~ 0
A2
Text GLabel 1150 5550 0    60   Input ~ 0
A3
Text GLabel 1150 5750 0    60   Input ~ 0
A4
Text GLabel 1150 5950 0    60   Input ~ 0
A5
Text GLabel 1100 3150 0    60   Input ~ 0
IOREF
Text GLabel 1100 3350 0    60   Input ~ 0
MCU_RESET
Text GLabel 1100 3550 0    60   Input ~ 0
3.3V
Text GLabel 1100 3750 0    60   Input ~ 0
5V
Text GLabel 1100 3950 0    60   Input ~ 0
GND
Text GLabel 1100 4150 0    60   Input ~ 0
GND
Text GLabel 1100 4350 0    60   Input ~ 0
VIN
Text GLabel 2250 2750 0    60   Input ~ 0
SCL
Text GLabel 2250 2950 0    60   Input ~ 0
SDA
Text GLabel 2250 3150 0    60   Input ~ 0
AREF
Text GLabel 3050 6200 1    60   Input ~ 0
SDO
Text GLabel 2250 3350 0    60   Input ~ 0
GND
Text GLabel 2950 6200 1    60   Input ~ 0
SDI
Text GLabel 2250 3550 0    60   Input ~ 0
SCLK
Text GLabel 2300 5950 0    60   Input ~ 0
TX
Text GLabel 2300 6150 0    60   Input ~ 0
RX
Text GLabel 2300 5750 0    60   Input ~ 0
DOUT3
Text GLabel 2250 4150 0    60   Input ~ 0
CS
Text GLabel 2250 4350 0    60   Input ~ 0
ADC_RESET
Text GLabel 2300 5550 0    60   Input ~ 0
DOUT2
Text GLabel 2300 5350 0    60   Input ~ 0
DOUT1
Text GLabel 2300 5150 0    60   Input ~ 0
DOUT0
Text GLabel 2300 4950 0    60   Input ~ 0
DCLK
Text GLabel 2250 4550 0    60   Input ~ 0
START
Text GLabel 2300 4750 0    60   Input ~ 0
DRDY
$Comp
L CONN_02X03 P2
U 1 1 57801C6A
P 1300 6450
F 0 "P2" H 1300 6650 50  0000 C CNN
F 1 "ICSP" H 1300 6250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x03" H 1300 5250 50  0001 C CNN
F 3 "" H 1300 5250 50  0000 C CNN
	1    1300 6450
	1    0    0    -1  
$EndComp
Text GLabel 950  6250 0    60   Input ~ 0
IO12
Text GLabel 950  6450 0    60   Input ~ 0
IO13
Text GLabel 950  6650 0    60   Input ~ 0
RESET
Text GLabel 1650 6250 2    60   Input ~ 0
5V
Text GLabel 1650 6450 2    60   Input ~ 0
_IO11
Text GLabel 1650 6650 2    60   Input ~ 0
GND
Text GLabel 8200 5700 2    60   Input ~ 0
EN
Text GLabel 650  7250 1    60   Input ~ 0
AVSS
Text GLabel 7400 5000 3    60   Input ~ 0
AVSS1B
Text GLabel 7000 5000 3    60   Input ~ 0
REF2-
Text GLabel 5850 5700 2    60   Input ~ 0
EN
Text GLabel 10550 5700 2    60   Input ~ 0
EN
Text GLabel 6150 6100 2    60   Input ~ 0
IN
Text GLabel 10900 6100 2    60   Input ~ 0
IN
Text GLabel 10900 5900 2    60   Input ~ 0
GND
Text GLabel 6150 5900 2    60   Input ~ 0
GND
Text GLabel 750  7250 1    60   Input ~ 0
DGND
Text GLabel 4650 6100 0    60   Input ~ 0
OUT_IOVDD
Text GLabel 9350 6100 0    60   Input ~ 0
OUT_VREF
Text GLabel 10000 950  1    60   Input ~ 0
REF1+
Text GLabel 6800 5000 3    60   Input ~ 0
REF2+
Text GLabel 8500 6100 2    60   Input ~ 0
IN
Text GLabel 8500 5900 2    60   Input ~ 0
GND
Text GLabel 7000 6100 0    60   Input ~ 0
OUT_AVDD
Text GLabel 10200 950  1    60   Input ~ 0
REF1-
Text GLabel 10600 950  1    60   Input ~ 0
AVSS1A
Text GLabel 9000 5000 3    60   Input ~ 0
AVSS
Text GLabel 10600 5000 3    60   Input ~ 0
AVSS2A
Text GLabel 8400 5000 3    60   Input ~ 0
AVSS2B
Text GLabel 4800 5000 3    60   Input ~ 0
DGND
Text GLabel 5200 5000 3    60   Input ~ 0
IOVDD
Text GLabel 10200 5000 3    60   Input ~ 0
AVDD2A
Text GLabel 8800 5000 3    60   Input ~ 0
AVDD2B
Text GLabel 9800 4050 3    60   Input ~ 0
CLK_SEL
Text GLabel 9400 4050 3    60   Input ~ 0
FORMAT0
Text GLabel 9200 4050 3    60   Input ~ 0
FORMAT1
Text GLabel 5600 4050 3    60   Input ~ 0
START
Text GLabel 5400 1950 1    60   Input ~ 0
DRDY
Text GLabel 8000 1950 1    60   Input ~ 0
CS
Text GLabel 7800 1950 1    60   Input ~ 0
SCLK
Text GLabel 7600 1950 1    60   Input ~ 0
SDI
Text GLabel 7400 1950 1    60   Input ~ 0
SDO
$Comp
L C C1
U 1 1 57803D35
P 5200 4700
F 0 "C1" H 5225 4800 50  0000 L CNN
F 1 "C 1uF" H 5225 4600 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 5238 4550 50  0001 C CNN
F 3 "" H 5200 4700 50  0000 C CNN
	1    5200 4700
	0    -1   -1   0   
$EndComp
Text GLabel 7200 5000 3    60   Input ~ 0
AVDD1B
Text GLabel 4450 2950 1    60   Input ~ 0
EPAD
$Comp
L Crystal Y1
U 1 1 57804CA7
P 4900 1350
F 0 "Y1" H 4900 1500 50  0000 C CNN
F 1 "32 MHz" H 4900 1200 50  0000 C CNN
F 2 "SMD_Packages:SMD-1206_Pol" H 4900 1350 50  0001 C CNN
F 3 "" H 4900 1350 50  0000 C CNN
	1    4900 1350
	1    0    0    -1  
$EndComp
Text GLabel 10800 4050 3    60   Input ~ 0
AIN0-
Text GLabel 11000 1950 1    60   Input ~ 0
AIN1-
Text GLabel 11000 4050 3    60   Input ~ 0
AIN0+
Text GLabel 9800 1950 1    60   Input ~ 0
AIN2-
Text GLabel 9400 1950 1    60   Input ~ 0
AIN3-
Text GLabel 10800 1950 1    60   Input ~ 0
AIN1+
Text GLabel 9600 1950 1    60   Input ~ 0
AIN2+
Text GLabel 9200 1950 1    60   Input ~ 0
AIN3+
Text GLabel 8200 4050 3    60   Input ~ 0
AIN4-
Text GLabel 8000 4050 3    60   Input ~ 0
AIN4+
Text GLabel 7600 4050 3    60   Input ~ 0
AIN5+
Text GLabel 6400 4050 3    60   Input ~ 0
AIN6+
Text GLabel 6000 4050 3    60   Input ~ 0
AIN7+
Text GLabel 7800 4050 3    60   Input ~ 0
AIN5-
Text GLabel 6200 4050 3    60   Input ~ 0
AIN7-
Text GLabel 6600 4050 3    60   Input ~ 0
AIN6-
Text GLabel 10400 950  1    60   Input ~ 0
AVDD1A
$Comp
L C C5
U 1 1 5780C539
P 4800 4700
F 0 "C5" H 4825 4800 50  0000 L CNN
F 1 "C 10uF" H 4825 4600 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 4838 4550 50  0001 C CNN
F 3 "" H 4800 4700 50  0000 C CNN
	1    4800 4700
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 5780CC33
P 4800 4500
F 0 "C6" H 4825 4600 50  0000 L CNN
F 1 "100pF" H 4825 4400 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 4838 4350 50  0001 C CNN
F 3 "" H 4800 4500 50  0000 C CNN
	1    4800 4500
	0    -1   -1   0   
$EndComp
$Comp
L C C2
U 1 1 5780CC6E
P 5200 4500
F 0 "C2" H 5225 4600 50  0000 L CNN
F 1 "100pF" H 5225 4400 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 5238 4350 50  0001 C CNN
F 3 "" H 5200 4500 50  0000 C CNN
	1    5200 4500
	0    -1   -1   0   
$EndComp
$Comp
L C C14
U 1 1 5780D089
P 10100 1450
F 0 "C14" H 10125 1550 50  0000 L CNN
F 1 "100pF" H 10125 1350 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10138 1300 50  0001 C CNN
F 3 "" H 10100 1450 50  0000 C CNN
	1    10100 1450
	0    1    1    0   
$EndComp
$Comp
L C C13
U 1 1 5780DDD1
P 10100 1250
F 0 "C13" H 10125 1350 50  0000 L CNN
F 1 "C 1uF" H 10125 1150 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10138 1100 50  0001 C CNN
F 3 "" H 10100 1250 50  0000 C CNN
	1    10100 1250
	0    1    1    0   
$EndComp
$Comp
L C C17
U 1 1 5780DE17
P 10500 1250
F 0 "C17" H 10525 1350 50  0000 L CNN
F 1 "C 1uF" H 10525 1150 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10538 1100 50  0001 C CNN
F 3 "" H 10500 1250 50  0000 C CNN
	1    10500 1250
	0    1    1    0   
$EndComp
$Comp
L C C18
U 1 1 5780DE66
P 10500 1450
F 0 "C18" H 10525 1550 50  0000 L CNN
F 1 "100pF" H 10525 1350 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10538 1300 50  0001 C CNN
F 3 "" H 10500 1450 50  0000 C CNN
	1    10500 1450
	0    1    1    0   
$EndComp
Connection ~ 10250 1450
Connection ~ 10250 1250
Connection ~ 9950 1450
Connection ~ 9950 1250
Connection ~ 10350 1250
Connection ~ 10350 1450
Connection ~ 10650 1450
Connection ~ 10650 1250
Connection ~ 4650 4700
Connection ~ 5350 4700
Connection ~ 5350 4500
Connection ~ 4950 4500
Connection ~ 5050 4700
$Comp
L C C19
U 1 1 5780EAA6
P 10550 4550
F 0 "C19" H 10575 4650 50  0000 L CNN
F 1 "100pF" H 10575 4450 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10588 4400 50  0001 C CNN
F 3 "" H 10550 4550 50  0000 C CNN
	1    10550 4550
	0    -1   -1   0   
$EndComp
$Comp
L C C15
U 1 1 5780FBDF
P 10150 4550
F 0 "C15" H 10175 4650 50  0000 L CNN
F 1 "100pF" H 10175 4450 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10188 4400 50  0001 C CNN
F 3 "" H 10150 4550 50  0000 C CNN
	1    10150 4550
	0    -1   -1   0   
$EndComp
$Comp
L C C16
U 1 1 5780FC4A
P 10150 4750
F 0 "C16" H 10175 4850 50  0000 L CNN
F 1 "1uF" H 10175 4650 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10188 4600 50  0001 C CNN
F 3 "" H 10150 4750 50  0000 C CNN
	1    10150 4750
	0    -1   -1   0   
$EndComp
Connection ~ 10000 4550
Connection ~ 10000 4750
Connection ~ 10700 4550
Connection ~ 10300 4750
$Comp
L C C11
U 1 1 5781025B
P 8900 4550
F 0 "C11" H 8925 4650 50  0000 L CNN
F 1 "100pF" H 8925 4450 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 8938 4400 50  0001 C CNN
F 3 "" H 8900 4550 50  0000 C CNN
	1    8900 4550
	0    -1   -1   0   
$EndComp
$Comp
L C C12
U 1 1 578102EE
P 8900 4750
F 0 "C12" H 8925 4850 50  0000 L CNN
F 1 "1uF" H 8925 4650 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 8938 4600 50  0001 C CNN
F 3 "" H 8900 4750 50  0000 C CNN
	1    8900 4750
	0    -1   -1   0   
$EndComp
$Comp
L C C9
U 1 1 57810352
P 8500 4550
F 0 "C9" H 8525 4650 50  0000 L CNN
F 1 "100pF" H 8525 4450 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 8538 4400 50  0001 C CNN
F 3 "" H 8500 4550 50  0000 C CNN
	1    8500 4550
	0    -1   -1   0   
$EndComp
Connection ~ 8350 4550
Connection ~ 8350 4750
Connection ~ 8750 4550
Connection ~ 8750 4750
Connection ~ 9050 4750
Connection ~ 9050 4550
$Comp
L C C7
U 1 1 578108CA
P 7300 4550
F 0 "C7" H 7325 4650 50  0000 L CNN
F 1 "100pF" H 7325 4450 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 7338 4400 50  0001 C CNN
F 3 "" H 7300 4550 50  0000 C CNN
	1    7300 4550
	0    -1   -1   0   
$EndComp
$Comp
L C C8
U 1 1 5781095F
P 7300 4750
F 0 "C8" H 7325 4850 50  0000 L CNN
F 1 "1uF" H 7325 4650 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 7338 4600 50  0001 C CNN
F 3 "" H 7300 4750 50  0000 C CNN
	1    7300 4750
	0    -1   -1   0   
$EndComp
$Comp
L C C4
U 1 1 578109CD
P 6900 4750
F 0 "C4" H 6925 4850 50  0000 L CNN
F 1 "1uF" H 6925 4650 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 6938 4600 50  0001 C CNN
F 3 "" H 6900 4750 50  0000 C CNN
	1    6900 4750
	0    -1   -1   0   
$EndComp
$Comp
L C C3
U 1 1 57810A46
P 6900 4550
F 0 "C3" H 6925 4650 50  0000 L CNN
F 1 "100pF" H 6925 4450 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 6938 4400 50  0001 C CNN
F 3 "" H 6900 4550 50  0000 C CNN
	1    6900 4550
	0    -1   -1   0   
$EndComp
Connection ~ 6750 4550
Connection ~ 6750 4750
Connection ~ 7050 4750
Connection ~ 7050 4550
Connection ~ 7150 4750
Connection ~ 7150 4550
Connection ~ 7450 4550
Connection ~ 7450 4750
Wire Wire Line
	5350 4350 5200 4350
Wire Wire Line
	4800 1650 4750 1650
Wire Wire Line
	4750 1650 4750 1050
Wire Wire Line
	5000 1650 5050 1650
Wire Wire Line
	5050 1650 5050 1050
Wire Wire Line
	9950 1650 10000 1650
Wire Wire Line
	10250 1650 10200 1650
Wire Wire Line
	10350 1650 10400 1650
Wire Wire Line
	10650 1650 10600 1650
Wire Wire Line
	4950 4350 5000 4350
Wire Wire Line
	4950 4700 4950 4350
Wire Wire Line
	4650 4900 4650 4350
Wire Wire Line
	5350 4900 5350 4350
Wire Wire Line
	5350 4900 5200 4900
Wire Wire Line
	5200 4900 5200 5000
Wire Wire Line
	4800 5000 4800 4900
Wire Wire Line
	5050 4900 4650 4900
Wire Wire Line
	5050 4900 5050 4500
Connection ~ 4800 4900
Wire Wire Line
	10250 1050 10250 1650
Wire Wire Line
	10250 1050 10200 1050
Wire Wire Line
	10200 1050 10200 950 
Wire Wire Line
	9950 1050 9950 1650
Wire Wire Line
	9950 1050 10000 1050
Wire Wire Line
	10000 1050 10000 950 
Wire Wire Line
	10350 1050 10350 1650
Wire Wire Line
	10350 1050 10400 1050
Wire Wire Line
	10400 1050 10400 950 
Wire Wire Line
	10650 1050 10650 1650
Wire Wire Line
	10650 1050 10600 1050
Wire Wire Line
	10600 1050 10600 950 
Wire Wire Line
	10600 5000 10600 4950
Wire Wire Line
	10300 4950 10700 4950
Wire Wire Line
	10700 4950 10700 4400
Wire Wire Line
	10700 4400 10600 4400
Wire Wire Line
	10200 4400 10000 4400
Wire Wire Line
	10000 4400 10000 4950
Wire Wire Line
	10000 4950 10200 4950
Wire Wire Line
	10200 4950 10200 5000
Wire Wire Line
	10300 4550 10300 4950
Connection ~ 10600 4950
Wire Wire Line
	8650 4400 8600 4400
Wire Wire Line
	8400 4400 8350 4400
Wire Wire Line
	8350 4400 8350 4950
Wire Wire Line
	8350 4950 8400 4950
Wire Wire Line
	8400 4950 8400 5000
Wire Wire Line
	8800 5000 8800 4950
Wire Wire Line
	8800 4950 8750 4950
Wire Wire Line
	8750 4950 8750 4400
Wire Wire Line
	8750 4400 8800 4400
Wire Wire Line
	9000 4400 9050 4400
Wire Wire Line
	9050 4400 9050 4950
Wire Wire Line
	9050 4950 9000 4950
Wire Wire Line
	9000 4950 9000 5000
Wire Wire Line
	7400 4400 7450 4400
Wire Wire Line
	7450 4400 7450 4950
Wire Wire Line
	7450 4950 7400 4950
Wire Wire Line
	7400 4950 7400 5000
Wire Wire Line
	7200 5000 7200 4950
Wire Wire Line
	7200 4950 7150 4950
Wire Wire Line
	7150 4950 7150 4400
Wire Wire Line
	7150 4400 7200 4400
Wire Wire Line
	7000 4400 7050 4400
Wire Wire Line
	7050 4400 7050 4950
Wire Wire Line
	7050 4950 7000 4950
Wire Wire Line
	7000 4950 7000 5000
Wire Wire Line
	6800 5000 6800 4950
Wire Wire Line
	6800 4950 6750 4950
Wire Wire Line
	6750 4950 6750 4400
Wire Wire Line
	6750 4400 6800 4400
Text GLabel 1050 1900 0    60   Input ~ 0
AIN0+
Text GLabel 1050 1500 0    60   Input ~ 0
AIN1+
Text GLabel 1050 1100 0    60   Input ~ 0
AIN2+
Text GLabel 1050 700  0    60   Input ~ 0
AIN3+
Text GLabel 2250 1900 0    60   Input ~ 0
AIN4+
Text GLabel 2250 1500 0    60   Input ~ 0
AIN5+
Text GLabel 2250 1100 0    60   Input ~ 0
AIN6+
Text GLabel 2250 700  0    60   Input ~ 0
AIN7+
Wire Wire Line
	2550 1050 2450 1050
Wire Wire Line
	2550 1150 2400 1150
Wire Wire Line
	2550 1250 2350 1250
Wire Wire Line
	2550 1350 2300 1350
Wire Wire Line
	2550 1450 2300 1450
Wire Wire Line
	2300 1450 2300 1500
Wire Wire Line
	2300 1500 2250 1500
Wire Wire Line
	2300 1350 2300 1300
Wire Wire Line
	2300 1300 2250 1300
Wire Wire Line
	2350 1250 2350 1100
Wire Wire Line
	2350 1100 2250 1100
Wire Wire Line
	2400 1150 2400 900 
Wire Wire Line
	2400 900  2250 900 
Wire Wire Line
	2450 1050 2450 700 
Wire Wire Line
	2450 700  2250 700 
Wire Wire Line
	2550 1550 2350 1550
Wire Wire Line
	2350 1550 2350 1700
Wire Wire Line
	2350 1700 2250 1700
Wire Wire Line
	2550 1650 2400 1650
Wire Wire Line
	2400 1650 2400 1900
Wire Wire Line
	2400 1900 2250 1900
Wire Wire Line
	2550 1750 2450 1750
Wire Wire Line
	2450 1750 2450 2100
Wire Wire Line
	2450 2100 2250 2100
Text GLabel 1050 2100 0    60   Input ~ 0
AIN0-
Text GLabel 1050 1700 0    60   Input ~ 0
AIN1-
Text GLabel 1050 1300 0    60   Input ~ 0
AIN2-
Text GLabel 1050 900  0    60   Input ~ 0
AIN3-
Text GLabel 2250 2100 0    60   Input ~ 0
AIN4-
Text GLabel 2250 1700 0    60   Input ~ 0
AIN5-
Text GLabel 2250 1300 0    60   Input ~ 0
AIN6-
Text GLabel 2250 900  0    60   Input ~ 0
AIN7-
Wire Wire Line
	8100 5700 8200 5700
Wire Wire Line
	1050 6350 1000 6350
Wire Wire Line
	1000 6350 1000 6250
Wire Wire Line
	1000 6250 950  6250
Wire Wire Line
	1050 6550 1000 6550
Wire Wire Line
	1000 6550 1000 6650
Wire Wire Line
	1000 6650 950  6650
Wire Wire Line
	950  6450 1050 6450
Wire Wire Line
	4650 6100 4750 6100
Wire Wire Line
	5750 6100 5800 6100
Wire Wire Line
	5800 5900 5750 5900
Wire Wire Line
	5750 5700 5850 5700
Wire Wire Line
	9350 6100 9450 6100
Wire Wire Line
	10450 5700 10550 5700
Wire Wire Line
	10450 5900 10550 5900
Wire Wire Line
	10550 6100 10450 6100
Wire Wire Line
	7000 6100 7100 6100
Wire Wire Line
	8100 5900 8150 5900
Wire Wire Line
	8150 6100 8100 6100
Wire Wire Line
	9400 1950 9400 1950
Wire Wire Line
	2550 4100 2500 4100
Wire Wire Line
	2500 4100 2500 4550
Wire Wire Line
	2500 4550 2250 4550
Wire Wire Line
	2550 4000 2450 4000
Wire Wire Line
	2450 4000 2450 4350
Wire Wire Line
	2450 4350 2250 4350
Wire Wire Line
	2550 3900 2400 3900
Wire Wire Line
	2400 3900 2400 4150
Wire Wire Line
	2400 4150 2250 4150
Wire Wire Line
	2550 3800 2350 3800
Wire Wire Line
	2350 3800 2350 3950
Wire Wire Line
	2350 3950 2250 3950
Wire Wire Line
	2550 3700 2300 3700
Wire Wire Line
	2300 3700 2300 3750
Wire Wire Line
	2300 3750 2250 3750
Wire Wire Line
	2550 3600 2300 3600
Wire Wire Line
	2300 3600 2300 3550
Wire Wire Line
	2300 3550 2250 3550
Wire Wire Line
	2550 3500 2350 3500
Wire Wire Line
	2350 3500 2350 3350
Wire Wire Line
	2350 3350 2250 3350
Wire Wire Line
	2550 3400 2400 3400
Wire Wire Line
	2400 3400 2400 3150
Wire Wire Line
	2400 3150 2250 3150
Wire Wire Line
	2550 3300 2450 3300
Wire Wire Line
	2450 3300 2450 2950
Wire Wire Line
	2450 2950 2250 2950
Wire Wire Line
	2550 3200 2500 3200
Wire Wire Line
	2500 3200 2500 2750
Wire Wire Line
	2500 2750 2250 2750
Wire Wire Line
	2550 5100 2500 5100
Wire Wire Line
	2500 5100 2500 4750
Wire Wire Line
	2500 4750 2300 4750
Wire Wire Line
	2550 5200 2450 5200
Wire Wire Line
	2450 5200 2450 4950
Wire Wire Line
	2450 4950 2300 4950
Wire Wire Line
	2550 5300 2400 5300
Wire Wire Line
	2400 5300 2400 5150
Wire Wire Line
	2400 5150 2300 5150
Wire Wire Line
	2550 5400 2350 5400
Wire Wire Line
	2350 5400 2350 5350
Wire Wire Line
	2350 5350 2300 5350
Wire Wire Line
	2550 5500 2350 5500
Wire Wire Line
	2350 5500 2350 5550
Wire Wire Line
	2350 5550 2300 5550
Wire Wire Line
	2550 5800 2500 5800
Wire Wire Line
	2500 5800 2500 6150
Wire Wire Line
	2500 6150 2300 6150
Wire Wire Line
	2550 5700 2450 5700
Wire Wire Line
	2450 5700 2450 5950
Wire Wire Line
	2450 5950 2300 5950
Wire Wire Line
	2550 5600 2400 5600
Wire Wire Line
	2400 5600 2400 5750
Wire Wire Line
	2400 5750 2300 5750
Text GLabel 2250 2500 0    60   Input ~ 0
GND
Text GLabel 2250 2300 0    60   Input ~ 0
GND
Wire Wire Line
	1200 5400 1200 5350
Wire Wire Line
	1200 5350 1150 5350
Wire Wire Line
	1200 5500 1200 5550
Wire Wire Line
	1200 5550 1150 5550
Text GLabel 1100 2950 0    60   Input ~ 0
AREF
Text GLabel 1050 2500 0    60   Input ~ 0
AUXAIN-
Text GLabel 750  7350 3    60   Input ~ 0
GND
Text GLabel 650  7350 3    60   Input ~ 0
GND
Wire Wire Line
	750  7250 750  7350
Wire Wire Line
	650  7250 650  7350
Text GLabel 5600 1950 1    60   Input ~ 0
DCLK
Text GLabel 5800 1950 1    60   Input ~ 0
DOUT0
Text GLabel 6000 1950 1    60   Input ~ 0
DOUT1
Text GLabel 6200 1950 1    60   Input ~ 0
DOUT2
Text GLabel 6400 1950 1    60   Input ~ 0
DOUT3
Text GLabel 5200 1950 1    60   Input ~ 0
ADC_RESET
$Comp
L CONN_01X16 P8
U 1 1 57830D69
P 3850 1500
F 0 "P8" H 3850 2350 50  0000 C CNN
F 1 "CONN_01X16" V 3950 1500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16" H 3850 1500 50  0001 C CNN
F 3 "" H 3850 1500 50  0000 C CNN
	1    3850 1500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X16 P9
U 1 1 57830E1B
P 3850 3250
F 0 "P9" H 3850 4100 50  0000 C CNN
F 1 "CONN_01X16" V 3950 3250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16" H 3850 3250 50  0001 C CNN
F 3 "" H 3850 3250 50  0000 C CNN
	1    3850 3250
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X16 P10
U 1 1 57830EE7
P 3850 5000
F 0 "P10" H 3850 5850 50  0000 C CNN
F 1 "CONN_01X16" V 3950 5000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16" H 3850 5000 50  0001 C CNN
F 3 "" H 3850 5000 50  0000 C CNN
	1    3850 5000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X16 P11
U 1 1 57830FDE
P 3850 6750
F 0 "P11" H 3850 7600 50  0000 C CNN
F 1 "CONN_01X16" V 3950 6750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16" H 3850 6750 50  0001 C CNN
F 3 "" H 3850 6750 50  0000 C CNN
	1    3850 6750
	1    0    0    -1  
$EndComp
Text GLabel 3650 7400 0    60   Input ~ 0
AIN0-
Text GLabel 3650 7500 0    60   Input ~ 0
AIN0+
Text GLabel 3650 750  0    60   Input ~ 0
AIN1-
Text GLabel 3650 850  0    60   Input ~ 0
AIN1+
Text GLabel 3650 1350 0    60   Input ~ 0
AIN2-
Text GLabel 3650 1450 0    60   Input ~ 0
AIN2+
Text GLabel 3650 1550 0    60   Input ~ 0
AIN3-
Text GLabel 3650 1650 0    60   Input ~ 0
AIN3+
Text GLabel 3650 6100 0    60   Input ~ 0
AIN4-
Text GLabel 3650 6000 0    60   Input ~ 0
AIN4+
Text GLabel 3650 5750 0    60   Input ~ 0
AIN5-
Text GLabel 3650 5650 0    60   Input ~ 0
AIN5+
Text GLabel 3650 5150 0    60   Input ~ 0
AIN6-
Text GLabel 3650 5050 0    60   Input ~ 0
AIN6+
Text GLabel 3650 4950 0    60   Input ~ 0
AIN7-
Text GLabel 3650 4850 0    60   Input ~ 0
AIN7+
Text GLabel 850  7350 3    60   Input ~ 0
AVSS
Text GLabel 950  7350 3    60   Input ~ 0
AVDD
Text GLabel 1050 7350 3    60   Input ~ 0
AVSS
Text GLabel 1150 7350 3    60   Input ~ 0
VREF
Text GLabel 2750 7350 3    60   Input ~ 0
IOVDD
Wire Wire Line
	4450 3000 4450 2950
Wire Wire Line
	4650 4350 4800 4350
Connection ~ 4650 4500
Text GLabel 2650 7350 3    60   Input ~ 0
IOVDD
Text GLabel 2550 7350 3    60   Input ~ 0
IOVDD
Text GLabel 2450 7350 3    60   Input ~ 0
IOVDD
Text GLabel 3650 2250 0    60   Input ~ 0
CS
Text GLabel 3650 2500 0    60   Input ~ 0
SCLK
Text GLabel 3650 2600 0    60   Input ~ 0
SDI
Text GLabel 3650 2700 0    60   Input ~ 0
SDO
Text GLabel 3650 4450 0    60   Input ~ 0
IOVDD
Text GLabel 3650 4250 0    60   Input ~ 0
DGND
Text GLabel 3650 3200 0    60   Input ~ 0
DOUT3
Text GLabel 3650 3300 0    60   Input ~ 0
DOUT2
Text GLabel 3650 3400 0    60   Input ~ 0
DOUT1
Text GLabel 3650 3500 0    60   Input ~ 0
DOUT0
Text GLabel 3650 3600 0    60   Input ~ 0
DCLK
Text GLabel 3650 3700 0    60   Input ~ 0
DRDY
Text GLabel 3650 1250 0    60   Input ~ 0
REF1+
Text GLabel 3650 1150 0    60   Input ~ 0
REF1-
Text GLabel 3650 950  0    60   Input ~ 0
AVSS1A
Text GLabel 3650 1050 0    60   Input ~ 0
AVDD1A
Text GLabel 3650 6900 0    60   Input ~ 0
CLK_SEL
Text GLabel 3650 6700 0    60   Input ~ 0
FORMAT0
Text GLabel 3650 6600 0    60   Input ~ 0
FORMAT1
Text GLabel 3650 7100 0    60   Input ~ 0
AVDD2A
Text GLabel 3650 7300 0    60   Input ~ 0
AVSS2A
Text GLabel 3650 6500 0    60   Input ~ 0
AVSS
Text GLabel 3650 6400 0    60   Input ~ 0
AVDD2B
Text GLabel 3650 6200 0    60   Input ~ 0
AVSS2B
Text GLabel 3650 5550 0    60   Input ~ 0
AVSS1B
Text GLabel 3650 5450 0    60   Input ~ 0
AVDD1B
Text GLabel 3650 5350 0    60   Input ~ 0
REF2-
Text GLabel 3650 5250 0    60   Input ~ 0
REF2+
Text GLabel 3650 3800 0    60   Input ~ 0
ADC_RESET
Text GLabel 3650 4650 0    60   Input ~ 0
START
Text GLabel 850  7250 1    60   Input ~ 0
AVSS1A
Text GLabel 950  7250 1    60   Input ~ 0
AVDD1A
Text GLabel 1050 7250 1    60   Input ~ 0
REF1-
Text GLabel 1150 7250 1    60   Input ~ 0
REF1+
Text GLabel 2050 7250 1    60   Input ~ 0
AVSS2A
Text GLabel 1950 7250 1    60   Input ~ 0
AVDD2A
Text GLabel 1750 7250 1    60   Input ~ 0
AVDD2B
Text GLabel 1650 7250 1    60   Input ~ 0
AVSS2B
Text GLabel 1250 7350 3    60   Input ~ 0
VREF
Text GLabel 2050 7350 3    60   Input ~ 0
AVSS
Text GLabel 1650 7350 3    60   Input ~ 0
AVSS
Text GLabel 1950 7350 3    60   Input ~ 0
AVDD
Text GLabel 1750 7350 3    60   Input ~ 0
AVDD
Text GLabel 1250 7250 1    60   Input ~ 0
REF2+
Text GLabel 1350 7250 1    60   Input ~ 0
REF2-
Text GLabel 1450 7250 1    60   Input ~ 0
AVDD1B
Text GLabel 1550 7250 1    60   Input ~ 0
AVSS1B
Text GLabel 1450 7350 3    60   Input ~ 0
AVDD
Text GLabel 1550 7350 3    60   Input ~ 0
AVSS
Text GLabel 1350 7350 3    60   Input ~ 0
AVSS
Wire Wire Line
	2050 7350 2050 7250
Wire Wire Line
	1950 7350 1950 7250
Wire Wire Line
	1750 7350 1750 7250
Wire Wire Line
	1650 7350 1650 7250
Wire Wire Line
	1550 7350 1550 7250
Wire Wire Line
	1450 7350 1450 7250
Wire Wire Line
	1350 7350 1350 7250
Wire Wire Line
	1250 7350 1250 7250
Wire Wire Line
	1150 7350 1150 7250
Wire Wire Line
	1050 7350 1050 7250
Wire Wire Line
	950  7350 950  7250
Wire Wire Line
	850  7350 850  7250
Text GLabel 5800 4050 3    60   Input ~ 0
SYNC_OUT
Text GLabel 5400 4050 3    60   Input ~ 0
SYNC_IN
Text GLabel 10000 4050 3    60   Input ~ 0
VCM
Text GLabel 5000 950  1    60   Input ~ 0
XTAL1
Text GLabel 4800 950  1    60   Input ~ 0
XTAL2
Text GLabel 8400 1950 1    60   Input ~ 0
GPIO2
Text GLabel 8600 1950 1    60   Input ~ 0
GPIO1
Text GLabel 8800 1950 1    60   Input ~ 0
GPIO0
Text GLabel 2350 7250 1    60   Input ~ 0
EPAD
Text GLabel 2350 7350 3    60   Input ~ 0
GND
Text GLabel 2450 7250 1    60   Input ~ 0
FORMAT1
Text GLabel 2550 7250 1    60   Input ~ 0
FORMAT0
Text GLabel 2650 7250 1    60   Input ~ 0
CLK_SEL
Wire Wire Line
	2350 7350 2350 7250
Wire Wire Line
	2450 7350 2450 7250
Wire Wire Line
	2550 7350 2550 7250
Wire Wire Line
	2650 7350 2650 7250
Wire Wire Line
	2750 7350 2750 7250
Wire Wire Line
	5050 1050 5000 1050
Wire Wire Line
	5000 1050 5000 950 
Connection ~ 5050 1350
Wire Wire Line
	4800 950  4800 1050
Wire Wire Line
	4800 1050 4750 1050
Connection ~ 4750 1350
Text GLabel 3650 1850 0    60   Input ~ 0
GPIO0
Text GLabel 3650 1950 0    60   Input ~ 0
GPIO1
Text GLabel 3650 2050 0    60   Input ~ 0
GPIO2
Text GLabel 3650 3900 0    60   Input ~ 0
XTAL1
Text GLabel 3650 4000 0    60   Input ~ 0
XTAL2
Text GLabel 3650 4750 0    60   Input ~ 0
SYNC_OUT
Text GLabel 3650 4550 0    60   Input ~ 0
SYNC_IN
Text GLabel 3650 7000 0    60   Input ~ 0
VCM
$Comp
L CONN_01X03 P12
U 1 1 5783D841
P 4800 7050
F 0 "P12" H 4800 7250 50  0000 C CNN
F 1 "CONN_01X03" V 4900 7050 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 4800 7050 50  0001 C CNN
F 3 "" H 4800 7050 50  0000 C CNN
	1    4800 7050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P13
U 1 1 5783D91F
P 4800 7450
F 0 "P13" H 4800 7650 50  0000 C CNN
F 1 "CONN_01X03" V 4900 7450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 4800 7450 50  0001 C CNN
F 3 "" H 4800 7450 50  0000 C CNN
	1    4800 7450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P14
U 1 1 5783D9FF
P 5800 7100
F 0 "P14" H 5800 7300 50  0000 C CNN
F 1 "CONN_01X03" V 5900 7100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 5800 7100 50  0001 C CNN
F 3 "" H 5800 7100 50  0000 C CNN
	1    5800 7100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P15
U 1 1 5783DA96
P 5800 7500
F 0 "P15" H 5800 7700 50  0000 C CNN
F 1 "CONN_01X03" V 5900 7500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 5800 7500 50  0001 C CNN
F 3 "" H 5800 7500 50  0000 C CNN
	1    5800 7500
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P16
U 1 1 5783DB30
P 6750 7100
F 0 "P16" H 6750 7300 50  0000 C CNN
F 1 "CONN_01X03" V 6850 7100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6750 7100 50  0001 C CNN
F 3 "" H 6750 7100 50  0000 C CNN
	1    6750 7100
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 P17
U 1 1 5783DBCD
P 6750 7500
F 0 "P17" H 6750 7700 50  0000 C CNN
F 1 "CONN_01X03" V 6850 7500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6750 7500 50  0001 C CNN
F 3 "" H 6750 7500 50  0000 C CNN
	1    6750 7500
	1    0    0    -1  
$EndComp
Text GLabel 2750 6300 3    60   Input ~ 0
3.3V
Text GLabel 2850 6300 3    60   Input ~ 0
3.3V
Text GLabel 2750 6200 1    60   Input ~ 0
EN
Text GLabel 2850 6200 1    60   Input ~ 0
IN
Wire Wire Line
	1600 6350 1600 6250
Wire Wire Line
	1600 6250 1650 6250
Wire Wire Line
	1550 6350 1600 6350
Wire Wire Line
	1600 6550 1600 6650
Wire Wire Line
	1650 6450 1550 6450
Wire Wire Line
	1550 6550 1600 6550
Wire Wire Line
	1600 6650 1650 6650
Wire Wire Line
	1300 4950 1150 4950
Wire Wire Line
	1300 5200 1300 4950
Wire Wire Line
	1250 5300 1250 5150
Wire Wire Line
	1250 5150 1150 5150
Wire Wire Line
	1250 5750 1150 5750
Wire Wire Line
	1250 5600 1250 5750
Wire Wire Line
	1300 5700 1300 5950
Wire Wire Line
	1300 5950 1150 5950
Wire Wire Line
	1350 5600 1250 5600
Wire Wire Line
	1350 5300 1250 5300
Wire Wire Line
	1350 5200 1300 5200
Wire Wire Line
	1350 5400 1200 5400
Wire Wire Line
	1350 5500 1200 5500
Wire Wire Line
	1350 5700 1300 5700
Wire Wire Line
	1200 3950 1100 3950
Wire Wire Line
	1250 4150 1100 4150
Wire Wire Line
	1300 4350 1100 4350
Wire Wire Line
	1300 4000 1300 4350
Wire Wire Line
	1250 3900 1250 4150
Wire Wire Line
	1200 3800 1200 3950
Wire Wire Line
	1150 3750 1100 3750
Wire Wire Line
	1250 3150 1100 3150
Wire Wire Line
	1300 2950 1100 2950
Wire Wire Line
	1200 3350 1100 3350
Wire Wire Line
	1150 3550 1100 3550
Wire Wire Line
	1150 3600 1150 3550
Wire Wire Line
	1150 3700 1150 3750
Wire Wire Line
	1200 3500 1200 3350
Wire Wire Line
	1250 3400 1250 3150
Wire Wire Line
	1300 3300 1300 2950
Wire Wire Line
	1350 3300 1300 3300
Wire Wire Line
	1350 3400 1250 3400
Wire Wire Line
	1350 3500 1200 3500
Wire Wire Line
	1350 3600 1150 3600
Wire Wire Line
	1350 3700 1150 3700
Wire Wire Line
	1350 3800 1200 3800
Wire Wire Line
	1350 3900 1250 3900
Wire Wire Line
	1350 4000 1300 4000
Wire Wire Line
	1200 1650 1200 1900
Wire Wire Line
	1250 1750 1250 2100
Wire Wire Line
	1250 2100 1050 2100
Wire Wire Line
	1200 1900 1050 1900
Wire Wire Line
	1150 1700 1050 1700
Wire Wire Line
	1150 1550 1150 1700
Wire Wire Line
	1100 1500 1050 1500
Wire Wire Line
	1100 1450 1100 1500
Wire Wire Line
	1100 1350 1100 1300
Wire Wire Line
	1100 1300 1050 1300
Wire Wire Line
	1150 1100 1050 1100
Wire Wire Line
	1150 1250 1150 1100
Wire Wire Line
	1200 1150 1200 900 
Wire Wire Line
	1200 900  1050 900 
Wire Wire Line
	1350 1350 1100 1350
Wire Wire Line
	1350 1750 1250 1750
Wire Wire Line
	1350 1650 1200 1650
Wire Wire Line
	1350 1550 1150 1550
Wire Wire Line
	1350 1450 1100 1450
Wire Wire Line
	1350 1250 1150 1250
Wire Wire Line
	1350 1150 1200 1150
Wire Wire Line
	1350 1050 1250 1050
Wire Wire Line
	1250 1050 1250 700 
Wire Wire Line
	1250 700  1050 700 
Text GLabel 3050 7350 3    60   Input ~ 0
IOVDD
Text GLabel 2950 7350 3    60   Input ~ 0
VREF
Text GLabel 2850 7350 3    60   Input ~ 0
AVDD
Text GLabel 3050 7250 1    60   Input ~ 0
OUT_IOVDD
Text GLabel 2950 7250 1    60   Input ~ 0
OUT_VREF
Text GLabel 2850 7250 1    60   Input ~ 0
OUT_AVDD
Text GLabel 4600 6950 0    60   Input ~ 0
IN
Text GLabel 5600 7000 0    60   Input ~ 0
IN
Text GLabel 6550 7000 0    60   Input ~ 0
IN
Text GLabel 4600 7050 0    60   Input ~ 0
GND
Text GLabel 5600 7100 0    60   Input ~ 0
GND
Text GLabel 6550 7100 0    60   Input ~ 0
GND
Text GLabel 4600 7150 0    60   Input ~ 0
EN
Text GLabel 5600 7200 0    60   Input ~ 0
EN
Text GLabel 6550 7200 0    60   Input ~ 0
EN
Text GLabel 4600 7550 0    60   Input ~ 0
OUT_IOVDD
Text GLabel 5600 7600 0    60   Input ~ 0
OUT_AVDD
Text GLabel 6550 7600 0    60   Input ~ 0
OUT_VREF
Wire Wire Line
	2850 7350 2850 7250
Wire Wire Line
	2950 7350 2950 7250
Wire Wire Line
	3050 7350 3050 7250
Wire Wire Line
	2750 6300 2750 6200
Wire Wire Line
	2850 6300 2850 6200
Wire Wire Line
	8650 4400 8650 4750
$Comp
L C C20
U 1 1 57846078
P 4550 5850
F 0 "C20" H 4575 5950 50  0000 L CNN
F 1 "1uF" H 4575 5750 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 4588 5700 50  0001 C CNN
F 3 "" H 4550 5850 50  0000 C CNN
	1    4550 5850
	1    0    0    -1  
$EndComp
$Comp
L C C24
U 1 1 578461F6
P 6950 5850
F 0 "C24" H 6975 5950 50  0000 L CNN
F 1 "1uF" H 6975 5750 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 6988 5700 50  0001 C CNN
F 3 "" H 6950 5850 50  0000 C CNN
	1    6950 5850
	1    0    0    -1  
$EndComp
$Comp
L C C26
U 1 1 578462B7
P 9300 5850
F 0 "C26" H 9325 5950 50  0000 L CNN
F 1 "1uF" H 9325 5750 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 9338 5700 50  0001 C CNN
F 3 "" H 9300 5850 50  0000 C CNN
	1    9300 5850
	1    0    0    -1  
$EndComp
$Comp
L C C23
U 1 1 5784635D
P 5950 6000
F 0 "C23" H 5975 6100 50  0000 L CNN
F 1 "1uF" H 5975 5900 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 5988 5850 50  0001 C CNN
F 3 "" H 5950 6000 50  0000 C CNN
	1    5950 6000
	1    0    0    -1  
$EndComp
$Comp
L C C27
U 1 1 57846404
P 10700 6000
F 0 "C27" H 10725 6100 50  0000 L CNN
F 1 "1uF" H 10725 5900 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10738 5850 50  0001 C CNN
F 3 "" H 10700 6000 50  0000 C CNN
	1    10700 6000
	1    0    0    -1  
$EndComp
$Comp
L C C25
U 1 1 5784673C
P 8300 6000
F 0 "C25" H 8325 6100 50  0000 L CNN
F 1 "1uF" H 8325 5900 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 8338 5850 50  0001 C CNN
F 3 "" H 8300 6000 50  0000 C CNN
	1    8300 6000
	1    0    0    -1  
$EndComp
Text GLabel 4350 5700 0    60   Input ~ 0
GND
Text GLabel 6750 5700 0    60   Input ~ 0
GND
Text GLabel 9100 5700 0    60   Input ~ 0
GND
Wire Wire Line
	9100 5700 9300 5700
Wire Wire Line
	9300 6000 9450 6000
Wire Wire Line
	9450 6000 9450 6100
Wire Wire Line
	6750 5700 6950 5700
Wire Wire Line
	6950 6000 7100 6000
Wire Wire Line
	7100 6000 7100 6100
Wire Wire Line
	4550 6000 4750 6000
Wire Wire Line
	4750 6000 4750 6100
Wire Wire Line
	4550 5700 4350 5700
Wire Wire Line
	5800 5900 5800 5850
Wire Wire Line
	5800 5850 6100 5850
Wire Wire Line
	6100 5850 6100 5900
Wire Wire Line
	6100 5900 6150 5900
Connection ~ 5950 5850
Wire Wire Line
	5800 6100 5800 6150
Wire Wire Line
	5800 6150 6100 6150
Wire Wire Line
	6100 6150 6100 6100
Wire Wire Line
	6100 6100 6150 6100
Connection ~ 5950 6150
Wire Wire Line
	8150 5900 8150 5850
Wire Wire Line
	8150 5850 8450 5850
Wire Wire Line
	8450 5850 8450 5900
Wire Wire Line
	8450 5900 8500 5900
Connection ~ 8300 5850
Wire Wire Line
	8150 6100 8150 6150
Wire Wire Line
	8150 6150 8450 6150
Wire Wire Line
	8450 6150 8450 6100
Wire Wire Line
	8450 6100 8500 6100
Connection ~ 8300 6150
Wire Wire Line
	10550 5900 10550 5850
Wire Wire Line
	10550 5850 10850 5850
Wire Wire Line
	10850 5850 10850 5900
Wire Wire Line
	10850 5900 10900 5900
Connection ~ 10700 5850
Wire Wire Line
	10550 6100 10550 6150
Wire Wire Line
	10550 6150 10850 6150
Wire Wire Line
	10850 6150 10850 6100
Wire Wire Line
	10850 6100 10900 6100
Connection ~ 10700 6150
$Comp
L CONN_01X04 P19
U 1 1 57879A6B
P 2750 1600
F 0 "P19" H 2750 1850 50  0000 C CNN
F 1 "AIN45" V 2850 1600 50  0000 C CNN
F 2 "" H 2750 1600 50  0000 C CNN
F 3 "" H 2750 1600 50  0000 C CNN
	1    2750 1600
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P20
U 1 1 57879DC2
P 2750 1200
F 0 "P20" H 2750 1450 50  0000 C CNN
F 1 "AIN67" V 2850 1200 50  0000 C CNN
F 2 "" H 2750 1200 50  0000 C CNN
F 3 "" H 2750 1200 50  0000 C CNN
	1    2750 1200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P6
U 1 1 5787A0C5
P 1550 1600
F 0 "P6" H 1550 1850 50  0000 C CNN
F 1 "AIN01" V 1650 1600 50  0000 C CNN
F 2 "" H 1550 1600 50  0000 C CNN
F 3 "" H 1550 1600 50  0000 C CNN
	1    1550 1600
	1    0    0    1   
$EndComp
$Comp
L CONN_01X04 P7
U 1 1 5787A19D
P 1550 1200
F 0 "P7" H 1550 1450 50  0000 C CNN
F 1 "AIN23" V 1650 1200 50  0000 C CNN
F 2 "" H 1550 1200 50  0000 C CNN
F 3 "" H 1550 1200 50  0000 C CNN
	1    1550 1200
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P21
U 1 1 5787A49B
P 2750 2400
F 0 "P21" H 2750 2550 50  0000 C CNN
F 1 "GNDAIN" V 2850 2400 50  0000 C CNN
F 2 "" H 2750 2400 50  0000 C CNN
F 3 "" H 2750 2400 50  0000 C CNN
	1    2750 2400
	1    0    0    1   
$EndComp
$Comp
L CONN_01X02 P18
U 1 1 5787A728
P 1550 2400
F 0 "P18" H 1550 2550 50  0000 C CNN
F 1 "AUXAIN" V 1650 2400 50  0000 C CNN
F 2 "" H 1550 2400 50  0000 C CNN
F 3 "" H 1550 2400 50  0000 C CNN
	1    1550 2400
	1    0    0    1   
$EndComp
Text GLabel 1050 2300 0    60   Input ~ 0
AUXAIN+
Wire Wire Line
	2250 2300 2500 2300
Wire Wire Line
	2500 2300 2500 2350
Wire Wire Line
	2500 2350 2550 2350
Wire Wire Line
	2250 2500 2500 2500
Wire Wire Line
	2500 2500 2500 2450
Wire Wire Line
	2500 2450 2550 2450
Wire Wire Line
	1050 2500 1300 2500
Wire Wire Line
	1300 2500 1300 2450
Wire Wire Line
	1300 2450 1350 2450
Wire Wire Line
	1050 2300 1300 2300
Wire Wire Line
	1300 2300 1300 2350
Wire Wire Line
	1300 2350 1350 2350
Text GLabel 2250 3750 0    60   Input ~ 0
MISO
Text GLabel 2250 3950 0    60   Input ~ 0
MOSI
Text GLabel 3050 6300 3    60   Input ~ 0
MISO
Text GLabel 2950 6300 3    60   Input ~ 0
MOSI
Wire Wire Line
	2950 6300 2950 6200
Wire Wire Line
	3050 6300 3050 6200
Wire Wire Line
	4500 3000 4450 3000
$Comp
L AD7768 U?
U 1 1 57A27530
P 7900 3000
F 0 "U?" H 7900 3050 60  0000 C CNN
F 1 "AD7768" H 7850 2950 60  0000 C CNN
F 2 "" H 7900 3050 60  0000 C CNN
F 3 "" H 7900 3050 60  0000 C CNN
	1    7900 3000
	1    0    0    -1  
$EndComp
Text GLabel 6600 1950 1    60   Input ~ 0
DOUT4
Text GLabel 6800 1950 1    60   Input ~ 0
DOUT5
Text GLabel 7000 1950 1    60   Input ~ 0
DOUT6
Text GLabel 7200 1950 1    60   Input ~ 0
DOUT7
Text GLabel 9000 1950 1    60   Input ~ 0
GPIO4
Text GLabel 8200 1950 1    60   Input ~ 0
GPIO3
Wire Wire Line
	10600 1650 10600 2050
Wire Wire Line
	10400 1650 10400 2050
Wire Wire Line
	10200 1650 10200 2050
Wire Wire Line
	10000 1650 10000 2050
Wire Wire Line
	11000 1950 11000 2050
Wire Wire Line
	10800 1950 10800 2050
Wire Wire Line
	9800 1950 9800 2050
Wire Wire Line
	9600 1950 9600 2050
Wire Wire Line
	9400 1950 9400 2050
Wire Wire Line
	9200 1950 9200 2050
Wire Wire Line
	9000 1950 9000 2050
Wire Wire Line
	8800 1950 8800 2050
Wire Wire Line
	8600 1950 8600 2050
Wire Wire Line
	8400 1950 8400 2050
Wire Wire Line
	8200 1950 8200 2050
Wire Wire Line
	8000 1950 8000 2050
Wire Wire Line
	7800 1950 7800 2050
Wire Wire Line
	7600 1950 7600 2050
Wire Wire Line
	7400 1950 7400 2050
Wire Wire Line
	7200 1950 7200 2050
Wire Wire Line
	7000 1950 7000 2050
Wire Wire Line
	6800 1950 6800 2050
Wire Wire Line
	6600 1950 6600 2050
Wire Wire Line
	6400 1950 6400 2050
Wire Wire Line
	6200 1950 6200 2050
Wire Wire Line
	6000 1950 6000 2050
Wire Wire Line
	5800 1950 5800 2050
Wire Wire Line
	5600 1950 5600 2050
Wire Wire Line
	5400 1950 5400 2050
Wire Wire Line
	5200 1950 5200 2050
Wire Wire Line
	4800 1650 4800 2050
Wire Wire Line
	5000 1650 5000 2050
Wire Wire Line
	4800 4350 4800 3950
Wire Wire Line
	5000 4350 5000 3950
Wire Wire Line
	5200 4350 5200 3950
Wire Wire Line
	5400 4050 5400 3950
Wire Wire Line
	5600 4050 5600 3950
Wire Wire Line
	5800 4050 5800 3950
Wire Wire Line
	6000 4050 6000 3950
Wire Wire Line
	6200 4050 6200 3950
Wire Wire Line
	6400 4050 6400 3950
Wire Wire Line
	6600 4050 6600 3950
Wire Wire Line
	6800 4400 6800 3950
Wire Wire Line
	7000 4400 7000 3950
Wire Wire Line
	7200 4400 7200 3950
Wire Wire Line
	7400 4400 7400 3950
Wire Wire Line
	7600 4050 7600 3950
Wire Wire Line
	7800 4050 7800 3950
Wire Wire Line
	8000 4050 8000 3950
Wire Wire Line
	8200 4050 8200 3950
Wire Wire Line
	8400 4400 8400 3950
Wire Wire Line
	8600 4400 8600 3950
Wire Wire Line
	8800 4400 8800 3950
Wire Wire Line
	9000 4400 9000 3950
Wire Wire Line
	9200 4050 9200 3950
Wire Wire Line
	9400 4050 9400 3950
Wire Wire Line
	9800 4050 9800 3950
Wire Wire Line
	10000 4050 10000 3950
Wire Wire Line
	10200 4400 10200 3950
Wire Wire Line
	10400 3950 10400 4750
Wire Wire Line
	10600 4400 10600 3950
Wire Wire Line
	10800 4050 10800 3950
Wire Wire Line
	11000 4050 11000 3950
Text GLabel 9600 4050 3    60   Input ~ 0
PIN/SPI
Wire Wire Line
	9600 3950 9600 4050
$Comp
L C C?
U 1 1 57A30BD3
P 8500 4750
F 0 "C?" H 8525 4850 50  0000 L CNN
F 1 "1uF" H 8525 4650 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 8538 4600 50  0001 C CNN
F 3 "" H 8500 4750 50  0000 C CNN
	1    8500 4750
	0    -1   -1   0   
$EndComp
Connection ~ 8650 4550
$Comp
L C C?
U 1 1 57A31369
P 10550 4750
F 0 "C?" H 10575 4850 50  0000 L CNN
F 1 "1uF" H 10575 4650 50  0000 L CNN
F 2 "Capacitors_Tantalum_SMD:TantalC_SizeR_EIA-2012" H 10588 4600 50  0001 C CNN
F 3 "" H 10550 4750 50  0000 C CNN
	1    10550 4750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10700 4750 10700 4550
Connection ~ 10700 4750
Connection ~ 10400 4550
Text GLabel 3650 3100 0    60   Input ~ 0
DOUT4
Text GLabel 3650 3000 0    60   Input ~ 0
DOUT5
Text GLabel 3650 2900 0    60   Input ~ 0
DOUT6
Text GLabel 3650 2800 0    60   Input ~ 0
DOUT7
Text GLabel 3650 1750 0    60   Input ~ 0
GPIO4
Text GLabel 3650 6800 0    60   Input ~ 0
PIN/SPI
Text GLabel 3650 2150 0    60   Input ~ 0
GPIO3
Text GLabel 2750 7250 1    60   Input ~ 0
PIN/SPI
$EndSCHEMATC
