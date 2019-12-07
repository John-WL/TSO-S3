/*****************************Type conversion handling*******************************/
/*
		Nom du fichier: TypeConversion.c
		Auteur : John-William Lebel

		Date de cr�ation: 2019-11-29

    Fonction(s) utile(s) pour convertir certains types en d'autres


*****************************************************************************************/

//-------------- header files  -----------------
#include "_DS89C450Modifie.h"				// D�finition des bits et des registres du microcontr�leur
#include "_DeclarationGenerale.h"
#include "TypeConversion.h"

// Pr�d�clarations priv�es
void vHalfCharToHexaDecimal(unsigned char* ucpNumberToEvaluate);


// *************************************************************************************************
unsigned char* ucpUnsignedCharToAsciiHexaDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable into an ascii encoded hexadecimal value. If digitIndex == 0,
//								then the msb is returned (4 bits). If digitIndex == 1, then the lsb is returned (4 bits too).
//								If digitIndex == anything else, then the character ' ' is returned.
//  Param�tres d'entr�es 	: numberToEvaluate, digitIndex
//  Param�tres de sortie 	: an ascii encoded hexadecimal value
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		unsigned char* ucpResult;
	
		if(ucDigitIndex == 0)		// need to change the 0 for the "define", and include the right file
		{
        *ucpResult = *ucpNumberToEvaluate >> 4;
		}
		else if(ucDigitIndex == 1)
		{
        *ucpResult = (*ucpNumberToEvaluate) & 0x0F;
		}
		else
		{
				*ucpResult = ' ';
		}
		vHalfCharToHexaDecimal(ucpResult);
		
		return ucpResult;
}

// *************************************************************************************************
unsigned char* ucpUnsignedCharToAsciiDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable into an ascii encoded decimal value. If digitIndex == 0,
//								then the 1st digit is returned. If digitIndex == 1, then the 2nd digit is returned.
//								If digitIndex == 2, the 3rd digit is returned. If digitIndex == anything else, then
//								the character ' ' is returned.
//  Param�tres d'entr�es 	: numberToEvaluate, digitIndex
//  Param�tres de sortie 	: an ascii encoded decimal value
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		unsigned char* ucpResult;
	
		if(ucDigitIndex == 0)
		{
        *ucpResult = '0' + (*ucpNumberToEvaluate / 100);
		}
		else if(ucDigitIndex == 1)
		{
        *ucpResult = '0' + (*ucpNumberToEvaluate / 10);
		}
		else if(ucDigitIndex == 2)
		{
        *ucpResult = '0' + (*ucpNumberToEvaluate % 10);
		}
		else
		{
				*ucpResult = ' ';
		}
		
		return ucpResult;
}

// *************************************************************************************************
unsigned char* ucpWeightTypeToString(unsigned char* ucpWeightTypeIndex)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable that represents the type of weight (wheither it's red,
//								green, or blue), which can be seen as an index, into its corresponding name in the string format
//  Param�tres d'entr�es 	: weightTypeIndex
//  Param�tres de sortie 	: the name of the weight type
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
void vHalfCharToHexaDecimal(unsigned char* ucpNumberToEvaluate)
//
//  Auteur: John-William Lebel
//
//  Description: Convert an unsigned char variable smaller than 0x10 into an hexadecimal value in ascii.
//  Param�tres d'entr�es 	: numberToEvaluate
//  Param�tres de sortie 	: an ascii encoded hexadecimal value
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		if(*ucpNumberToEvaluate <= 9)
		{
        *ucpNumberToEvaluate = '0' + *ucpNumberToEvaluate;
		}
		else if(*ucpNumberToEvaluate <= 0x0F)
		{
        *ucpNumberToEvaluate = 'A' + (*ucpNumberToEvaluate - 0x0A);
		}
		else
		{
				*ucpNumberToEvaluate = ' ';
		}
}