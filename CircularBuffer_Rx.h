/****************************************************************************************
   Nom du fichier: CircularBuffer_Rx.h
   Auteur: Hugo Pellerin
   Date de création: 2019-12-02
        Fichier de déclaration et de définition de la reception de la trame
  
****************************************************************************************/
#ifndef CIRCULARBUFFER_RX_H
#define CIRCULARBUFFER_RX_H

// Prédéclarations
void vInitInterrupt(void);
void vCircularBuffer(struct TramePIC *tramePtr);
unsigned char ucKbHit();
#endif