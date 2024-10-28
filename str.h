/* lib to operation strings; */

void trim(char *str) {
    while (isspace((unsigned char)str[0])){
        memmove(str, str + 1, strlen(str));
    }
    while (isspace((unsigned char)str[strlen(str) - 1])){
        str[strlen(str) - 1] = '\0';
    }
}

// Returns -1 if line is a string containing only whitespace (or is empty);
int isBlank (char const * line)
{
    int is_blank = 1;
    for (int i = 0; i<strlen(line); i++){
        if (!isspace(line[i])){
            // Found a non-whitespace character.
            is_blank = -1;
            break;
        }
    }
    return is_blank;
}

int only_alphabets( char *s )
{
    unsigned char c;
    char *p = s;
    while( (c = *p) && (isalpha(c) || (c == '_') || (c == '-')) ) ++p;
    return *p == '\0';
}

// C substring function definition
void get_substring(char s[], char sub[], int pos, int len) {
    int i = 0;
    while (i < len) {
        sub[i] = s[pos+i];
        i++;
    }
    sub[i] = '\0';
}

char *insert_aspas(const char *str, bool aspa_simples){
	char tipo_aspa = (aspa_simples) ? ('\'') : ('\"');
	int tam = strlen(str);
	char *copy = (char*)malloc((tam + 3)* sizeof(char));
	copy[0] = tipo_aspa;
	memcpy(copy+1, str, strlen(str));
	copy[tam+1] = tipo_aspa;
	copy[tam+2] = '\0';
	return copy;
}

/*\/ ; */
char* str_retirar_aspas(const char *str){
    if((str[0] == '\'' || str[0] == '\"') && (str[strlen(str)-1] == '\'' || str[strlen(str)-1] == '\"'))
    {
        char* word_sasp = (char*)malloc((strlen(str))* sizeof(char));
        memcpy(word_sasp, str+1, strlen(str)-2);
        word_sasp[strlen(str)-2] = '\0';
        return word_sasp;
    }
    return NULL;
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

void free_strings(char **strings, int size){
	// Free memory for each string
	for (int i = 0; i < size; i++) {
		free(strings[i]);
	}
	// Free memory for the array of pointers
	free(strings);
}

int detectLowerOrUpper( const char * string ) /* pass a null-terminated char pointer */
{
    int length = strlen(string); /* Length */
    int foundLower = 0; /* "boolean" integers */
    int foundUpper = 0;

    for( int i = 0; i < length; ++i ) /* Loop over the entire string */
    {
        if( string[i] >= 'a' && string[i] <= 'z' ) /* Check for lowercase */
            foundLower++;
        else if( string[i] >= 'A' && string[i] <= 'Z' ) /* Compare uppercase */
            foundUpper++;
    }

    int res = 0;
    if( foundLower == length && foundUpper == 0 ) res = 0;
    else if( foundUpper == length && foundLower == 0 ) res = 1;
    else res = -1;

    return res; /* All of the letters are one case */
}

bool is_string(const char *str)
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

char **get_strings_in_string(char str[], int *len){
    int max_allocated = 20;
    char **strings = (char**)malloc(max_allocated * sizeof(char*));
    int ind_str = 0;
    int ps1 = 0, ps2 = 0;
    const int quad = 2;
    int aspas[quad][quad]; // 0 => simples; 1 => duplas;
    aspas[0][0] = aspas[0][1] = aspas[1][0] = aspas[1][1] = -1;

    for(int i=0; i<strlen(str); i++){

        bool nexts = (((i+1)<strlen(str)) && str[i+1] == '\'');
        bool nextd = (((i+1)<strlen(str)) && str[i+1] == '"');

        if(str[i] == '\''){
            ps1++;
            if(ps1 == 1) {aspas[0][0] = i;}
            if(ps1 == 2) {aspas[0][1] = i;}
            if(ps1 == 2 && nexts && (aspas[0][1]-aspas[0][0])==1) {aspas[0][1] = i+1;}
        }
        if(str[i] == '"'){
            ps2++;
            if(ps2 == 1) {aspas[1][0] = i;}
            if(ps2 == 2) {aspas[1][1] = i;}
            if(ps2 == 2 && nextd && (aspas[1][1]-aspas[1][0])==1) {aspas[1][1] = i+1;}
        }

        for(int g=0; g<quad; g++){
            int idx_ant = aspas[g][0];
            int prese = aspas[g][1];

            if(idx_ant != -1 && prese != -1){
                int tam = (prese-idx_ant)+1;
                if(ind_str < max_allocated){
                    strings[ind_str] = (char*)malloc((tam)* sizeof(char));
                    get_substring(str, strings[ind_str], idx_ant, tam);
                    ind_str++;
                    (*len)++;
                }
                i = aspas[g][1];
                ps1 = ps2 = 0;
                aspas[g][0] = aspas[g][1] = -1;
            }
        }
    }
    return strings;
}