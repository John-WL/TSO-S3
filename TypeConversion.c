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
unsigned char halfCharToHexaDecimal(unsigned char* numberToEvaluate);


// *************************************************************************************************
unsigned char unsignedCharToHexaDecimal(unsigned char* numberToEvaluate, unsigned char digitIndex)
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
		unsigned char result;
	
		if(digitIndex == 0)		// need to change the 0 for the "define", and include the right file
		{
			result = *numberToEvaluate >> 4;
		}
		else if(digitIndex == 1)
		{
			result = (*numberToEvaluate) & 0x0F;
		}
		else
		{
				result = ' ';
		}
		result = halfCharToHexaDecimal(&result);
		
		return result;
}

// *************************************************************************************************
unsigned char unsignedCharToDecimal(unsigned char* numberToEvaluate, unsigned char digitIndex)
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
		unsigned char result;
	
		if(digitIndex == 0)
		{
			result = '0' + (*numberToEvaluate / 100);
		}
		else if(digitIndex == 1)
		{
			result = '0' + (*numberToEvaluate / 10);
		}
		else if(digitIndex == 2)
		{
			result = '0' + (*numberToEvaluate % 10);
		}
		else
		{
				result = ' ';
		}
		
		return result;
}

// *************************************************************************************************
unsigned char* weightTypeToString(unsigned char* weightTypeIndex)
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
		unsigned char* result;
		
		if(*weightTypeIndex == BLUE_WEIGHT)
		{
				result = "Bleu ";
		}
		else if(*weightTypeIndex == GREEN_WEIGHT)
		{
				result = "Vert ";
		}
		else if(*weightTypeIndex == RED_WEIGHT)
		{
				result = "Rouge";
		}
		else
		{
				result = "Aucun";
		}
		
		return result;
}

// *************************************************************************************************
unsigned char halfCharToHexaDecimal(unsigned char* numberToEvaluate)
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
		unsigned char result;
		
		if(*numberToEvaluate <= 9)
		{
			result = '0' + *numberToEvaluate;
		}
		else if(*numberToEvaluate <= 0x0F)
		{
			result = 'A' + (*numberToEvaluate - 0x0A);
		}
		else
		{
				result = ' ';
		}
		
		return result;
}