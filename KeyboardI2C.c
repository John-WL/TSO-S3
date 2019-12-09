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
#include "SequenceHandler.h"

// Prototypes privés
void vManualIncrementMotor(struct STKeyboardManualSettings* stpKeyboardManualSettings, struct STArmState* stpCurrentArmState, char cDirection);
void vHandleMotorValueOverflow(unsigned char* ucpMotorValue, char* cpDirection);

unsigned char ucKeyboardCharacters[16] = {'1', '2', '3', 'A',
                                        '4', '5', '6', 'B',
                                        '7', '8', '9', 'C',
                                        '*', '0', '#', 'D'};


// Implémentation fonctions
unsigned char* ucpReadKeyboardI2C()
{
    unsigned char ucKey = ' ';
    unsigned char ucAckValue = 0;
    
    if(!P1_2)
    {
        vStartBitI2C();
        ucAckValue = ucEcrire8BitsI2C(KEYBOARD_ADDRESS_I2C + 1);
        if(ucAckValue)
        {
            return &ucKey; // return space if noAcks were detected
        }
        ucKey = ucLire8BitsI2C(0xFF);  // read with noAck
        vStopBitI2C();
        
        ucKey = ucKeyboardCharacters[ucKey % 16];
    }
    
    return &ucKey;
}

void vHandleKey(unsigned char* ucpKey,
    struct STKeyboardManualSettings* stpKeyboardManualSettings,
    struct STArmState* stpCurrentArmState,
    struct STSequenceStep* stpCurrentSequenceIndexes)
{
    switch(*ucpKey)
    {
        case '1':
            stpKeyboardManualSettings->ucManualySelectedMotor = MOTOR_0;
            break;
        case '2':
            stpKeyboardManualSettings->ucManualySelectedMotor = MOTOR_1;
            break;
        case '3':
            stpKeyboardManualSettings->ucManualySelectedMotor = MOTOR_2;
            break;
        case '4':
            stpKeyboardManualSettings->ucManualySelectedMotor = MOTOR_3;
            break;
        case '5':
            stpKeyboardManualSettings->ucManualySelectedMotor = MOTOR_4;
            break;
        case '0':
            stpKeyboardManualSettings->ucManualMovingSpeed = (stpKeyboardManualSettings->ucManualMovingSpeed + 4) % 20;
            break;
        
        case '*':
            vManualIncrementMotor(stpKeyboardManualSettings, stpCurrentArmState, -1);
            break;
        case '#':
            vManualIncrementMotor(stpKeyboardManualSettings, stpCurrentArmState, 1);
            break;
        
        case 'A':
            vSetOperatingState(WARM_UP_SETUP_OPERATING_STATE);
            break;
        case 'B':
            stpCurrentArmState->ucBase = 0x10;
            stpCurrentArmState->ucShoulder = 0x4C;
            stpCurrentArmState->ucElbow = 0x00;
            stpCurrentArmState->ucWrist = 0x55;
            stpCurrentArmState->ucGrip = 0x00;
            break;
        
        case 'C':
            stpCurrentSequenceIndexes->ucSequence = (stpCurrentSequenceIndexes->ucSequence + 1) % 7;
            stpCurrentSequenceIndexes->ucStep = 0;
            break;
        case 'D':
            stpCurrentSequenceIndexes->ucStep = (stpCurrentSequenceIndexes->ucStep + 1) % 10;
            break;
            
    }
}

void vManualIncrementMotor(struct STKeyboardManualSettings* stpKeyboardManualSettings, struct STArmState* stpCurrentArmState, char cDirection)
{
    switch(stpKeyboardManualSettings->ucManualySelectedMotor)
    {
        case MOTOR_0:
            stpCurrentArmState->ucBase += (char)(((int)stpKeyboardManualSettings->ucManualMovingSpeed) * cDirection);
            vHandleMotorValueOverflow(&(stpCurrentArmState->ucBase), &cDirection);
            break;
        case MOTOR_1:
            stpCurrentArmState->ucShoulder += (char)(((int)stpKeyboardManualSettings->ucManualMovingSpeed) * cDirection);
            vHandleMotorValueOverflow(&(stpCurrentArmState->ucShoulder), &cDirection);
            break;
        case MOTOR_2:
            stpCurrentArmState->ucElbow += (char)(((int)stpKeyboardManualSettings->ucManualMovingSpeed) * cDirection);
            vHandleMotorValueOverflow(&(stpCurrentArmState->ucElbow), &cDirection);
            break;
        case MOTOR_3:
            stpCurrentArmState->ucWrist += (char)(((int)stpKeyboardManualSettings->ucManualMovingSpeed) * cDirection);
            vHandleMotorValueOverflow(&(stpCurrentArmState->ucWrist), &cDirection);
            break;
        case MOTOR_4:
            stpCurrentArmState->ucGrip += (char)(((int)stpKeyboardManualSettings->ucManualMovingSpeed) * cDirection);
            vHandleMotorValueOverflow(&(stpCurrentArmState->ucGrip), &cDirection);
            break;
    }
}

void vHandleMotorValueOverflow(unsigned char* ucpMotorValue, char* cpDirection)
{
    if(*cpDirection == 1 && *ucpMotorValue > 205)
    {
        *ucpMotorValue = 205;
    }
    else if(*cpDirection == -1 && *ucpMotorValue > 205)
    {
        *ucpMotorValue = 0;
    }
}