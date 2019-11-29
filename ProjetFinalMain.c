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

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

#define MINIMUM_POSITION	205
#define MIDDLE_POSITION		102
#define MAXIMUM_POSITION	0

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

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
struct ArmState currentArmState = { MIDDLE_POSITION,			// base starting position
																		MIDDLE_POSITION,			// shoulder starting position
																		MIDDLE_POSITION,			// elbow starting position
																		MIDDLE_POSITION,			// wrist starting position
																		MAXIMUM_POSITION };		// grip starting position (open)
unsigned char lcdContent[4][21] = {	{"1:66 2:66 3:66 4:66 "},
																		{"5:66 X:FF Y:FF P:FF "},
																		{"B:FF PILE:--        "},
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
		vInitPortSerie();
		vInitLCD();
		initTimer50ms();
		
		//manualMovingSpeed = 5;
		vAfficheLCDComplet(lcdContent);
		
		while(1)
		{
				
		}
}



// *************************************************************************************************
void initTimer50ms()
//
//  Auteur: John-William Lebel
//
//  Description: Initialize a timer that overflows every 50 milliseconds
//  Paramètres d'entrées 	: Aucun
//  Paramètres de sortie 	: Aucun
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		TMOD = TMOD & 0xF0;           // Timer0, internal, no control
		TMOD = TMOD | 0x01;           // external pin, 16 bits counter
		TL0 = 0x00;                   // overflows every milliseconds
		TH0 = 0x4C;                   // 
		TR0 = 1;                      // Start the timer
}



