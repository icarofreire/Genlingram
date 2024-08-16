#include <string.h>
#include <ctype.h>
#include "symbols.h"
//~ #include "LinkedList.c"
#include "adjacency-list.h"

#define MAX_TOKEN 100

//~ struct numbers_tokens_grammar {
	//~ int ponto;
	//~ int number_tokens_grammar;
	
	//~ char *token;
	//~ struct numbers_tokens_grammar *prox_token[MAX_TOKEN];
//~ } numers_grammar;

//~ struct numbers_tokens_grammar* new_node();

//~ struct numbers_tokens_grammar* push_tokens_grammar(struct numbers_tokens_grammar *x, int token, char* str_token){
	//~ printf("Add token [%d][%s]\n", token, str_token);
	//~ x->ponto++;
	//~ printf("Add token [%d][%s]\n", token, str_token);
	//~ x->number_tokens_grammar = token;
	//~ x->token = str_token;
	//~ return x;
//~ }

//~ struct numbers_tokens_grammar* add_node(struct numbers_tokens_grammar *x, int token, char* str_token){
	//~ struct numbers_tokens_grammar *novo = new_node();
	//~ novo->ponto = 1;
	//~ novo->number_tokens_grammar = token;
	//~ novo->token = str_token;
	
	//~ x->prox_token[x->ponto] = novo;
	//~ x->ponto++;
	//~ return novo;
//~ }

//~ struct numbers_tokens_grammar* new_node(){
	//~ struct numbers_tokens_grammar* temp =
		//~ (struct numbers_tokens_grammar*)malloc(sizeof(struct numbers_tokens_grammar));
	//~ return temp;
//~ }

bool isKeyword(char* str);

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
	//~ if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		//~ ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		//~ ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		//~ ch == '[' || ch == ']' || ch == '{' || ch == '}')
		//~ return (true);
	//~ return (false);
	int k, tam = TAMANHO(delimiters);
	for (k = 0; k < tam; k++) {
		if (ch == delimiters[k]){
			return (true);
		}
	}
	return (false);
}

bool isID(char *str)
{

  if(isKeyword(str)){
	return false;
  }

  if(isdigit(str[0]))
    return false;
  int counter = 0;
  if(str[0] == '_')
    counter++;

  for(; counter < strlen(str); counter++)
    if(!(isalnum(str[counter])))
      return false;

  return true;
}

bool isString(char *str)
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

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str)
{
	//~ if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		//~ str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		//~ str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		//~ str[0] == '9' || isDelimiter(str[0]) == true)
		//~ return (false);
	//~ return (true);
	return isID(str);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{
	bool f = false;
	int i, tam = TAMANHO(reserved_words);
	for (i = 0; i < tam; i++) {
		if (strcmp(str, reserved_words[i]) == 0){
			f = true;
		}
	}
	return f;
	/*if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") ||
		!strcmp(str, "break") ||
		!strcmp(str, "continue") || !strcmp(str, "int")
		|| !strcmp(str, "double") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char")
		|| !strcmp(str, "case") || !strcmp(str, "char")
		|| !strcmp(str, "sizeof") || !strcmp(str, "long")
		|| !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "switch") || !strcmp(str, "unsigned")
		|| !strcmp(str, "void") || !strcmp(str, "static")
		|| !strcmp(str, "struct") || !strcmp(str, "goto"))
		return (true);
	return (false);*/
}

// Returns 'true' if the string is a OPERATOR.
bool isOpetatorLanguage(char* str)
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
bool isInteger(char* str)
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
bool isRealNumber(char* str)
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
bool isBinaryNumber(char* str)
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

bool isBooleanNumber(char* str)
{
	int len = strlen(str);
	bool f = false;

	if (len == 0) return (false);

	if ((strcmp(str, "true") == 0) || (strcmp(str, "false") == 0)){ f = true; }
	return (f);
}

bool isNullLiteral(char* str)
{
	int len = strlen(str);
	bool f = false;

	if (len == 0) return (false);

	if ((strcmp(str, "null") == 0) || (strcmp(str, "NULL") == 0)){ f = true; }
	return (f);
}

bool isOctalNumber(char* str)
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

bool isHexNumber(char* str)
{
	int i, len = strlen(str);
	bool f1 = false, f2 = false;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'x') || (str[0] == '0' && str[1] == 'X') ){ f1 = true; }
	for (i = 2; i < len; i++) {
		if( (isdigit(str[i]) > 0) &&
		( str[i] != 'a' && str[i] != 'b' && str[i] != 'c' && str[i] != 'd' && str[i] != 'e' && str[i] != 'f' &&
		  str[i] != 'A' && str[i] != 'B' && str[i] != 'D' && str[i] != 'D' && str[i] != 'E' && str[i] != 'F'
		)
		){
			f2 = true;
		}
	}
	return (f1 == true && f2 == true);
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right)
{
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

//~ void showNode(Node *node){
	//~ while(node != NULL && node->previous != NULL && node->next != NULL){
		//~ printf("[%s]<< >>[%s]\n", (char*)node->previous->value, (char*)node->next->value);
	//~ }
//~ }

//~ void showLinkedList(struct LinkedList *linked) {
    //~ LinkedListIterator *iterator = LinkedListIterator_new(linked);
	//~ LinkedListIterator_move_to_next(iterator);
	//~ while(iterator->index != LINKEDLIST_INDEX_END){
			//~ printf("N(%d): [%s]\n", iterator->index, (char*)iterator->current->value);
			//~ LinkedListIterator_move_to_next(iterator);
	//~ }
//~ }

//~ //void LinkedListIterator_move_to_previous(LinkedListIterator *itr_ptr);
//~ void reg_previous_nodeList(struct LinkedList *linked) {
    //~ LinkedListIterator *iterator = LinkedListIterator_new(linked);
	//~ // obtém valor do no anterior;
	//~ printf("[prev]: [%d][%s]\n", iterator->index, (char*)linked->last->previous->value);
	
	//~ LinkedList_pushback(linked, (char*)linked->last->previous->value);
//~ }


void parse2(char* str)
{
    // Space is used as the delimiter to split
    char delimiter[] = {' ', ';'};
 
    // Declare empty string to store token
    char* token;
 
    //~ printf("Initial String: %s", str);
    //~ printf("\nAfter Tokenization: \n");
    // Get the first token
    token = strtok(str, delimiters);
    
    //~ struct numbers_tokens_grammar *numers_grammar = new_node();//{0, {0}};
    //~ numers_grammar->ponto = 0;
    //~ LinkedList *linked = LinkedList_new();
    
    // Create an undirected graph with 3 vertices
    struct AdjacencyList* graph = createGraph(20);

    // using loop to get the rest of the token
    while (token) {
        	char* str = token;
			if(isKeyword(str)){
				//~ printf("IS AN KEY >>\n");
				//~ push_tokens_grammar(numers_grammar, TOKEN_PALAVRA_CHAVE, str);
				//~ LinkedList_pushback(linked, str);
				//~ add_node(numers_grammar, TOKEN_PALAVRA_CHAVE, str);
				addEdge(graph, str, TOKEN_PALAVRA_CHAVE);
			}
			if(isOpetatorLanguage(str)){
				//~ printf("IS AN OPER 2 >>\n");
				//~ push_tokens_grammar(numers_grammar, TOKEN_OPERADOR, str);
				//~ LinkedList_pushback(linked, str);
				//~ reg_previous_nodeList(linked);
				addEdge(graph, str, TOKEN_OPERADOR);
				//~ addEdgeNNodes(graph, 1);
			}
			if(isString(str)){
				//~ push_tokens_grammar(&numers_grammar, stringLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ add_node(numers_grammar, Literal, str);
				//~ LinkedList_pushback(linked, str);
			}
			if(validIdentifier(str)){
				//~ push_tokens_grammar(numers_grammar, Identifier, str, openf);openf = 0;
				//~ add_node(numers_grammar, Identifier, str);
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Identifier);
			}
			if(isInteger(str)){
				//~ push_tokens_grammar(&numers_grammar, decimalLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ add_node(numers_grammar, Literal, str);
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
			if(isRealNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, numericLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
			if(isBinaryNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, numericLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
			if(isBooleanNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, booleanLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
			if(isNullLiteral(str)){
				//~ push_tokens_grammar(&numers_grammar, nullLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
			if(isOctalNumber(str)){
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ push_tokens_grammar(&numers_grammar, Literal);
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
			if(isHexNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, hexIntegerLiteral);
				//~ push_tokens_grammar(numers_grammar, Literal, str, openf);openf = 0;
				//~ LinkedList_pushback(linked, str);
				addEdge(graph, str, Literal);
			}
        
        token = strtok(NULL, delimiter);
    }
    
    /*\/ exibir a tabela de tokens; */
	//~ int r;
	//~ for(r = 0; r <= numers_grammar->ponto; r++){
		//~ printf(">> %d - [%s]\n", numers_grammar->number_tokens_grammar, numers_grammar->token);
		//~ if(numers_grammar->prox_token){
			//~ printf(">>>> %d - [%s]\n", numers_grammar->prox_token[0]->number_tokens_grammar, numers_grammar->prox_token[0]->token);
		//~ }
	//~ }

	//~ showLinkedList(linked);
	//~ balanceGraph(graph);
	int tokens[] = {Identifier, TOKEN_OPERADOR, Literal};
	reduceNode(graph, tokens, 3);
	//~ balanceGraph2(graph, graph->adjLists[3], graph->adjLists[4]);
	printGraph(graph);
	//~ printf(">> (%d) %d - [%s]\n", numers_grammar->ponto, numers_grammar->number_tokens_grammar, numers_grammar->token);

	//~ int r = 0;
	//~ struct numbers_tokens_grammar *next = numers_grammar->prox_token;
	//~ while(next && r < 10){
		//~ printf(">>>> %d - [%s]\n", numers_grammar->number_tokens_grammar, numers_grammar->token);
		//~ next = numers_grammar->prox_token;
		//~ r++;
	//~ }
}

/*
// Parsing the input STRING.
void parse(char* str)
{
	int left = 0, right = 0;
	int len = strlen(str);
	struct numbers_tokens_grammar numers_grammar = {0, {0}};

	while (right <= len && left <= right) {
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right) {
			//~ if (isOperator(str[right]) == true)
				//~ printf("'%c' IS AN OPERATOR\n", str[right]);
			//~ if( str[right] != ' ' ){ 
				char sinal[] = {str[right], '\0'};
				if(isOpetatorLanguage(sinal)){
					
					printf("%c[%d] IS AN OPERATOR >> %s\n", sinal[0], right, sinal);
					push_tokens_grammar(&numers_grammar, sinal[0], sinal);
				}
			//~ }
			right++;
			left = right;
		} else if ((isDelimiter(str[right]) == true && left != right)
				|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);

			printf("--> '%s'\n", subStr);
			char* str = subStr;
			
			if(isKeyword(str)){
				printf("IS AN KEY >>\n");
				push_tokens_grammar(&numers_grammar, TOKEN_PALAVRA_CHAVE, str);
			}
			if(isOpetatorLanguage(str)){
				//~ printf("IS AN OPER 2 >>\n");
				push_tokens_grammar(&numers_grammar, TOKEN_OPERADOR, str);
			}
			if(isString(str)){
				//~ push_tokens_grammar(&numers_grammar, stringLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			if(validIdentifier(str)){
				push_tokens_grammar(&numers_grammar, Identifier, str);
			}
			if(isInteger(str)){
				//~ push_tokens_grammar(&numers_grammar, decimalLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			if(isRealNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, numericLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			if(isBinaryNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, numericLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			if(isBooleanNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, booleanLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			if(isNullLiteral(str)){
				//~ push_tokens_grammar(&numers_grammar, nullLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			if(isOctalNumber(str)){
				push_tokens_grammar(&numers_grammar, Literal, str);
				//~ push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isHexNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, hexIntegerLiteral);
				push_tokens_grammar(&numers_grammar, Literal, str);
			}
			
			left = right;
		}
	}
	
	// exibir a tabela de tokens;
	int r;
	for(r = 0; r <= numers_grammar.ponto; r++){
		printf(">> %d - [%s]\n", numers_grammar.number_tokens_grammar[r], numers_grammar.token[r]);
	}
	
	return;
}
*/
