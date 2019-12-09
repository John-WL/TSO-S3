/**************************************************************************************************
    Nom du fichier : SequenceHandler.c
    
    Auteur : John-William Lebel
    Date de cr�ation : 2019-12-05
    g�rance de la s�quence en fonction de la s�quence envoy�e par le PIC
    
***************************************************************************************************/
#include "SequenceHandler.h"
#include "ProjectDefinitions.h"

// d�finitions
#define WEIGHT_POSITIONING_OPERATING_STATE 2  // va mettre le poid sur la balance
#define WEIGHT_SAMPLING_OPERATING_STATE 3     // calcul la couleur du poid en fonction de ce que la balance indique
#define WEIGHT_SORTING_OPERATING_STATE 4      // va porter le poid dans la bonne case

#define WARM_UP_OPERATING_STATE 6             // fait quelques mouvements pour s'�chauffer

// variables
unsigned char ucCurrentOperatingState = STAND_BY_OPERATING_STATE; // valeur par d�faut de l'�xecution du programme
                                                                  // par d�faut, le programme attend qu'un poid se
                                                                  // place sur le touchscreen avant de
                                                                  // poursuivre l'�xecution

// prototypes

//**************************************************************
void vHandleTouchScreen(struct STTouchScreen* stpTouchScreen, struct STSequenceStep* stpCurrentSequenceIndexes);
/*  Auteur: John-William Lebel
    
    Behaviour:  test le touchscreen jusqu'� ce que des valeurs x et y correspondants � l'une des 3 cases A6, B2 ou C5
                soient lues. D�s qu'une de ces cases est rep�r�e, ucCurrentOperatingState est actualis�e 
                pour poursuivre l'�xecution dans le switch case de la fonction vHandleSequence, et la
                s�quence et le step sont sett�s de sorte que la pince puisse aller chercher le poid � la bonne case.
                
    Parameters: struct STTouchScreen* stpTouchScreen, struct STSequenceStep* stpCurrentSequenceIndexes
    Return:     void
***************************************************************/

//**************************************************************
unsigned char ucGetSortingSequenceFromWheightSampling(unsigned char* ucpWeightSensor);
/*  Auteur: John-William Lebel
    
    Behaviour:  test la balance. Si la valeur lue correspond au poid bleu, le num�ro de la s�quence pour aller d�poser le poid bleu
                � la case du poid bleu est retourn�, de m�me pour les autres poids. 
                
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
          if(stpCurrentSequenceIndexes->ucStep == 4)  // si on atteint la 4e s�quence, c'est qu'on a fini
                                                      // d'aller prendre le poid dans la pince. On passe �
                                                      // la s�quence suivante pour aller porter le poid sur
                                                      // la balance. 
          {
              stpCurrentSequenceIndexes->ucSequence = 3;
              stpCurrentSequenceIndexes->ucStep = 0;
              ucCurrentOperatingState = WEIGHT_POSITIONING_OPERATING_STATE;
            
              if(stpTrame->stAdcSensors.ucGripIntensity > 0xC7) // par contre, si la pince d�tecte qu'elle n'a
                                                                // en r�alit� rien pris du tout, eh bien on
                                                                // revient � la position de base et on attend
                                                                // qu'un nouveau poid se pr�sente sur le touchscreen
              {
                stpCurrentSequenceIndexes->ucSequence = 4;  // oui, cette s�quence et ce step ont l'air d'�tre
                stpCurrentSequenceIndexes->ucStep = 5;      // absurdement arbitraires. En r�alit�, ils correspondent
                                                            // � la position de repos du bras. 
                
                ucCurrentOperatingState = WEIGHT_SORTING_OPERATING_STATE;
                      // �a, c'est le summom des conneries. En fait, j'�tais un peu l�che et je n'avais pas envie de coder un
                      // autre case dans le switch avec un autre #define rien que pour remettre le bras � sa position
                      // de base. J'avais remarqu� qu'en settant l'�tat d'�xecution (ucCurrentOperatingState) � 
                      // WEIGHT_SORTING_OPERATING_STATE quand les variables s�quences et steps �taient sett�s aux 
                      // valeurs que j'ai mis plus haut, eh bien le code s'�xecute absolument correctement! 
                      // en effet, dans le case WEIGHT_SORTING_OPERATING_STATE, d�s que le step est �guale � 6,
                      // ucCurrentOperatingState est remis � STAND_BY_OPERATING_STATE. 
                      //
                      // En gors, apr�s toutes ces lignes de codes, on sort de la fonction, le main �xecute la s�quence 4
                      // et le step 5. Ensuite, on rerentre dans cette fonction, et on rentre dans le case WEIGHT_SORTING_OPERATING_STATE.
                      // Le step est incr�ment� � 6 avant d'�tre test�. Puisqu'il �tait �gal � 5, il entre dans le if et remet ucCurrentOperatingState
                      // � STAND_BY_OPERATING_STATE. Tadaa. Tout �a parce que je suis l�che. 
                                                                        
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
      //x:0x00 � 0x60
      //y:0x00 � 0x70
    //B2::
      //x:0x60 � 0xA0
      //y:0xC0 � 0xFF
    //C5::
      //x:0xA0 � 0xFF
      //y:0x70 � 0xC0

    // A6 appuy�?
    if(stpTouchScreen->ucX >= 0x00 && stpTouchScreen->ucX <= 0x60
        && stpTouchScreen->ucY >= 0x00 && stpTouchScreen->ucY <= 0x70)
    {
        stpCurrentSequenceIndexes->ucSequence = 0;
        stpCurrentSequenceIndexes->ucStep = 0;
        ucCurrentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
    // B2 appuy�?
    else if(stpTouchScreen->ucX >= 0x60 && stpTouchScreen->ucX <= 0xA0
        && stpTouchScreen->ucY >= 0xC0 && stpTouchScreen->ucY <= 0xFF)
    {
        stpCurrentSequenceIndexes->ucSequence = 1;
        stpCurrentSequenceIndexes->ucStep = 0;
        ucCurrentOperatingState = WEIGHT_GRABING_OPERATING_STATE;
    }
    // C5 appuy�?
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