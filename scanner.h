#include <string.h>
#include <ctype.h>
#include "symbols.h"

#include "adjacency-list.h"
#include "Token.h"
#include "tokenization.h"
#include "vector.h"

//~ #define MAX_TOKEN 100

bool isKeyword(const char* str);

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
	int k, tam = TAMANHO(delimiters);
	for (k = 0; k < tam; k++) {
		if (ch == delimiters[k]){
			return (true);
		}
	}
	return (false);
}

//~ int num_token_delimiter(char *str){
	//~ int num_token = -1;
	//~ if (strcmp(str, "=") == 0) num_token = EQ;
	//~ else if (strcmp(str, "+") == 0) num_token = ADD;
	//~ else if (strcmp(str, "-") == 0) num_token = SUB;
	//~ else if (strcmp(str, "!") == 0) num_token = NOT;
	//~ else if (strcmp(str, "&") == 0) num_token = AND;
	//~ else if (strcmp(str, "*") == 0) num_token = MUL;
	//~ else if (strcmp(str, "/") == 0) num_token = DIV;
	//~ else if (strcmp(str, "(") == 0) num_token = LPAREN;
	//~ else if (strcmp(str, ")") == 0) num_token = RPAREN;
	//~ else if (strcmp(str, ".") == 0) num_token = DOT;
	//~ else if (strcmp(str, ",") == 0) num_token = COMMA;
	//~ else if (strcmp(str, "?") == 0) num_token = QUESTION;
	//~ else if (strcmp(str, "~") == 0) num_token = TILDE;
	//~ else if (strcmp(str, ":") == 0) num_token = COLON;
	//~ else if (strcmp(str, ";") == 0) num_token = SEMICOLON;
	//~ else if (strcmp(str, "{") == 0) num_token = LBRACE;
	//~ else if (strcmp(str, "}") == 0) num_token = RBRACE;
	//~ else if (strcmp(str, "[") == 0) num_token = LBRACK;
	//~ else if (strcmp(str, "]") == 0) num_token = RBRACK;
	//~ else if (strcmp(str, "<") == 0) num_token = LESSER;
	//~ else if (strcmp(str, "|") == 0) num_token = OR;
	//~ else if (strcmp(str, "^") == 0) num_token = XOR;
	//~ else if (strcmp(str, "%") == 0) num_token = MOD;
	//~ else if (strcmp(str, ">") == 0) num_token = GREATER;
	//~ return num_token;
//~ }

int tokenType_predefinidos(char* str){
	for(int i=0; i<TOKEN_FIM; i++){
		if(strcmp(str, tokens_struct[i].identifier) == 0){
			//~ printf("%s -> %d\n", tokens_struct[i].identifier, tokens_struct[i].tokenType );
			return tokens_struct[i].tokenType;
		}
	}
	return -1;
}

int obter_tokenType_predefinido(int tokenType){
	if(tokenType < TOKEN_FIM){
		return (tokens_struct[tokenType].tokenType == tokenType) ? (tokenType) : (-1);
	}
	return -1;
}

bool isString(const char *str)
{
  int fim = strlen(str);
  if(
	(str[0] == '"' || str[0] == '\'') &&
	(str[fim-1] == '"' || str[fim-1] == '\'')
   ){
	return true;
   }else{
	return false;
   }
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=')
		return (true);
	return (false);
}

// Returns true if [c] is a valid (non-initial) identifier character.
bool isName(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(const char* str)
{
	for(int counter = 0; counter < strlen(str); counter++){
		if(!isName(str[counter])){ return false; }
	}
	return true;
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(const char* str)
{
	bool f = false;
	int i, tam = TAMANHO(reserved_words);
	for (i = 0; i < tam; i++) {
		if (strcmp(str, reserved_words[i]) == 0){
			f = true;
		}
	}
	return f;
}

// Returns 'true' if the string is a OPERATOR.
bool isOpetatorLanguage(const char* str)
{
	int i, tam = TAMANHO(operators);
	for (i = 0; i < tam; i++) {
		if (strcmp(str, operators[i]) == 0){
			return true;
		}
	}
	return false;
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(const char* str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if ((str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9') || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(const char* str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if ((str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.') ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

// Returns 'true' if the string is a BINARY NUMBER.
bool isBinaryNumber(const char* str)
{
	int i, len = strlen(str);
	bool fb1 = false, fb2 = true;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'b') || (str[0] == '0' && str[1] == 'B') ){ fb1 = true; }
	for (i = 2; i < len; i++) {
		if ((str[i] != '0' && str[i] != '1')){
			fb2 = false;
		}
	}
	return (fb1 && fb2);
}

bool isBooleanNumber(const char* str)
{
	int len = strlen(str);
	bool f = false;

	if (len == 0) return (false);

	if ((strcmp(str, "true") == 0) || (strcmp(str, "false") == 0)){ f = true; }
	return (f);
}

bool isNullLiteral(const char* str)
{
	int len = strlen(str);
	bool f = false;

	if (len == 0) return (false);

	if ((strcmp(str, "null") == 0) || (strcmp(str, "NULL") == 0)){ f = true; }
	return (f);
}

bool isOctalNumber(const char* str)
{
	int i, len = strlen(str);
	bool f1 = false, f2 = true;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'o') || (str[0] == '0' && str[1] == 'O') ){ f1 = true; }
	for (i = 2; i < len; i++) {
		if( isdigit(str[i]) == 0 ){
			f2 = false;
		}
	}
	return (f1 && f2);
}

bool isHexNumber(const char* str)
{
	int i, len = strlen(str);
	bool f1 = false, f2 = false;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'x') || (str[0] == '0' && str[1] == 'X') ){ f1 = true; }
	for (i = 2; i < len; i++) {
		if( (isdigit(str[i]) > 0) &&
		( str[i] != 'a' && str[i] != 'b' && str[i] != 'c' && str[i] != 'd' && str[i] != 'e' && str[i] != 'f' &&
		  str[i] != 'A' && str[i] != 'B' && str[i] != 'D' && str[i] != 'E' && str[i] != 'F'
		)
		){
			f2 = true;
		}
	}
	return (f1 == true && f2 == true);
}

// Extracts the SUBSTRING.
char* subString(const char* str, int left, int right)
{
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

void parse(char*, int, struct NodeDLL*);
void create_graph(struct NodeDLL *, struct Graph* graph);

void tokentize(char* str, int line, struct NodeDLL *nodeDLL)
{
	tokentize_by_delimiters(str, nodeDLL);

	// Start traversal from the head of the list
    struct NodeDLL* curr = nodeDLL;

    // Continue until the current node is not
    // null (end of list)
    while (curr != NULL) {
        // Output data of the current node
        //~ printf("%s -> ", curr->data);
        parse(curr->data, line, curr);
        //~ if(curr->token)printf("['%s' -> %d : idx %d]\n", curr->token->identifier, curr->token->tokenType, curr->index);
        //~ printf("['%s']\n", curr->data);
      
        // Move to the next node
        curr = curr->next;
    }
    //~ printf("\n***\n");
}

bool compare_tokenType_node(struct NodeDLL* curr, int tokenType){
	return (curr->token->tokenType == tokenType);
}

bool detect_operator(struct NodeDLL* curr, int tokenType){
int operadores[] = {
TOKEN_EQ,
TOKEN_ADD,
TOKEN_SUB,
TOKEN_NOT,
TOKEN_AND,
TOKEN_MUL,
TOKEN_DIV,
TOKEN_LESSER,
TOKEN_OR,
TOKEN_XOR,
TOKEN_MOD,
TOKEN_GREATER,
TOKEN_EQEQ,
TOKEN_ADDEQ,
TOKEN_INCR,
TOKEN_SUBEQ,
TOKEN_DECR,
TOKEN_NOTEQ,
TOKEN_ANDEQ,
TOKEN_LAND,
TOKEN_OREQ,
TOKEN_LOR,
TOKEN_XOREQ,
TOKEN_LXOR,
TOKEN_MODEQ,
TOKEN_DIVEQ,
TOKEN_MULEQ,
TOKEN_LESSEREQ,
TOKEN_LSHF,
TOKEN_GREATEREQ,
TOKEN_RSHF,
TOKEN_FARROW,
TOKEN_LSHFEQ,
TOKEN_EQEQEQ,
TOKEN_NOTEQEQ,
TOKEN_RSHFEQ,
TOKEN_URSHF,
TOKEN_URSHFEQ
};
	for(int i=0; i<TAMANHO(operadores); i++){
		if( operadores[i] == curr->token->tokenType ){
			return true;
		}
	}
	return false;
}

void criarEdgeIndexAnterior(struct Graph*, struct NodeDLL*, int);
void criarEdgeIndexPos(struct Graph*, struct NodeDLL*, int);

struct NodeDLL* searchFaixasIndexs(struct Graph* graph, struct NodeDLL* head, int index_ini, int index_fim) {
    struct NodeDLL* curr = head;

    while (curr != NULL) {

        if(curr->index > index_ini && curr->index <= index_fim){
			//edge anterior -> atual;
			insertNode(graph, curr->index);
			criarEdgeIndexAnterior(graph, curr, curr->index);
		}
        // Move to the next node
        curr = curr->next;
    }
    return NULL;
}

void searchForwardClosesNodeByTokenType(struct Graph* graph, struct NodeDLL* head, int tokenTypeAbertura, int tokenTypeFechamento, vector* visitados) {
    struct NodeDLL* curr = head;
    
    const int max_p = 100;
    struct NodeDLL pilha[max_p];
    int encont = 0;
    while (curr != NULL) {

        if(curr->token->tokenType == tokenTypeAbertura && !vector_contains_int(visitados, curr->index)){
			pilha[encont] = *curr;
			 vector_add(visitados, &curr->index);
			encont++;

		}else if(curr->token->tokenType == tokenTypeFechamento && !vector_contains_int(visitados, curr->index)){
			encont--;
			vector_add(visitados, &curr->index);
			if(encont >= 0){
				printf("edge: (P: %d)%d -> %d\n", pilha[0].index, pilha[encont].index, curr->index);
				
				insertNode(graph, pilha[0].index);
				insertNode(graph, pilha[encont].index);
				insertNode(graph, curr->index);
				/*\/ evitar criar edge de cada vertice para o vertice pai principal; */
				if( pilha[0].index != pilha[encont].index){
					searchFaixasIndexs(graph, head, pilha[encont].index, curr->index);
					insertEdge(graph, pilha[0].index, pilha[encont].index);
				}
			}
		}
        // Move to the next node
        curr = curr->next;
    }

}

void printGraph2(struct Graph*, struct NodeDLL*);
void printGraphInTree(struct Graph* graph, struct NodeDLL* head);

void create_graph(struct NodeDLL *nodeDLL, struct Graph* graph){
	
	vector visitados;
    vector_init(&visitados);

    struct NodeDLL* curr = nodeDLL;
    while (curr != NULL) {

        if(curr->token){
			//~ printf("['%s' -> %d]\n", curr->token->identifier, curr->token->tokenType);
			
			int predTokenType = obter_tokenType_predefinido(curr->token->tokenType);
			if(predTokenType != -1){
				insertNode(graph, curr->index);
			}
			if(compare_tokenType_node(curr, IDENTIFIER_NAME)){
				insertNode(graph, curr->index);
			}
			if(compare_tokenType_node(curr, DECIMAL_LITERAL)){
				insertNode(graph, curr->index);
			}
			if(compare_tokenType_node(curr, STRING_LITERAL)){
				insertNode(graph, curr->index);
			}
			if(compare_tokenType_node(curr, HEX_INTEGER_LITERAL)){
				insertNode(graph, curr->index);
			}
			if(compare_tokenType_node(curr, Literal)){
				insertNode(graph, curr->index);
			}
			if(compare_tokenType_node(curr, NULL_LITERAL)){
				insertNode(graph, curr->index);
			}

			//~ if(detect_operator(curr, curr->token->tokenType)){
				//~ insertNode(graph, curr->index);
				//~ criarEdgeIndexAnterior(graph, curr, curr->index);
				//~ criarEdgeIndexPos(graph, curr, curr->index);
			//~ }
			
			//~ {TOKEN_IF, "if"}, {TOKEN_ELSE, "else"},
			//~ if(compare_tokenType_node(curr, TOKEN_IF)){
				//~ insertNode(graph, curr->index);
				//~ searchForwardClosesNodeByTokenType(graph, curr, TOKEN_IF, TOKEN_ELSE);
			//~ }

			//~ {TOKEN_LPAREN, "("},{TOKEN_RPAREN, ")"},
			if(compare_tokenType_node(curr, TOKEN_LPAREN)){
				insertNode(graph, curr->index);
				searchForwardClosesNodeByTokenType(graph, curr, TOKEN_LPAREN, TOKEN_RPAREN, &visitados);
			}
			
			//~ {TOKEN_LBRACK, "["},{TOKEN_RBRACK, "]"},
			if(compare_tokenType_node(curr, TOKEN_LBRACK)){
				insertNode(graph, curr->index);
				searchForwardClosesNodeByTokenType(graph, curr, TOKEN_LBRACK, TOKEN_RBRACK, &visitados);
			}
			
			//~ {TOKEN_LBRACE, "{"},{TOKEN_RBRACE, "}"},
			if(compare_tokenType_node(curr, TOKEN_LBRACE)){
				insertNode(graph, curr->index);
				searchForwardClosesNodeByTokenType(graph, curr, TOKEN_LBRACE, TOKEN_RBRACE, &visitados);
			}
			
			
		}

        // Move to the next node
        curr = curr->next;
    }
    
    vector_delete_all(&visitados);
    vector_free(&visitados);

	//~ printGraph(graph);
	printGraph2(graph, nodeDLL);
}

void printGraph2(struct Graph* graph, struct NodeDLL* head) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

	FILE *fptr = fopen("graph.txt","w");
	if(fptr != NULL){
		while (tempNode != NULL) {
			printf("\nNodo %d: ", tempNode->val);
			tempEdge = tempNode->edges;
			while (tempEdge) {
				struct NodeDLL* node = searchForwardNodeByIndex(head, tempEdge->dest->val);
				if(node != NULL){
					printf(" -> %d('%s')", tempEdge->dest->val, node->data);
					fprintf(fptr,"%d -> %d[label=\"%s\"];\n", tempNode->val, tempEdge->dest->val, node->data);
				}
				tempEdge = tempEdge->next;
			}
			tempNode = tempNode->next;
		}
	}
}

void criarEdgeIndexAnterior(struct Graph* graph, struct NodeDLL* nodeDLL, int indexAtual){
	/*\/ inserir edge do token anterior para o token atual; */
	struct NodeDLL* node_anterior = nodeDLL->prev;
	if(node_anterior != NULL){
		insertEdge(graph, node_anterior->index, indexAtual);
	}
}

void criarEdgeIndexPos(struct Graph* graph, struct NodeDLL* nodeDLL, int indexAtual){
	/*\/ inserir edge do token posterior para o token atual; */
	struct NodeDLL* node_pos = nodeDLL->next;
	if(node_pos != NULL){
		insertNode(graph, node_pos->index);
		insertEdge(graph, indexAtual, node_pos->index);
	}
}

void parse(char* token, int line, struct NodeDLL* nodeDLL)
{
	char* str = token;
	
	int tokenTypePreDef = tokenType_predefinidos(str);
	if(tokenTypePreDef != -1){
		struct Token token = {str, line, tokenTypePreDef};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isKeyword(str)){
		int tokenType = tokenType_predefinidos(str);
		if(tokenType != -1){
			struct Token token = {str, line, tokenType};
			insertTokenStructInDLL(nodeDLL, &token);
		}
	}
	if(isOpetatorLanguage(str)){
		int tokenType = tokenType_predefinidos(str);
		if(tokenType != -1){
			struct Token token = {str, line, tokenType};
			insertTokenStructInDLL(nodeDLL, &token);
		}
	}
	if(isString(str)){
		struct Token token = {str, line, STRING_LITERAL};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(validIdentifier(str)){
		struct Token token = {str, line, IDENTIFIER_NAME};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isInteger(str)){
		struct Token token = {str, line, DECIMAL_LITERAL};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isRealNumber(str)){
		struct Token token = {str, line, Literal};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isBinaryNumber(str)){
		struct Token token = {str, line, Literal};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isBooleanNumber(str)){
		struct Token token = {str, line, Literal};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isNullLiteral(str)){
		struct Token token = {str, line, NULL_LITERAL};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isOctalNumber(str)){
		struct Token token = {str, line, Literal};
		insertTokenStructInDLL(nodeDLL, &token);
	}
	if(isHexNumber(str)){
		struct Token token = {str, line, HEX_INTEGER_LITERAL};
		insertTokenStructInDLL(nodeDLL, &token);
	}

}

/*
void parse2(char* str)
{
    // Space is used as the delimiter to split
    const char delimiter[] = {' ', ';', '\0'};

    // Declare empty string to store token
    char* token;

    // Get the first token
    token = strtok(str, delimiters);
    
    // Create an undirected graph with 3 vertices
    //~ struct AdjacencyList* graph = createGraph(20);

    // using loop to get the rest of the token
    while (token) {
        	char* str = token;
			if(isKeyword(str)){
				//~ addEdge(graph, str, TOKEN_PALAVRA_CHAVE);
			}
			if(isOpetatorLanguage(str)){
				//~ addEdge(graph, str, TOKEN_OPERADOR);
			}
			//~ if(isDelimiter(str)){
				//~ addEdge(graph, str, TOKEN_PALAVRA_CHAVE);
			//~ }
			if(isString(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(validIdentifier(str)){
				//~ addEdge(graph, str, Identifier);
			}
			if(isInteger(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(isRealNumber(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(isBinaryNumber(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(isBooleanNumber(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(isNullLiteral(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(isOctalNumber(str)){
				//~ addEdge(graph, str, Literal);
			}
			if(isHexNumber(str)){
				//~ addEdge(graph, str, Literal);
			}
        
        token = strtok(NULL, delimiter);
    }

	//~ int tokens[] = {Identifier, TOKEN_OPERADOR, Literal};
	//~ reduceNode(graph, tokens, TAMANHO(tokens));
	//~ printGraph(graph);
	
	//~ free(graph->adjLists);
	//~ free(graph);
}
*/
