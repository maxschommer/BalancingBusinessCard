EESchema Schematic File Version 4
LIBS:BalancingBusinessCard-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 3
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
L Motor:Motor_DC M?
U 1 1 5BCBEB5F
P 4350 4400
F 0 "M?" V 4055 4350 50  0000 C CNN
F 1 "Motor_DC" V 4146 4350 50  0000 C CNN
F 2 "" H 4350 4310 50  0001 C CNN
F 3 "~" H 4350 4310 50  0001 C CNN
	1    4350 4400
	0    1    1    0   
$EndComp
$Comp
L Custom:AP1017AEN U?
U 1 1 5BCBEC9C
P 4300 3750
AR Path="/5BCBEC9C" Ref="U?"  Part="1" 
AR Path="/5BCB9C49/5BCBEC9C" Ref="U?"  Part="1" 
F 0 "U?" H 4300 4125 50  0000 C CNN
F 1 "AP1017AEN" H 4300 4034 50  0000 C CNN
F 2 "" H 4300 3750 50  0001 C CNN
F 3 "" H 4300 3750 50  0001 C CNN
	1    4300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 3900 3900 4400
Wire Wire Line
	3900 4400 4050 4400
Wire Wire Line
	4700 3900 4700 4400
Wire Wire Line
	4700 4400 4550 4400
Text HLabel 3900 4400 0    50   Input ~ 0
DIFF1
Text HLabel 4700 4400 2    50   Input ~ 0
DIFF2
Text HLabel 3900 3600 0    50   Input ~ 0
INA
Text HLabel 3900 3700 0    50   Input ~ 0
INB
$Comp
L power:+1V8 #PWR?
U 1 1 5BCBEF43
P 4800 3600
F 0 "#PWR?" H 4800 3450 50  0001 C CNN
F 1 "+1V8" H 4815 3773 50  0000 C CNN
F 2 "" H 4800 3600 50  0001 C CNN
F 3 "" H 4800 3600 50  0001 C CNN
	1    4800 3600
	1    0    0    -1  
$EndComp
$Comp
L power:+1V8 #PWR?
U 1 1 5BCBEF69
P 3550 3800
F 0 "#PWR?" H 3550 3650 50  0001 C CNN
F 1 "+1V8" H 3565 3973 50  0000 C CNN
F 2 "" H 3550 3800 50  0001 C CNN
F 3 "" H 3550 3800 50  0001 C CNN
	1    3550 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 3800 3900 3800
Wire Wire Line
	4700 3600 4800 3600
$EndSCHEMATC
