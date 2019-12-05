/**************************************************************************************************
    Nom du fichier : SequenceHandler.c
    
    Auteur : John-William Lebel
    Date de création : 2019-12-05
    gérance de la séquence en fonction de la séquence envoyée par le PIC
    
***************************************************************************************************/
#include "SequenceHandler.h"
#include "ProjectDefinitions.h"

// variables
unsigned char currentOperatingState = STAND_BY_OPERATING_STATE;

// prototypes
void handleTouchScreen(struct TouchScreen* toucheScreen, struct SequenceStep* currentSequenceIndexes);
unsigned char getSortingSequenceFromWheightSampling(unsigned char* weightSensor);

// function implementations
void handleSequence(struct TramePIC* trame, struct SequenceStep* currentSequenceIndexes, unsigned char* weightType)
{
    switch(currentOperatingState)
    {
      case STAND_BY_OPERATING_STATE:
          handleTouchScreen(&(trame->adcSensors.touchScreen), currentSequenceIndexes);
          break;
      case WEIGHT_GRABING_OPERATING_STATE:
          currentSequenceIndexes->step++;
          if(currentSequenceIndexes->step == 4)
          {
              currentSequenceIndexes->sequence = 3;
              currentSequenceIndexes->step = 0;
              currentOperatingState = WEIGHT_POSITIONING_OPERATING_STATE;
          }
          break;
      case WEIGHT_POSITIONING_OPERATING_STATE:
          currentSequenceIndexes->step++;
          if(currentSequenceIndexes->step == 2)
          {
              currentOperatingState = WEIGHT_SAMPLING_OPERATING_STATE;
          }
          break;
      case WEIGHT_SAMPLING_OPERATING_STATE:
          currentSequenceIndexes->sequence = getSortingSequenceFromWheightSampling(&(trame->adcSensors.weightSensor));
          *weightType = currentSequenceIndexes->sequence - 4;
          currentSequenceIndexes->step = 0;
          currentOperatingState = WEIGHT_SORTING_OPERATING_STATE;
          break;
      case WEIGHT_SORTING_OPERATING_STATE:
          currentSequenceIndexes->step++;
          if(currentSequenceIndexes->step == 6)
          {
              currentOperatingState = STAND_BY_OPERATING_STATE;
              *weightType = 4;
          }
          break;
    }
}

void handleTouchScreen(struct TouchScreen* touchScreen, struct SequenceStep* currentSequenceIndexes)
{
    //A6::
      //x:0x00 à 0x60
      //y:0x00 à 0x70
    //B2::
      //x:0x60 à 0xA0
      //y:0xC0 à 0xFF
    //C5::
      //x:0xA0 à 0xFF
      //y:0x70 à 0xC0

    // A6 appuyé?
    if(touchScreen->x >= 0x00 && touchScreen->x <= 0x60
        && touchScreen->y >= 0x00 && touchScreen->x <= 0x70)
    {
        currentSequenceIndexes->sequence = 0;
        currentSequenceIndexes->step = 0;
        currentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
    // B2 appuyé?
    else if(touchScreen->x >= 0x60 && touchScreen->x <= 0xA0
        && touchScreen->y >= 0xC0 && touchScreen->x <= 0xFF)
    {
        currentSequenceIndexes->sequence = 1;
        currentSequenceIndexes->step = 0;
        currentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
    // C5 appuyé?
    else if(touchScreen->x >= 0xA0 && touchScreen->x <= 0xFF
        && touchScreen->y >= 0x70 && touchScreen->x <= 0xC0)
    {
        currentSequenceIndexes->sequence = 2;
        currentSequenceIndexes->step = 0;
        currentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
}

unsigned char getSortingSequenceFromWheightSampling(unsigned char* weightSensor)
{
    unsigned char sequenceIndex;
  
    if(*weightSensor < 0x40)
    {
        sequenceIndex = 4;
    }
    else if(*weightSensor < 0x70)
    {
        sequenceIndex = 5;
    }
    else
    {
        sequenceIndex = 6;
    }
    
    return sequenceIndex;
}

unsigned char isOperating(void)
{
    return currentOperatingState;
}