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
    JS
};