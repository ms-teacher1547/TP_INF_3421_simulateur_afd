#include <string.h>
#include <stdio.h>
#include <afd.h>

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
