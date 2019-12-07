/****************************************************************************************
   Nom du fichier: SubOptimizedLcdPrinter.h
   Auteur: John-William Lebel
   Date de création: 2019-11-29
        Fichier de déclaration et de définition pour optimiser le temps d'affichage du LCD.
        Au lieu d'afficher le LCD au complet à chaque fois, on affiche seulement l'emplacement
        où sont affichées les valeurs variables.
        
        Une autre optimisation serait de n'afficher uniquement que les valeurs qui changent
        sur le LCD, mais après avoir finalisé et essayé le projet, on s'est rendu compte que
        cette optimisation n'était pas nécessaire pour garder une comunication suffisante avec le PIC.
  
****************************************************************************************/
#ifndef SUBOPTIMIZEDLCDPRINTER_H
#define SUBOPTIMIZEDLCDPRINTER_H

// Prédéclarations
//**************************************************************
void vPrintLcdDeltaMotors(struct STArmState* stpCurrentArmState);
/*  Auteur: John-William Lebel
    
    Behaviour:  update sur le LCD la valeur des 5 moteurs
    Parameters: struct ArmState* stpCurrentArmState
    Return:     void
***************************************************************/

//**************************************************************
void vPrintLcdDeltaTrame(struct STTramePIC* stpTrame);
/*  Auteur: John-William Lebel
    
    Behaviour:  update sur le LCD le touchscreen, la pince et la balance
    Parameters: struct TramePIC* stpTrame
    Return:     void
***************************************************************/

//**************************************************************
void vPrintLcdDeltaWeightType(unsigned char* ucWeightType);
/*  Auteur: John-William Lebel
    
    Behaviour:  update sur le LCD la couleur du poid
    Parameters: unsigned char* stpWeightType
    Return:     void
***************************************************************/

//**************************************************************
void vPrintLcdDeltaManualSettings(struct STKeyboardManualSettings* stpKeyboardManualSettings);
/*  Auteur: John-William Lebel
    
    Behaviour:  update sur le LCD la vitesse de déplacement manuelle des moteur
    Parameters: struct KeyboardManualSettings* stpKeyboardManualSettings
    Return:     void
***************************************************************/

//**************************************************************
void vPrintLcdCurrentSequenceStep(struct STSequenceStep* stpCurrentSequenceIndexes);
/*  Auteur: John-William Lebel
    
    Behaviour:  update sur le LCD la séquence et le step actuels dans l'array des déplacements
    Parameters: struct SequenceStep* stpCurrentSequenceIndexes
    Return:     void
***************************************************************/

//**************************************************************
void vPrintLcdDeltaConnectionState(unsigned char ucConnectionStateString[]);
/*  Auteur: John-William Lebel
    
    Behaviour:  update sur le LCD l'état de la communication série avec le PIC (onL ou offL)
    Parameters: struct SequenceStep* stpCurrentSequenceIndexes
    Return:     void
***************************************************************/

#endif