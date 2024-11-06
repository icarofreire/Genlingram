/* lib to verify AST; */

/*\/ obter alguns tokenTypes de tokens inseridos; */
int get_tokenType_token(struct grammar_symbols* gsymbols, char *token){
    char *token_aspas_s = insert_aspas(token, true);
    char *token_aspas_d = insert_aspas(token, false);

    int tk = -1;
    int sym = get(gsymbols->symbolNum, token_aspas_s);
    if(sym != -1){
        tk = sym;
    }
    sym = get(gsymbols->symbolNum, token_aspas_d);
    if(sym != -1){
        tk = sym;
    }
    sym = get(gsymbols->symbolNum, token);
    if(sym != -1){
        tk = sym;
    }

    free(token_aspas_s);
	free(token_aspas_d);
    return tk;
}

int get_NonTerm_token(struct grammar_symbols* gsymbols, struct Graph* ast, char *token){
    int tk = get(gsymbols->symbolNum, token);
    if(tk != -1 && getNode(ast, tk) != NULL){
        int nonTerm = get_NonTerm(ast, tk);
        return nonTerm;
    }
    return -1;
}

/*\/ criar exemplos de verificação de regras; */
void verify(struct grammar_symbols* gsymbols, struct Graph* ast){

    int tk = get(gsymbols->symbolNum, "STMT");
    if(tk != -1 && getNode(gsymbols->grammar, tk) != NULL){
        printf("[Ok STMT];\n");
    }
    tk = get(gsymbols->symbolNum, "ARG");
    if(tk != -1 && getNode(gsymbols->grammar, tk) != NULL){
        printf("[Ok ARG];\n");
    }

    /** ... */

    int tk_if = get_NonTerm_token(gsymbols, ast, "if");
    int tk_ig = get(gsymbols->symbolNum, "=");
    int is = isPath(ast, tk_if, tk_ig);
    printf("[%d, %d]\n", tk_if, tk_ig);
    printf("path: [%d]\n", is);

}
