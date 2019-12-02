/****************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.h
   Auteur: John-William Lebel
   Date de création: 2019-12-02
        Fichier de déclaration et de définition pour lire et traiter le clavier I2C
  
****************************************************************************************/
#ifndef KEYBOARDI2C_H
#define KEYBOARDI2C_H

# Définitions
#define KEYBOARD_ADDRESS_I2C 0x28

// Prédéclarations
void readKeyboardI2C(void);
void handleKey(unsigned char* key);



#endif