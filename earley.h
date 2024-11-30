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

void print_all_states_tokens(struct grammar_symbols* gsymbols, struct State *state){
    for(int i=0; i<state->max; i++){
        if(state->states[i] != state->vzero) printf("S: %d(%s)\n", state->states[i], getKeyByValue(gsymbols->symbolNum, state->states[i]) );
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

void PREDICTOR(struct NodeDLL *grammarDLL, struct State *state, int state_x, struct NodeDLL *tree) {
    int child = state_x;
    struct NodeDLL *curr = grammarDLL;
    while (curr != NULL) {
        int pai = curr->data;
        if(curr->len_children_datas > 0){
            for(int i=0; i<curr->len_children_datas; i++){
                if(curr->children_datas[i] != -1 && curr->children_datas[i] == child){
                    
                    add_state(state, pai);

                    /*\/ tree; */
                    if(!searchNodeByKey(tree, pai)){
                        append(&tree, pai);
                    }
                    if(!searchNodeByKey(tree, child)){
                        append(&tree, child);
                    }
                    add_date_in_array_node(tree, pai, child);
                    /* --- */
                }
            }
        }
        curr = curr->next;
    }
}

void SCANNER(struct NodeDLL *grammarDLL, struct State *state, int state_x, struct NodeDLL *tree, struct Tokens *stru_token) {
    int child = state_x;
    struct NodeDLL *curr = grammarDLL;
    while (curr != NULL) {
        int pai = curr->data;
        if(curr->len_children_datas > 0){
            for(int i=0; i<curr->len_children_datas; i++){
                if(curr->children_datas[i] != -1 && curr->children_datas[i] == child){
                    
                    add_state(state, child);

                    /*\/ tree; */
                    if(!searchNodeByKey(tree, pai)){
                        append(&tree, pai);
                    }
                    if(!searchNodeByKey(tree, child)){
                        append(&tree, child);
                    }
                    add_date_in_array_node(tree, pai, child);

                    /*\/ registrar no nó pai, a linha onde o token
                    filho(terminal) foi encontrado; */
                    struct NodeDLL* node = searchNodeByKey(tree, pai);
                    if(node){
                        node->token = stru_token;
                    }
                    /* --- */
                }
            }
        }
        curr = curr->next;
    }
}

void COMPLETER(struct NodeDLL *grammarDLL, struct State *state, struct NodeDLL *tree) {
    for(int i=1; i<state->max; i++){
        if(state->states[i] != state->vzero){
            PREDICTOR(grammarDLL, state, state->states[i], tree);
        }
    }
}

void get_states_production(struct NodeDLL *grammarDLL, int state_x, int production[], int max_production, int *con_std_prod) {
    int ind = 0;
    struct NodeDLL* nodePai = searchNodeByChildren(grammarDLL, state_x);
    if(nodePai){
        production[ind] = nodePai->data;
        ind++;
        (*con_std_prod)++;

        for(int i=0; i<nodePai->len_children_datas; i++){
            if(nodePai->children_datas[i] != -1 && ind < max_production){
                production[ind] = nodePai->children_datas[i];
                ind++;
                (*con_std_prod)++;
            }
        }
    }
}

void EARLEY_PARSE(struct NodeDLL *grammarDLL, int nonTerminals[], int max_nonTer, int state_ini_grammar, struct NodeDLL *tree, struct Tokens* list_tokens){
    struct State* state = ini();

    add_state(state, state_ini_grammar);

    int max_production = 200;
    int production[max_production];
    int con_std_prod = 0;
    for(int i=0; i<max_production; i++) production[i] = -1;


    struct ListDLL* el;
	list_forward(el, list_tokens->list){
		struct Tokens *stru_token = (struct Tokens*)el->__struct;
        int token_input = stru_token->TokenType;

        get_states_production(grammarDLL, token_input, production, max_production, &con_std_prod);
        // printf("token: %d;\n", token_input);

        int colum = 0;
        while(production[colum] != token_input && colum < con_std_prod){
            colum++;
        }
        // printf("colum: %d\n", colum);

        for(int s=colum/*0*/; s<con_std_prod; s++){
            int act_state = production[s];
            if(act_state != -1){

                // printf("std: %d\n", act_state);

                if(state_is_a_nonterminal(nonTerminals, max_nonTer, act_state) != -1){
                    PREDICTOR(grammarDLL, state, act_state, tree); // non_terminal
                }else{
                    SCANNER(grammarDLL, state, token_input, tree, stru_token); // terminal
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

        /*\/ utilizando esta forma de complete para obter uma maior amplitude de reduce dos tokens da production; */
        COMPLETER(grammarDLL, state, tree);
        // print_all_states(state);

        // printf("***\n\n");
        /*\/ apagar dados da production anterior; */
        for(int s=0; s<con_std_prod; s++) production[s] = -1;
        con_std_prod = 0;
    }
    // print_all_states(state);
    // print_all_states_tokens(gsymbols, state);
    free_states(state);
}
