/****************************************************************************************
   Nom du fichier : SequenceHandler.h
   Auteur : John-William Lebel
      Date de creation : 12-05-2019
      g�rance de la s�quence en fonction de la s�quence envoy�e par le PIC
  
****************************************************************************************/
#ifndef SEQUENCEHANDLER_H
#define SEQUENCEHANDLER_H

// D�finitions
#define STAND_BY_OPERATING_STATE 0            // ne fait rien
#define WEIGHT_GRABING_OPERATING_STATE 1      // va chercher le poid sur le touchscreen

#define WARM_UP_SETUP_OPERATING_STATE 5       // initialise quelques param�tres pour la s�quence d'�chauffage

// Prototypes
//**************************************************************
void vHandleSequence(struct STTramePIC* stpTrame,
    struct STSequenceStep* stpCurrentSequenceIndexes,
    unsigned char* ucpWeightType);
/*  Auteur: John-William Lebel
    
    Behaviour:  g�re la logique du bras robotis�.
                Au d�but, on test constamment le touchscreen.
                Tant qu'il n'y a pas de poid sur une des 3 cases, on ne fait rien.
                
                D�s qu'un point est reconnu, le bras se dirige � la bonne destination
                pour le prendre, le peser, et le mettre dans la bonne case.
                
                Si la pince manque le poid au moment de le saisir pour le mettre sur la balance,
                elle annule les s�quences � venir et se remet en position de d�part, jusqu'� ce
                qu'elle d�tecte un autre poid sur le touchscreen.
                
    Parameters: struct STTramePIC* stpTrame, struct STSequenceStep* stpCurrentSequenceIndexes, unsigned char* ucpWeightType
    Return:     void
***************************************************************/

//**************************************************************
void vSetOperatingState(unsigned char ucNewOperatingState);
/*  Auteur: John-William Lebel
    
    Behaviour:  set un nouvel �tat d'op�ration pour le bras.
                Les diff�rents �tats d'op�rations acc�dable depuis le main sont dans
                ce fichier-ci, alors que les autres sont dans le fichier "SequenceHandler.c",
                et sont des op�rations interm�diaires.
                
    Parameters: unsigned char ucNewOperatingState
    Return:     void
***************************************************************/

//**************************************************************
unsigned char ucIsOperating(void);
/*  Auteur: John-William Lebel
    
    Behaviour:  renvoie l'�tat d'op�ration actuel du bras.
                si on code un if(), isOperating() sera faux
                si et seulement si l'�tat d'op�ration est en "STAND_BY".
                
    Parameters: void
    Return:     unsigned char
***************************************************************/

#endif