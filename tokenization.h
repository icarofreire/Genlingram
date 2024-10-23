#include "DoublyLinkedList.h"

void trimString(char *str) {
	while (isspace((unsigned char)str[0])){
		memmove(str, str + 1, strlen(str));
	}
	while (isspace((unsigned char)str[strlen(str) - 1])){
		str[strlen(str) - 1] = '\0';
	}
}

// C substring function definition
void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

/*
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
*/

bool is_special_char(char c){
	return ((isalpha(c) == 0) && (c != '_'));
}

// Returns 'true' if the character is a DELIMITER.
bool is_delimiter(char ch)
{
	int k, tam = TAMANHO(delimiters);
	for (k = 0; k < tam; k++) {
		if (ch == delimiters[k]){
			return (true);
		}
	}
	return (false);
}

int next_index_delimiter(char *str, int lim){
	lim = ((lim > 0) ? (lim) : (strlen(str)));
	for(int i=0; i<lim; i++){
		if(is_delimiter(str[i])){
			return i;
		}
	}
	return -1;
}

bool is_not_only_space(char* str){
	for(int i=0; i<strlen(str); i++){
		if(isspace(str[i]) != 0){
			return false;
		}
	}
	return true;
}

void tokentize_by_delimiters(char *str, struct NodeDLL *nodeDLL){
    for(; (*str) != '\0'; str++){
		int index_deli = next_index_delimiter(str, 0);
		if(index_deli != -1){

			char delimiter = str[index_deli];
			char word[index_deli+1];
			substring(str, word, 1, index_deli);
			trimString(word);

			if(strcmp(word, "") != 0 && is_not_only_space(word)){
				//~ printf(">> '%s' p: '%d'\n", word, strlen(word) );
				insertEnd(nodeDLL, word);
			}
			if(delimiter != ' '){
				//~ printf("d>> '%c'\n", delimiter);
				char temp_str_delimiter[] = {delimiter, '\0'};
				insertEnd(nodeDLL, temp_str_delimiter);
			}
			str+=index_deli;
		}
		else if(index_deli == -1){
			/* \/ caso a string esteja perto de seu fim, mas não encontra um delimitador; */
			int index_prox_fim = next_index_delimiter(str, index_deli);
			if(index_prox_fim == -1){

				char word_fim[index_prox_fim+1];
				substring(str, word_fim, 1, strlen(str));
				if(is_not_only_space(word_fim)){
					insertEnd(nodeDLL, word_fim);
					str+=strlen(str)-1;
				}
				//~ printf("FIM: %s\n", word_fim);
			}
		}
	}
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
