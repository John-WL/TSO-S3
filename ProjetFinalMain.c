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
//#include "MemoryI2C.h"
#include "ProjectDefinitions.h"
#include "SubOptimizedLcdPrinter.h"
#include "KeyboardI2C.h"

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

// in "ProjectDefinitions.h"

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************

void printLcdDeltaCharacters(void);
//void writeSequencesToMemoryI2C(void);			// only needed once when we'll fill up the memory

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************

// in "ProjectDefinitions.h"

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
struct ArmState currentArmState = { MIDDLE_POSITION,			// base starting position
																		MIDDLE_POSITION,			// shoulder starting position
																		MIDDLE_POSITION,			// elbow starting position
																		MIDDLE_POSITION,			// wrist starting position
																		MAXIMUM_POSITION };		// grip starting position (open)

struct TramePIC trame = {{{0xFF, 0xFF}, 0xFF, 0xFF}, 0xFF};		// default readings
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
																									{"B:FF Poid:Aucun     "},
																									{"05 seq:0 step:0 OffL"} };

			// that stupid and massive array might be useful to fill up the I2C memory... just a thought
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
		vInitPortSerie();			// init the serial port to utilize the RxTx232 comunication with the pic16F88
		vInitLCD();						// init the lcd
		//writeSequencesToMemoryI2C();	// that function might be misimplemented... gotta look into how to write 350 values to the I2C memory in an optimized fashion
		initTimer50ms();			// init the timer0
		vAfficheLCDComplet(lcdInitializationContent);					// initialize the content of the lcd
		
		while(1)
		{
        printLcdDeltaCharacters();
				if(isOperating)		// the movements of the robot arm are automatic
				{
						//currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, BASE);
						//currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, SHOULDER);
						//currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, ELBOW);
						//currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, WRIST);
						//currentArmState.base = readMemoryI2C(currentSequenceIndexes.sequence, currentSequenceIndexes.step, GRIP);
				}
				else							// the movements of the robot arm are manual; we need to read the keyboard
				{
						handleKey(readKeyboardI2C(), &keyboardManualSettings, &currentArmState);					// read the keyboard and update the variables accordingly
				}
				
				//if(isBufferFull)															// if the circular buffer has sent a whole sequence of 8 valid bytes
				{
																											// update the global variables accordingly
				}
				
				// ... gotta finish what happens next!
		}
}

void printLcdDeltaCharacters()
{
		printLcdDeltaMotors(&currentArmState);
		printLcdDeltaTrame(&trame);
		printLcdDeltaWeightType(&weightType);
		printLcdDeltaManualSettings(&keyboardManualSettings);
		printLcdCurrentSequenceStep(&currentSequenceIndexes);
		printLcdDeltaConnectionState(connectionStateString);
}

//void writeSequencesToMemoryI2C()
//{
	//writeMemoryI2C(sequences);
//}