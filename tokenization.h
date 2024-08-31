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
