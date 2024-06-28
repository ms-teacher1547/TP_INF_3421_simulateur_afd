#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <afd.h>
#include <error.h>

void get_afd_input(AFD *afd);
void get_and_simulate_strings(AFD *afd);

int main() {
    AFD afd;
    int num_states, alphabet_size;
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Entrer un nouvel automate\n");
        printf("2. Simuler des chaines\n");
        printf("3. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Entrez le nombre d'etats: ");
                scanf("%d", &num_states);
                printf("Entrez la taille de l'alphabet: ");
                scanf("%d", &alphabet_size);

                initialize_afd(&afd, num_states, alphabet_size);
                get_afd_input(&afd);

                if (!is_deterministic(&afd)) {
                    print_error("L'automate est Non-deterministe.");
                    break;
                }

                printf("Ajout AFD reussi.\n"); // Message d'ajout réussi
                break;
            case 2:
                get_and_simulate_strings(&afd);
                break;
            case 3:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 3);

    return 0;
}

void get_afd_input(AFD *afd) {
    int num_transitions, from_state, to_state;
    char symbol;

    printf("Entrez le nombre de transitions: ");
    scanf("%d", &num_transitions);

    for (int i = 0; i < num_transitions; ++i) {
        printf("Entrez la transition (from_state symbol to_state): ");
        scanf("%d %c %d", &from_state, &symbol, &to_state);
        set_transition(afd, from_state, symbol, to_state);
    }

    int initial_state;
    printf("Entrez l'etat initial: ");
    scanf("%d", &initial_state);
    set_initial_state(afd, initial_state);

    int num_final_states, final_state;
    printf("Entrez le nombre d'etats finaux: ");
    scanf("%d", &num_final_states);

    for (int i = 0; i < num_final_states; ++i) {
        printf("Entrez un etat final: ");
        scanf("%d", &final_state);
        add_final_state(afd, final_state);
    }
}

void get_and_simulate_strings(AFD *afd) {
    char input[100];

    while (1) {
        printf("Entrez une chaine (ou 'exit' pour quitter): ");
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            break;
        }
        int result = simulate_afd(afd, input);
        if (result == 1) {
            printf("La chaine est acceptee par l'AFD.\n");
        } else {
            // Explication du rejet
            printf("La chaine n'est pas acceptee par l'AFD. ");
            printf("Car elle n'a pas  atteint un etat final.\n");
        }
    }
}
