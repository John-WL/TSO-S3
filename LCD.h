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
void vInitLCD(void);
void vLoadCGRAM(unsigned char ucTab[8][8]);
void vLcdEcrireCaract(unsigned char ucCaract, unsigned char ucLigne, unsigned char ucCase);
void vAfficheLigneLCD(unsigned char ucTab[],unsigned char ucLine);
void vAfficheLCDComplet(unsigned char ucTab[4][21]);
void vEffaceLCD(void);
#endif