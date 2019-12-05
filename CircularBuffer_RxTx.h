/****************************************************************************************
   Nom du fichier: CircularBuffer_RxTx.h
   Auteur: Hugo Pellerin
   Date de cr�ation: 2019-12-02
        Fichier de d�claration et de d�finition de la reception de la trame
  
****************************************************************************************/
#ifndef CIRCULARBUFFER_RXTX_H
#define CIRCULARBUFFER_RXTX_H

// Pr�d�clarations
void vInitInterrupt(void);
void vCircularBuffer(struct TramePIC *tramePtr);
void vSendTrame(struct ArmState *statePtr);
unsigned char isTrameReceived(void);
void resetIsTrameReceived(void);
unsigned char ucKbHit(void);
#endif