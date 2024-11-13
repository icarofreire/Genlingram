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
#include "scan_spaced_things.h"
#include "tokenize_code.h"
#include "read_file_rules.h"


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

			if(strcmp(a, "") != 0 && strcmp(b, "") != 0)fprintf(fptr,"\"%s\" -> \"%s%s\"\n", a, sl, b );
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
	fprintf(fptr,"}\n");
	fclose(fptr);
}

/*\/ criar arquivo .dot a partir da arvore em DLL; */
void create_file_dot_tree(struct grammar_symbols* gsymbols, struct NodeDLL *head, char* name_file) {

	FILE *fptr;
   	fptr = fopen(name_file,"w");
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
					if(strcmp(a, "") != 0 && strcmp(b, "") != 0)fprintf(fptr,"\"%s\" -> \"%s%s\"\n", a, sl, b );
				}
            }
        }
        curr = curr->next;
    }

	fprintf(fptr,"}\n");
	fclose(fptr);
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

/*\/ exibindo a arvore para verificar a ordem dos tokens inseridos; */
void gerate_txt_tree(struct grammar_symbols* gsymbols, struct NodeDLL *head) {

	FILE *fptr;
   	fptr = fopen("tree.txt","w");
	if(fptr == NULL) return;

    struct NodeDLL *curr = head;
    while (curr != NULL) {
		fprintf(fptr, "[%d](%s):\n", curr->data, getKeyByValue(gsymbols->symbolNum, curr->data) );
        if(curr->len_children_datas > 0){
			fprintf(fptr, "\t");
            for(int i=0; i<curr->len_children_datas; i++){
                if(curr->children_datas[i] != -1) {
					fprintf(fptr, "[%d](%s) -> ", curr->children_datas[i], getKeyByValue(gsymbols->symbolNum, curr->children_datas[i]));
                }
            }fprintf(fptr, "\n\n");
        }
        curr = curr->next;
    }
	fclose(fptr);
}

/*\/ ; */
struct NodeDLL* apply_earley_in_code(struct grammar_symbols* gsymbols, struct tokens_reads* tokensFileCode, const int lang){

	struct tokens_reads* tksReads = tokensFileCode;

	int sizeNonTerm = 0;
	int *pNonTerminals = getValues(gsymbols->nonTerminals, &sizeNonTerm);

	/*\/ tree; */
	struct NodeDLL *tree = createNodeDLL(0);

	struct Graph *ast = createGraph();
	int ini_grammar = get_ini_nonTerm_grammar(gsymbols, lang);
	if(ini_grammar != -1){
		EARLEY_PARSE(gsymbols->grammar, tksReads->pTokenTypes, tksReads->sizePtokenTypes, pNonTerminals, sizeNonTerm, ini_grammar, ast, gsymbols, tree);
	}

	free(pNonTerminals);
	deleteAllGraph(ast);
	free(ast);

	return tree;
}
