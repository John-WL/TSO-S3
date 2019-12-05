/*****************************Timer0 handling*******************************/
/*
		Nom du fichier: Keyboard.c
		Auteur : John-William Lebel

		Date de création: 2019-12-02

    Fonction(s) nécessaire(s) pour intercepter et gérer les touches du clavier I2C


*****************************************************************************************/
#include "_DS89C450Modifie.h"				// Définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"
#include "ProjectDefinitions.h"
#include "KeyboardI2C.h"
#include "I2C.h"

// Prototypes privés
void manualIncrementMotor(struct KeyboardManualSettings* keyboardManualSettings, struct ArmState* currentArmState, char direction);
void handleMotorValueOverflow(unsigned char* motorValue, unsigned char* direction);

unsigned char keyboardCharacters[16] = {'1', '2', '3', 'A',
                                        '4', '5', '6', 'B',
                                        '7', '8', '9', 'C',
                                        '*', '0', '#', 'D'};


// Implémentation fonctions
unsigned char* readKeyboardI2C()
{
    unsigned char key = ' ';
    unsigned char ackValue = 0;
    
    if(!P1_2)
    {
        vStartBitI2C();
        ackValue = ucEcrire8BitsI2C(KEYBOARD_ADDRESS_I2C + 1);
        if(ackValue)
        {
            return &key; // return space if noAcks were detected
        }
        key = ucLire8BitsI2C(0xFF);  // read with noAck
        vStopBitI2C();
        
        key = keyboardCharacters[key % 16];
    }
    
    return &key;
}

void handleKey(unsigned char* key, struct KeyboardManualSettings* keyboardManualSettings, struct ArmState* currentArmState, struct SequenceStep* currentSequenceIndexes)
{
    switch(*key)
    {
        case '1':
            keyboardManualSettings->manualySelectedMotor = MOTOR_0;
            break;
        case '2':
            keyboardManualSettings->manualySelectedMotor = MOTOR_1;
            break;
        case '3':
            keyboardManualSettings->manualySelectedMotor = MOTOR_2;
            break;
        case '4':
            keyboardManualSettings->manualySelectedMotor = MOTOR_3;
            break;
        case '5':
            keyboardManualSettings->manualySelectedMotor = MOTOR_4;
            break;
        case '0':
            keyboardManualSettings->manualMovingSpeed = (keyboardManualSettings->manualMovingSpeed + 4) % 20;
            break;
        
        case '*':
            manualIncrementMotor(keyboardManualSettings, currentArmState, -1);
            break;
        case '#':
            manualIncrementMotor(keyboardManualSettings, currentArmState, 1);
            break;
        case 'A':
            // NEEDING IMPLEMENTATION! This line is supposed to make the robot arm warm up
            break;
        
        case 'B':
            currentArmState->base = 0x10;
            currentArmState->shoulder = 0x4C;
            currentArmState->elbow = 0x00;
            currentArmState->wrist = 0xA0;
            currentArmState->grip = 0x00;
            break;
        
        case 'C':
            currentSequenceIndexes->sequence = (currentSequenceIndexes->sequence + 1) % 7;
            currentSequenceIndexes->step = 0;
            break;
        case 'D':
            currentSequenceIndexes->step = (currentSequenceIndexes->step + 1) % 10;
            break;
            
    }
}

void manualIncrementMotor(struct KeyboardManualSettings* keyboardManualSettings, struct ArmState* currentArmState, char direction)
{
    switch(keyboardManualSettings->manualySelectedMotor)
    {
      case MOTOR_0:
          currentArmState->base += (char)(((int)keyboardManualSettings->manualMovingSpeed) * direction);
          handleMotorValueOverflow(&(currentArmState->base), &direction);
          break;
      case MOTOR_1:
          currentArmState->shoulder += (char)(((int)keyboardManualSettings->manualMovingSpeed) * direction);
          handleMotorValueOverflow(&(currentArmState->shoulder), &direction);
          break;
      case MOTOR_2:
          currentArmState->elbow += (char)(((int)keyboardManualSettings->manualMovingSpeed) * direction);
          handleMotorValueOverflow(&(currentArmState->elbow), &direction);
          break;
      case MOTOR_3:
          currentArmState->wrist += (char)(((int)keyboardManualSettings->manualMovingSpeed) * direction);
          handleMotorValueOverflow(&(currentArmState->wrist), &direction);
          break;
      case MOTOR_4:
          currentArmState->grip += (char)(((int)keyboardManualSettings->manualMovingSpeed) * direction);
          handleMotorValueOverflow(&(currentArmState->grip), &direction);
          break;
    }
}

void handleMotorValueOverflow(unsigned char* motorValue, unsigned char* direction)
{
    if(*direction == 1 && *motorValue > 205)
    {
        *motorValue = 205;
    }
    else if(*direction == -1 && *motorValue > 205)
    {
        *motorValue = 0;
    }
}