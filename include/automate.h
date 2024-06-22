#ifndef __AUTOMATE__H__
#define __AUTOMATE__H__


    #define MAX_SYNBOLE 255
    
    typedef struct Etat
    {
        int etiq;
        int type;
    }Etat;

    typedef struct Transi
    {
        Etat* entrer;
        char synbole;
        Etat* sorti;
    }Transi;

    typedef struct automate
    {
        int nombreEtats;
        int nombreTransi;
        Etat* etats;// consider comme tableau d'etats
        Transi* trans; // comme tableau de transition
        char alphabet[MAX_SYNBOLE];
    }Automate;

    int in_alphabet(char x,char* alphabet);
    Automate* init_automate(int nbEta, int nbTransi, char* alphabet);
    void free_automate(Automate*);

    
#endif