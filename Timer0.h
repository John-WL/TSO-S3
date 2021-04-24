/****************************************************************************************
   Nom du fichier: Timer0.h
   Auteur: John-William Lebel
   Date de cr�ation: 2019-11-29
        Fichier de d�claration et de d�finition pour g�rer le timer0

****************************************************************************************/
#ifndef TIMER0_H
#define TIMER0_H

// Pr�d�claration

//**************************************************************
void vInitTimer50ms(void);
/*  Auteur: John-William Lebel
    
    Behaviour:  initialise le timer 0 � 50ms
    Parameters: void
    Return:     void
***************************************************************/

//**************************************************************
void vUpdateCompteurTimer0(struct STCompteur* stCompteur);
/*  Auteur: Hugo Pellerin
    
    Behaviour:  initialise le timer 0 � 50ms
    Parameters: void
    Return:     void
***************************************************************/
#endif