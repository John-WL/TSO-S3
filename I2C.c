/**************************************************************************************************
  Nom du fichier : I2C.c
    
    Auteur: Hugo Pellerin
    Modifications:
      - John-William Lebel (2019-12-06) => ajout de commentaires
    Date de création : 30-08-2019
    Code et definition pour les fonctions de traitement du I2C.
***************************************************************************************************/
	
#include "_DS89C450Modifie.h"				// définition des bits et des registres du microcontrôleur
#include "_DeclarationGenerale.h"   // déclaration pour coder de façon peu conventionnelle
#include "I2C.h"                    // fichier .h associé à celui-ci

void vInitPortSerie_0(void);
void vDelaiI2C(UI uiTemps);

void vStartBitI2C()

{ 
  SDA = 1;
  SCL = 1;
  
  vDelaiI2C(2);
  SDA = 0;
  vDelaiI2C(2);
  SCL = 0;
  vDelaiI2C(2);
}

void vStopBitI2C()
{
  SDA = 0;
  SCL = 0;
  
  vDelaiI2C(2);
  SCL = 1;  
  vDelaiI2C(2);
  SDA = 1;
  vDelaiI2C(2);
}

void vEcrire1BitI2C(UC ucBitASortir)
{
  if(ucBitASortir)
    SDA = 1;
  else
    SDA = 0;
  
  vDelaiI2C(2);
  SCL = 1;
  vDelaiI2C(2);
  SCL = 0;
  vDelaiI2C(2);
}

UC ucLire1BitI2C()
{
  UC ucBitLu = 1;
  
  SDA = 1;
  vDelaiI2C(2);
  SCL = 1;
  vDelaiI2C(2);
    
  if(!SDA)
    ucBitLu = 0;
  
  SCL = 0;
  vDelaiI2C(2);
    
  return ucBitLu;  
}

unsigned char ucEcrire8BitsI2C(UC ucTxData)
{
  int i;
  for(i = 0; i < 8; i++)
  {
    if((ucTxData & 0x80) == 0x80) //7e bit a 1?
    {
      vEcrire1BitI2C(1);
    }
    else
    {
      vEcrire1BitI2C(0);
    }
    ucTxData = ucTxData << 1;
  }
  SCL = 1;
  return ucLire1BitI2C();
}

UC ucLire8BitsI2C(UC ucAck)
{
  UC ucRecu = 0x00;
  int i;
  for(i=0; i<8; i++)
  {
    ucRecu = ucRecu << 1;
    if(ucLire1BitI2C())
    {
      ucRecu++;
    }
  }
  vEcrire1BitI2C(ucAck);
  return ucRecu;
}
  
UC ucLireMemI2C(UI uiAdr)
{
  UC ucVal = 0x00;
  
  vStartBitI2C();
  
  ucEcrire8BitsI2C(0xA0);
  
  ucVal = uiAdr >> 8;
  ucEcrire8BitsI2C(ucVal);
  
  ucVal = uiAdr;
  ucEcrire8BitsI2C(ucVal);
  
  vStartBitI2C();
  
  ucEcrire8BitsI2C(0xA1);
  ucVal = ucLire8BitsI2C(1);
  
  vStopBitI2C();
  
  return ucVal;
}

// *************************************************************************************************
//  Auteur: Hugo Pellerin
//  Date de creation :  30-08-2019
//
//  Description: Bloque le programme pendant un temps donnee
//  Parametres d'entrees : uiTemps
//  Parametres de sortie : Aucun
//  Notes     		 	 : Aucune
//
void vDelaiI2C(UI uiTemps)
{
  int i;
  for(i = 0; i < uiTemps; i++){}
}
// *************************************************************************************************