/**************************************************************************************************
   Nom du fichier : LCD.c
   Auteur : Stéphane Deschênes                  
   Date de création : 1-09-2019
	 Version 1.0
	 
	 Fichier qui contient les fonctions nécessaires à l'utilisation du LCD du 
   kit Dallas du CEGEP Limoilou.
   
	Versions:
	1.0:  Première version
								
***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include "_DS89C450Modifie.h"				// Définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"
#include "LCD.h"

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************
#define LIGNE0 0x80
#define LIGNE1 0xC0
#define LIGNE2 0x94
#define LIGNE3 0xD4

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************
void vAttendreBusyLcd(void);
void vDelaiLcd(void);
unsigned char ucDonneValeurLigne(unsigned char ucLine);

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************
 /* VIDE */

  
// *************************************************************************************************
// VARIABLES LOCALES
// *************************************************************************************************
unsigned char xdata *PtrLCDConfig = 0x8000;
unsigned char xdata *PtrLCDBusy = 0x8001;
unsigned char xdata *PtrLCDChar = 0x8002;



// *************************************************************************************************
void vInitLCD(void)
//
//  Auteur: Stéphane Deschênes
//  Date de création :  01-09-2019
//  Version 1.0
//
//  Description: Initialisation de l'écran LCD pour fonctionner avec la carte Dallas
//  Paramètres d'entrées : Aucun
//  Paramètres de sortie : Aucun
//  Notes     		       : Le premier delai est essentiel pour s'assurer que l'écran est bien en fonction 
//												 avant de commencer.
// *************************************************************************************************	
{	
	unsigned int i;
	for(i = 0; i < 12000; i++);	//Delai d'activation de l'ecran au demarrage	
  vAttendreBusyLcd();
	*PtrLCDConfig = 0x38;				// Fonction Set (8bits, 2 lines display, 5X8 dot)
 	vAttendreBusyLcd();
	*PtrLCDConfig = 0x0C;				// Display Control (Display on, cursor off et blink off)
	vEffaceLCD();
	vAttendreBusyLcd();
	*PtrLCDConfig = 0x06;				// Entry  Mode Set (Display is shifted by increment)	
}

#ifdef UTILISATION_CARACTERES_SPECIAUX
// *************************************************************************************************	
void vLoadCGRAM(unsigned char ucTab[8][8])
//
//  Auteur: Stéphane Deschênes 	
//  Date de création :  01-09-2019
//  Version 1.0
//
//  Description: Met dans la mémoire CGRAM du contrôleur de LCD un tableau complet pointé
//  Paramètres d'entrées : Tableau qui contient toutes les caractères spéciaux voulus
//  Paramètres de sortie : Aucun
//  Notes     		       : Sert à créer des caractères spéciaux
// *************************************************************************************************	
{
	unsigned char ucCompteurCaract;
	unsigned char ucCompteurOctetsDansCaract;
	
	// Boucle pour chacun des 8 caractères
	for (ucCompteurCaract= 0; ucCompteurCaract < 8; ucCompteurCaract++)		
	{
		
		// Boucle pour chacune des 8 lignes dans un caractère
		for(ucCompteurOctetsDansCaract = 0; ucCompteurOctetsDansCaract < 8; ucCompteurOctetsDansCaract++)
		{
			vAttendreBusyLcd();
			*PtrLCDConfig = 0x40 + (8*ucCompteurCaract) + ucCompteurOctetsDansCaract;
			vAttendreBusyLcd();
			*PtrLCDChar = ucTab[ucCompteurCaract][ucCompteurOctetsDansCaract];			
		}
	}	
}
#endif

// *************************************************************************************************
void vLcdEcrireCaract(unsigned char ucCaract, unsigned char ucLigne, unsigned char ucCase)
//
//  Auteur: Stéphane Deschênes, 
//  Date de création :  1-09-2019
//  Version 1.0
//
//  Description: Écrit un caractère sur le LCD, sur la ligne et la colonne voulue.
//  Paramètres d'entrées : ucCaract: Caractère que l'on veut écrire
//												 ucLigne:  Ligne où l'on veut écrire (o à 3)
//												 ucCase:  Colonne où l'on veut écrire (0 à 19)
//  Paramètres de sortie : Aucun
//  Notes     		       : Aucune
// *************************************************************************************************
{
	vAttendreBusyLcd();		
	*PtrLCDConfig = ucDonneValeurLigne(ucLigne) + ucCase;	
	vAttendreBusyLcd();
	*PtrLCDChar = ucCaract;
}


//****************************************************************************
void vAfficheLigneLCD(unsigned char ucTab[],unsigned char ucLine)
//
//  Auteur : Stéphane Deschênes                                     
//  Description : Affiche un tableau sur une ligne spécifiée en paramètre            
//  Date de création :  1-09-2019
//  Version 1.0
//  Paramètres d'entrée :  l'adresse du tableau et la ligne d'affichage
//  Paramètres de sortie : Aucun.                
//  Variables locales :    Aucune
//                                     
//****************************************************************************
{
	unsigned char i = 0;
	
	for(i = 0; i < 20 ; i++)
  {	 
    vLcdEcrireCaract(ucTab[i], ucLine, i);
  }	
}


//****************************************************************************
void vAfficheLCDComplet(unsigned char ucTab[4][21])
//
//  Auteur : Stéphane Deschênes                                     
//  Description : Affiche un tableau à deux dimensions sur le LCD            
//  Date de création :  1-09-2019
//  Version 1.0
//  Paramètres d'entrée :  l'adresse du tableau
//  Paramètres de sortie : Aucun.                
//  Variables locales :    Aucune
//                                     
//****************************************************************************
{
	unsigned char i;
	for(i = 0; i < 4 ; i++)
	{
		vAfficheLigneLCD(&ucTab[i][0], i);
	}			
}

//****************************************************************************
void vEffaceLCD(void)
//
//  Auteur : Stéphane Deschênes                                     
//  Description : Efface le LCD au complet           
//  Date de création :  1-09-2019
//  Version 1.0
//  Paramètres d'entrée :  Aucun
//  Paramètres de sortie : Aucun                
//  Variables locales :    Aucune
//                                     
//****************************************************************************
{	
	vAttendreBusyLcd(); 
	*PtrLCDConfig = 0x01;
}


// *************************************************************************************************
void vAttendreBusyLcd(void)
//
//  Auteur: Stéphane Deschênes 	
//  Date de création :  1-09-2019
//  Version 1.0
//
//  Description: Atttente que le LCD ne soit plus occupé (busy).Le flag busy devient à 0 lorsque le
//							 LCD n'est plus occupé.
//  Paramètres d'entrées : Aucun
//  Paramètres de sortie : Aucun
//  Notes     		       : Aucune
// *************************************************************************************************
{
	unsigned char i;
	while ( *PtrLCDBusy & 0x80 );
  for(i=0; i<10; i++);	
}

// *************************************************************************************************
unsigned char ucDonneValeurLigne(unsigned char ucLine)
//
//  Auteur: Stéphane Deschênes, 
//  Date de création :  1-09-2019
//  Version 1.0
//
//  Description: Associe la valeur réelle du pointeur en fonction d'une ligne voulue de 0 à 3
//  Paramètres d'entrées : ucLine: Ligne voulue de 0 à 3
//  Paramètres de sortie : Valeur réelle de la ligne ( LIGNE0, LIGNE1, LIGNE2,LIGNE3)
//  Notes     		       : Aucune
// *************************************************************************************************
{	
	unsigned char ucTemp;
	switch(ucLine)
	{
		case 0:			
      ucTemp = LIGNE0;
      break;
		case 1:          
			ucTemp = LIGNE1;
      break;  
		case 2:			 
      ucTemp = LIGNE2;
      break;  
    case 3:          
			ucTemp = LIGNE3;
      break;  
	}
	return ucTemp;
}


