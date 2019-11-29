/*****************************Contrôle Communication Série*******************************/
/* 
   Nom du fichier : RxTx232.c
   Auteur : Alain Champagne

Version 1.0 25-06-06
Date de modification :  09-11-09
 
D 
 
    Fonctions nécessaires pour la communication série de la carte Dallas. 
    
      
*****************************************************************************************/

//-------------- header files  -----------------
#include "ds89c450.h"				// Définition des bits et des registres du microcontrôleur
#include "RxTx232.h"



// *************************************************************************************************
void vInitPortSerie(void)
//   Auteur : Alain Champagne                  
//      Date de création : 22-06-06   
//   Description : Cette fonction initialise les SFRs pour permettre une communication série
//                 à 57600 bauds sans interruptions. La communication série utilise le timer
//                 1. On ne pourra donc pas utiliser ce timer lorsque la communication série 
//                 sera employée.
//          
//   Paramètres d'entrée : Aucun.
//   Paramètres de sortie : Aucun.                
//   Variables utilisées : Aucun.
//***************************************************************************************************
{
		SCON0 = 0x50;        	// Selectione mode 1, 8-bit avec reception      
		TMOD  = TMOD | 0x20; // timer 1, mode 2, 8-bit auto reload        
		TH1   = 0xFF;        // a 11.0592MHz: FA=4800,FD=9600,FE=14400 et FF=28800    
		PCON  = PCON | 0x80; // Le bit SMOD = 1 pour vitesse * 2 du port serie 
		TR1   = 1;           // Active le timer 1                          
		TI_0  = 1;           // Pour pouvoir envoyer un premier charactere    
}








