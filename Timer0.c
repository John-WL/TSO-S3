/*****************************Timer0 handling*******************************/
/*
		Nom du fichier: Timer0.c
		Auteur : John-William Lebel

		Date de création: 2019-11-29

    Fonction(s) nécessaire(s) pour gérer le timer0


*****************************************************************************************/

//-------------- header files  -----------------
#include "_DS89C450Modifie.h"				// Définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"
#include "Timer0.h"
#include "ProjectDefinitions.h"

  

// *************************************************************************************************
void vInitTimer50ms(void)
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

void vUpdateCompteurTimer0(struct STCompteur* stpCompteur)
{
  TF0 = 0;
  stpCompteur->ucCompteur300ms++;
  stpCompteur->ucCompteur200ms++;
  stpCompteur->ucCompteur2sec++;
}