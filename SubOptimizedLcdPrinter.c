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
void printLcdDeltaMotors(struct ArmState* currentArmState)
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
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->base), 0), LCD_LINE0, LCD_MOTOR_0_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->base), 1), LCD_LINE0, LCD_MOTOR_0_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->shoulder), 0), LCD_LINE0, LCD_MOTOR_1_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->shoulder), 1), LCD_LINE0, LCD_MOTOR_1_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->elbow), 0), LCD_LINE0, LCD_MOTOR_2_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->elbow), 1), LCD_LINE0, LCD_MOTOR_2_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->wrist), 0), LCD_LINE0, LCD_MOTOR_3_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->wrist), 1), LCD_LINE0, LCD_MOTOR_3_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->grip), 0), LCD_LINE1, LCD_MOTOR_4_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(currentArmState->grip), 1), LCD_LINE1, LCD_MOTOR_4_DIGIT_POSITION_1);
}

// *************************************************************************************************
void printLcdDeltaTrame(struct TramePIC* trame)
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
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.touchScreen.x), 0), LCD_LINE1, LCD_TOUCH_SCREEN_X_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.touchScreen.x), 1), LCD_LINE1, LCD_TOUCH_SCREEN_X_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.touchScreen.y), 0), LCD_LINE1, LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.touchScreen.y), 1), LCD_LINE1, LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_1);
																								
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.gripIntensity), 0), LCD_LINE1, LCD_GRIP_INTENSITY_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.gripIntensity), 1), LCD_LINE1, LCD_GRIP_INTENSITY_DIGIT_POSITION_1);
		
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.weightSensor), 0), LCD_LINE2, LCD_WEIGHT_SENSOR_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToHexaDecimal(&(trame->adcSensors.weightSensor), 1), LCD_LINE2, LCD_WEIGHT_SENSOR_DIGIT_POSITION_1);
}

// *************************************************************************************************
void printLcdDeltaWeightType(unsigned char* weightType)
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
		vLcdEcrireCaract(weightTypeToString(weightType)[0], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_0);
		vLcdEcrireCaract(weightTypeToString(weightType)[1], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_1);
		vLcdEcrireCaract(weightTypeToString(weightType)[2], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_2);
		vLcdEcrireCaract(weightTypeToString(weightType)[3], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_3);
		vLcdEcrireCaract(weightTypeToString(weightType)[4], LCD_LINE2, LCD_WEIGHT_TYPE_DIGIT_POSITION_4);
}

// *************************************************************************************************
void printLcdDeltaManualSettings(struct KeyboardManualSettings* keyboardManualSettings)
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
		vLcdEcrireCaract(unsignedCharToDecimal(&(keyboardManualSettings->manualMovingSpeed), 1), LCD_LINE3, LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_0);
		vLcdEcrireCaract(unsignedCharToDecimal(&(keyboardManualSettings->manualMovingSpeed), 2), LCD_LINE3, LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_1);
}

// *************************************************************************************************
void printLcdCurrentSequenceStep(struct SequenceStep* currentSequenceIndexes)
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
		vLcdEcrireCaract(currentSequenceIndexes->sequence + '0', LCD_LINE3, LCD_SEQ_DIGIT_POSITION);
		vLcdEcrireCaract(currentSequenceIndexes->step + '0', LCD_LINE3, LCD_STEP_DIGIT_POSITION);
}

// *************************************************************************************************
void printLcdDeltaConnectionState(unsigned char connectionStateString[])
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
		vLcdEcrireCaract(connectionStateString[0], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_0);
		vLcdEcrireCaract(connectionStateString[1], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_1);
		vLcdEcrireCaract(connectionStateString[2], LCD_LINE3, LCD_CONNECTION_STATE_DIGIT_POSITION_2);
}