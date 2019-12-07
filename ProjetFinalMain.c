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

void vPrintLcdDeltaCharacters(void);
unsigned char ucReadMemoryI2C(unsigned char* ucpSequence, unsigned char* ucpStep, unsigned char ucArmIndex);
//void writeSequencesToMemoryI2C(void);			// only needed once when we'll fill up the memory

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************

// in "ProjectDefinitions.h"

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************

struct STArmState stCurrentArmState = { MIDDLE_POSITION,			// base starting position
																		MIDDLE_POSITION,			// shoulder starting position
																		MIDDLE_POSITION,			// elbow starting position
																		MIDDLE_POSITION,			// wrist starting position
																		MAXIMUM_POSITION };		// grip starting position (open)
struct STCompteur stCompteur = {0, 0, 0};
struct STTramePIC stTrame = {{{0xFF, 0xFF}, 0xFF, 0xFF}, 0xFF};		// default readings
unsigned char ucWeightType = NONE_WEIGHT;										// default to "no weight"
struct STKeyboardManualSettings stKeyboardManualSettings = {MOTOR_0, 5};	// defaultselected motor = base
																																			// and default manual speed is
																																			// set to an arbitrary value.
struct STSequenceStep stCurrentSequenceIndexes = {0, 0};				// this is to store the current sequence
																														// the arm is executing with two indexes:
																														// "sequence" and "step". It probably needs
																														// a better name... plz be charitable to the community much luv thx.

unsigned char* ucpConnectionStateString = LCD_DELTA_OFFLINE_VALUE;
																														// OffL/OnL. It's a variable storing the changes to print to the
																														// lcd in case we lose contact with the exterior... 

unsigned char ucLcdInitializationContent[4][21] = {	{"1:66 2:66 3:66 4:66 "},
																									{"5:66 X:FF Y:FF P:FF "},
																									{"B:FF Poid:Aucun     "},
																									{"05 seq:0 step:0 OffL"} };

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
		vInitTimer50ms();			// init the timer0
    vAfficheLCDComplet(ucLcdInitializationContent);					// initialize the content of the lcd
    vInitInterrupt();     // init interrupt on serial 0
		
		while(1)
		{
      
        if(ucIsOperating())		// the movements of the robot arm are automatic
        {
            if(ucIsTrameReceived())
            {
                stCurrentArmState.ucBase = ucReadMemoryI2C(&stCurrentSequenceIndexes.ucSequence, &stCurrentSequenceIndexes.ucStep, BASE);
                stCurrentArmState.ucShoulder = ucReadMemoryI2C(&stCurrentSequenceIndexes.ucSequence, &stCurrentSequenceIndexes.ucStep, SHOULDER);
                stCurrentArmState.ucElbow = ucReadMemoryI2C(&stCurrentSequenceIndexes.ucSequence, &stCurrentSequenceIndexes.ucStep, ELBOW);
                stCurrentArmState.ucWrist = ucReadMemoryI2C(&stCurrentSequenceIndexes.ucSequence, &stCurrentSequenceIndexes.ucStep, WRIST);
                stCurrentArmState.ucGrip = ucReadMemoryI2C(&stCurrentSequenceIndexes.ucSequence, &stCurrentSequenceIndexes.ucStep, GRIP);
            }
				}
				else							// the movements of the robot arm are manual; we need to read the keyboard
				{
						vHandleKey(ucpReadKeyboardI2C(), &stKeyboardManualSettings, &stCurrentArmState, &stCurrentSequenceIndexes);		// read the keyboard and update the variables accordingly
				}
				
				// ... gotta finish what happens next!
        if(TF0 == 1)
        {
            vUpdateCompteurTimer0(&stCompteur);
        }
        
        if(stCompteur.ucCompteur300ms > 5)
        {
            stCompteur.ucCompteur300ms = 0;
            ucpConnectionStateString = LCD_DELTA_OFFLINE_VALUE;
        }
        
        if(stCompteur.ucCompteur200ms > 3)
        {
            stCompteur.ucCompteur200ms = 0;
            vPrintLcdDeltaCharacters();
        }
        
        if(stCompteur.ucCompteur2sec > 39)
        {
            stCompteur.ucCompteur2sec = 0;
            vHandleSequence(&stTrame, &stCurrentSequenceIndexes, &ucWeightType);
        }
        
        if(ucIsTrameReceived())
        {
            stCompteur.ucCompteur300ms = 0;
            ucpConnectionStateString = LCD_DELTA_ONLINE_VALUE;
          
            vResetIsTrameReceived();
            vSendTrame(&stCurrentArmState);
        }
        
        vCircularBuffer(&stTrame);
		}
}

void vPrintLcdDeltaCharacters()
{
		vPrintLcdDeltaMotors(&stCurrentArmState);
		vPrintLcdDeltaTrame(&stTrame);
		vPrintLcdDeltaWeightType(&ucWeightType);
		vPrintLcdDeltaManualSettings(&stKeyboardManualSettings);
		vPrintLcdCurrentSequenceStep(&stCurrentSequenceIndexes);
		vPrintLcdDeltaConnectionState(ucpConnectionStateString);
}

unsigned char ucReadMemoryI2C(unsigned char* ucpSequence, unsigned char* ucpStep, unsigned char ucArmIndex)
{
    unsigned int uiMemoryAddress = ((((unsigned int)*ucpSequence) * 50) + (*ucpStep * 5) + ucArmIndex);
    return ucLireMemI2C(uiMemoryAddress);
}