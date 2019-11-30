/**************************************************************************************************
Nom du fichier: ProjetFinalMain.c
Auteur: John-William Lebel
Date de création: 2019-11-26

Versions:
0.1 -> Code base

***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	

#include "ds89c450.h"				// Définition des bits et des registres du microcontrôleur
#include <stdio.h>          // Prototype de declarations des fonctions I/O	
#include "I2C.h"						// I2C functions handling
#include "RxTx232.h"				// RxTx232 functions handling
#include "LCD.h"						// LCD functions handling
#include "Timer0.h"					// Timer0 initialization handling
#include "TypeConversion.h"	// Fonctions useful when it comes to converting values between type representations and/or types

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

#define MINIMUM_POSITION 205
#define MIDDLE_POSITION 102
#define MAXIMUM_POSITION 0

#define BASE		 0
#define SHOULDER 1
#define ELBOW		 2
#define WRIST		 3
#define GRIP		 4

#define MOTOR_0 0
#define MOTOR_1 1
#define MOTOR_2 2
#define MOTOR_3 3
#define MOTOR_4 4

#define BLUE_WEIGHT	 0
#define GREEN_WEIGHT 1
#define RED_WEIGHT	 2
#define NONE_WEIGHT	 3

#define LCD_DELTA_ONLINE_VALUE	"nL "		// used with the connectionStateString[] array
#define LCD_DELTA_OFFLINE_VALUE	"ffL"		// to display on the LCD. The 'O' is always there
																				// so there's no need to store it explicitely.

#define LCD_LINE0 0
#define LCD_LINE1 1
#define LCD_LINE2 2
#define LCD_LINE3 3

#define LCD_MOTOR_0_DIGIT_POSITION_0 2
#define LCD_MOTOR_0_DIGIT_POSITION_1 3

#define LCD_MOTOR_1_DIGIT_POSITION_0 7
#define LCD_MOTOR_1_DIGIT_POSITION_1 8

#define LCD_MOTOR_2_DIGIT_POSITION_0 12
#define LCD_MOTOR_2_DIGIT_POSITION_1 13

#define LCD_MOTOR_3_DIGIT_POSITION_0 17
#define LCD_MOTOR_3_DIGIT_POSITION_1 18

#define LCD_MOTOR_4_DIGIT_POSITION_0 2
#define LCD_MOTOR_4_DIGIT_POSITION_1 3

#define LCD_TOUCH_SCREEN_X_DIGIT_POSITION_0 7
#define LCD_TOUCH_SCREEN_X_DIGIT_POSITION_1 8

#define LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_0 12
#define LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_1 13

#define LCD_GRIP_INTENSITY_DIGIT_POSITION_0 17
#define LCD_GRIP_INTENSITY_DIGIT_POSITION_1 18

#define LCD_WEIGHT_SENSOR_DIGIT_POSITION_0 2
#define LCD_WEIGHT_SENSOR_DIGIT_POSITION_1 3

#define LCD_WEIGHT_TYPE_DIGIT_POSITION_0 10
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_1 11
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_2 12
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_3 13
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_4 14

#define LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_0 0
#define LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_1 1

#define LCD_SEQ_DIGIT_POSITION	7
#define LCD_STEP_DIGIT_POSITION 14

#define LCD_CONNECTION_STATE_DIGIT_POSITION_0 17
#define LCD_CONNECTION_STATE_DIGIT_POSITION_1 18
#define LCD_CONNECTION_STATE_DIGIT_POSITION_2 19

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************


// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************
struct ArmState
{
		unsigned char base;
		unsigned char shoulder;
		unsigned char elbow;
		unsigned char wrist;
		unsigned char grip;
};

struct TouchScreen
{
		unsigned char x;
		unsigned char y;
};

struct AdcSensors
{
		struct TouchScreen touchScreen;
		unsigned char gripIntensity;
		unsigned char weightSensor;
};

struct SequenceStep
{
		unsigned char sequence;
		unsigned char step;
};

struct KeyboardManualSettings
{
		unsigned char manualySelectedMotor;
		unsigned char manualMovingSpeed;
};

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
struct ArmState currentArmState = { MIDDLE_POSITION,			// base starting position
																		MIDDLE_POSITION,			// shoulder starting position
																		MIDDLE_POSITION,			// elbow starting position
																		MIDDLE_POSITION,			// wrist starting position
																		MAXIMUM_POSITION };		// grip starting position (open)

struct AdcSensors sensors = {{0xFF, 0xFF}, 0xFF, 0xFF};		// default readings
unsigned char weightType = NONE_WEIGHT;										// default to "no weight"
struct KeyboardManualSettings keyboardManualSettings = {MOTOR_0, 5};	// defaultselected motor = base
																																			// and default manual speed is
																																			// set to an arbitrary value.
struct SequenceStep currentSequenceIndexes = {0, 0};				// this is to store the current sequence
																														// the arm is executing with two indexes:
																														// "sequence" and "step". It probably needs
																														// a better name... plz be charitable to the community much luv thx.

unsigned char connectionStateString[4] = LCD_DELTA_OFFLINE_VALUE;
																														// OffL/OnL. It's a variable storing the changes to print to the
																														// lcd in case we lose contact with the exterior... 

unsigned char isOperating = 0;															// variable that tells if we're in manual or automatic funtionning
																														// of the robotic arm.

unsigned char lcdInitializationContent[4][21] = {	{"1:66 2:66 3:66 4:66 "},
																									{"5:66 X:FF Y:FF P:FF "},
																									{"B:FF POID:--        "},
																									{"05 seq:0 step:0 OffL"} };

unsigned char xdata sequences[7][10][5] = { { {0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },

																						{	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },

																						{	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },

																						{	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },

																						{	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },

																						{	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },

																						{	{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
																							{0xFF, 0xFF, 0xFF, 0xFF, 0xFF} } };

// *************************************************************************************************
// VARIABLES LOCALES
// *************************************************************************************************


// *************************************************************************************************
void main(void)
//
//  Auteur: John-William Lebel
//
//  Description: Appelé lorsque le programme démarre
//  Paramètres d'entrées 	: Aucun
//  Paramètres de sortie 	: Aucun
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		unsigned char keyboardCharacter;	// just a little buffer for the keyboard
		vInitPortSerie();			// init the serial port to utilize the RxTx232 comunication with the pic16F88
		vInitLCD();						// init the lcd
		writeSequencesToMemoryI2C();	// that function might be misimplemented... gotta look into how to write 350 values to the I2C memory in an optimized fashion
		initTimer50ms();			// init the timer0
		vAfficheLCDComplet(lcdInitializationContent);					// initialize the content of the lcd
		
		while(1)
		{
				if(isOperating)		// the movements of the robot arm are automatic
				{
						currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, BASE);
						currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, SHOULDER);
						currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, ELBOW);
						currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, WRIST);
						currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, GRIP);
				}
				else							// the movements of the robot arm are manual; we need to read the keyboard
				{
						keyboardCharacter = readKeyboardI2C();		// read the keyboard and put the character in a variable
						if(keyboardCharacter != ' ')							// if we read a character
						{
								handleKey(keyboardCharacter);					// handle the character and update the global variables accordignly
						}
				}
				
				if(isBufferFull)															// if the circular buffer has sent a whole sequence of 8 valid bytes
				{
																											// update the global variables accordingly
				}
				
				// ... gotta finish what happens next!
		}
}

void printLcdDeltaCharacters()
{
		printLcdDeltaMotors();
		printLcdDeltaSensors();
		printLcdDeltaWeightType();
		printLcdDeltaManualSettings();
		printLcdCurrentSequenceStep();
		printLcdDeltaConnectionState();
}

void printLcdDeltaMotors()
{
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.base, 0), LCD_LINE0, LCD_MOTOR_0_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.base, 1), LCD_LINE0, LCD_MOTOR_0_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.shoulder, 0), LCD_LINE0, LCD_MOTOR_1_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.shoulder, 1), LCD_LINE0, LCD_MOTOR_1_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.elbow, 0), LCD_LINE0, LCD_MOTOR_2_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.elbow, 1), LCD_LINE0, LCD_MOTOR_2_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.wrist, 0), LCD_LINE0, LCD_MOTOR_3_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.wrist, 1), LCD_LINE0, LCD_MOTOR_3_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.grip, 0), LCD_LINE1, LCD_MOTOR_4_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(currentArmState.grip, 1), LCD_LINE1, LCD_MOTOR_4_DIGIT_POSITION_1);
}

void printLcdDeltaSensors()
{
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.touchScreen.x, 0), LCD_LINE1, LCD_TOUCH_SCREEN_X_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.touchScreen.x, 1), LCD_LINE1, LCD_TOUCH_SCREEN_X_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.touchScreen.y, 0), LCD_LINE1, LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.touchScreen.y, 1), LCD_LINE1, LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.gripIntensity, 0), LCD_LINE1, LCD_GRIP_INTENSITY_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.gripIntensity, 1), LCD_LINE1, LCD_GRIP_INTENSITY_DIGIT_POSITION_1);
		
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.weightSensor, 0), LCD_LINE2, LCD_WEIGHT_SENSOR_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(sensors.weightSensor, 1), LCD_LINE2, LCD_WEIGHT_SENSOR_DIGIT_POSITION_1);
}

void printLcdDeltaWeightType()
{
		vLcdEcrireCaract(weightTypeToString(&weightType)[0], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_0);
		vLcdEcrireCaract(weightTypeToString(&weightType)[1], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_1);
		vLcdEcrireCaract(weightTypeToString(&weightType)[2], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_2);
		vLcdEcrireCaract(weightTypeToString(&weightType)[3], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_3);
		vLcdEcrireCaract(weightTypeToString(&weightType)[4], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_4);
}

void printLcdDeltaManualSettings()
{
		vLcdEcrireCaract(unsignedCharToDecimal(keyboardManualSettings.manualMovingSpeed, 0), LCD_LINE3, LCD_MANUALY_SELECTED_MOTOR_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToDecimal(keyboardManualSettings.manualMovingSpeed, 0), LCD_LINE3, LCD_MANUALY_SELECTED_MOTOR_DIGIT_POSITION_1);
}

void printLcdCurrentSequenceStep()
{
		vLcdEcrireCaract(currentSequenceIndexes.sequence, LCD_LINE3, LCD_SEQ_DIGIT_POSITION);
		vLcdEcrireCaract(currentSequenceIndexes.step, LCD_LINE3, LCD_STEP_DIGIT_POSITION);
}

void printLcdDeltaConnectionState()
{
		vLcdEcrireCaract(connectionStateString[0], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_0);
		vLcdEcrireCaract(connectionStateString[1], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_1);
		vLcdEcrireCaract(connectionStateString[2], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_2);
}

void writeSequencesToMemoryI2C()
{
	writeMemoryI2C(sequences);
}