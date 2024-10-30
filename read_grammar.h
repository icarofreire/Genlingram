/* Lib ler arquivo BNF/EBNF; */


const char delimiters_grammar[] = " :|()[]?*+'\"";

bool if_non_term(char *s){
    char *p1 = strstr(s, "::=");
    char *p2 = strstr(s, ":");

    int idx1 = (p1 != NULL) ? (p1-s) : (0);
    int idx2 = (p2 != NULL) ? (p2-s) : (0);
    int idx_priori = 0;

    if(idx1 > 0){
        idx_priori = idx1;
    }else if(idx2 > 0){
        idx_priori = idx2;
    }

    int ini = 0;
    int fim = idx_priori-1;
    while(ini<idx_priori && isspace(s[++ini]));
    while(fim >= 0 && isspace(s[--fim]));

    // printf("f: [%d - %d]\n", ini, fim);

    int onlyLetOrUnder = 1;
    for(int i=ini; i<=fim; i++){
        if(!isalpha(s[i]) && s[i] != '_' && s[i] != '-'){
            onlyLetOrUnder = 0; break;
        }
    }

    return (onlyLetOrUnder == 1);
}

char *get_non_term(char *s){
    char *p1 = strstr(s, "::=");
    char *p2 = strstr(s, ":");

    int idx1 = (p1 != NULL) ? (p1-s) : (0);
    int idx2 = (p2 != NULL) ? (p2-s) : (0);

    char *sub = (char*)malloc((50)* sizeof(char));
    if(sub != NULL){
        if(idx1 > 0){
            get_substring(s, sub, 0, idx1); trim(sub);
            return (only_alphabets(sub) ? (sub) : (NULL));
        }else if(idx2 > 0){
            get_substring(s, sub, 0, idx2); trim(sub);
            return (only_alphabets(sub) ? (sub) : (NULL));
        }
    }
    return sub;
}

char *get_production(char *s){
    char *p1 = strstr(s, "::=");
    char *p2 = strstr(s, ":");

    int idx1 = (p1 != NULL) ? (p1-s) : (0);
    int idx2 = (p2 != NULL) ? (p2-s) : (0);

    char *sub = (char*)malloc((300)* sizeof(char));
    if(sub != NULL){
        if(idx1 > 0){
            get_substring(s, sub, idx1+3, strlen(s));
            trim(sub);
        }else if(idx2 > 0){
            get_substring(s, sub, idx2+1, strlen(s));
            trim(sub);
        }
    }
    return sub;
}

/*\/ verificar se string já foi adicionada na estrutura de simbolos; */
bool if_string_reg(struct grammar_symbols* gsymbols, char *str){
    char* str_saspas = str_retirar_aspas(str);
    bool f = (str_saspas != NULL && get(gsymbols->symbolNum, str_saspas) == -1);
    free(str_saspas);
    return f;
}

void tokenize_and_reg(struct grammar_symbols* gsymbols, char *linha){
    /*\/ obter as strings declaradas na production, ou na continuação da production; */
    int len = 0;
    char **strings = get_strings_in_string(linha, &len);
    if(len > 0){
        for(int i=0; i<len; i++){
            if(strings[i] != NULL){
                trim(strings[i]);
                toLower(strings[i]);
                if(
                    // (get(gsymbols->symbolNum, strings[i]) == -1) &&
                    (!if_string_reg(gsymbols, strings[i]))
                ){
                    gsymbols->tokenType++;
                    insert(gsymbols->symbolNum, strings[i], gsymbols->tokenType);
                }
            }
        }
    }
    free_strings(strings, len);

    int tam = 0;
    char **tokens = process_tokens(linha, delimiters_grammar, &tam, true);
    for(int i=0; i<tam; i++){
        trim(tokens[i]);
        if(get(gsymbols->symbolNum, tokens[i]) == -1){
            gsymbols->tokenType++;
            insert(gsymbols->symbolNum, tokens[i], gsymbols->tokenType);
        }
    }
    free_strings(tokens, tam);
}

void create_vertices_for_nonterminal(struct grammar_symbols* gsymbols, char *linha, int idx_nonTerm){
    int tam_prod = 0;
    char **tokens_prod = process_tokens(linha, delimiters_grammar, &tam_prod, true);
    for(int i=0; i<tam_prod; i++){
        trim(tokens_prod[i]);
        int gprod = get(gsymbols->symbolNum, tokens_prod[i]);
        if(gprod != -1){
            /*\/ criar vertice dos simbolos da production; */
            insertNode(gsymbols->grammar, gprod);
            /*\/ criando o vertice do não-terminal para cada simbolo da production; */
            insertEdge(gsymbols->grammar, idx_nonTerm, gprod);
        }
    }
    free_strings(tokens_prod, tam_prod);
}

void reg_keywords_lang(struct grammar_symbols* gsymbols, const int lang){
    /*\/ obter as kerwords da linguagem; */
    int len_keywords = 0;
    /*\/ no final da execução do projeto, esta memória será liberada; */
    char **keywords_lang = read_keywords(&len_keywords, lang);
    /*\/ reg em estrututra geral; */
    gsymbols->len_keywords = len_keywords;
    gsymbols->keywords_lang = keywords_lang;

    for(int i=0; i<len_keywords; i++){
        char* word = keywords_lang[i];
        if(word != NULL){
            toLower(word);
            if(get(gsymbols->symbolNum, word) == -1){
                gsymbols->tokenType++;
                insert(gsymbols->symbolNum, word, gsymbols->tokenType);
            }
        }
    }
}

struct grammar_symbols* read_file_grammar(char* arquivo, const int lang){
    // Create a file pointer and open the file "GFG.txt" in
    // read mode.
    FILE* file = fopen(arquivo, "r");
    const int max = 300;
    // Buffer to store each line of the file.
    char line[max];
    char linha_anterior[max];

    // Check if the file was opened successfully.
    if (file != NULL) {

        struct grammar_symbols* gsymbols = (struct grammar_symbols*)malloc(sizeof(struct grammar_symbols));
        gsymbols->symbolNum = ini_hashMap();
        gsymbols->nonTerminals = ini_hashMap();
        gsymbols->grammar = createGraph();
        gsymbols->tokenType = 0;

        /*\/ registrar primeiro as keywords; */
        reg_keywords_lang(gsymbols, lang);

        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {
            // Print each line to the standard output.
            trim(line);
            bool comment = ((isBlank(line) != 1) && (line[0] == '#'));
            bool production = (!comment && (isBlank(line) != 1) && (line[0] != '|') && if_non_term(line));
            bool continue_production = (!comment && (isBlank(line) != 1) && !production && (line[0] == '|'));

            /*\/ registrar linha que contém o non-terminal; */
            if(production){
                strcpy(linha_anterior, line);
            }

            /*\/ exibir linha que continua com a primeira linha do non-terminal, ou
             não, apenas continua *com a linha completa já registrada; */
            if(continue_production){
                /*\/ linha encontrada pertencente a linha do non-terminal; */

                /*\/ registrar cada simbolo de uma continuidade da production; */
                /*\/ registrar o restante das continuações da production ... | ... | ... */
                tokenize_and_reg(gsymbols, line);

                /*\/ registra cada production de um não-terminal; */
                char *non_term = get_non_term(linha_anterior);
                if(non_term != NULL ){
                    int idx_nonTerm = get(gsymbols->symbolNum, non_term);
                    if(idx_nonTerm != -1){
                        create_vertices_for_nonterminal(gsymbols, line, idx_nonTerm);
                    }
                    free(non_term);
                }

            }else if(production){
                /*\/ linha inteira encontrada o non-terminal, até seu fim; */

                /*\/ registrar cada simbolo de uma production; */
                tokenize_and_reg(gsymbols, line);

                /*\/ registrar non-terminals em hash particular; */
                char *non_term = get_non_term(line);
                if(non_term != NULL){
                    int idx_nonTerm = get(gsymbols->symbolNum, non_term);
                    if(idx_nonTerm != -1){
                        insert(gsymbols->nonTerminals, non_term, idx_nonTerm);
                        /*\/ criar vertice do não-terminal; */
                        insertNode(gsymbols->grammar, idx_nonTerm);

                        char *prod = get_production(line);
                        if(prod != NULL){
                            create_vertices_for_nonterminal(gsymbols, prod, idx_nonTerm);
                            free(prod);
                        }
                    }
                    free(non_term);
                }
            }
        }
        // printMap(gsymbols->symbolNum);
        // printMap(gsymbols->nonTerminals);
        // printGraph(gsymbols->grammar);
        // Close the file stream once all lines have been
        // read.
        fclose(file);
        return gsymbols;
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
	}
	return NULL;
}

struct grammar_symbols* read_grammar(const int lang){
    struct grammar_symbols* gsymbols;
    switch(lang){
        case RUBY: gsymbols = read_file_grammar("grammars/ruby-grammar.txt", lang); break;
        case PYTHON: gsymbols = read_file_grammar("grammars/python-grammar.txt", lang); break;
        case JS: gsymbols = read_file_grammar("grammars/js-grammar.txt", lang); break;
        case JAVA: gsymbols = read_file_grammar("grammars/java-grammar.txt", lang); break;
    }
    return gsymbols;
}
