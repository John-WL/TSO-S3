/**************************************************************************************************
    Nom du fichier : SequenceHandler.c
    
    Auteur : John-William Lebel
    Date de création : 2019-12-05
    gérance de la séquence en fonction de la séquence envoyée par le PIC
    
***************************************************************************************************/
#include "SequenceHandler.h"
#include "ProjectDefinitions.h"

// définitions
#define WEIGHT_POSITIONING_OPERATING_STATE 2  // va mettre le poid sur la balance
#define WEIGHT_SAMPLING_OPERATING_STATE 3     // calcul la couleur du poid en fonction de ce que la balance indique
#define WEIGHT_SORTING_OPERATING_STATE 4      // va porter le poid dans la bonne case

#define WARM_UP_OPERATING_STATE 6             // fait quelques mouvements pour s'échauffer

// variables
unsigned char ucCurrentOperatingState = STAND_BY_OPERATING_STATE;

// prototypes
void vHandleTouchScreen(struct STTouchScreen* stpTouchScreen, struct STSequenceStep* stpCurrentSequenceIndexes);
unsigned char ucGetSortingSequenceFromWheightSampling(unsigned char* ucpWeightSensor);

// function implementations
void vHandleSequence(struct STTramePIC* stpTrame, struct STSequenceStep* stpCurrentSequenceIndexes, unsigned char* ucpWeightType)
{
    switch(ucCurrentOperatingState)
    {
      case STAND_BY_OPERATING_STATE:
          vHandleTouchScreen(&(stpTrame->stAdcSensors.stTouchScreen), stpCurrentSequenceIndexes);
          break;
      case WEIGHT_GRABING_OPERATING_STATE:
          stpCurrentSequenceIndexes->ucStep++;
          if(stpCurrentSequenceIndexes->ucStep == 4)
          {
              stpCurrentSequenceIndexes->ucSequence = 3;
              stpCurrentSequenceIndexes->ucStep = 0;
              ucCurrentOperatingState = WEIGHT_POSITIONING_OPERATING_STATE;
              if(stpTrame->stAdcSensors.ucGripIntensity > 0xC7)
              {
                stpCurrentSequenceIndexes->ucSequence = 4;
                stpCurrentSequenceIndexes->ucStep = 5;
                ucCurrentOperatingState = WEIGHT_SORTING_OPERATING_STATE;
              }
          }
          break;
      case WEIGHT_POSITIONING_OPERATING_STATE:
          stpCurrentSequenceIndexes->ucStep++;
          if(stpCurrentSequenceIndexes->ucStep == 2)
          {
              ucCurrentOperatingState = WEIGHT_SAMPLING_OPERATING_STATE;
          }
          break;
      case WEIGHT_SAMPLING_OPERATING_STATE:
          stpCurrentSequenceIndexes->ucSequence = ucGetSortingSequenceFromWheightSampling(&(stpTrame->stAdcSensors.ucWeightSensor));
          *ucpWeightType = stpCurrentSequenceIndexes->ucSequence - 4;
          stpCurrentSequenceIndexes->ucStep = 0;
          ucCurrentOperatingState = WEIGHT_SORTING_OPERATING_STATE;
          break;
      case WEIGHT_SORTING_OPERATING_STATE:
          stpCurrentSequenceIndexes->ucStep++;
          if(stpCurrentSequenceIndexes->ucStep == 6)
          {
              ucCurrentOperatingState = STAND_BY_OPERATING_STATE;
              *ucpWeightType = 4;
          }
          break;
      case WARM_UP_SETUP_OPERATING_STATE:
          stpCurrentSequenceIndexes->ucSequence = 0;
          stpCurrentSequenceIndexes->ucStep = 0;
          ucCurrentOperatingState = WARM_UP_OPERATING_STATE;
          break;
      case WARM_UP_OPERATING_STATE:
          stpCurrentSequenceIndexes->ucStep++;
          if(stpCurrentSequenceIndexes->ucStep >= 4)
          {
              stpCurrentSequenceIndexes->ucSequence++;
              stpCurrentSequenceIndexes->ucStep = 0;
          }
          if(stpCurrentSequenceIndexes->ucSequence == 3)
          {
              stpCurrentSequenceIndexes->ucSequence = 4;
              stpCurrentSequenceIndexes->ucStep = 5;
          }
          else if(stpCurrentSequenceIndexes->ucSequence >= 4)
          {
              stpCurrentSequenceIndexes->ucSequence = 0;
              stpCurrentSequenceIndexes->ucStep = 0;
              ucCurrentOperatingState = STAND_BY_OPERATING_STATE;
          }
          break;
    }
}

void vHandleTouchScreen(struct STTouchScreen* stpTouchScreen, struct STSequenceStep* stpCurrentSequenceIndexes)
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
    if(stpTouchScreen->ucX >= 0x00 && stpTouchScreen->ucX <= 0x60
        && stpTouchScreen->ucY >= 0x00 && stpTouchScreen->ucY <= 0x70)
    {
        stpCurrentSequenceIndexes->ucSequence = 0;
        stpCurrentSequenceIndexes->ucStep = 0;
        ucCurrentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
    // B2 appuyé?
    else if(stpTouchScreen->ucX >= 0x60 && stpTouchScreen->ucX <= 0xA0
        && stpTouchScreen->ucY >= 0xC0 && stpTouchScreen->ucY <= 0xFF)
    {
        stpCurrentSequenceIndexes->ucSequence = 1;
        stpCurrentSequenceIndexes->ucStep = 0;
        ucCurrentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
    // C5 appuyé?
    else if(stpTouchScreen->ucX >= 0xA0 && stpTouchScreen->ucX <= 0xFF
        && stpTouchScreen->ucY >= 0x70 && stpTouchScreen->ucY <= 0xC0)
    {
        stpCurrentSequenceIndexes->ucSequence = 2;
        stpCurrentSequenceIndexes->ucStep = 0;
        ucCurrentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
}

unsigned char ucGetSortingSequenceFromWheightSampling(unsigned char* ucpWeightSensor)
{
    unsigned char ucSequenceIndex;
  
    if(*ucpWeightSensor < 0x40)
    {
        ucSequenceIndex = 4;
    }
    else if(*ucpWeightSensor < 0x70)
    {
        ucSequenceIndex = 5;
    }
    else
    {
        ucSequenceIndex = 6;
    }
    
    return ucSequenceIndex;
}

void vSetOperatingState(unsigned char ucNewOperatingState)
{
    ucCurrentOperatingState = ucNewOperatingState;
}

unsigned char ucIsOperating(void)
{
    return ucCurrentOperatingState;
}