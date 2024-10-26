/* lib to verify AST; */

/*\/ obter alguns tokenTypes de tokens inseridos; */
int get_tokenType_token(struct grammar_symbols* gsymbols, char *token){
    char *token_aspas_s = insert_aspas(token, true);
    char *token_aspas_d = insert_aspas(token, false);

    int sym = get(gsymbols->symbolNum, token_aspas_s);
    if(sym != -1){
        return sym;
    }
    sym = get(gsymbols->symbolNum, token_aspas_d);
    if(sym != -1){
        return sym;
    }
    sym = get(gsymbols->symbolNum, token);
    if(sym != -1){
        return sym;
    }
    return -1;
}

/*\/ criar exemplos de verificação de regras; */
void verify(struct grammar_symbols* gsymbols){

    int tk = get(gsymbols->symbolNum, "STMT");
    if(tk != -1 && getNode(gsymbols->grammar, tk) != NULL){
        printf("[Ok STMT];\n");
    }
    tk = get(gsymbols->symbolNum, "ARG");
    if(tk != -1 && getNode(gsymbols->grammar, tk) != NULL){
        printf("[Ok ARG];\n");
    }

    /** ... */

}
