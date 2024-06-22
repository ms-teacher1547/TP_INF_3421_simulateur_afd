#include <stdio.h>
#include <stdlib.h>
#include <automate.h>

int main(void)
{
    int choix;
    do
    {
        printf("-------------MENU-------------\n");
        printf("Liste de Automate enregistrer\n");
        // code pour afficher les automate

        printf("------------------------------\n");
        printf("1. Ajouter un automate\n");
        printf("2. Tester un automate\n");
        printf("0. Quitter le programme\n");
        printf("entrez le choix:");
        scanf("%d",&choix);
        switch (choix)
        {
        case 1:
            printf("en cour de dev !!\n");
            break;
        
        case 2:
            printf("en cour de dev !!\n");
            break;

        
        default:
            printf("choix invalide !!\n");
            break;
        }
    } while (choix);
    

    return 0;
}