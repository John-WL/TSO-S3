/****************************************************************************************
   Nom du fichier : I2C.h
   Auteur : Alain Champagne
      Date de création : 19-03-2006 
        Fichier de déclaration et de définition pour les fonctions de traitement du 
        I2C.
  
****************************************************************************************/

#ifndef I2C_H
  #define I2C_H


// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************
//Definitions de parametres. 
#define SDA P1_4		//P1_0
#define SCL P1_5		//P1_1
#define dDelai 1
 
// *************************************************************************************************
//  LES PRÉDÉCLARATIONS DES FONCTIONS
// *************************************************************************************************
  
void vI2CStartBit(void);
void vI2CStopBit(void);
unsigned char ucLire8BitsI2C (unsigned char ucAckValue);
unsigned char ucEcrire8BitsI2C (unsigned char ucTxData);

#endif 

















