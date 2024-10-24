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

int state_is_a_nonterminal(int nonTerminals[], int max_nonTer, int state_x){
    for(int i=0; i<max_nonTer; i++){
        if(nonTerminals[i] == state_x){
            return 1;
        }
    }
    return -1;
}

void PREDICTOR(struct Graph* graph, struct State *state, int state_x, int nonTerminals[], int max_nonTer, struct Graph *ast) {
    // printf("PREDICTOR: %d\n", state_x);
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if( tempEdge->dest->val == state_x && state_is_a_nonterminal(nonTerminals, max_nonTer, tempNode->val) == 1){
                // printf("PREDICTOR %d to %d;\n", state_x, tempNode->val);
                add_state(state, tempNode->val);

                /*\/ criando os vertices e arestas do ast; */
                insertNode(ast, state_x);
                insertNode(ast, tempNode->val);
                insertEdge(ast, tempNode->val, state_x);
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

void get_states_production(struct Graph* graph, int state_x, int production[], int max_production, int *con_std_prod);

void PREDICTOR2(struct Graph* graph, int state_x, int production[], int max_production, int *con_std_prod, int *idx_production) {
    // printf("PREDICTOR: %d;\n", state_x);
    /*\/ apagar dados da production anterior; */
    for(int s=0; s<*con_std_prod; s++) production[s] = -1;
    get_states_production(graph, state_x, production, max_production, con_std_prod);
    *idx_production = 0;
}

void SCANNER(struct Graph* graph, struct State *state, int state_x, int nonTerminals[], int max_nonTer) {
    // printf("SCANNER: %d\n", state_x);
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if( tempEdge->dest->val == state_x /*&& state_is_a_nonterminal(nonTerminals, max_nonTer, state_x) == -1*/){
                add_state(state, state_x);
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

int get_NonTerm(struct Graph* graph, int state_x) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        // printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            // printf(" -> %d", tempEdge->dest->val);
            if( tempEdge->dest->val == state_x){
                return tempNode->val;
            }
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
    return -1;
}

void COMPLETER(struct Graph* graph, struct State *state, int state_x, int nonTerminals[], int max_nonTer, struct Graph *ast) {
    // printf("COMPLETER:\n");
    for(int i=1; i<state->max; i++){
        if(state->states[i] != state->vzero){
            PREDICTOR(graph, state, state->states[i], nonTerminals, max_nonTer, ast);
        }
    }
}

void get_states_production(struct Graph* graph, int state_x, int production[], int max_production, int *con_std_prod) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    int ind = 0;

    int nonTerm = get_NonTerm(graph, state_x);
    if(nonTerm != -1){
        while (tempNode != NULL) {
            // printf("\nNodo %d: ", tempNode->val);
            tempEdge = tempNode->edges;
            while (tempEdge) {
                // printf(" -> %d", tempEdge->dest->val);
                if( tempNode->val == nonTerm ){

                    if(ind == 0){
                        production[ind] = tempNode->val;
                        ind++;
                        (*con_std_prod)++;
                    }
                    if(ind > 0 && ind < max_production){
                        production[ind] = tempEdge->dest->val;
                        ind++;
                        (*con_std_prod)++;
                    }
                }
                tempEdge = tempEdge->next;
            }
            tempNode = tempNode->next;
        }
    }
}

void EARLEY_PARSE(struct Graph* graph, int tokens_input[], int len_tokens_input, int state_p, int nonTerminals[], int max_nonTer, int state_ini_grammar, struct Graph *ast){
    struct State* state = ini();

    add_state(state, state_ini_grammar);

    int max_production = 100;
    int production[max_production];
    int con_std_prod = 0;
    for(int i=0; i<max_production; i++) production[i] = -1;

    for(int i=0; i<len_tokens_input; i++){

        get_states_production(graph, tokens_input[i], production, max_production, &con_std_prod);
        // printf("token: %d;\n", tokens_input[i]);

        int colum = 0;
        while(production[colum] != tokens_input[i] && colum < con_std_prod){
            colum++;
        }
        // printf("colum: %d\n", colum);

        for(int s=colum/*0*/; s<con_std_prod; s++){
            int act_state = production[s];
            if(act_state != -1){

                // printf("std: %d\n", act_state);

                if(state_is_a_nonterminal(nonTerminals, max_nonTer, act_state) != -1){
                    PREDICTOR(graph, state, act_state, nonTerminals, max_nonTer, ast); // non_terminal
                    // PREDICTOR2(graph, act_state, production, max_production, &con_std_prod, &s);
                }else{
                    SCANNER(graph, state, tokens_input[i], nonTerminals, max_nonTer); // terminal
                }

            }
        }

        int act_state = production[con_std_prod-1];
        // printf("prod: [");
        // for(int i=0; i<con_std_prod; i++){
        //     printf("%d, ", production[i]);
        // }
        // printf("];\n");
        // print_all_states(state);

        COMPLETER(graph, state, act_state, nonTerminals, max_nonTer, ast);
        // print_all_states(state);

        // printf("***\n\n");
        /*\/ apagar dados da production anterior; */
        for(int s=0; s<con_std_prod; s++) production[s] = -1;
        con_std_prod = 0;
    }
    // print_all_states(state);
    free_states(state);
}
