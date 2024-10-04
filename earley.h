/* Lib Earley parser algorithm; */


struct State {
    int max;
    int *states;
    int vzero;
};

struct State* ini(){
    struct State* state = (struct State*)malloc(sizeof(struct State));
    state->max = 100;
    state->states = (int*)malloc(state->max * sizeof(int));
    state->vzero = -1;

    for(int i=0; i<state->max; i++){
        state->states[i] = state->vzero;
    }
    return state;
}

void print_all_states(struct State *state){
    for(int i=0; i<state->max; i++){
        if(state->states[i] != state->vzero) printf("S: %d\n", state->states[i]);
    }
}

void free_states(struct State *state){
    free(state->states);
    free(state);
}

void add_state(struct State *state, int state_x){
    for(int i=0; i<state->max; i++){
        if(state->states[i] == state_x){
            break;
        }else if(state->states[i] == state->vzero){
            state->states[i] = state_x;
            break;
        }
    }
}

void PREDICTOR(struct Graph* graph, struct State *state, int state_x) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if( tempEdge->dest->val == state_x){
                add_state(state, tempNode->val);
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

void SCANNER(struct Graph* graph, struct State *state, int state_x, int tokens_input[], int len_tokens_input, int idx_input) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            int next_token = (idx_input+1 < len_tokens_input) ? (tokens_input[idx_input+1]) : (-1);
            if(next_token != -1 && tempEdge->dest->val == next_token){

                add_state(state, next_token);
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

void COMPLETER(struct Graph* graph, struct State *state, int state_x) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if(tempEdge->dest->val == state_x){
                PREDICTOR(graph, state, state_x);
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

int IF_NOT_FINISHED_STATE(struct Graph* graph, int state_x) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if( tempNode->val == state_x && tempEdge->dest->val > 0 ){
                return 1;
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
    return -1;
}

int NEXT_ELEMENT_OF(struct State *state, int state_x){
    for(int i=0; i<state->max; i++){
        int j = i+1;
        if( j < state->max && state->states[i] == state_x && state->states[j] != state->vzero){
            return state->states[j];
        }
    }
    return -1;
}

int state_is_a_nonterminal(int nonTerminals[], int max_nonTer, int state_x){
    for(int i=0; i<max_nonTer; i++){
        if(nonTerminals[i] == state_x){
            return 1;
        }
    }
    return -1;
}

void EARLEY_PARSE(struct Graph* graph, int tokens_input[], int len_tokens_input, int state_p, int nonTerminals[], int max_nonTer){
    struct State* state = ini();
    add_state(state, state_p);

    for(int i=0; i<len_tokens_input; i++){
        for(int s=0; s<state->max; s++){
            int act_state = state->states[s];
            if(IF_NOT_FINISHED_STATE(graph, act_state) != -1){
                if(act_state != state->vzero){
                    int next_state = NEXT_ELEMENT_OF(state, act_state);
                    if(next_state != -1 && state_is_a_nonterminal(nonTerminals, max_nonTer, next_state) != -1){
                        PREDICTOR(graph, state, act_state); // non_terminal
                    }else{
                        SCANNER(graph, state, act_state, tokens_input, len_tokens_input, i); // terminal
                    }
                }
            }else{
                COMPLETER(graph, state, act_state);
            }
        }
    }
    print_all_states(state);
    free_states(state);
}
