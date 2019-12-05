/****************************************************************************************
   Nom du fichier : SequenceHandler.h
   Auteur : John-William Lebel
      Date de creation : 12-05-2019
      gérance de la séquence en fonction de la séquence envoyée par le PIC
  
****************************************************************************************/
#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

// Définitions
#define STAND_BY_OPERATING_STATE 0
#define WEIGHT_GRABING_OPERATING_STATE 1
#define WEIGHT_POSITIONING_OPERATING_STATE 2
#define WEIGHT_SAMPLING_OPERATING_STATE 3
#define WEIGHT_SORTING_OPERATING_STATE 4


// Prototypes
void handleSequence(struct TramePIC* trame, struct SequenceStep* currentSequenceIndexes, unsigned char* weightType);
unsigned char isOperating(void);

#endif