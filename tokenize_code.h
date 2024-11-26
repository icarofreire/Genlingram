/* lib to read file code and tokenize; */

int literal_tokenType_grammar_lang(struct grammar_symbols* gsymbols, const int lang){
	int tokenType = -1;
	switch(lang){
		case RUBY: tokenType = get(gsymbols->symbolNum, "LITERAL"); break;
		case PYTHON: tokenType = get(gsymbols->symbolNum, "literal_pattern"); break;
		case JS: tokenType = get(gsymbols->symbolNum, "Literal"); break;
		case JAVA: tokenType = get(gsymbols->symbolNum, "literal"); break;
		case PHP: tokenType = get(gsymbols->symbolNum, "LITERAL"); break;
	}
	return tokenType;
}

int get_literal_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = identify_primitive_types(token);
	if(tokenType != -1){
		tokenType = literal_tokenType_grammar_lang(gsymbols, lang);
	}
	return tokenType;
}

bool if_token_keyword(struct grammar_symbols* gsymbols, const char *token){
	char copy[strlen(token)];
	strcpy(copy, token);
	toLower(copy);
	for(int i=0; i<gsymbols->len_keywords; i++){
		if(strcmp(gsymbols->keywords_lang[i], copy) == 0){
			return true;
		}
	}
	return false;
}

int get_identifier_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = -1;
	if(!if_token_keyword(gsymbols, token)){
		tokenType = identify_identifier(token);
		if(tokenType != -1){
			switch(lang){
				case RUBY: tokenType = get(gsymbols->symbolNum, "IDENTIFIER"); break;
				case PYTHON: tokenType = get(gsymbols->symbolNum, "NAME"); break;
				case JS: tokenType = get(gsymbols->symbolNum, "Identifier"); break;
				case JAVA: tokenType = get(gsymbols->symbolNum, "identifier"); break;
				case PHP: tokenType = get(gsymbols->symbolNum, "IDENTIFIER"); break;
			}
		}
	}
	return tokenType;
}

int get_tokenType_symbols_grammar(struct grammar_symbols* gsymbols, char *token){
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

void array_resize(int **items, int *capacity, int plus) {
	if(plus > 0 && plus >= *capacity){
		*capacity += plus;
		*items = (int*)realloc(*items, (*capacity) * sizeof(int));
	}
}

void array_add_size(int **items, int *capacity, int plus) {
	if(plus > 0){
		*capacity += plus;
		*items = (int*)realloc(*items, (*capacity) * sizeof(int));
	}
}

void add_struc_token_in_list(struct Tokens* struc_tokens, int tokenType, int linha, char* str_token){
	struct Tokens* token = (struct Tokens*)malloc(sizeof(struct Tokens));
	token->TokenType = tokenType;
	token->linha = linha;
	token->value = (char*)malloc((100)* sizeof(char));
	strcpy(token->value, str_token);

	token->link = createListDLL();
	list_append(&struc_tokens->link, token->link);
}

struct tokens_reads* read_code_tokenize(char* arquivo, struct grammar_symbols* gsymbols, const int lang){
	// Create a file pointer and open the file "GFG.txt" in
	// read mode.
	FILE* file = fopen(arquivo, "r");

	// Buffer to store each line of the file.
	char line[300];

	// Check if the file was opened successfully.
	if (file != NULL) {

		int sizePtokenTypes = 1;
		int *pTokenTypes = (int*)malloc((sizePtokenTypes) * sizeof(int));

		int sizeLineTokens = 1;
		int *lineTokens = (int*)malloc((sizeLineTokens) * sizeof(int));

		/*\/ raiz da estrutura de tokens com sua propriedade de dll(Doubly Linked List),
		para registrar a sequência de tokens lidos; */
		struct Tokens* struc_tokens = (struct Tokens*)malloc(sizeof(struct Tokens));
		struc_tokens->TokenType = 0;
		struc_tokens->linha = 0;
		struc_tokens->value = NULL;
		struc_tokens->link = createListDLL();

		// Read each line from the file and store it in the
		// 'line' buffer.
		int con_lines = 0;
		/*\/ indice para registrar os tokenTypes; */
		int idx_reg = 0;
		int tk_obtidos = 0;
		/*\/ para detectar strings espaçadas; */
		int con_str_part = 0;
		/*\/ para detectar comentários; */
		int con_comment_part = 0, ncoment = 0;
		while (fgets(line, sizeof(line), file)) {
			// Print each line to the standard output.
			con_lines++;

			/*\/ inserir simbolos registrados(token types) em um vetor para análise; */
			int tam = 0;
			char **tokens = process_tokens(line, delimiters, &tam, true);
			array_add_size(&pTokenTypes, &sizePtokenTypes, tam);
			array_add_size(&lineTokens, &sizeLineTokens, tam);

			for(int i=0; i<tam; i++){
				trim(tokens[i]);
				if(strcmp(tokens[i], "") != 0){
					// printf("tk: [%s]\n", tokens[i]);
					tk_obtidos++;
					int take = 0;

					if(!take){
						int part = veri_string_counter_based(tokens[i], &con_str_part);
						if(part >= 1 && part <= 3){
							int tokenType_literal = literal_tokenType_grammar_lang(gsymbols, lang);
							if(tokenType_literal != -1){
								pTokenTypes[idx_reg] = tokenType_literal;
								lineTokens[idx_reg] = con_lines;
								idx_reg++;
								// printf("4tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, tokenType_literal));
								take = tokenType_literal;

								add_struc_token_in_list(struc_tokens, tokenType_literal, con_lines, tokens[i]);
							}
						}
					}

					/*\/ detect comment; */
					if(!take){
						int part = veri_comment_counter_based(tokens[i], &con_comment_part);
						if((part >= 1 && part <= 3) || veri_comment_ini_line(tokens[i])){
							ncoment++;
						}
					}

					/*\/ identificar literal tokentype; */
					if(!take){
						int tokenType_literal = get_literal_tokenType_lang(gsymbols, tokens[i], lang);
						if(tokenType_literal != -1){
							pTokenTypes[idx_reg] = tokenType_literal;
							lineTokens[idx_reg] = con_lines;
							idx_reg++;
							// printf("1tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, tokenType_literal));
							take = tokenType_literal;

							add_struc_token_in_list(struc_tokens, tokenType_literal, con_lines, tokens[i]);
						}
					}

					/*\/ identificar identifier tokentype; */
					if(!take){
						int tokenType_identifier = get_identifier_tokenType_lang(gsymbols, tokens[i], lang);
						if(tokenType_identifier != -1){
							pTokenTypes[idx_reg] = tokenType_identifier;
							lineTokens[idx_reg] = con_lines;
							idx_reg++;
							// printf("2tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, tokenType_identifier));
							take = tokenType_identifier;

							add_struc_token_in_list(struc_tokens, tokenType_identifier, con_lines, tokens[i]);
						}
					}

					/*\/ identificar não-terminais tokentype; */
					if(!take){
						int sym = get_tokenType_symbols_grammar(gsymbols, tokens[i]);
						if(sym != -1){
							pTokenTypes[idx_reg] = sym;
							lineTokens[idx_reg] = con_lines;
							idx_reg++;
							// printf("3tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, sym));
							take = sym;

							add_struc_token_in_list(struc_tokens, sym, con_lines, tokens[i]);
						}
					}

					if(take > 0){
						// printf("tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, take));
					}

				}// fim if;
			}
			free_strings(tokens, tam);
		}
		if(tk_obtidos == (idx_reg+ncoment)) printf("[todos os tokens reconhecidos; %d tokens de entrada];\n", tk_obtidos);
		// printf("tt: [%d, %d, %d]\n", tk_obtidos, j, ncoment);
		// Close the file stream once all lines have been
		// read.
		fclose(file);

		struct tokens_reads* tksReads = (struct tokens_reads *)malloc(sizeof(struct tokens_reads));
		tksReads->sizePtokenTypes = idx_reg;
		tksReads->pTokenTypes = pTokenTypes;
		tksReads->lineTokens = lineTokens;

		return tksReads;
	}
	else {
		// Print an error message to the standard error
		// stream if the file cannot be opened.
		fprintf(stderr, "Unable to open file!\n");
	}
	return NULL;
}
