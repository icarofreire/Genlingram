/* lib to verify AST; */


bool isNonTerm(struct grammar_symbols* gsymbols, int token){
    return (getKeyByValue(gsymbols->nonTerminals, token) != NULL);
}

/*\/ criar exemplos de verificação de regras; */
void verify(struct grammar_symbols* gsymbols, struct NodeDLL *tree, int *tokensRules, int sizeTokens){

    /** ... */
    int n_path = 0;
    if(sizeTokens > 0){
        int tk1 = tokensRules[0];
        if(!isNonTerm(gsymbols, tk1)){// << terminal;
            struct NodeDLL* nodeNonTerm = searchNodeByChildren(tree, tk1);
            if(nodeNonTerm){
                tk1 = nodeNonTerm->data;
            }
        }

        for(int i=1; i<sizeTokens; i++){
            int tk2 = tokensRules[i];
            if(!isNonTerm(gsymbols, tk2)){// << terminal;
                struct NodeDLL* nodeNonTerm = searchNodeByChildren(tree, tk2);
                if(nodeNonTerm){
                    tk2 = nodeNonTerm->data;
                }
            }
            // printf("[%d - %d]\n", tk1, tk2);
            int is_path = isPathInDLL(tree, tk1, tk2);
            printf("[%s - %s] = %d;\n", getKeyByValue(gsymbols->symbolNum, tk1), getKeyByValue(gsymbols->symbolNum, tk2), is_path);
            if(is_path == 1){
                n_path++;
            }
        }
    }
    printf("n_path: [%d]\n", n_path);

    // int tk_if = get_NonTerm_token(gsymbols, ast, "if");
    // int tk_ig = get(gsymbols->symbolNum, "=");
    // // int is = isPath(ast, tk_if, tk_ig);
    // int is = isPathInDLL(tree, tk_if, tk_ig);
    // printf("[%d, %d]\n", tk_if, tk_ig);
    // printf("path: [%d]\n", is);
}

/*\/ passar para um array nós pai que não são terminais; */
void get_nos_nao_term(struct NodeDLL *head, struct tokens_reads* tokens_reads, int* nodesNaoTerm_file, int* ind, int* max){
    struct NodeDLL *curr = head;
    while (curr != NULL) {
        int pfcode = curr->data;
        if(pfcode > 0){

            bool ifTerm = false;
            for(int i=0; i<tokens_reads->sizePtokenTypes; i++){
                 if(tokens_reads->pTokenTypes[i] == pfcode){
                    ifTerm = true; break;
                 }
            }
            if(!ifTerm && *ind < *max){
                nodesNaoTerm_file[*ind] = pfcode;
                (*ind)++;
            }
        }
        curr = curr->next;
    }
}

void verify_for_reduce_tree(struct grammar_symbols* gsymbols, struct NodeDLL *tree, struct tokens_reads* tokensFileCode, struct NodeDLL *tree_file_rules, struct tokens_reads* tokensRules){

    /*\/ reduce tree file code; */
    struct NodeDLL *reduceTreeFileCode = reduce_tree_term(tree, tokensFileCode->pTokenTypes, tokensFileCode->sizePtokenTypes);

    /*\/ reduce tree file rules code; */
	struct NodeDLL *reduceTreeFileRules = reduce_tree_term(tree_file_rules, tokensRules->pTokenTypes, tokensRules->sizePtokenTypes);


    int ind1 = 0, ind2 = 0, max = 300;
    int nodesNaoTerm_file_code[max];
    int nodesNaoTerm_file_rules[max];

    get_nos_nao_term(reduceTreeFileCode, tokensFileCode, nodesNaoTerm_file_code, &ind1, &max);

    get_nos_nao_term(reduceTreeFileRules, tokensRules, nodesNaoTerm_file_rules, &ind2, &max);


    for(int i=0; i<ind1; i++){
        for(int j=0; j<ind2; j++){
            if(nodesNaoTerm_file_code[i] == nodesNaoTerm_file_rules[j]){
                printf("P: [%s];\n", getKeyByValue(gsymbols->symbolNum, nodesNaoTerm_file_code[i]));
                break;
            }
        }
    }

}