/* lib to tokenize strings; */

#include <ctype.h>

const char delimiters[] = {
' ', /* espaço em branco; */
'=', /* EQ */
'+', /* ADD */
'-', /* SUB */
'!', /* NOT */
'&', /* AND */
'*', /* MUL */
'/', /* DIV */
'(', /* LPAREN */
')', /* RPAREN */
'.', /* DOT */
',', /* COMMA */
'?', /* QUESTION */
'~', /* TILDE */
':', /* COLON */
';', /* SEMICOLON */
'{', /* LBRACE */
'}', /* RBRACE */
'[', /* LBRACK */
']', /* RBRACK */
'<', /* LESSER */
'|', /* OR */
'^', /* XOR */
'%', /* MOD */
'>', /* GREATER */
'\0'
};

char *insert_aspas(char *str, bool aspa_simples){
	char tipo_aspa = (aspa_simples) ? ('\'') : ('\"');
	int tam = strlen(str);
	char *copy = (char*)malloc((tam + 3)* sizeof(char));
	copy[0] = tipo_aspa;
	memcpy(copy+1, str, strlen(str));
	copy[tam+1] = tipo_aspa;
	copy[tam+2] = '\0';
	return copy;
}

bool is_special_char(char c){
	return ((isalpha(c) == 0) && (c != '_'));
}

void appendChar(char *str, char ch) {
	// Find the length of the string
	int len = strlen(str);

	// Place the character at the end
	str[len] = ch;

	// Null-terminate the string
	str[len + 1] = '\0';
}

/**
 * @brief Call a function for each token found in the input string.
 * @param s input string
 * @param sep nul-terminated set of delimiter characters, or NULL for default
 * @param reftam pointer to reference a length of array of tokens to be returned
 * @param returnDelims bollean to return delimiters or not
 */
char** process_tokens(char *s, const char *sep, int *reftam, bool returnDelims)
{
	char** strings = NULL;
	// Declare the initial size of the dynamic array
	int size = 20;

	// Allocate memory for the array of strings
	strings = (char**)malloc(size * sizeof(char*));
	if (strings == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		return NULL;
	}

	/*\/ inserir um delimitador no final da linha para garantir a tokenização da ultima palavra; */
	char tokenEnd = ' ';
	if(s[strlen(s)-1] != tokenEnd){
		appendChar(s, tokenEnd);
	}

	int i = 0;
	for(; (*s) != '\0'; s++){

		for(int k=0; k<strlen(s); k++){
			char* sh = strchr(sep, s[k]);
			if(sh != NULL) {
				int idx = k;
				char delim = s[k];

				/*\/ string antes do delimitador; */
				char buf[idx + 1];
				memcpy(buf, s, idx);
				buf[idx] = 0;
				// printf(">> buf: [%s] >> delim: [%c]\n", buf, delim);

				if((i+2) < size){
					if(strcmp(buf, "") != 0){
						strings[i] = (char*)malloc((idx + 1)* sizeof(char));
						if (strings[i] != NULL) {
							memcpy(strings[i], s, idx);
							strings[i][idx] = 0;
							i++;
						}
					}

					if(returnDelims && delim != ' '){
						strings[i] = (char*)malloc((1)* sizeof(char));
						if (strings[i] != NULL) {
							strings[i][0] = delim;
							strings[i][1] = 0;
							i++;
						}
					}
				}else{
					size++;
					strings = (char**)realloc(strings, size * sizeof(char*));
					s--; break;
				}
				s += idx;
				break;
			}
		}
	}

	if(i > 0) *reftam = i;
	return strings;
}

void free_strings(char **strings, int size){
	// Free memory for each string
	for (int i = 0; i < size; i++) {
		free(strings[i]);
	}
	// Free memory for the array of pointers
	free(strings);
}
