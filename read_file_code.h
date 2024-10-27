/* lib to read file code and apply; */
#include <stdint.h>
#include "adjacency-list.h"
#include "tokenization.h"
#include "valid_basic_types.h"
#include "earley.h"
#include "read_grammar.h"
#include "verify_ast.h"

int get_literal_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = identify_primitive_types(token);
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

void read_code_tokenize(char* arquivo, struct grammar_symbols* gsymbols, int **pTokenTypes, int *sizePtokenTypes, const int lang){
	// Create a file pointer and open the file "GFG.txt" in
	// read mode.
	FILE* file = fopen(arquivo, "r");

	// Buffer to store each line of the file.
	char line[300];

	// Check if the file was opened successfully.
	if (file != NULL) {
		// Read each line from the file and store it in the
		// 'line' buffer.
		int j = 0;
		while (fgets(line, sizeof(line), file)) {
			// Print each line to the standard output.

			/*\/ inserir simbolos registrados(token types) em um vetor para análise; */
			int tam = 0;
			char **tokens = process_tokens(line, delimiters, &tam, true);
			array_add_size(pTokenTypes, sizePtokenTypes, tam);

			for(int i=0; i<tam; i++){
				trim(tokens[i]);

				/*\/ identificar literal tokentype; */
				int tokenType_literal = get_literal_tokenType_lang(gsymbols, tokens[i], lang);
				if(tokenType_literal != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], tokenType_literal);
					// printf("[%d, %d]\n", *sizePtokenTypes, j++);
					(*pTokenTypes)[j++] = tokenType_literal;
					// printf("1tk: [%s] = [%d]\n", tokens[i], tokenType_literal);
				}

				/*\/ identificar identifier tokentype; */
				// int tokenType_identifier = get_identifier_tokenType_lang(gsymbols, tokens[i], lang);
				// if(tokenType_identifier != -1){
				// 	// printf("tk: [%s] = [%d]\n", tokens[i], tokenType_identifier);
				// 	// printf("[%d, %d]\n", *sizePtokenTypes, j++);
				// 	(*pTokenTypes)[j++] = tokenType_identifier;
				// 	// printf("2tk: [%s] = [%d]\n", tokens[i], tokenType_identifier);
				// }

				/*\/ TODO identificar keywords tokentype; */

				/*\/ identificar não-terminais tokentype; */
				int sym = get_nonTerminals_tokenType_lang(gsymbols, tokens[i]);
				if(sym != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], sym);
					// printf("[%d, %d]\n", *sizePtokenTypes, j++);
					(*pTokenTypes)[j++] = sym;
					// printf("3tk: [%s] = [%d]\n", tokens[i], sym);
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

/*\/ imprimir o ast como forma de debug; */
void printGraphNonTerm(struct Graph* graph, struct grammar_symbols* gsymbols) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            printf(" -> %d(%s)", tempEdge->dest->val, getKeyByValue(gsymbols->symbolNum, tempEdge->dest->val));
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

void apply_earley_in_code(char *file_code, const int lang){
	struct grammar_symbols* gsymbols = read_grammar(lang);

	int sizePtokenTypes = 2;
	int *pTokenTypes = (int*)malloc((sizePtokenTypes) * sizeof(int));

	read_code_tokenize(file_code, gsymbols, &pTokenTypes, &sizePtokenTypes, lang);

	int sizeNonTerm = 0;
	int *pNonTerminals = getValues(gsymbols->nonTerminals, &sizeNonTerm);

	struct Graph *ast = createGraph();
	EARLEY_PARSE(gsymbols->grammar, pTokenTypes, sizePtokenTypes, pNonTerminals[0], pNonTerminals, sizeNonTerm, pNonTerminals[0], ast);

	// printGraph(ast);
	printGraphNonTerm(ast, gsymbols);

	// verify(gsymbols);
	printf("[%d] Non-Terminals;\n", sizeNonTerm);
	printf("[%d] tokens de entrada;\n", sizePtokenTypes);


	free(pNonTerminals);
	free(pTokenTypes);
	deleteAllGraph(ast);
	free(ast);
	free_map(gsymbols->symbolNum);
	free_map(gsymbols->nonTerminals);
	deleteAllGraph(gsymbols->grammar);
	free(gsymbols->grammar);
}
