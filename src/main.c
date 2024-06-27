#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void get_afd_input(AFD *afd);
void get_and_simulate_strings(AFD *afd);

void initialize_afd(AFD *afd, int num_states, int alphabet_size) {
    afd->num_states = num_states;
    afd->alphabet_size = alphabet_size;
    afd->initial_state = -1;
    afd->num_final_states = 0;
    memset(afd->transitions, -1, sizeof(afd->transitions));
}

void set_transition(AFD *afd, int from_state, char symbol, int to_state) {
    int symbol_index = symbol - 'a';
    afd->transitions[from_state][symbol_index] = to_state;
}

void set_initial_state(AFD *afd, int state) {
    afd->initial_state = state;
}

void add_final_state(AFD *afd, int state) {
    afd->final_states[afd->num_final_states++] = state;
}

int simulate_afd(AFD *afd, const char *input) {
    int current_state = afd->initial_state;
    for (int i = 0; input[i] != '\0'; ++i) {
        int symbol_index = input[i] - 'a';
        if (symbol_index < 0 || symbol_index >= afd->alphabet_size) {
            return -1; // Symbol not in alphabet
        }
        current_state = afd->transitions[current_state][symbol_index];
        if (current_state == -1) {
            return 0; // Transition not defined
        }
    }
    for (int i = 0; i < afd->num_final_states; ++i) {
        if (afd->final_states[i] == current_state) {
            return 1; // Accepted
        }
    }
    return 0; // Not accepted
}

int main() {
    AFD afd;
    int num_states, alphabet_size;

    printf("Enter number of states: ");
    scanf("%d", &num_states);
    printf("Enter size of alphabet: ");
    scanf("%d", &alphabet_size);

    initialize_afd(&afd, num_states, alphabet_size);
    get_afd_input(&afd);
    get_and_simulate_strings(&afd);

    return 0;
}

void get_afd_input(AFD *afd) {
    int num_transitions, from_state, to_state;
    char symbol;

    printf("Enter number of transitions: ");
    scanf("%d", &num_transitions);

    for (int i = 0; i < num_transitions; ++i) {
        printf("Enter transition (from_state symbol to_state): ");
        scanf("%d %c %d", &from_state, &symbol, &to_state);
        set_transition(afd, from_state, symbol, to_state);
    }

    int initial_state;
    printf("Enter initial state: ");
    scanf("%d", &initial_state);
    set_initial_state(afd, initial_state);

    int num_final_states, final_state;
    printf("Enter number of final states: ");
    scanf("%d", &num_final_states);

    for (int i = 0; i < num_final_states; ++i) {
        printf("Enter final state: ");
        scanf("%d", &final_state);
        add_final_state(afd, final_state);
    }
}

void print_error(const char *message) {
    fprintf(stderr, "Error: %s\n", message);
}


void get_and_simulate_strings(AFD *afd) {
    char input[100];

    while (1) {
        printf("Enter input string (or 'exit' to quit): ");
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            break;
        }
        int result = simulate_afd(afd, input);
        if (result == -1) {
            print_error("Input contains symbols not in the alphabet");
        } else if (result == 1) {
            printf("The string is accepted by the AFD.\n");
        } else {
            printf("The string is not accepted by the AFD.\n");
        }
    }
}
