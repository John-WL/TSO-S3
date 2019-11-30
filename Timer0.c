/*****************************Timer0 handling*******************************/
/*
		Nom du fichier: Timer0.c
		Auteur : John-William Lebel

		Date de cr�ation: 2019-11-29

    Fonction(s) n�cessaire(s) pour g�rer le timer0


*****************************************************************************************/

//-------------- header files  -----------------
#include "ds89c450.h"				// D�finition des bits et des registres du microcontr�leur
#include "Timer0.h"


// *************************************************************************************************
void initTimer50ms(void)
//
//  Auteur: John-William Lebel
//
//  Description: Initialize a timer that overflows every 50 milliseconds
//  Param�tres d'entr�es 	: Aucun
//  Param�tres de sortie 	: Aucun
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