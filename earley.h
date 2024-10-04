/* Lib Earley parser algorithm; */


struct State {
    const int max = 100;
    int states[max];
    int visite[max];
};

struct State* ini(struct State *state){
    struct State* state = (struct State*)malloc(sizeof(struct State));
    for(int i=0; i<state->max; i++){
        state->states[i] = 0;
        state->visite[i] = 0;
    }
    return state;
}

void add_state(struct State *state, int state_x){
    for(int i=0; i<state->max; i++){
        if(state->states[i] == state_x){
            break;
        }else if(state->states[i] == 0){
            state->states[i] = state_x;
            break;
        }
    }
}

void add_state_visited(struct State *state, int state_x){
    for(int i=0; i<state->max; i++){
        if(state->visite[i] == 0){
            state->visite[i] = state_x;
            break;
        }
    }
}

int se_state_visited(struct State *state, int state_x){
    for(int i=0; i<state->max; i++){
        if(state->visite[i] == state_x){
            return 1;
        }
    }
    return -1;
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

void SCANNER(struct Graph* graph, struct State *state, int state_x) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if(tempEdge->dest->val == state_x){
                add_state(state, tempEdge->dest->val);
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
