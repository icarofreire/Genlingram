/* structs for project; */

/**  **/
struct grammar_symbols {
    struct hashMap* symbolNum;
    struct hashMap* nonTerminals;
    struct Graph *grammar;
    int tokenType;
};

/*\/ ;*/
enum languages{
    PYTHON,
    RUBY,
    JS
};