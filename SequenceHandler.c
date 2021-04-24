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
unsigned char ucCurrentOperatingState = STAND_BY_OPERATING_STATE; // valeur par défaut de l'éxecution du programme
                                                                  // par défaut, le programme attend qu'un poid se
                                                                  // place sur le touchscreen avant de
                                                                  // poursuivre l'éxecution

// prototypes

//**************************************************************
void vHandleTouchScreen(struct STTouchScreen* stpTouchScreen, struct STSequenceStep* stpCurrentSequenceIndexes);
/*  Auteur: John-William Lebel
    
    Behaviour:  test le touchscreen jusqu'à ce que des valeurs x et y correspondants à l'une des 3 cases A6, B2 ou C5
                soient lues. Dès qu'une de ces cases est repérée, ucCurrentOperatingState est actualisée 
                pour poursuivre l'éxecution dans le switch case de la fonction vHandleSequence, et la
                séquence et le step sont settés de sorte que la pince puisse aller chercher le poid à la bonne case.
                
    Parameters: struct STTouchScreen* stpTouchScreen, struct STSequenceStep* stpCurrentSequenceIndexes
    Return:     void
***************************************************************/

//**************************************************************
unsigned char ucGetSortingSequenceFromWheightSampling(unsigned char* ucpWeightSensor);
/*  Auteur: John-William Lebel
    
    Behaviour:  test la balance. Si la valeur lue correspond au poid bleu, le numéro de la séquence pour aller déposer le poid bleu
                à la case du poid bleu est retourné, de même pour les autres poids. 
                
    Parameters: unsigned char* ucpWeightSensor
    Return:     unsigned char
***************************************************************/

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
          if(stpCurrentSequenceIndexes->ucStep == 4)  // si on atteint la 4e séquence, c'est qu'on a fini
                                                      // d'aller prendre le poid dans la pince. On passe à
                                                      // la séquence suivante pour aller porter le poid sur
                                                      // la balance. 
          {
              stpCurrentSequenceIndexes->ucSequence = 3;
              stpCurrentSequenceIndexes->ucStep = 0;
              ucCurrentOperatingState = WEIGHT_POSITIONING_OPERATING_STATE;
            
              if(stpTrame->stAdcSensors.ucGripIntensity > 0xC7) // par contre, si la pince détecte qu'elle n'a
                                                                // en réalité rien pris du tout, eh bien on
                                                                // revient à la position de base et on attend
                                                                // qu'un nouveau poid se présente sur le touchscreen
              {
                stpCurrentSequenceIndexes->ucSequence = 4;  // oui, cette séquence et ce step ont l'air d'être
                stpCurrentSequenceIndexes->ucStep = 5;      // absurdement arbitraires. En réalité, ils correspondent
                                                            // à la position de repos du bras. 
                
                ucCurrentOperatingState = WEIGHT_SORTING_OPERATING_STATE;
                      // ça, c'est le summom des conneries. En fait, j'étais un peu lâche et je n'avais pas envie de coder un
                      // autre case dans le switch avec un autre #define rien que pour remettre le bras à sa position
                      // de base. J'avais remarqué qu'en settant l'état d'éxecution (ucCurrentOperatingState) à 
                      // WEIGHT_SORTING_OPERATING_STATE quand les variables séquences et steps étaient settés aux 
                      // valeurs que j'ai mis plus haut, eh bien le code s'éxecute absolument correctement! 
                      // en effet, dans le case WEIGHT_SORTING_OPERATING_STATE, dès que le step est éguale à 6,
                      // ucCurrentOperatingState est remis à STAND_BY_OPERATING_STATE. 
                      //
                      // En gors, après toutes ces lignes de codes, on sort de la fonction, le main éxecute la séquence 4
                      // et le step 5. Ensuite, on rerentre dans cette fonction, et on rentre dans le case WEIGHT_SORTING_OPERATING_STATE.
                      // Le step est incrémenté à 6 avant d'être testé. Puisqu'il était égal à 5, il entre dans le if et remet ucCurrentOperatingState
                      // à STAND_BY_OPERATING_STATE. Tadaa. Tout ça parce que je suis lâche. 
                                                                        
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
                    // 
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