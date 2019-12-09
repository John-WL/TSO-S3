/*****************************Type conversion handling*******************************/
/*
		Nom du fichier: TypeConversion.c
		Auteur : John-William Lebel

		Date de création: 2019-11-29

    Fonction(s) utile(s) pour convertir certains types en d'autres


*****************************************************************************************/

//-------------- header files  -----------------
#include "_DS89C450Modifie.h"				// Définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"
#include "TypeConversion.h"

// Prédéclarations privées

//**************************************************************
unsigned char ucHalfCharToHexaDecimal(unsigned char ucNumberToEvaluate);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme une valeur unsigned char de 4 bits enn valeur ascii hexadécimale
    Parameters: unsigned char ucNumberToEvaluate
    Return:     unsigned char
***************************************************************/


// *************************************************************************************************
unsigned char ucUnsignedCharToAsciiHexaDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable into an ascii encoded hexadecimal value. If digitIndex == 0,
//								then the msb is returned (4 bits). If digitIndex == 1, then the lsb is returned (4 bits too).
//								If digitIndex == anything else, then the character ' ' is returned.
//  Paramètres d'entrées 	: numberToEvaluate, digitIndex
//  Paramètres de sortie 	: an ascii encoded hexadecimal value
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		unsigned char ucResult;
	
		if(ucDigitIndex == 0)		// need to change the 0 for the "define", and include the right file
		{
        ucResult = *ucpNumberToEvaluate >> 4;
		}
		else if(ucDigitIndex == 1)
		{
        ucResult = (*ucpNumberToEvaluate) & 0x0F;
		}
		else
		{
				ucResult = ' ';
		}
		ucResult = ucHalfCharToHexaDecimal(ucResult);
		
		return ucResult;
}

// *************************************************************************************************
unsigned char ucUnsignedCharToAsciiDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable into an ascii encoded decimal value. If digitIndex == 0,
//								then the 1st digit is returned. If digitIndex == 1, then the 2nd digit is returned.
//								If digitIndex == 2, the 3rd digit is returned. If digitIndex == anything else, then
//								the character ' ' is returned.
//  Paramètres d'entrées 	: numberToEvaluate, digitIndex
//  Paramètres de sortie 	: an ascii encoded decimal value
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		unsigned char ucResult;
	
		if(ucDigitIndex == 0)
		{
        ucResult = '0' + (*ucpNumberToEvaluate / 100);
		}
		else if(ucDigitIndex == 1)
		{
        ucResult = '0' + (*ucpNumberToEvaluate / 10);
		}
		else if(ucDigitIndex == 2)
		{
        ucResult = '0' + (*ucpNumberToEvaluate % 10);
		}
		else
		{
				ucResult = ' ';
		}
		
		return ucResult;
}

// *************************************************************************************************
unsigned char* ucpWeightTypeToString(unsigned char* ucpWeightTypeIndex)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable that represents the type of weight (wheither it's red,
//								green, or blue), which can be seen as an index, into its corresponding name in the string format
//  Paramètres d'entrées 	: weightTypeIndex
//  Paramètres de sortie 	: the name of the weight type
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		unsigned char* ucpResult;
		
		if(*ucpWeightTypeIndex == BLUE_WEIGHT)
		{
				ucpResult = "Bleu ";
		}
		else if(*ucpWeightTypeIndex == GREEN_WEIGHT)
		{
				ucpResult = "Vert ";
		}
		else if(*ucpWeightTypeIndex == RED_WEIGHT)
		{
				ucpResult = "Rouge";
		}
		else
		{
				ucpResult = "Aucun";
		}
		
    return ucpResult;
}

// *************************************************************************************************
unsigned char ucHalfCharToHexaDecimal(unsigned char ucNumberToEvaluate)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable smaller than 0x10 into an hexadecimal value in ascii.
//  Paramètres d'entrées 	: numberToEvaluate
//  Paramètres de sortie 	: an ascii encoded hexadecimal value
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		if(ucNumberToEvaluate <= 9)
		{
        ucNumberToEvaluate = '0' + ucNumberToEvaluate;
		}
		else if(ucNumberToEvaluate <= 0x0F)
		{
        ucNumberToEvaluate = 'A' + (ucNumberToEvaluate - 0x0A);
		}
		else
		{
				ucNumberToEvaluate = ' ';
		}
    
    return ucNumberToEvaluate;
}