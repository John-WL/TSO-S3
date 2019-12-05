/*****************************Contrôle Communication Série*******************************/
/* 
   Nom du fichier : CircularBuffer_Rx.c
   Auteur : Hugo Pellerin

Date de creation :  02-12-19
 
Fonction necessaire pour reception la trame du PIC
    
    
      
*****************************************************************************************/
#include <stdio.h>   
#include "RxTx232.h"
#include "_DS89C450Modifie.h"				// Définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"
#include "ProjectDefinitions.h"
#include "CircularBuffer_RxTx.h"

unsigned char ucRx(void);
unsigned char ucHandleCS(struct ArmState *statePtr);
void ucTx(unsigned char ucTransmi);

unsigned char ucIndiceIN = 0;
unsigned char ucIndiceOUT = 0;
unsigned char ucIndiceTrame = 0;
unsigned char ucData = 0;
unsigned char ucIsTrameReceived = 0;

unsigned char ucCircularBuffer[8];


void vInitInterrupt(void)
//
//  Auteur: Hugo Pellerin 	
//  Date de création :  19-11-08
//  Version 1.0
//
//  Description: initialise les interruption (general, SERIAL0)
//               
//  Paramètres d'entrées : -
//  Paramètres de sortie : -
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
    ES0 = 1;    // Permettre interruption du Serial 0
    EA = 1;     // Permettre les interruptions générale
}

void InterruptionSerie0 (void) interrupt 4
//
//  Auteur: Hugo Pellerin 	
//  Date de création :  19-11-08
//  Version 1.0
//
//  Description: remet les flag du port serie a 0 et call RX
//  Paramètres d'entrées : -
//  Paramètres de sortie : vrai ou faux
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
    if(RI_0 == 1)
    {
        ucData = ucRx();
        ucCircularBuffer[ucIndiceIN] = ucData;
        ucIndiceIN = ((ucIndiceIN + 1) & 0x07);
        RI_0 = 0;
    }
    if(TI_0 == 1)
    {
        TI_0 = 0;
    }
}

unsigned char ucRx()
//
//  Auteur: Hugo Pellerin 	
//  Date de création :  19-11-08
//  Version 1.0
//
//  Description: met la valeur de SBUF0 dans une varible et appel des fonction pour l'affichage LCD
//  Paramètres d'entrées : -
//  Paramètres de sortie : -
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
    unsigned char ucTemp;
    ucTemp = SBUF0;
    return ucTemp;
}

void vCircularBuffer(struct TramePIC *tramePtr)
//
//  Auteur: Hugo Pellerin 	
//  Date de création :  19-12-02
//  Version 1.0
//
//  Description: 
//  Paramètres d'entrées : -
//  Paramètres de sortie : -
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
    unsigned char ucRecu = 0;
    if(ucIndiceIN != ucIndiceOUT)
    {
        switch(ucIndiceTrame)
        {
            case 0:
                ucRecu = ucCircularBuffer[ucIndiceOUT];
                ucCircularBuffer[ucIndiceOUT] = 0x00;
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
              
                if(ucRecu == 'G')
                {
                    ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                }
                
                break;
            case 1:
                ucRecu = ucCircularBuffer[ucIndiceOUT];
                ucCircularBuffer[ucIndiceOUT] = 0x00;
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
              
                if(ucRecu == 'O')
                {
                    ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                }
                else 
                {
                    ucIndiceTrame = ((ucIndiceTrame - 1) & 0x07);
                }
                break;
            case 2:
                tramePtr->adcSensors.touchScreen.x = ucCircularBuffer[ucIndiceOUT];
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
                ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                break;
            case 3:
                tramePtr->adcSensors.touchScreen.y = ucCircularBuffer[ucIndiceOUT];
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
                ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                break;
            case 4:
                tramePtr->adcSensors.gripIntensity = ucCircularBuffer[ucIndiceOUT];
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
                ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                break;
            case 5:
                tramePtr->adcSensors.weightSensor = ucCircularBuffer[ucIndiceOUT];
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
                ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                break;
            case 6:
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
                ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                break;
            case 7:
                tramePtr->ucCheckSum = ucCircularBuffer[ucIndiceOUT];
                ucIndiceOUT = ((ucIndiceOUT + 1) & 0x07);
                ucIndiceTrame = ((ucIndiceTrame + 1) & 0x07);
                ucIsTrameReceived = 1;    // circular buffer is full and trame is read to be read
                break;
        }
    }
}

void vSendTrame(struct ArmState *statePtr)
{
    ucTx('G');
    ucTx('O');
    ucTx(statePtr->base);
    ucTx(statePtr->shoulder);
    ucTx(statePtr->elbow);
    ucTx(statePtr->wrist);
    ucTx(statePtr->grip);
    ucTx(ucHandleCS(statePtr));
}

unsigned char ucHandleCS(struct ArmState *statePtr)
{
    unsigned char ucCheckSum;
    ucCheckSum = (0x47 + 0x4F + statePtr->base + statePtr->shoulder + statePtr->elbow + statePtr->wrist + statePtr->grip);  
    return ucCheckSum;
}

void ucTx(unsigned char ucTransmi)
//
//  Auteur: Hugo Pellerin 	
//  Date de création :  19-11-08
//  Version 1.0
//
//  Description: envoie une donner sur UART
//  Paramètres d'entrées : donne a envoyer unsigned char
//  Paramètres de sortie : -
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
    ES0 = 0;
    SBUF0 = ucTransmi;
    while(TI_0 == 0);
    TI_0 = 0;
    ES0 = 1;
}

unsigned char ucKbHit()
//
//  Auteur: Hugo Pellerin 	
//  Date de création :  19-10-11
//  Version 1.0
//
//  Description: Test si le flag du port serie est lever
//  Paramètres d'entrées : -
//  Paramètres de sortie : vrai ou faux
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
    return (unsigned char) RI_0;
}

unsigned char isTrameReceived()
{
    return ucIsTrameReceived;
}

void resetIsTrameReceived()
{
    ucIsTrameReceived = 0;
}