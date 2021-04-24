/****************************************************************************************
   Nom du fichier: CircularBuffer_RxTx.h
   Auteur: Hugo Pellerin
   Date de création: 2019-12-02
        Fichier de déclaration et de définition de la reception de la trame
  
****************************************************************************************/
#ifndef CIRCULARBUFFER_RXTX_H
#define CIRCULARBUFFER_RXTX_H

// Prédéclarations
//**************************************************************
void vInitInterrupt(void);
/*  Auteur: Hogo Pellerin
    
    Behaviour:  initialise l'interuption
    Parameters: void
    Return:     void
***************************************************************/

//**************************************************************
void vCircularBuffer(struct STTramePIC* stpTrame);
/*  Auteur: Hogo Pellerin
    
    Behaviour:  gère le buffer circulaire
    Parameters: struct STTramePIC* stpTrame
    Return:     void
***************************************************************/

//**************************************************************
void vSendTrame(struct STArmState *stpCurrentArmState);
/*  Auteur: Hogo Pellerin
    
    Behaviour:  envoie la trame des moteurs via RS-232
    Parameters: struct ArmState *stpState
    Return:     void
***************************************************************/

//**************************************************************
unsigned char ucIsTrameReceived(void);
/*  Auteur: John-William Lebel
    
    Behaviour:  renvoie 0 si on a pas reçu de trame depuis le dernier call
                de la fonction vResetIsTrameReceived().
    Parameters: void
    Return:     unsigned char
***************************************************************/

//**************************************************************
void vResetIsTrameReceived(void);
/*  Auteur: John-William Lebel
    
    Behaviour:  reset le "flag" qui indique qu'on vient de recevoir une trame.
                cette fonction et la fonction ucIsTrameReceived() sont utilisées
                ensemble pour ne pouvoir gèrer la réception qu'une seule fois.
    Parameters: void
    Return:     void
***************************************************************/
#endif