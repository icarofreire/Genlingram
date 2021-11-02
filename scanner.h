#include <string.h>
#include <ctype.h>
#include "symbols.h"

struct numbers_tokens_grammar {
	int ponto;
	int number_tokens_grammar[1000];
} numers_grammar;

void push_tokens_grammar(struct numbers_tokens_grammar *x, int token){
	x->ponto++;
	printf("Add token [%d]\n", token);
	x->number_tokens_grammar[x->ponto] = token;
}

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
	bool f = false;
	int i, tam = TAMANHO(operators);
	for (i = 0; i < tam; i++) {
		if (strcmp(str, operators[i]) == 0){
			f = true;
		}
	}
	return f;
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
			/*\/ eliminar o espaço em branco e interpretar somente os operadores reais; */
			if( str[right] != ' ' ){ 
				char sinal[] = {str[right], '\0'};
				if(isOpetatorLanguage(sinal)){
					//~ printf("%c[%d] IS AN OPERATOR >> %s\n", str[right], right, sinal);
					push_tokens_grammar(&numers_grammar, TOKEN_OPERADOR);
				}
			}
			right++;
			left = right;
		} else if ((isDelimiter(str[right]) == true && left != right)
				|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);

			printf("--> '%s'\n", subStr);
			char* str = subStr;
			
			if(isKeyword(str)){
				push_tokens_grammar(&numers_grammar, TOKEN_PALAVRA_CHAVE);
			}
			if(isOpetatorLanguage(str)){
				push_tokens_grammar(&numers_grammar, TOKEN_OPERADOR);
			}
			if(isString(str)){
				//~ push_tokens_grammar(&numers_grammar, stringLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			if(validIdentifier(str)){
				push_tokens_grammar(&numers_grammar, Identifier);
			}
			if(isInteger(str)){
				//~ push_tokens_grammar(&numers_grammar, decimalLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isRealNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, numericLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isBinaryNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, numericLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isBooleanNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, booleanLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isNullLiteral(str)){
				//~ push_tokens_grammar(&numers_grammar, nullLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isOctalNumber(str)){
				push_tokens_grammar(&numers_grammar, Literal);
				//~ push_tokens_grammar(&numers_grammar, Literal);
			}
			if(isHexNumber(str)){
				//~ push_tokens_grammar(&numers_grammar, hexIntegerLiteral);
				push_tokens_grammar(&numers_grammar, Literal);
			}
			
			left = right;
		}
	}
	
	/*\/ exibir a tabela de tokens; */
	int r;
	for(r = 0; r < numers_grammar.ponto; r++){
		printf(">> %d\n", numers_grammar.number_tokens_grammar[r]);
	}
	
	return;
}
