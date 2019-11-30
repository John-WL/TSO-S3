/****************************************************************************************
   Nom du fichier: TypeConversion.H
   Auteur: John-William Lebel
   Date de cr�ation: 2019-11-29
        Fichier de d�claration et de d�finition pour g�rer le timer0
  
****************************************************************************************/
#ifndef TYPECONVERSION_H
#define TYPECONVERSION_H

// D�finitions
#define BLUE_WEIGHT	 0
#define GREEN_WEIGHT 1
#define RED_WEIGHT	 2
#define NONE_WEIGHT	 3

// Pr�d�clarations
unsigned char unsignedCharToHexaDecimal(unsigned char* numberToEvaluate, unsigned char digitIndex);
unsigned char unsignedCharToDecimal(unsigned char* numberToEvaluate, unsigned char digitIndex);
unsigned char* weightTypeToString(unsigned char* weightTypeIndex);

#endif