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

//**************************************************************
void vInitLCD(void);
/*  Auteur: Stéphane Deschênes
    
    Behaviour: initialization du LCD
    Parameters: void
    Return: void
***************************************************************/

//**************************************************************
void vLoadCGRAM(unsigned char ucTab[8][8]);
/*  Auteur: Stéphane Deschênes
    
    Behaviour: load dans la ram du LCD une préconfiguration donnée
    Parameters: unsigned char ucTab[8][8]
    Return: void
***************************************************************/

//**************************************************************
void vLcdEcrireCaract(unsigned char ucCaract, unsigned char ucLigne, unsigned char ucCase);
/*  Auteur: Stéphane Deschênes
    
    Behaviour: écris un charactère à un emplacement donné sur le LCD
    Parameters: unsigned char ucCaract, unsigned char ucLigne, unsigned char ucCase
    Return: void
***************************************************************/

//**************************************************************
void vAfficheLigneLCD(unsigned char ucTab[], unsigned char ucLine);
/*  Auteur: Stéphane Deschênes
    
    Behaviour: écris une string à une ligne donnée sur le LCD
    Parameters: unsigned char ucTab[], unsigned char ucLigne
    Return: void
***************************************************************/

//**************************************************************
void vAfficheLCDComplet(unsigned char ucTab[4][21]);
/*  Auteur: Stéphane Deschênes
    
    Behaviour: écris sur tout le LCD au complet
    Parameters: unsigned char ucTab[4][21]
    Return: void
***************************************************************/

//**************************************************************
void vEffaceLCD(void);
/*  Auteur: Stéphane Deschênes
    
    Behaviour: affiche pleins d'espace (' ') partout sur tout les caractères du LCD
    Parameters: void
    Return: void
***************************************************************/
#endif