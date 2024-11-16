/* structs for project; */

/*\/ estrutura para armazenar dados da gramática analisada; */
struct grammar_symbols {
    struct hashMap* symbolNum;
    struct hashMap* nonTerminals;
    struct Graph *grammar;

    /*\/ atributo incremental que dará o número
    tokentype para cada token obtido da gramatica; */
    int tokenType;

    /*\/ array de keywords da linguagem; */
    int len_keywords;
    char **keywords_lang;
};

/*\/ linguagens para as quais existém gramáticas
disponíveis para analise;*/
enum languages{
    PYTHON,
    RUBY,
    JS,
    JAVA,
    PHP
};

/*\/ free dates for struct grammar_symbols; */
void free_dates_grammar_symbols(struct grammar_symbols* gsymbols){
	free_map(gsymbols->symbolNum);
	free_map(gsymbols->nonTerminals);
	deleteAllGraph(gsymbols->grammar);
	free_strings(gsymbols->keywords_lang, gsymbols->len_keywords);
	free(gsymbols->grammar);
}

/*\/ estrutura de tokens lidos no arquivo de código; */
struct tokens_reads {
    int sizePtokenTypes;
	int *pTokenTypes;
    /*\/ linhas que foram encontrados cada tokens lidos no arquivo;
    cada linha armazenada no array, está no mesmo indice a qual o
    token foi enconrtado no arquivo;
    Ex: lineTokens[N] = linha --> pTokenTypes[N] = token;
    */
    int *lineTokens;
};

/*\/ free dates for struct grammar_symbols; */
void free_tokens_reads(struct tokens_reads* tksReads){
	free(tksReads->pTokenTypes);
    free(tksReads->lineTokens);
    free(tksReads);
}