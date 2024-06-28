#ifndef AFD_H
#define AFD_H

#define MAX_STATES 100
#define MAX_ALPHABET 26

typedef struct {
    int transitions[MAX_STATES][MAX_ALPHABET];
    int num_states;
    int alphabet_size;
    int initial_state;
    int final_states[MAX_STATES];
    int num_final_states;
} AFD;

void initialize_afd(AFD *afd, int num_states, int alphabet_size);
void set_transition(AFD *afd, int from_state, char symbol, int to_state);
void set_initial_state(AFD *afd, int state);
void add_final_state(AFD *afd, int state);
int simulate_afd(AFD *afd, const char *input);
int is_deterministic(AFD *afd);

#endif
