/* lib to read file code and apply; */

#include "adjacency-list.h"
#include "tokenization.h"
#include "vector.h"
#include "valid_basic_types.h"
#include "earley.h"
#include "read_grammar.h"
#include "verify_ast.h"

int get_literal_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = identify_types(token);
	if(tokenType != -1){
		switch(lang){
			case RUBY: tokenType = get(gsymbols->symbolNum, "LITERAL"); break;
			case PYTHON: tokenType = get(gsymbols->symbolNum, "literal_pattern"); break;
			case JS: tokenType = get(gsymbols->symbolNum, "Literal"); break;
		}
	}
	return tokenType;
}


int get_identifier_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = identify_identifier(token);
	if(tokenType != -1){
		switch(lang){
			case RUBY: tokenType = get(gsymbols->symbolNum, "IDENTIFIER"); break;
			case PYTHON: tokenType = get(gsymbols->symbolNum, "NAME"); break;
			case JS: tokenType = get(gsymbols->symbolNum, "Identifier"); break;
		}
	}
	return tokenType;
}

int get_nonTerminals_tokenType_lang(struct grammar_symbols* gsymbols, char *token){
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

	free(token_aspas_s);
	free(token_aspas_d);
	return -1;
}

void read_code_tokenize(char* arquivo, struct grammar_symbols* gsymbols, vector *tokenTypes, const int lang){
	// Create a file pointer and open the file "GFG.txt" in
	// read mode.
	FILE* file = fopen(arquivo, "r");

	// Buffer to store each line of the file.
	char line[300];

	// Check if the file was opened successfully.
	if (file != NULL) {
		// Read each line from the file and store it in the
		// 'line' buffer.
		while (fgets(line, sizeof(line), file)) {
			// Print each line to the standard output.

			/*\/ inserir simbolos registrados(token types) em um vetor para análise; */
			int tam = 0;
			char **tokens = process_tokens(line, delimiters, &tam, true);
			for(int i=0; i<tam; i++){
				trim(tokens[i]);

				/*\/ identificar literal tokentype; */
				int tokenType_literal = get_literal_tokenType_lang(gsymbols, tokens[i], lang);
				if(tokenType_literal != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], tokenType_literal);
					vector_add(tokenTypes, (void *)tokenType_literal);
				}

				/*\/ identificar identifier tokentype; */
				int tokenType_identifier = get_identifier_tokenType_lang(gsymbols, tokens[i], lang);
				if(tokenType_identifier != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], tokenType_identifier);
					vector_add(tokenTypes, (void *)tokenType_identifier);
				}

				/*\/ identificar não-terminais tokentype; */
				int sym = get_nonTerminals_tokenType_lang(gsymbols, tokens[i]);
				if(sym != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], sym);
					vector_add(tokenTypes, (void *)sym);
				}
			}
			free_strings(tokens, tam);
		}

		// Close the file stream once all lines have been
		// read.
		fclose(file);
	}
	else {
		// Print an error message to the standard error
		// stream if the file cannot be opened.
		fprintf(stderr, "Unable to open file!\n");
	}
}

int* vector_to_array(vector *v, int *reftam){
	*reftam = v->total;
	int *dados = (int*)malloc((v->total) * sizeof(int));
	for (int i = 0; i < v->total; i++) {
		dados[i] = (int)v->items[i];
	}
	return dados;
}

void apply_earley_in_code(char *file_code, const int lang){
	struct grammar_symbols* gsymbols = read_grammar(lang);
	vector tokenTypes;
	vector_init(&tokenTypes);
	read_code_tokenize(file_code, gsymbols, &tokenTypes, RUBY);

	/*\/ to array; */
	int sizeTokenTypes = 0;
	int *ptokenTypes = vector_to_array(&tokenTypes, &sizeTokenTypes);

	int sizeNonTerm = 0;
	int *pNonTerminals = getValues(gsymbols->nonTerminals, &sizeNonTerm);

	struct Graph *ast = createGraph();
	EARLEY_PARSE(gsymbols->grammar, ptokenTypes, sizeTokenTypes, pNonTerminals[0], pNonTerminals, sizeNonTerm, pNonTerminals[0], ast);

	printGraph(ast);

	verify(gsymbols);

	free(ptokenTypes);
	free(pNonTerminals);
	vector_free(&tokenTypes);
	deleteAllGraph(ast);
	free(ast);
}
