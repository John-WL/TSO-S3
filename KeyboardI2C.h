/****************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.h
   Auteur: John-William Lebel
   Date de cr�ation: 2019-12-02
        Fichier de d�claration et de d�finition pour lire et traiter le clavier I2C
  
****************************************************************************************/
#ifndef KEYBOARDI2C_H
#define KEYBOARDI2C_H

# D�finitions
#define KEYBOARD_ADDRESS_I2C 0x28

// Pr�d�clarations
void readKeyboardI2C(void);
void handleKey(unsigned char* key);



#endif