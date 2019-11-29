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

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

#define MINIMUM_POSITION	205
#define MIDDLE_POSITION		102
#define MAXIMUM_POSITION	0

#define BASE							0
#define SHOULDER					1
#define ELBOW							2
#define WRIST							3
#define GRIP							4

#define BLUE_WEIGHT				0
#define GREEN_WEIGHT			1
#define RED_WEIGHT				2

#define LCD_DELTA_ONLINE_VALUE	"nL "
#define LCD_DELTA_OFFLINE_VALUE	"ffL"

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
}

struct AdcSensors
{
		unsigned char gripIntensity;
		unsigned char weightSensor;
}

struct SequenceStep
{
		unsigned char sequence;
		unsigned char step;
};

struct keyboardManualSettings
{
		unsigned char manualySelectedMotor;
		unsigned char manualMovingSpeed;
}

struct ProgramValues
{
		struct ArmState currentArmState;
		struct TouchScreen touchScreen;
		struct AdcSensors sensors;
		unsigned char weightType;
		struct SequenceStep currentSequenceIndexes;
		unsigned char connectionState[4];
};

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
struct ArmState currentArmState = { MIDDLE_POSITION,			// base starting position
																		MIDDLE_POSITION,			// shoulder starting position
																		MIDDLE_POSITION,			// elbow starting position
																		MIDDLE_POSITION,			// wrist starting position
																		MAXIMUM_POSITION };		// grip starting position (open)
struct TouchScreen touchScreen;
struct AdcSensors sensors;
unsigned char weightType;
struct KeyboardManualSettings keyboardManualSettings;
struct SequenceStep currentSequenceIndexes = {0, 0};
unsigned char connectionState[4];

unsigned char lcdContent[4][21] = {	{"1:66 2:66 3:66 4:66 "},
																		{"5:66 X:FF Y:FF P:FF "},
																		{"B:FF POID:--        "},
																		{"05 seq:0 step:0 OffL"} };
unsigned char manualMovingSpeed;

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
		unsigned char keyboardCharacter;
		vInitPortSerie();
		vInitLCD();
		initTimer50ms();
		
		manualMovingSpeed = 5;
		vAfficheLCDComplet(lcdContent);
		
		while(1)
		{
				if(isOperating)
				{
						currentArmState.base = sequences[currentSequenceIndexes.sequence][currentSequenceIndexes.step][BASE];
						currentArmState.base = sequences[currentSequenceIndexes.sequence][currentSequenceIndexes.step][SHOULDER];
						currentArmState.base = sequences[currentSequenceIndexes.sequence][currentSequenceIndexes.step][ELBOW];
						currentArmState.base = sequences[currentSequenceIndexes.sequence][currentSequenceIndexes.step][WRIST];
						currentArmState.base = sequences[currentSequenceIndexes.sequence][currentSequenceIndexes.step][GRIP];
				}
				else
				{
						keyboardCharacter = readKeyboardI2c();
						if(keyboardCharacter != ' ')
						{
								handleKey(keyboardCharacter);
						}
				}
				
				if(isBufferFull)
				{
						
				}
		}
}

void printLcdDeltaCharacters()
{
		static unsigned char lcdDeltaValues[30] = {};
		for
		vLcdEcrireCaract()
}

unsigned char unsignedCharToHex(unsigned char numberToEvaluate, unsigned char digitIndex)
{
		
}
