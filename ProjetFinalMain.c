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

#include "_DS89C450Modifie.h"				// Définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"
#include <stdio.h>          // Prototype de declarations des fonctions I/O	
#include "I2C.h"						// I2C functions handling
#include "RxTx232.h"				// RxTx232 functions handling
#include "LCD.h"						// LCD functions handling
#include "Timer0.h"					// Timer0 initialization handling
#include "TypeConversion.h"	// Fonctions useful when it comes to converting values between type representations and/or types
#include "ProjectDefinitions.h"
#include "SubOptimizedLcdPrinter.h"
#include "KeyboardI2C.h"
#include "CircularBuffer_RxTx.h"
#include "SequenceHandler.h"

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

// in "ProjectDefinitions.h"

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************

void printLcdDeltaCharacters(void);
unsigned char readMemoryI2C(unsigned char* sequence, unsigned char* step, unsigned char armIndex);
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

struct Compteur stCompteur = {0, 0, 0};

struct TramePIC trame = {{{0xFF, 0xFF}, 0xFF, 0xFF}, 0xFF};		// default readings
unsigned char weightType = NONE_WEIGHT;										// default to "no weight"
struct KeyboardManualSettings keyboardManualSettings = {MOTOR_0, 5};	// defaultselected motor = base
																																			// and default manual speed is
																																			// set to an arbitrary value.
struct SequenceStep currentSequenceIndexes = {0, 0};				// this is to store the current sequence
																														// the arm is executing with two indexes:
																														// "sequence" and "step". It probably needs
																														// a better name... plz be charitable to the community much luv thx.

unsigned char* connectionStateString = LCD_DELTA_OFFLINE_VALUE;
																														// OffL/OnL. It's a variable storing the changes to print to the
																														// lcd in case we lose contact with the exterior... 

unsigned char lcdInitializationContent[4][21] = {	{"1:66 2:66 3:66 4:66 "},
																									{"5:66 X:FF Y:FF P:FF "},
																									{"B:FF Poid:Aucun     "},
																									{"05 seq:0 step:0 OffL"} };

			// that stupid and massive array might be useful to fill up the I2C memory... just a thought
unsigned char xdata sequences[7][10][5] = { { {0x0C, 0x4C, 0x1C, 0x51, 0x00},
																							{0x0C, 0x73, 0x1C, 0x51, 0x00},
																							{0x0C, 0x78, 0x23, 0x51, 0x00},
																							{0x0C, 0x78, 0x23, 0x51, 0xFF}, // position A6 sur le touchscreen
																							{0x0C, 0x78, 0x23, 0x51, 0xFF},
																							{0x0C, 0x78, 0x23, 0x51, 0xFF},
																							{0x0C, 0x78, 0x23, 0x51, 0xFF},
																							{0x0C, 0x78, 0x23, 0x51, 0xFF},
																							{0x0C, 0x78, 0x23, 0x51, 0xFF},
																							{0x0C, 0x78, 0x23, 0x51, 0xFF} }, 

																						{ {0x11, 0x4C, 0x05, 0x4D, 0x00},
																							{0x11, 0x5E, 0x00, 0x4D, 0x00},
																							{0x11, 0x69, 0x0C, 0x4D, 0x00},
																							{0x11, 0x69, 0x0C, 0x4D, 0xFF}, // position B2 sur le touchscreen
																							{0x11, 0x69, 0x0C, 0x4D, 0xFF},
																							{0x11, 0x69, 0x0C, 0x4D, 0xFF},
																							{0x11, 0x69, 0x0C, 0x4D, 0xFF},
																							{0x11, 0x69, 0x0C, 0x4D, 0xFF},
																							{0x11, 0x69, 0x0C, 0x4D, 0xFF},
                                              {0x11, 0x69, 0x0C, 0x4D, 0xFF} },

																						{ {0x15, 0x4C, 0x13, 0x51, 0x00},
																							{0x15, 0x6B, 0x13, 0x51, 0x00},
																							{0x15, 0x75, 0x1E, 0x51, 0x00},
																							{0x15, 0x75, 0x1E, 0x51, 0xFF}, // position C5 sur le touchscreen
																							{0x15, 0x75, 0x1E, 0x51, 0xFF},
																							{0x15, 0x75, 0x1E, 0x51, 0xFF},
																							{0x15, 0x75, 0x1E, 0x51, 0xFF},
																							{0x15, 0x75, 0x1E, 0x51, 0xFF},
																							{0x15, 0x75, 0x1E, 0x51, 0xFF},
                                              {0x15, 0x75, 0x1E, 0x51, 0xFF} },

																						{	{0x0B, 0x64, 0x4A, 0x66, 0xFF},
																							{0x0B, 0x81, 0x39, 0x66, 0xFF},
																							{0x0B, 0x81, 0x39, 0x66, 0x00}, // position balance
																							{0x0B, 0x81, 0x39, 0x66, 0x00},
																							{0x0B, 0x81, 0x39, 0x66, 0x00},
																							{0x0B, 0x81, 0x39, 0x66, 0x00},
																							{0x0B, 0x81, 0x39, 0x66, 0x00},
																							{0x0B, 0x81, 0x39, 0x66, 0x00},
																							{0x0B, 0x81, 0x39, 0x66, 0x00},
																							{0x0B, 0x81, 0x39, 0x66, 0x00} }, // position balance PINCE RELÂCHÉE (on fait comment pour prendre des mesures sinon)

																						{	{0x0B, 0x81, 0x39, 0x66, 0xFF}, // position balance (pince fermée)
																							{0x20, 0x60, 0x37, 0x5C, 0xFF},
																							{0x20, 0x82, 0x37, 0x5C, 0xFF},
																							{0x20, 0x82, 0x37, 0x5C, 0x00}, // position bleu (AA)
																							{0x20, 0x4C, 0x37, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00}, // position DE REPOS 
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00} },
                                            
																						{	{0x0B, 0x81, 0x39, 0x66, 0xFF}, // position balance (pince fermée)
																							{0x1C, 0x60, 0x31, 0x5C, 0xFF},
																							{0x1C, 0x7E, 0x31, 0x5C, 0xFF},
																							{0x1C, 0x7E, 0x31, 0x5C, 0x00}, // position vert (C)
																							{0x1C, 0x4C, 0x31, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00}, // position DE REPOS
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00} },

																						{	{0x0B, 0x81, 0x39, 0x66, 0xFF}, // position balance (pince fermée)
																							{0x18, 0x60, 0x2D, 0x5C, 0xFF},
																							{0x18, 0x7C, 0x2D, 0x5C, 0xFF},
																							{0x18, 0x7C, 0x2D, 0x5C, 0x00}, // position rouge (9V)
																							{0x18, 0x4C, 0x2D, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00}, // position DE REPOS
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00},
																							{0x10, 0x4C, 0x00, 0xA0, 0x00} } };

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
		initTimer50ms();			// init the timer0
    vAfficheLCDComplet(lcdInitializationContent);					// initialize the content of the lcd
    vInitInterrupt();     // init interrupt on serial 0
		
		while(1)
		{
      
        if(isOperating())		// the movements of the robot arm are automatic
        {
            if(isTrameReceived())
            {
                currentArmState.base = readMemoryI2C(&currentSequenceIndexes.sequence, &currentSequenceIndexes.step, BASE);
                currentArmState.shoulder = readMemoryI2C(&currentSequenceIndexes.sequence, &currentSequenceIndexes.step, SHOULDER);
                currentArmState.elbow = readMemoryI2C(&currentSequenceIndexes.sequence, &currentSequenceIndexes.step, ELBOW);
                currentArmState.wrist = readMemoryI2C(&currentSequenceIndexes.sequence, &currentSequenceIndexes.step, WRIST);
                currentArmState.grip = readMemoryI2C(&currentSequenceIndexes.sequence, &currentSequenceIndexes.step, GRIP);
            }
				}
				else							// the movements of the robot arm are manual; we need to read the keyboard
				{
						handleKey(readKeyboardI2C(), &keyboardManualSettings, &currentArmState, &currentSequenceIndexes);		// read the keyboard and update the variables accordingly
				}
				
				// ... gotta finish what happens next!
        if(TF0 == 1)
        {
            vUpdateCompteurTimer0(&stCompteur);
        }
        
        if(stCompteur.ucCompteur300ms > 5)
        {
            stCompteur.ucCompteur300ms = 0;
            connectionStateString = LCD_DELTA_OFFLINE_VALUE;
        }
        
        if(stCompteur.ucCompteur200ms > 3)
        {
            stCompteur.ucCompteur200ms = 0;
            printLcdDeltaCharacters();
        }
        
        if(stCompteur.ucCompteur2sec > 39)
        {
            stCompteur.ucCompteur2sec = 0;
            handleSequence(&trame, &currentSequenceIndexes, &weightType);
        }
        
        if(isTrameReceived())
        {
            stCompteur.ucCompteur300ms = 0;
            connectionStateString = LCD_DELTA_ONLINE_VALUE;
          
            resetIsTrameReceived();
            vSendTrame(&currentArmState);
        }
        
        vCircularBuffer(&trame);
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

unsigned char readMemoryI2C(unsigned char* sequence, unsigned char* step, unsigned char armIndex)
{
    unsigned int memoryAddress = ((((unsigned int)*sequence) * 50) + (*step * 5) + armIndex);
    return ucLireMemI2C(memoryAddress);
}