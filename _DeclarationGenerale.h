 


// ***************** FICHIER:  _DeclarationGenerale.H  ************************
//
//  DEFINITION GENERALE POUR UN PROJET
//
//  Application realisee avec Keil 3.6
//
//  AUTEUR : DANIEL BRETON
//  DATE CREATION :    2014-01-13         VERSION: 1.0
//  DATE MODIFICATION: ****-**-**
//
// ****************************************************************************
// CHOIX DU TYPE DE COMPILATEUR
//
   #define KEIL_COMPILATEUR
//
//
// ****************************************************************************
 
 
 #ifndef DECLARATIONGENERALEH
   #define DECLARATIONGENERALEH

   #include "_DS89C450Modifie.h"

   // *************************************************************************
   //
   //                            DEFINITION DE MOT CLE
   //
   // *************************************************************************
   #define ACTIF   1              //
   #define INACTIF 0              //
   
   #define PESE    0              // Pour les boutons peses a 0.
   #define PASPESE 1

   #define ON      1              //
   #define OFF     0              //
   #define VRAI    1              //
   #define FAUX    0              //
   #define TRUE    1              //
   #define FALSE   0              //


   // *************************************************************************
   //
   //                            DEFINITION DE TYPE
   //
   // *************************************************************************
    
   #ifndef NULL
     #define NULL    0  
   #endif

     
   #define UC unsigned char
   #define UI unsigned int
   #define US unsigned short int
   #define USI unsigned short int

   #define UINT16 US


#endif // #ifndef _DECLARATIONGENERALEH


// *************************************************************************




