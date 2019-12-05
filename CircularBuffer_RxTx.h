/****************************************************************************************
   Nom du fichier: CircularBuffer_RxTx.h
   Auteur: Hugo Pellerin
   Date de création: 2019-12-02
        Fichier de déclaration et de définition de la reception de la trame
  
****************************************************************************************/
#ifndef CIRCULARBUFFER_RXTX_H
#define CIRCULARBUFFER_RXTX_H

// Prédéclarations
void vInitInterrupt(void);
void vCircularBuffer(struct TramePIC *tramePtr);
void vSendTrame(struct ArmState *statePtr);
unsigned char isTrameReceived(void);
void resetIsTrameReceived(void);
unsigned char ucKbHit(void);
#endif