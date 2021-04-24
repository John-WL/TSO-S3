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
//**************************************************************
unsigned char ucUnsignedCharToAsciiHexaDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme un nombre de 8 bits en ascii hexadecimal.
                si ucDigitIndex == 0, alors les 4 bits msb sont convertis.
                si ucDigitIndex == 1, alors les 4 bits lsb sont convertis.
                si ucDigitIndex == quelque chose d'autre que 0 ou 1, alors le caractère ' ' est renvoyé.
                
                exemple: ucUnsignedCharToAsciiHexaDecimal(0x35, 0):
                          
                          0011 0101
                            ^
                            |
             '0' veut dire--
             
                et donc, le msb, c'est à dire "0011", ou 0x3, sera utilisé
                pour générer le caractère en ascii, c'est à dire 0x33, ou '3'
                
                
                sinon: ucUnsignedCharToAsciiHexaDecimal(0x35, 1):
                          
                          0011 0101
                                ^
                                |
             '1' veut dire------
             
                et donc, le lsb, c'est à dire "0101", ou 0x5, sera utilisé
                pour générer le caractère en ascii, c'est à dire 0x35, ou '5'
                            
    Parameters: unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex
    Return:     unsigned char*
***************************************************************/

//**************************************************************
unsigned char ucUnsignedCharToAsciiDecimal(unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme un nombre de 8 bits en ascii decimal.
                si ucDigitIndex == 0, alors les unitées sont converties.
                si ucDigitIndex == 1, alors les dizaines sont converties.
                si ucDigitIndex == 2, alors les centaines sont converties.
                si ucDigitIndex == quelque chose d'autre que 0, 1 ou 2, alors le caractère ' ' est renvoyé.
                
                exemple: ucUnsignedCharToAsciiDecimal(0x35, 1):
                          
                          0x35, c'est 053 en décimal (0 centaines, 5 dizaines, 3 unitées).
                          
                          0 5 3
                            ^
                            |
           '1' veut dire----
             
                et donc, 5 est converti en ascii, c'est à dire 0x35, ou '5'
                            
    Parameters: unsigned char* ucpNumberToEvaluate, unsigned char ucDigitIndex
    Return:     unsigned char*
***************************************************************/

//**************************************************************
unsigned char* ucpWeightTypeToString(unsigned char* ucpWeightTypeIndex);
/*  Auteur: John-William Lebel
    
    Behaviour:  transforme un nombre de 8 bits en ascii decimal.
                si *ucpWeightTypeIndex == BLUE_WEIGHT, alors la string "Bleu " est retournée.
                si *ucpWeightTypeIndex == GREEN_WEIGHT, alors la string "Vert " est retournée.
                si *ucpWeightTypeIndex == BLUE_RED, alors la string "Rouge" est retournée.
                si *ucpWeightTypeIndex == quoi que ce soit d'autre, alors la string "Aucun" est retournée.
                
    Parameters: unsigned char* ucpWeightTypeIndex
    Return:     unsigned char*
***************************************************************/

#endif