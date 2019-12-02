/**************************************************************************************************
Nom du fichier : I2C.c
Auteur : St�phane Desch�nes                  
Date de cr�ation : 01-09-2019
Version 1.0
	 
	Contient les fonctions I2C
			
***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include "ds89c450.h"				// D�finition des bits et des registres du microcontr�leur
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
//       Date de cr�ation : 30-05-2007				      
//	Description : 	Routine de d�lai pour la communication I2C. 
//							
//	Fonctions appel�es : 	Aucune		
//	Param�tres d'entr�e : 	Aucun		
//  Param�tres de sortie : 	Aucun		
//	Variables utilis�es : 	Aucune
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
//  Date de cr�ation : 30-05-2007				      
//	Description : 	Fonction qui effectue un start bit avec les lignes SDA et SCL 
//		
//	Param�tres d'entr�e : 	Aucun		
//	Param�tres de sortie : 	Aucun		
//	Notes: Passage de 1 � 0 de la ligne SDA durant un niveau haut de SCL
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
//       Date de cr�ation : 30-05-2007				      
//	Description : 	Routine de cl�ture d'une communication s�rie
//			I2C. Doit �tre appel�e � la fin de toutes 
//			op�rations.
//
//	Param�tres d'entr�e : 	Aucun		
//	Param�tres de sortie : 	Aucun		
//	Variables utilis�es : 	Aucune
// 						
//**********************************************************************
{
	//Passage de 0 � 1 sur la ligne SDA durant
	//un niveau 1 sur la ligne SCL initie un 
	//STOP BIT.
  SDA = 0;			  		// Donn�e � z�ro et
  SCL = 0;						// clock aussi.
  vI2CDelai (dDelai);	// L�g�re attente.
  SCL = 1;						// SCL � 1.
  vI2CDelai (dDelai);	// L�g�re attente.
  SDA = 1;						// SDA � 1.
  vI2CDelai (dDelai);	// L�g�re attente.  
}



//**********************************************************************
void vEcrire1BitI2C(unsigned char ucBitOut)
//	Auteur : Alain Champagne		
//      Date de cr�ation : 30-05-2007				      
//	Description : 	Routine d'�mission d'un bit de communication 
//			I2C.  La routine prend le bit de la variable
//			vBitOut et ajuste la ligne SDA en fonction de cette 
//			 variable. Les lignes SDA et SCL sont activ�e � tour
//			 de r�le pour communiquer l'information 
//			 du ma�tre � l'esclave.
//							
//	Fonctions appel�es : 	Aucune		
//	Param�tres d'entr�e : 	La valeur du bit � envoyer		
//	Param�tres de sortie : 	Aucun		
//	Variables utilis�es : 	ucBitVar
//	Equate : 		Aucun	
//	#Define : 		SDA, SCL	
// 						
//**********************************************************************
{
	SCL = 0;
  
	// On assume le bit � 0.
  if (ucBitOut==0xFF)	// V�rifier et ajuster l'�tat du bit � sortir.
    SDA = 1;
	else
		SDA = 0;	
  vI2CDelai(dDelai);	// L�g�re attente.
  SCL = 1;						// Aller activer la ligne SCL.
  vI2CDelai(dDelai);	// L�g�re attente.
  SCL = 0;						// On replace la ligne SCL � 0.
  vI2CDelai(dDelai);	// L�g�re attente.
}




//**********************************************************************
unsigned char ucLire1BitI2C(void)
//	Auteur : Alain Champagne		
//      Date de cr�ation : 30-05-2006				      
//	Description : 	Routine de r�ception d'un bit de communication 
//			I2C.  La routine prend le bit de la ligne SDA
//			apr�s avoir activ� la ligne SCL. Le bit de 
//			donn�e est plac� temporairement dans une va-
//			riable ucBitIn et sera r�utilis� dans 
//			une routine de traitement d'octets.
//							
//	Fonctions appel�es : 		Aucune		
//	Param�tres d'entr�e : 	Aucun		
//	Param�tres de sortie : 	Retourne la valeur du bit lu	
//
//**********************************************************************
{
unsigned char ucBitIn;
	ucBitIn = 0xFF;	  		// On assume le bit � lire � 1.
	SDA = 1;							// La ligne SDA est en entr�e.
	vI2CDelai(dDelai);		// L�g�re attente.
	SCL = 1;							// On l�ve la ligne SCL.
	vI2CDelai(dDelai);		// L�g�re attente.
	if (!SDA)							// V�rifier et ajuster le bit de donn�e.
	  ucBitIn = 0x00;
	SCL = 0;							// On replace la ligne SCL � 0.
	vI2CDelai(dDelai);		// L�g�re attente.
	return (ucBitIn);			// Retourner l'�tat du bit.
}



// *************************************************************************************************
unsigned char ucEcrire8BitsI2C (unsigned char ucTxData)
//  Auteur: Alain Champagne	
//  Date de cr�ation :  30-05-2007
//  
//	Modification: 	Ajout du ACK.
//	30-07-2019  Ajout du retour du ACK
//
//  Description: Routine de r�ception de 8 bits de donn�es en I2C.
//  Param�tres d'entr�es : Octet que l'on veut envoyer
//  Param�tres de sortie : �tat du ack venant du slave
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
//      Date de cr�ation : 30-05-2001				      
//	Description : 	Routine de r�ception de 8 bits de donn�e 
//			provenant d'une communication I2C.
//
//	Modification - St�phane Desch�nes 	
//	30-07-2019  Ajout de la valeur du ACK en param�tre
//
//	Param�tres d'entr�e : 	Valeur du ack voulu.		
//	Param�tres de sortie : 	ucRxData.		
//	Variables utilis�es : 	ucI2C, i.
//  Variable globale :      Aucune.
//	Equate : 		Aucun	
//	#Define : 		Aucun	
// 						
//**********************************************************************
{
	unsigned char ucRxData, ucI2C;
	int i;
  ucRxData = 0x00;			 			// Remise � z�ro de la variable d'entr�e.
  for (i=0; i<8; i++)					// Faire 8 fois pour un octet.
  {
    ucRxData = ucRxData << 1;	// D�caler la donn�e re�ue.
		ucI2C = ucLire1BitI2C();	// Appel de la fonction de lecture d'un bit.
		vI2CDelai(dDelai);				// L�g�re attente.
		if (ucI2C==0xFF)					// Traitement et ajustement de la variable.
	  ucRxData = ucRxData | 0x01;  
  } 
	vEcrire1BitI2C(ucAckValue);		  // Envoyer la valeur du ack � la fin
	return (ucRxData);					// Retour de la variable.
}



