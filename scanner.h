#include <string.h>
#include <ctype.h>
#include "symbols.h"
//~ #include "adjacency-list.h"
#include "tokenization.h"
#include "adjacency-list-lib2.h"

#define MAX_TOKEN 100

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

int num_token_demiliter(char *str){
	int num_token = -1;
	if (strcmp(str, "=") == 0) num_token = EQ;
	else if (strcmp(str, "+") == 0) num_token = ADD;
	else if (strcmp(str, "-") == 0) num_token = SUB;
	else if (strcmp(str, "!") == 0) num_token = NOT;
	else if (strcmp(str, "&") == 0) num_token = AND;
	else if (strcmp(str, "*") == 0) num_token = MUL;
	else if (strcmp(str, "/") == 0) num_token = DIV;
	else if (strcmp(str, "(") == 0) num_token = LPAREN;
	else if (strcmp(str, ")") == 0) num_token = RPAREN;
	else if (strcmp(str, ".") == 0) num_token = DOT;
	else if (strcmp(str, ",") == 0) num_token = COMMA;
	else if (strcmp(str, "?") == 0) num_token = QUESTION;
	else if (strcmp(str, "~") == 0) num_token = TILDE;
	else if (strcmp(str, ":") == 0) num_token = COLON;
	else if (strcmp(str, ";") == 0) num_token = SEMICOLON;
	else if (strcmp(str, "{") == 0) num_token = LBRACE;
	else if (strcmp(str, "}") == 0) num_token = RBRACE;
	else if (strcmp(str, "[") == 0) num_token = LBRACK;
	else if (strcmp(str, "]") == 0) num_token = RBRACK;
	else if (strcmp(str, "<") == 0) num_token = LESSER;
	else if (strcmp(str, "|") == 0) num_token = OR;
	else if (strcmp(str, "^") == 0) num_token = XOR;
	else if (strcmp(str, "%") == 0) num_token = MOD;
	else if (strcmp(str, ">") == 0) num_token = GREATER;
	return num_token;
}

bool isID(const char *str)
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

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(const char* str)
{
	return isID(str);
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

void parse(char*, int, struct NodeDLL*, struct Graph*);

void tokentize(char* str, int line)
{
	struct NodeDLL *nodeDLL = createNodeDLL("");
	tokentize_by_delimiters(str, nodeDLL);
	
	struct Graph* graph = createGraph();

	//~ forwardTraversal(nodeDLL);
	//~ forwardTraversalPassingFunction(nodeDLL, parse, line);


	// Start traversal from the head of the list
    struct NodeDLL* curr = nodeDLL;

    // Continue until the current node is not
    // null (end of list)
    while (curr != NULL) {
      
        // Output data of the current node
        //~ printf("%s -> ", curr->data);
        parse(curr->data, line, curr, graph);
      
        // Move to the next node
        curr = curr->next;
    }
    
    printGraph(graph);

}

void parse(char* token, int line, struct NodeDLL* nodeDLL, struct Graph* graph)
{
	char* str = token;
	if(isKeyword(str)){
		struct Token token = {str, line, TOKEN_PALAVRA_CHAVE};
		insertNode(graph, TOKEN_PALAVRA_CHAVE, &token);
	}
	if(isOpetatorLanguage(str)){
		struct Token token = {str, line, TOKEN_OPERADOR};
		insertNode(graph, TOKEN_PALAVRA_CHAVE, &token);
	}
	int token_demiliter = num_token_demiliter(str);
	if(token_demiliter != -1){
		struct Token token = {str, line, token_demiliter};
		insertNode(graph, token_demiliter, &token);
	}
	if(isString(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(validIdentifier(str)){
		struct Token token = {str, line, Identifier};
		insertNode(graph, Identifier, &token);
	}
	if(isInteger(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(isRealNumber(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(isBinaryNumber(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(isBooleanNumber(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(isNullLiteral(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(isOctalNumber(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}
	if(isHexNumber(str)){
		struct Token token = {str, line, Literal};
		insertNode(graph, Literal, &token);
	}

	//~ int tokens[] = {Identifier, TOKEN_OPERADOR, Literal};
	//~ reduceNode(graph, tokens, TAMANHO(tokens));
	//~ printGraph(graph);
	
	//~ free(graph->adjLists);
	//~ free(graph);
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
