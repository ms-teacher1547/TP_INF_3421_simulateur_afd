#include <stdio.h>
#include <stdlib.h>
#include <automate.h>

int in_alphabet(char x,char* alphabet)
{
    int exist = 0;
    int i = 0;
    while (!exist && alphabet[i] != '\0')
    {
        if(alphabet[i] == x)
            exist = !exist;
        i++;
    }

    return exist;
    
}
Automate* init_automate(int nbEta, int nbTransi, char* alphabet)
{
    Automate* afn = (Automate*)malloc(sizeof(Automate));
    afn->nombreEtats = nbEta;
    afn->nombreTransi = nbTransi;

    int i =0;
    while (alphabet[i] != '\0')
    {
        afn->alphabet[i] = alphabet[i];
        i++;
    }
    afn->alphabet[i] = alphabet[i];
    afn->etats = (Etat*)malloc(sizeof(Etat)*nbEta);
    

    return afn;
}
void free_automate(Automate* afn)
{
    if(afn != NULL)
    {
        if(afn->etats != NULL)
            free(afn->etats);
        if(afn->trans != NULL)
            free(afn->trans);
    }

    return ;
}