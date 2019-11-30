/****************************************************************************************
   Nom du fichier: TypeConversion.H
   Auteur: John-William Lebel
   Date de création: 2019-11-29
        Fichier de déclaration et de définition pour gérer le timer0
  
****************************************************************************************/
#ifndef TYPECONVERSION_H
#define TYPECONVERSION_H

// Définitions
#define BLUE_WEIGHT	 0
#define GREEN_WEIGHT 1
#define RED_WEIGHT	 2
#define NONE_WEIGHT	 3

// Prédéclarations
unsigned char unsignedCharToHexaDecimal(unsigned char* numberToEvaluate, unsigned char digitIndex);
unsigned char unsignedCharToDecimal(unsigned char* numberToEvaluate, unsigned char digitIndex);
unsigned char* weightTypeToString(unsigned char* weightTypeIndex);

#endif