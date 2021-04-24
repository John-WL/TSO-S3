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
//**************************************************************
unsigned char ucUnsignedCharToAsciiHexaDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme un nombre de 8 bits en ascii hexadecimal.
                si ucDigitIndex == 0, alors les 4 bits msb sont convertis.
                si ucDigitIndex == 1, alors les 4 bits lsb sont convertis.
                si ucDigitIndex == quelque chose d'autre que 0 ou 1, alors le caract�re ' ' est renvoy�.
                
                exemple: ucUnsignedCharToAsciiHexaDecimal(0x35, 0):
                          
                          0011 0101
                            ^
                            |
             '0' veut dire--
             
                et donc, le msb, c'est � dire "0011", ou 0x3, sera utilis�
                pour g�n�rer le caract�re en ascii, c'est � dire 0x33, ou '3'
                
                
                sinon: ucUnsignedCharToAsciiHexaDecimal(0x35, 1):
                          
                          0011 0101
                                ^
                                |
             '1' veut dire------
             
                et donc, le lsb, c'est � dire "0101", ou 0x5, sera utilis�
                pour g�n�rer le caract�re en ascii, c'est � dire 0x35, ou '5'
                            
    Parameters: unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex
    Return:     unsigned char*
***************************************************************/

//**************************************************************
unsigned char ucUnsignedCharToAsciiDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme un nombre de 8 bits en ascii decimal.
                si ucDigitIndex == 0, alors les unit�es sont converties.
                si ucDigitIndex == 1, alors les dizaines sont converties.
                si ucDigitIndex == 2, alors les centaines sont converties.
                si ucDigitIndex == quelque chose d'autre que 0, 1 ou 2, alors le caract�re ' ' est renvoy�.
                
                exemple: ucUnsignedCharToAsciiDecimal(0x35, 1):
                          
                          0x35, c'est 053 en d�cimal (0 centaines, 5 dizaines, 3 unit�es).
                          
                          0 5 3
                            ^
                            |
           '1' veut dire----
             
                et donc, 5 est converti en ascii, c'est � dire 0x35, ou '5'
                            
    Parameters: unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex
    Return:     unsigned char*
***************************************************************/

//**************************************************************
unsigned char* ucpWeightTypeToString(unsigned char* ucpWeightTypeIndex);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme un nombre de 8 bits en ascii decimal.
                si *ucpWeightTypeIndex == BLUE_WEIGHT, alors la string "Bleu " est retourn�e.
                si *ucpWeightTypeIndex == GREEN_WEIGHT, alors la string "Vert " est retourn�e.
                si *ucpWeightTypeIndex == BLUE_RED, alors la string "Rouge" est retourn�e.
                si *ucpWeightTypeIndex == quoi que ce soit d'autre, alors la string "Aucun" est retourn�e.
                
    Parameters: unsigned char* ucpWeightTypeIndex
    Return:     unsigned char*
***************************************************************/

#endif