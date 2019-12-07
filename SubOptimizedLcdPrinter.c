/**************************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.c
   Auteur: John-William Lebel
   Date de création: 2019-11-29
	 
	 Fichier qui contient les fonctions utiles à l'optimisation partielle du temps d'affichage du LCD
	 dans le câdre du projet final de 3e session
   
								
***************************************************************************************************/
// headers
#include "LCD.h"
#include "ProjectDefinitions.h"
#include "TypeConversion.h"


// implémentations
// *************************************************************************************************
void vPrintLcdDeltaMotors(struct STArmState* stpCurrentArmState)
//
//  Auteur: John-William Lebel
//
//  Description: prints at the right place on the LCD the motor values that are sent to the pic
//  Paramètres d'entrées 	: currentArmState
//  Paramètres de sortie 	: None
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucBase), 0), LCD_LINE0, LCD_MOTOR_0_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucBase), 1), LCD_LINE0, LCD_MOTOR_0_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucShoulder), 0), LCD_LINE0, LCD_MOTOR_1_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucShoulder), 1), LCD_LINE0, LCD_MOTOR_1_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucElbow), 0), LCD_LINE0, LCD_MOTOR_2_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucElbow), 1), LCD_LINE0, LCD_MOTOR_2_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucWrist), 0), LCD_LINE0, LCD_MOTOR_3_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucWrist), 1), LCD_LINE0, LCD_MOTOR_3_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucGrip), 0), LCD_LINE1, LCD_MOTOR_4_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpCurrentArmState->ucGrip), 1), LCD_LINE1, LCD_MOTOR_4_DIGIT_POSITION_1);
}

// *************************************************************************************************
void vPrintLcdDeltaTrame(struct STTramePIC* stpTrame)
//
//  Auteur: John-William Lebel
//
//  Description: prints at the right place on the LCD the sensor values that the pic sent so we can read them
//  Paramètres d'entrées 	: sensors
//  Paramètres de sortie 	: None
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.stTouchScreen.ucX), 0), LCD_LINE1, LCD_TOUCH_SCREEN_X_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.stTouchScreen.ucX), 1), LCD_LINE1, LCD_TOUCH_SCREEN_X_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.stTouchScreen.ucY), 0), LCD_LINE1, LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.stTouchScreen.ucY), 1), LCD_LINE1, LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.ucGripIntensity), 0), LCD_LINE1, LCD_GRIP_INTENSITY_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.ucGripIntensity), 1), LCD_LINE1, LCD_GRIP_INTENSITY_DIGIT_POSITION_1);
		
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.ucWeightSensor), 0), LCD_LINE2, LCD_WEIGHT_SENSOR_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiHexaDecimal(&(stpTrame->stAdcSensors.ucWeightSensor), 1), LCD_LINE2, LCD_WEIGHT_SENSOR_DIGIT_POSITION_1);
}

// *************************************************************************************************
void vPrintLcdDeltaWeightType(unsigned char* ucpWeightType)
//
//  Auteur: John-William Lebel
//
//  Description: prints at the right place on the LCD the current estimated weight type we're dealing with
//								(wheither it's red, green or blue)
//  Paramètres d'entrées 	: weightType
//  Paramètres de sortie 	: None
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
    unsigned char* ucpWeightTypeString = ucpWeightTypeToString(ucpWeightType);
		vLcdEcrireCaract(ucpWeightTypeString[0], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_0);
		vLcdEcrireCaract(ucpWeightTypeString[1], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_1);
		vLcdEcrireCaract(ucpWeightTypeString[2], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_2);
		vLcdEcrireCaract(ucpWeightTypeString[3], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_3);
		vLcdEcrireCaract(ucpWeightTypeString[4], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_4);
}

// *************************************************************************************************
void vPrintLcdDeltaManualSettings(struct STKeyboardManualSettings* stpKeyboardManualSettings)
//
//  Auteur: John-William Lebel
//
//  Description: prints at the right place on the LCD the current setted values for the manual control of the arm
//  Paramètres d'entrées 	: keyboardManualSettings
//  Paramètres de sortie 	: None
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiDecimal(&(stpKeyboardManualSettings->ucManualMovingSpeed), 1), LCD_LINE3, LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_0);
		vLcdEcrireCaract(*ucpUnsignedCharToAsciiDecimal(&(stpKeyboardManualSettings->ucManualMovingSpeed), 2), LCD_LINE3, LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_1);
}

// *************************************************************************************************
void vPrintLcdCurrentSequenceStep(struct STSequenceStep* stpCurrentSequenceIndexes)
//
//  Auteur: John-William Lebel
//
//  Description: prints at the right place on the LCD the current sequence and step the arm is performing
//  Paramètres d'entrées 	: currentSequenceIndexes
//  Paramètres de sortie 	: None
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		vLcdEcrireCaract(stpCurrentSequenceIndexes->ucSequence + '0', LCD_LINE3, LCD_SEQ_DIGIT_POSITION);
		vLcdEcrireCaract(stpCurrentSequenceIndexes->ucStep + '0', LCD_LINE3, LCD_STEP_DIGIT_POSITION);
}

// *************************************************************************************************
void vPrintLcdDeltaConnectionState(unsigned char ucConnectionStateString[])
//
//  Auteur: John-William Lebel
//
//  Description: prints at the right place on the LCD the current connection state, wheither it's OffL or OnL
//  Paramètres d'entrées 	: connectionStateString[]
//  Paramètres de sortie 	: None
//  Notes     		 				: Aucune
//
// *************************************************************************************************
{
		vLcdEcrireCaract(ucConnectionStateString[0], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_0);
		vLcdEcrireCaract(ucConnectionStateString[1], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_1);
		vLcdEcrireCaract(ucConnectionStateString[2], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_2);
}