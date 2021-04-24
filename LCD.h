/****************************************************************************************
   Nom du fichier : LCD.h
   Auteur : St�phane Desch�nes                  
  Date de cr�ation : 01-09-19
        Fichier de d�claration et de d�finition pour les fonctions de controle du LCD 
        sur le kit Dallas
  
****************************************************************************************/
#ifndef LCDH
#define LCDH

// *************************************************************************************************
//  CONSTANTS
// *************************************************************************************************

// Rajouter ce #define si on utilise les caract�res sp�ciaux
// #define UTILISATION_CARACTERES_SPECIAUX





// *************************************************************************************************
//  PREDECLARATION DE FONCTIONS
// *************************************************************************************************

//**************************************************************
void vInitLCD(void);
/*  Auteur: St�phane Desch�nes
    
    Behaviour: initialization du LCD
    Parameters: void
    Return: void
***************************************************************/

//**************************************************************
void vLoadCGRAM(unsigned char ucTab[8][8]);
/*  Auteur: St�phane Desch�nes
    
    Behaviour: load dans la ram du LCD une pr�configuration donn�e
    Parameters: unsigned char ucTab[8][8]
    Return: void
***************************************************************/

//**************************************************************
void vLcdEcrireCaract(unsigned char ucCaract, unsigned char ucLigne, unsigned char ucCase);
/*  Auteur: St�phane Desch�nes
    
    Behaviour: �cris un charact�re � un emplacement donn� sur le LCD
    Parameters: unsigned char ucCaract, unsigned char ucLigne, unsigned char ucCase
    Return: void
***************************************************************/

//**************************************************************
void vAfficheLigneLCD(unsigned char ucTab[], unsigned char ucLine);
/*  Auteur: St�phane Desch�nes
    
    Behaviour: �cris une string � une ligne donn�e sur le LCD
    Parameters: unsigned char ucTab[], unsigned char ucLigne
    Return: void
***************************************************************/

//**************************************************************
void vAfficheLCDComplet(unsigned char ucTab[4][21]);
/*  Auteur: St�phane Desch�nes
    
    Behaviour: �cris sur tout le LCD au complet
    Parameters: unsigned char ucTab[4][21]
    Return: void
***************************************************************/

//**************************************************************
void vEffaceLCD(void);
/*  Auteur: St�phane Desch�nes
    
    Behaviour: affiche pleins d'espace (' ') partout sur tout les caract�res du LCD
    Parameters: void
    Return: void
***************************************************************/
#endif