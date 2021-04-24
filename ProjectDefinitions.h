/****************************************************************************************
   Nom du fichier: ProjectDefinition.h
   Auteur: John-William Lebel
   Date de création: 2019-11-29
        Fichier de déclaration et de définition des variables et constantes du projet
  
****************************************************************************************/

#ifndef PROJECTDEFINITION_H
	#define PROJECTDEFINITION_H

// #defines
#define MINIMUM_POSITION 205
#define MIDDLE_POSITION 102
#define MAXIMUM_POSITION 0

#define BASE		 0
#define SHOULDER 1
#define ELBOW		 2
#define WRIST		 3
#define GRIP		 4

#define MOTOR_0 0
#define MOTOR_1 1
#define MOTOR_2 2
#define MOTOR_3 3
#define MOTOR_4 4

#define LCD_DELTA_ONLINE_VALUE	"nL "		// used with the connectionStateString[] array
#define LCD_DELTA_OFFLINE_VALUE	"ffL"		// to display on the LCD. The 'O' is always there
																				// so there's no need to store it explicitely.

#define LCD_LINE0 0
#define LCD_LINE1 1
#define LCD_LINE2 2
#define LCD_LINE3 3

#define LCD_MOTOR_0_DIGIT_POSITION_0 2
#define LCD_MOTOR_0_DIGIT_POSITION_1 3

#define LCD_MOTOR_1_DIGIT_POSITION_0 7
#define LCD_MOTOR_1_DIGIT_POSITION_1 8

#define LCD_MOTOR_2_DIGIT_POSITION_0 12
#define LCD_MOTOR_2_DIGIT_POSITION_1 13

#define LCD_MOTOR_3_DIGIT_POSITION_0 17
#define LCD_MOTOR_3_DIGIT_POSITION_1 18

#define LCD_MOTOR_4_DIGIT_POSITION_0 2
#define LCD_MOTOR_4_DIGIT_POSITION_1 3

#define LCD_TOUCH_SCREEN_X_DIGIT_POSITION_0 7
#define LCD_TOUCH_SCREEN_X_DIGIT_POSITION_1 8

#define LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_0 12
#define LCD_TOUCH_SCREEN_Y_DIGIT_POSITION_1 13

#define LCD_GRIP_INTENSITY_DIGIT_POSITION_0 17
#define LCD_GRIP_INTENSITY_DIGIT_POSITION_1 18

#define LCD_WEIGHT_SENSOR_DIGIT_POSITION_0 2
#define LCD_WEIGHT_SENSOR_DIGIT_POSITION_1 3

#define LCD_WEIGHT_TYPE_DIGIT_POSITION_0 10
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_1 11
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_2 12
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_3 13
#define LCD_WEIGHT_TYPE_DIGIT_POSITION_4 14

#define LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_0 0
#define LCD_MANUAL_MOTOR_SPEED_DIGIT_POSITION_1 1

#define LCD_SEQ_DIGIT_POSITION	7
#define LCD_STEP_DIGIT_POSITION 14

#define LCD_CONNECTION_STATE_DIGIT_POSITION_0 17
#define LCD_CONNECTION_STATE_DIGIT_POSITION_1 18
#define LCD_CONNECTION_STATE_DIGIT_POSITION_2 19

// structs
struct STArmState
{
		unsigned char ucBase;
		unsigned char ucShoulder;
		unsigned char ucElbow;
		unsigned char ucWrist;
		unsigned char ucGrip;
};

struct STTouchScreen
{
		unsigned char ucX;
		unsigned char ucY;
};

struct STAdcSensors
{
		struct STTouchScreen stTouchScreen;
		unsigned char ucGripIntensity;
		unsigned char ucWeightSensor;
};

struct STTramePIC
{
  struct STAdcSensors stAdcSensors;
  unsigned char ucCheckSum;
};

struct STSequenceStep
{
		unsigned char ucSequence;
		unsigned char ucStep;
};

struct STKeyboardManualSettings
{
		unsigned char ucManualySelectedMotor;
		unsigned char ucManualMovingSpeed;
};
struct STCompteur
{
  unsigned char ucCompteur300ms;
  unsigned char ucCompteur200ms;
  unsigned char ucCompteur2sec;
};

#endif