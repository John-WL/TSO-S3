/****************************************************************************************
   Nom du fichier : LCD.h
   Auteur : Stéphane Deschênes                  
  Date de création : 01-09-19
        Fichier de déclaration et de définition pour les fonctions de controle du LCD 
        sur le kit Dallas
  
****************************************************************************************/
#ifndef LCDH
#define LCDH

// *************************************************************************************************
//  CONSTANTS
// *************************************************************************************************

// Rajouter ce #define si on utilise les caractères spéciaux
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