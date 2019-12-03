/****************************************************************************************
   Nom du fichier: CircularBuffer_Rx.h
   Auteur: Hugo Pellerin
   Date de cr�ation: 2019-12-02
        Fichier de d�claration et de d�finition de la reception de la trame
  
****************************************************************************************/
#ifndef CIRCULARBUFFER_RX_H
#define CIRCULARBUFFER_RX_H

// Pr�d�clarations
void vInitInterrupt(void);
void vCircularBuffer(struct TramePIC *tramePtr);
unsigned char ucKbHit();
#endif