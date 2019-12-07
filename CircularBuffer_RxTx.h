/****************************************************************************************
   Nom du fichier: CircularBuffer_RxTx.h
   Auteur: Hugo Pellerin
   Date de cr�ation: 2019-12-02
        Fichier de d�claration et de d�finition de la reception de la trame
  
****************************************************************************************/
#ifndef CIRCULARBUFFER_RXTX_H
#define CIRCULARBUFFER_RXTX_H

// Pr�d�clarations
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
    
    Behaviour:  g�re le buffer circulaire
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
    
    Behaviour:  renvoie 0 si on a pas re�u de trame depuis le dernier call
                de la fonction vResetIsTrameReceived().
    Parameters: void
    Return:     unsigned char
***************************************************************/

//**************************************************************
void vResetIsTrameReceived(void);
/*  Auteur: John-William Lebel
    
    Behaviour:  reset le "flag" qui indique qu'on vient de recevoir une trame.
                cette fonction et la fonction ucIsTrameReceived() sont utilis�es
                ensemble pour ne pouvoir g�rer la r�ception qu'une seule fois.
    Parameters: void
    Return:     void
***************************************************************/
#endif