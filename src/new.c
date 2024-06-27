#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_TRANSITIONS 100
#define MAX_INPUT 100

typedef struct {
    int current_state;
    char input;
    int next_state;
} Transition;

typedef struct {
    int num_states;
    int num_transitions;
    int initial_state;
    int final_states[MAX_STATES];
    int num_final_states;
    Transition transitions[MAX_TRANSITIONS];
} AFD;

void initialize_afd(AFD *afd) {
    afd->num_states = 0;
    afd->num_transitions = 0;
    afd->initial_state = 0;
    afd->num_final_states = 0;
}

void add_transition(AFD *afd, int current_state, char input, int next_state) {
    afd->transitions[afd->num_transitions].current_state = current_state;
    afd->transitions[afd->num_transitions].input = input;
    afd->transitions[afd->num_transitions].next_state = next_state;
    afd->num_transitions++;
}

int is_final_state(AFD *afd, int state) {
    for (int i = 0; i < afd->num_final_states; i++) {
        if (afd->final_states[i] == state) {
            return 1;
        }
    }
    return 0;
}

int simulate_afd(AFD *afd, const char *input_string) {
    int current_state = afd->initial_state;
    for (int i = 0; i < strlen(input_string); i++) {
        int found = 0;
        for (int j = 0; j < afd->num_transitions; j++) {
            if (afd->transitions[j].current_state == current_state && afd->transitions[j].input == input_string[i]) {
                current_state = afd->transitions[j].next_state;
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Transition non trouvée pour l'état %d avec l'entrée '%c'\n", current_state, input_string[i]);
            return 0;
        }
    }
    return is_final_state(afd, current_state);
}

void afficher_afd(AFD *afd) {
    printf("\n--- Détails de l'AFD ---\n");
    printf("Nombre d'états : %d\n", afd->num_states);
    printf("État initial : %d\n", afd->initial_state);
    printf("États finaux : ");
    for (int i = 0; i < afd->num_final_states; i++) {
        printf("%d ", afd->final_states[i]);
    }
    printf("\nTransitions :\n");
    for (int i = 0; i < afd->num_transitions; i++) {
        printf("(%d, '%c') -> %d\n", afd->transitions[i].current_state, afd->transitions[i].input, afd->transitions[i].next_state);
    }
    printf("-----------------------\n");
}

void afficher_menu() {
    printf("\n--- Simulateur d'AFD ---\n");
    printf("1. Ajouter un état final\n");
    printf("2. Ajouter une transition\n");
    printf("3. Tester une chaîne\n");
    printf("4. Afficher l'AFD\n");
    printf("5. Quitter\n");
    printf("Choisissez une option : ");
}

int main() {
    AFD afd;
    initialize_afd(&afd);

    int choix, etat, etat_suivant, nombre_final_states;
    char input;
    char chaine[MAX_INPUT];

    printf("Entrez le nombre d'états : ");
    scanf("%d", &afd.num_states);

    printf("Entrez l'état initial : ");
    scanf("%d", &afd.initial_state);

    printf("Entrez le nombre d'états finaux : ");
    scanf("%d", &nombre_final_states);

    for (int i = 0; i < nombre_final_states; i++) {
        printf("Entrez l'état final %d : ", i + 1);
        scanf("%d", &etat);
        afd.final_states[afd.num_final_states++] = etat;
    }

    while (1) {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez l'état final : ");
                scanf("%d", &etat);
                afd.final_states[afd.num_final_states++] = etat;
                break;
            case 2:
                printf("Entrez la transition (état actuel, entrée, état suivant) : ");
                scanf("%d %c %d", &etat, &input, &etat_suivant);
                add_transition(&afd, etat, input, etat_suivant);
                break;
            case 3:
                printf("Entrez une chaîne à tester : ");
                scanf("%s", chaine);
                if (simulate_afd(&afd, chaine)) {
                    printf("La chaîne '%s' est acceptée.\n", chaine);
                } else {
                    printf("La chaîne '%s' n'est pas acceptée.\n", chaine);
                }
                break;
            case 4:
                afficher_afd(&afd);
                break;
            case 5:
                exit(0);
            default:
                printf("Option invalide.\n");
        }
    }

    return 0;
}
