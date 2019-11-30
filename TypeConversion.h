/****************************************************************************************
   Nom du fichier: TypeConversion.H
   Auteur: John-William Lebel
   Date de création: 2019-11-29
        Fichier de déclaration et de définition pour gérer le timer0
  
****************************************************************************************/
#ifndef TYPECONVERSION_H
#define TYPECONVERSION_H

// Prédéclaration
unsigned char unsignedCharToHexaDecimal(unsigned char numberToEvaluate, unsigned char digitIndex);
unsigned char unsignedCharToDecimal(unsigned char numberToEvaluate, unsigned char digitIndex);
unsigned char* weightTypeToString(unsigned char* weightTypeIndex);

#endif