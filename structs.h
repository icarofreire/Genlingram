/* structs for project; */

/**  **/
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

/*\/ ;*/
enum languages{
    PYTHON,
    RUBY,
    JS,
    JAVA
};

/*\/ free dates for struct grammar_symbols; */
void free_dates_grammar_symbols(struct grammar_symbols* gsymbols){
	free_map(gsymbols->symbolNum);
	free_map(gsymbols->nonTerminals);
	deleteAllGraph(gsymbols->grammar);
	free_strings(gsymbols->keywords_lang, gsymbols->len_keywords);
	free(gsymbols->grammar);
}