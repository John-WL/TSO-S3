/*****************************Timer0 handling*******************************/
/*
		Nom du fichier: Keyboard.c
		Auteur : John-William Lebel

		Date de création: 2019-12-02

    Fonction(s) nécessaire(s) pour intercepter et gérer les touches du clavier I2C


*****************************************************************************************/
#include "Keyboard.h"
#include "I2C.h"

void readKeyboardI2C()
{
    unsigned char key = ' ';
    unsigned char ackValue = 0;
    
    if(!P1_7)
    {
        vI2CStartBit();
        if(!ucEcrire8BitsI2C(KEYBOARD_ADDRESS_I2C + 1))
        {
            return ' '; // return space if noAcks were detected
        }
        key = ucLire8BitsI2C(0);  // read with noAck
        vI2CStopBit();
    }
    
    return key;
}


void handleKey(unsigned char* key)
{
    switch()
}