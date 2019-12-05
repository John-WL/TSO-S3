/****************************************************************************************
   Nom du fichier : I2C.h
   Auteur : Hugo Pellerin                  
      Date de creation : 30-08-2019
        Fichier de declaration et de definition pour les fonctions de traitement du 
        I2C.
  
****************************************************************************************/
#include "_DeclarationGenerale.h"
#ifndef I2C_H
  #define I2C_H


// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************
//Definitions de parametres. 

#define SDA P1_4
#define SCL P1_5
 
// *************************************************************************************************
//  LES PReDeCLARATIONS DES FONCTIONS
// *************************************************************************************************




  
// *************************************************************************************************
//  Auteur: Hugo Pellerin
//  Date de creation :  30-08-2019
//
//  Description: provoque un "start-condition" I2C sur les lignes SDA et SCL
//  Parametres d'entrees : Aucun
//  Parametres de sortie : Aucun
//  Notes     		 	 : Aucune
//
void vStartBitI2C();
// *************************************************************************************************

// *************************************************************************************************
//  Auteur: Hugo Pellerin	
//  Date de creation :  30-08-2019
//
//  Description: provoque un "stop-condition" I2C sur les lignes SDA et SCL
//  Parametres d'entrees : Aucun
//  Parametres de sortie : Aucun
//  Notes     		 : Aucune
//
void vStopBitI2C();
// *************************************************************************************************

// *************************************************************************************************
//	Auteur : Hugo Pellerin		
//      Date de creation : 30-08-2019				      
//	Description : 	Routine de reception de 8 bits de donnee 
//			provenant d'une communication I2C.
//
//
//	Parametres d'entree : 	Valeur du ack voulu (0x00 = 0 et 0xFF = 1).		
//	Parametres de sortie : 	Byte recu.		
//
unsigned char ucLire8BitsI2C(UC ucAck);
// *************************************************************************************************



// *************************************************************************************************
//  Auteur: Hugo Pellerin	
//  Date de creation :  30-08-2019
//  
//
//  Description: Routine de reception de 8 bits de donnees en I2C.
//  Parametres d'entrees : Octet que l'on veut envoyer
//  Notes     		 			 : Aucune
//
unsigned char ucEcrire8BitsI2C(UC ucTxData);
// *************************************************************************************************



// *************************************************************************************************
// Auteur : Hugo Pellerin		     Date de creation : 30-08-2019				      
//
// Description  : Fonction de reception d'un octet de donnee provenant de la
//                memoire I2C. Si le circuit ne repond pas, on l'indique
//                e l'ecran.  
// Parametres d'entree :  uiAdr (adresse oe l'on veut lire)		
// Parametres de sortie : ucData (Valeur lue)		
// 					
//
UC ucLireMemI2C(UI uiAdr);
// *************************************************************************************************



// *************************************************************************************************
// Auteur : Hugo Pellerin	           Date de creation : 30-08-2019				      
//
// Description :  Fonction de transmission d'un octet de donnee 
//                provenant de la memoire I2C.
//							
		
// Parametres d'entree :  ucData - Octet e ecrire
//												uiAdr - Addresse oe l'on veut ecrire dans la memoire.		
// Parametres de sortie : Aucun		
// 						
void vEcrireMemI2C(UC ucData, UI uiAdr);
// *************************************************************************************************


#endif 















