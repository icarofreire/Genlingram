/* lib to read file code and apply; */

#include "hashMap.h"
#include "adjacency-list.h"
#include "DoublyLinkedList.h"
#include "tokenization.h"
#include "valid_basic_types.h"
#include "structs.h"
#include "earley.h"
#include "read_file_keywords.h"
#include "read_grammar.h"
#include "verify_ast.h"
#include "scan_spaced_things.h"

int literal_tokenType_grammar_lang(struct grammar_symbols* gsymbols, const int lang){
	int tokenType = -1;
	switch(lang){
		case RUBY: tokenType = get(gsymbols->symbolNum, "LITERAL"); break;
		case PYTHON: tokenType = get(gsymbols->symbolNum, "literal_pattern"); break;
		case JS: tokenType = get(gsymbols->symbolNum, "Literal"); break;
		case JAVA: tokenType = get(gsymbols->symbolNum, "literal"); break;
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

int* read_code_tokenize(char* arquivo, struct grammar_symbols* gsymbols, int *reftam, const int lang){
	// Create a file pointer and open the file "GFG.txt" in
	// read mode.
	FILE* file = fopen(arquivo, "r");

	// Buffer to store each line of the file.
	char line[300];

	// Check if the file was opened successfully.
	if (file != NULL) {

		int sizePtokenTypes = 2;
		int *pTokenTypes = (int*)malloc((sizePtokenTypes) * sizeof(int));

		// Read each line from the file and store it in the
		// 'line' buffer.
		int j = 0;
		int tk_obtidos = 0;
		/*\/ para detectar strings espaçadas; */
		int con_str_part = 0;
		/*\/ para detectar comentários; */
		int con_comment_part = 0, ncoment = 0;
		while (fgets(line, sizeof(line), file)) {
			// Print each line to the standard output.

			/*\/ inserir simbolos registrados(token types) em um vetor para análise; */
			int tam = 0;
			char **tokens = process_tokens(line, delimiters, &tam, true);
			array_add_size(&pTokenTypes, &sizePtokenTypes, tam);

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
								pTokenTypes[j++] = tokenType_literal;
								// printf("4tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, tokenType_literal));
								take = tokenType_literal;
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
							pTokenTypes[j++] = tokenType_literal;
							// printf("1tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, tokenType_literal));
							take = tokenType_literal;
						}
					}

					/*\/ identificar identifier tokentype; */
					if(!take){
						int tokenType_identifier = get_identifier_tokenType_lang(gsymbols, tokens[i], lang);
						if(tokenType_identifier != -1){
							pTokenTypes[j++] = tokenType_identifier;
							// printf("2tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, tokenType_identifier));
							take = tokenType_identifier;
						}
					}

					/*\/ identificar não-terminais tokentype; */
					if(!take){
						int sym = get_tokenType_symbols_grammar(gsymbols, tokens[i]);
						if(sym != -1){
							pTokenTypes[j++] = sym;
							// printf("3tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, sym));
							take = sym;
						}
					}

					if(take > 0){
						printf("tk: [%s] = [%s]\n", tokens[i], getKeyByValue(gsymbols->symbolNum, take));
					}

				}// fim if;
			}
			free_strings(tokens, tam);
		}
		if(tk_obtidos == (j+ncoment)) printf("[todos os tokens reconhecidos];\n");
		// printf("tt: [%d, %d, %d]\n", tk_obtidos, j, ncoment);
		*reftam = j;
		// Close the file stream once all lines have been
		// read.
		fclose(file);
		return pTokenTypes;
	}
	else {
		// Print an error message to the standard error
		// stream if the file cannot be opened.
		fprintf(stderr, "Unable to open file!\n");
	}
	return NULL;
}

void printGraphNonTerm(struct Graph* graph, struct grammar_symbols* gsymbols) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        printf("\nNodo %d(%s): ", tempNode->val, getKeyByValue(gsymbols->symbolNum, tempNode->val));
        tempEdge = tempNode->edges;
        while (tempEdge) {
            printf(" -> %d(%s)", tempEdge->dest->val, getKeyByValue(gsymbols->symbolNum, tempEdge->dest->val));
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

/*\/ Criar arquivo .dot com dados do grafo para
poder gerar uma imagem do grafo; 
criar arquivo .dot e poder criar o grafo(Graphviz);
# instalar Graphviz:
https://graphviz.org/download/
$ sudo apt install graphviz

# comando para criar a imagem do grafo:
$ dot -Tjpg ast.dot > ast.jpg
https://graphviz.org/doc/info/command.html
*/
void create_file_dot_graph(struct Graph* graph, struct grammar_symbols* gsymbols) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

	FILE *fptr;
   	fptr = fopen("ast.dot","w");
	if(fptr == NULL) return;
	fprintf(fptr,"digraph {\n");
	fprintf(fptr,"overlap=prism\n");
	fprintf(fptr,"rankdir=\"LR\"\n");
	fprintf(fptr,"splines=curved\n");

    while (tempNode != NULL) {
        tempEdge = tempNode->edges;
        while (tempEdge) {
			char *a = getKeyByValue(gsymbols->symbolNum, tempNode->val);
			char *b = getKeyByValue(gsymbols->symbolNum, tempEdge->dest->val);

			char *sl = "";
			if(strcmp(b, "\"") == 0) sl = "\\";

			fprintf(fptr,"\"%s\" -> \"%s%s\"\n", a, sl, b );
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
	fprintf(fptr,"}\n");
}

/*\/ criar arquivo .dot a partir da arvore em DLL; */
void create_file_dot_tree(struct grammar_symbols* gsymbols, struct NodeDLL *head) {

	FILE *fptr;
   	fptr = fopen("tree.dot","w");
	if(fptr == NULL) return;
	fprintf(fptr,"digraph {\n");
	fprintf(fptr,"overlap=prism\n");
	fprintf(fptr,"rankdir=\"LR\"\n");
	fprintf(fptr,"splines=curved\n");
	
	struct NodeDLL *curr = head;
    while (curr != NULL) {
        if(curr->len_children_datas > 0){
            for(int i=0; i<curr->len_children_datas; i++){
                if(curr->children_datas[i] != -1){
					char *a = getKeyByValue(gsymbols->symbolNum, curr->data);
					char *b = getKeyByValue(gsymbols->symbolNum, curr->children_datas[i]);
					char *sl = "";
					if(strcmp(b, "\"") == 0) sl = "\\";
					fprintf(fptr,"\"%s\" -> \"%s%s\"\n", a, sl, b );
				}
            }
        }
        curr = curr->next;
    }

	fprintf(fptr,"}\n");
}

void printTokenTypesInput(int *pTokenTypes, int sizePtokenTypes, struct grammar_symbols* gsymbols){
	for(int i=0; i<sizePtokenTypes; i++){
		printf("tk-Num: [%d][%s]\n", pTokenTypes[i], getKeyByValue(gsymbols->symbolNum, pTokenTypes[i]));
	}
}

int get_ini_nonTerm_grammar(struct grammar_symbols* gsymbols, const int lang){
	int ini_grammar = -1;
	switch(lang){
		case RUBY: ini_grammar = get(gsymbols->nonTerminals, "PROGRAM"); break;
		case PYTHON: ini_grammar = get(gsymbols->nonTerminals, "statements"); break;
		case JS: ini_grammar = get(gsymbols->nonTerminals, "Program"); break;
		case JAVA: ini_grammar = get(gsymbols->nonTerminals, "compilation_unit"); break;
	}
	return ini_grammar;
}

/*\/ free dates for struct grammar_symbols; */
void free_dates_grammar_symbols(struct grammar_symbols* gsymbols){
	free_map(gsymbols->symbolNum);
	free_map(gsymbols->nonTerminals);
	deleteAllGraph(gsymbols->grammar);
	free_strings(gsymbols->keywords_lang, gsymbols->len_keywords);
	free(gsymbols->grammar);
}

void apply_earley_in_code(char *file_code, const int lang){
	struct grammar_symbols* gsymbols = read_grammar(lang);

	int sizePtokenTypes = 0;
	int *pTokenTypes = read_code_tokenize(file_code, gsymbols, &sizePtokenTypes, lang);

	int sizeNonTerm = 0;
	int *pNonTerminals = getValues(gsymbols->nonTerminals, &sizeNonTerm);

	/*\/ tree; */
	struct NodeDLL *tree = createNodeDLL(0);

	struct Graph *ast = createGraph();
	int ini_grammar = get_ini_nonTerm_grammar(gsymbols, lang);
	if(ini_grammar != -1){
		EARLEY_PARSE(gsymbols->grammar, pTokenTypes, sizePtokenTypes, pNonTerminals, sizeNonTerm, ini_grammar, ast, gsymbols, tree);
	}

	// printGraph(ast);
	// printGraphNonTerm(ast, gsymbols);
	create_file_dot_graph(ast, gsymbols);
	// printMap(gsymbols->symbolNum);
	// printTokenTypesInput(pTokenTypes, sizePtokenTypes, gsymbols);
	struct NodeDLL *reduceTree = reduce_tree(tree, pTokenTypes, sizePtokenTypes);
	// verify(gsymbols, ast, tree);
	// printListAndChildrens(tree);
	create_file_dot_tree(gsymbols, reduceTree);
	// printf("[%d] Non-Terminals;\n", sizeNonTerm);
	printf("[%d] tokens de entrada;\n", sizePtokenTypes);


	free(pNonTerminals);
	free(pTokenTypes);
	deleteAllGraph(ast);
	free(ast);

	deleteAllNodes(&tree);
	free(tree);

	/*\/ free dates for struct grammar_symbols; */
	free_dates_grammar_symbols(gsymbols);
}
