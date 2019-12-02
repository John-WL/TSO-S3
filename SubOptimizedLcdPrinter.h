/****************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.h
   Auteur: John-William Lebel
   Date de cr�ation: 2019-11-29
        Fichier de d�claration et de d�finition pour optimiser le temps d'affichage du LCD
  
****************************************************************************************/
#ifndef SUBOPTIMIZEDLCDPRINTER_H
#define SUBOPTIMIZEDLCDPRINTER_H

// Pr�d�clarations
void printLcdDeltaMotors(struct ArmState* currentArmState);
void printLcdDeltaTrame(struct TramePIC* trame);
void printLcdDeltaWeightType(unsigned char* weightType);
void printLcdDeltaManualSettings(struct KeyboardManualSettings* keyboardManualSettings);
void printLcdCurrentSequenceStep(struct SequenceStep* currentSequenceIndexes);
void printLcdDeltaConnectionState(unsigned char connectionStateString[]);

#endif