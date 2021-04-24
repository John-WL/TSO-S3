/****************************************************************************************
   Nom du fichier : SequenceHandler.h
   Auteur : John-William Lebel
      Date de creation : 12-05-2019
      gérance de la séquence en fonction de la séquence envoyée par le PIC
  
****************************************************************************************/
#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

// Définitions
#define STAND_BY_OPERATING_STATE 0            // ne fait rien
#define WEIGHT_GRABING_OPERATING_STATE 1      // va chercher le poid sur le touchscreen

#define WARM_UP_SETUP_OPERATING_STATE 5       // initialise quelques paramètres pour la séquence d'échauffage

// Prototypes
//**************************************************************
void vHandleSequence(struct STTramePIC* stpTrame,
    struct STSequenceStep* stpCurrentSequenceIndexes,
    unsigned char* ucpWeightType);
/*  Auteur: John-William Lebel
    
    Behaviour:  gère la logique du bras robotisé.
                Au début, on test constamment le touchscreen.
                Tant qu'il n'y a pas de poid sur une des 3 cases, on ne fait rien.
                
                Dès qu'un point est reconnu, le bras se dirige à la bonne destination
                pour le prendre, le peser, et le mettre dans la bonne case.
                
                Si la pince manque le poid au moment de le saisir pour le mettre sur la balance,
                elle annule les séquences à venir et se remet en position de départ, jusqu'à ce
                qu'elle détecte un autre poid sur le touchscreen.
                
    Parameters: struct STTramePIC* stpTrame, struct STSequenceStep* stpCurrentSequenceIndexes, unsigned char* ucpWeightType
    Return:     void
***************************************************************/

//**************************************************************
void vSetOperatingState(unsigned char ucNewOperatingState);
/*  Auteur: John-William Lebel
    
    Behaviour:  set un nouvel état d'opération pour le bras.
                Les différents états d'opérations accèdable depuis le main sont dans
                ce fichier-ci, alors que les autres sont dans le fichier "SequenceHandler.c",
                et sont des opérations intermédiaires.
                
    Parameters: unsigned char ucNewOperatingState
    Return:     void
***************************************************************/

//**************************************************************
unsigned char ucIsOperating(void);
/*  Auteur: John-William Lebel
    
    Behaviour:  renvoie l'état d'opération actuel du bras.
                si on code un if(), isOperating() sera faux
                si et seulement si l'état d'opération est en "STAND_BY".
                
    Parameters: void
    Return:     unsigned char
***************************************************************/

#endif