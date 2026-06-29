#include <stdio.h>
int main () {
    unsigned jour, mois,annee, NbrJour;
    printf("Entrez une date : "); 
    scanf("%u/%u/%u", &jour, &mois, &annee);

    int estBissextile = 0;

if (annee > 1582) {
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        estBissextile = 1;
    }
} else {
    if (annee % 4 == 0) {
        estBissextile = 1;
    }
}
    if (jour == 0 || jour > 31 || mois == 0 || mois > 12 || (jour > 29 && mois == 2)) {
        printf("Date invalide\n");
    }   else if ((jour == 29 && mois == 2) && estBissextile == 0) {
        printf("Date invalide\n");
    }   else if (jour > 30 && (mois == 4 || mois == 6 || mois == 9 || mois == 11)) {
        printf("Date invalide\n");
    }   

    else 
    {
    int JourenPlus = jour + estBissextile;

    NbrJour = (annee - 1) * 365;

    if ( annee > 1582) {

        NbrJour += (annee - 1) / 4;
        NbrJour -= (annee - 1) / 100;
        NbrJour += (annee - 1) / 400;
        NbrJour += 2;

    }   else {

        NbrJour += (annee - 1) / 4; 

    } 

    /*
    unsigned JourenPlus;

    if (annee > 1582) 
    {
        if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0)
        {
            JourenPlus = jour + 1;
        } else {
            JourenPlus = jour;
        }
    } else 
    {
        if (annee % 4 == 0)
        {
            JourenPlus = jour + 1;
        } else {
            JourenPlus = jour;
        }
    }    

    AUTRE METHODE N°2 : Condition ternaire 

    int estBissextile = (annee > 1582) ? 
    ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) : 
    (annee % 4 == 0);

JourenPlus = jour + estBissextile;

    */

    switch (mois)
    {
    case 1:
    case 2:
        NbrJour += ((mois - 1) * 31) + jour;
        break;
    
    case 3:
    case 4:
        NbrJour += ((mois - 1) * 31) + JourenPlus - 3;
        break;

    case 5:
    case 6:
        NbrJour += ((mois - 1) * 31) + JourenPlus - 4;
        break;

    case 7:
    case 8:
    case 9:
        NbrJour += ((mois - 1) * 31) + JourenPlus - 5;
        break;

    case 10:
    case 11:
        NbrJour += ((mois - 1) * 31) + JourenPlus - 6;
        break;

    case 12:
        NbrJour += ((mois - 1) * 31) + JourenPlus - 7;
        break;

    default:
        break;
    }

    NbrJour = NbrJour - 1;
    NbrJour = NbrJour % 7;

    switch (NbrJour)
    {
    case 0:
        printf("C'est un Samedi");
        break;
    
    case 1:
        printf("C'est un Dimanche");
        break;

    case 2:
        printf("C'est un Lundi");
        break;

    case 3:
        printf("C'est un Mardi");
        break;

    case 4:
        printf("C'est un Mercredi");
        break;

    case 5:
        printf("C'est un Jeudi");
        break;

    case 6:
        printf("C'est un Vendredi");
        break;

    default:
        break;
    }

    printf("\n");

    return 0;

    }

}
