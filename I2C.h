/****************************************************************************************
   Nom du fichier : I2C.h
   Auteur : Alain Champagne                  
   Modifications: John-William Lebel 2019-12-02 -> modifications du pr�fixe v au lieu de
                  uc dans la fonction ucEcrire8BitsI2C(unsigned char ucTxData)
      Date de cr�ation : 19-03-2006 
        Fichier de d�claration et de d�finition pour les fonctions de traitement du 
        I2C.
  
****************************************************************************************/

#ifndef I2C_H
  #define I2C_H


// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************
//Definitions de parametres. 
#define SDA P3_4		//P1_0
#define SCL P3_5		//P1_1
#define DELAI 1
 
// *************************************************************************************************
//  LES PR�D�CLARATIONS DES FONCTIONS
// *************************************************************************************************
  
void vI2CStartBit(void);
void vI2CStopBit(void);
unsigned char ucLire8BitsI2C (unsigned char ucAckValue);
unsigned char ucEcrire8BitsI2C (unsigned char ucTxData);

#endif 

















