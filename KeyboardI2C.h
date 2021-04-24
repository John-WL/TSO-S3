/****************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.h
   Auteur: John-William Lebel
   Date de cr�ation: 2019-12-02
        Fichier de d�claration et de d�finition pour lire et traiter le clavier I2C
  
****************************************************************************************/
#ifndef KEYBOARDI2C_H
#define KEYBOARDI2C_H

// D�finitions
#define KEYBOARD_ADDRESS_I2C 0x28

// Prototypes
//**************************************************************
unsigned char* ucpReadKeyboardI2C(void);
/*  Auteur: John-William Lebel
    
    Behaviour: lis une touche du clavier I2C
    Parameters: void
    Return: unsigned char
***************************************************************/

//**************************************************************
void vHandleKey(unsigned char* ucpKey,
    struct STKeyboardManualSettings* stpKeyboardManualSettings,
    struct STArmState* stpCurrentArmState,
    struct STSequenceStep* stpCurrentSequenceIndexes);
/*  Auteur: John-William Lebel
    
    Behaviour: en fonction du charact�re re�u avec ucReadKeyboardI2C,
                cette fonction choisi le moteur qui sera contr�l� manuellement,
                la vitesse des mouvements manuels,
                une �xecution sp�cifique pour r�chauffer les moteurs
                ou remet le bras � sa position de base
    
    Parameters: unsigned char* ucpKey,
                struct KeyboardManualSettings* stpKeyboardManualSettings,
                struct ArmState* stpCurrentArmState,
                struct SequenceStep* stpCurrentSequenceIndexes
    Return: void
***************************************************************/

#endif