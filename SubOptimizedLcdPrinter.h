/****************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.h
   Auteur: John-William Lebel
   Date de création: 2019-11-29
        Fichier de déclaration et de définition pour optimiser le temps d'affichage du LCD
  
****************************************************************************************/
#ifndef SUBOPTIMIZEDLCDPRINTER_H
#define SUBOPTIMIZEDLCDPRINTER_H

// Prédéclarations
void printLcdDeltaMotors(struct ArmState* currentArmState);
void printLcdDeltaTrame(struct TramePIC* trame);
void printLcdDeltaWeightType(unsigned char* weightType);
void printLcdDeltaManualSettings(struct KeyboardManualSettings* keyboardManualSettings);
void printLcdCurrentSequenceStep(struct SequenceStep* currentSequenceIndexes);
void printLcdDeltaConnectionState(unsigned char connectionStateString[]);

#endif