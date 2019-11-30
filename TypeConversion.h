/****************************************************************************************
   Nom du fichier: TypeConversion.H
   Auteur: John-William Lebel
   Date de cr�ation: 2019-11-29
        Fichier de d�claration et de d�finition pour g�rer le timer0
  
****************************************************************************************/
#ifndef TYPECONVERSION_H
#define TYPECONVERSION_H

// Pr�d�claration
unsigned char unsignedCharToHexaDecimal(unsigned char numberToEvaluate, unsigned char digitIndex);
unsigned char unsignedCharToDecimal(unsigned char numberToEvaluate, unsigned char digitIndex);
unsigned char* weightTypeToString(unsigned char* weightTypeIndex);

#endif