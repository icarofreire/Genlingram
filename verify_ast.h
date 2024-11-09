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
            printf("[%d - %d]\n", tk1, tk2);
            int is_path = isPathInDLL(tree, tk1, tk2);
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
