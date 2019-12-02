/**************************************************************************************************
Nom du fichier : I2C.c
Auteur : Stéphane Deschênes                  
Date de création : 01-09-2019
Version 1.0
	 
	Contient les fonctions I2C
			
***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include "ds89c450.h"				// Définition des bits et des registres du microcontrôleur
#include "I2C.h"
#include <stdio.h>          // Prototype de declarations des fonctions I/O


// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

/* VIDE */

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************
void vI2CDelai(unsigned int tmp);
void vEcrire1BitI2C(unsigned char ucBitOut);
unsigned char ucLire1BitI2C(void);


// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************
/* VIDE */

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
/* VIDE */

// *************************************************************************************************
// VARIABLES LOCALES
// *************************************************************************************************
/* VIDE */



//********************************vDelaiI2C*****************************
//	Nom de la fonction : vDelaiI2C
//	Auteur : Alain Champagne		
//       Date de création : 30-05-2007				      
//	Description : 	Routine de délai pour la communication I2C. 
//							
//	Fonctions appelées : 	Aucune		
//	Paramètres d'entrée : 	Aucun		
//  Paramètres de sortie : 	Aucun		
//	Variables utilisées : 	Aucune
//	Equate : 		Aucun	
//	#Define : 		Aucun	
// 						
//**********************************************************************
void vI2CDelai (unsigned int tmp)
{   
	while (tmp>0)
  {
		tmp--;
	}   
}


//*********************************************************************
void vI2CStartBit(void)			
//	Auteur : Alain Champagne		
//  Date de création : 30-05-2007				      
//	Description : 	Fonction qui effectue un start bit avec les lignes SDA et SCL 
//		
//	Paramètres d'entrée : 	Aucun		
//	Paramètres de sortie : 	Aucun		
//	Notes: Passage de 1 à 0 de la ligne SDA durant un niveau haut de SCL
//**********************************************************************
{
  SDA = 1;			 			
	vI2CDelai (dDelai);	
	SCL = 1;						
  vI2CDelai (dDelai);
  SDA = 0;						
  vI2CDelai (dDelai);	
  SCL = 0;						
  vI2CDelai(dDelai);	
}


//**********************************************************************
void vI2CStopBit(void)
//	Auteur : Alain Champagne		
//       Date de création : 30-05-2007				      
//	Description : 	Routine de clôture d'une communication série
//			I2C. Doit être appelée à la fin de toutes 
//			opérations.
//
//	Paramètres d'entrée : 	Aucun		
//	Paramètres de sortie : 	Aucun		
//	Variables utilisées : 	Aucune
// 						
//**********************************************************************
{
	//Passage de 0 à 1 sur la ligne SDA durant
	//un niveau 1 sur la ligne SCL initie un 
	//STOP BIT.
  SDA = 0;			  		// Donnée à zéro et
  SCL = 0;						// clock aussi.
  vI2CDelai (dDelai);	// Légère attente.
  SCL = 1;						// SCL à 1.
  vI2CDelai (dDelai);	// Légère attente.
  SDA = 1;						// SDA à 1.
  vI2CDelai (dDelai);	// Légère attente.  
}



//**********************************************************************
void vEcrire1BitI2C(unsigned char ucBitOut)
//	Auteur : Alain Champagne		
//      Date de création : 30-05-2007				      
//	Description : 	Routine d'émission d'un bit de communication 
//			I2C.  La routine prend le bit de la variable
//			vBitOut et ajuste la ligne SDA en fonction de cette 
//			 variable. Les lignes SDA et SCL sont activée à tour
//			 de rôle pour communiquer l'information 
//			 du maître à l'esclave.
//							
//	Fonctions appelées : 	Aucune		
//	Paramètres d'entrée : 	La valeur du bit à envoyer		
//	Paramètres de sortie : 	Aucun		
//	Variables utilisées : 	ucBitVar
//	Equate : 		Aucun	
//	#Define : 		SDA, SCL	
// 						
//**********************************************************************
{
	SCL = 0;
  
	// On assume le bit à 0.
  if (ucBitOut==0xFF)	// Vérifier et ajuster l'état du bit à sortir.
    SDA = 1;
	else
		SDA = 0;	
  vI2CDelai(dDelai);	// Légère attente.
  SCL = 1;						// Aller activer la ligne SCL.
  vI2CDelai(dDelai);	// Légère attente.
  SCL = 0;						// On replace la ligne SCL à 0.
  vI2CDelai(dDelai);	// Légère attente.
}




//**********************************************************************
unsigned char ucLire1BitI2C(void)
//	Auteur : Alain Champagne		
//      Date de création : 30-05-2006				      
//	Description : 	Routine de réception d'un bit de communication 
//			I2C.  La routine prend le bit de la ligne SDA
//			après avoir activé la ligne SCL. Le bit de 
//			donnée est placé temporairement dans une va-
//			riable ucBitIn et sera réutilisé dans 
//			une routine de traitement d'octets.
//							
//	Fonctions appelées : 		Aucune		
//	Paramètres d'entrée : 	Aucun		
//	Paramètres de sortie : 	Retourne la valeur du bit lu	
//
//**********************************************************************
{
unsigned char ucBitIn;
	ucBitIn = 0xFF;	  		// On assume le bit à lire à 1.
	SDA = 1;							// La ligne SDA est en entrée.
	vI2CDelai(dDelai);		// Légère attente.
	SCL = 1;							// On lève la ligne SCL.
	vI2CDelai(dDelai);		// Légère attente.
	if (!SDA)							// Vérifier et ajuster le bit de donnée.
	  ucBitIn = 0x00;
	SCL = 0;							// On replace la ligne SCL à 0.
	vI2CDelai(dDelai);		// Légère attente.
	return (ucBitIn);			// Retourner l'état du bit.
}



// *************************************************************************************************
unsigned char ucEcrire8BitsI2C (unsigned char ucTxData)
//  Auteur: Alain Champagne	
//  Date de création :  30-05-2007
//  
//	Modification: 	Ajout du ACK.
//	30-07-2019  Ajout du retour du ACK
//
//  Description: Routine de réception de 8 bits de données en I2C.
//  Paramètres d'entrées : Octet que l'on veut envoyer
//  Paramètres de sortie : État du ack venant du slave
//  Notes     		 			 : Aucune
//
// *************************************************************************************************
{
	int i;
	unsigned char ucI2C, ucI2CBit;
  for (i=0; i<8; i++)		   		
  {
    ucI2CBit = 0x00;		   		
		ucI2C = ucTxData & 0x80;
    if (ucI2C == 0x80)				
		{
      ucI2CBit = 0xFF;		 		
		}
    vEcrire1BitI2C(ucI2CBit);	
		vI2CDelai(dDelai);		  	
    ucTxData = ucTxData << 1; 
  }  
  return(ucLire1BitI2C());		   	
}


//**********************************************************************
unsigned char ucLire8BitsI2C (unsigned char ucAckValue)
//	Auteur : Alain Champagne		
//      Date de création : 30-05-2001				      
//	Description : 	Routine de réception de 8 bits de donnée 
//			provenant d'une communication I2C.
//
//	Modification - Stéphane Deschênes 	
//	30-07-2019  Ajout de la valeur du ACK en paramètre
//
//	Paramètres d'entrée : 	Valeur du ack voulu.		
//	Paramètres de sortie : 	ucRxData.		
//	Variables utilisées : 	ucI2C, i.
//  Variable globale :      Aucune.
//	Equate : 		Aucun	
//	#Define : 		Aucun	
// 						
//**********************************************************************
{
	unsigned char ucRxData, ucI2C;
	int i;
  ucRxData = 0x00;			 			// Remise à zéro de la variable d'entrée.
  for (i=0; i<8; i++)					// Faire 8 fois pour un octet.
  {
    ucRxData = ucRxData << 1;	// Décaler la donnée reçue.
		ucI2C = ucLire1BitI2C();	// Appel de la fonction de lecture d'un bit.
		vI2CDelai(dDelai);				// Légère attente.
		if (ucI2C==0xFF)					// Traitement et ajustement de la variable.
	  ucRxData = ucRxData | 0x01;  
  } 
	vEcrire1BitI2C(ucAckValue);		  // Envoyer la valeur du ack à la fin
	return (ucRxData);					// Retour de la variable.
}



