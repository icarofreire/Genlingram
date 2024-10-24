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
    return -1;
}

/*\/ criar exemplos de verificação de regras; */
void verify(struct grammar_symbols* gsymbols){

    int tkSTMT = get(gsymbols->symbolNum, "STMT");
    if(tkSTMT != -1 && getNode(gsymbols->grammar, tkSTMT) != NULL){
        printf("[Ok STMT];\n");
    }

    int tokenType = get(gsymbols->symbolNum, "if");
    printf("[%d]\n", tokenType);

    // printf("[%d]\n", verify_token(gsymbols, "if") );
}
