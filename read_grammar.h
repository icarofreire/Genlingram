/* Lib ler arquivo BNF/EBNF; */

const char delimiters_grammar[] = {
' ', /* espaço em branco; */
':', /* COLON */
'|', /* OR */
'(', /* LPAREN */
')', /* RPAREN */
'[', /* LBRACK */
']', /* RBRACK */
'?', /* QUESTION */
'*', /* MUL */
'+', /* ADD */
'\'',
'"'
};

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

// C substring function definition
void get_substring(char s[], char sub[], int pos, int len) {
    int i = 0;
    while (i < len) {
        sub[i] = s[pos+i];
        i++;
    }
    sub[i] = '\0';
}

/* Function to remove white spaces on both sides of a string i.e trim */
void trim(char *s)
{
    int i;
    while(isspace(*s)) s++;   // skip left side white spaces
    for(i = strlen(s) - 1; (isspace(s[i])); i--);   // skip right side white spaces
    s[i + 1] = '\0';
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

char *get_non_term(char *s){
    char *p1 = strstr(s, "::=");
    char *p2 = strstr(s, ":");

    int idx1 = p1-s;
    int idx2 = p2-s;

    char *sub = (char*)malloc((50)* sizeof(char));
    if(sub != NULL){
        if(idx1 > 0){
            get_substring(s, sub, 0, idx1); trim(sub);
        }else if(idx2 > 0){
            get_substring(s, sub, 0, idx2); trim(sub);
        }
    }
    return sub;
}

int only_alphabets( char *s )
{
    unsigned char c;
    char *p = s;
    while( (c = *p) && (isalpha(c) || (c == '_')) ) ++p;
    return *p == '\0';
}

char *get_production(char *s){
    char *p1 = strstr(s, "::=");
    char *p2 = strstr(s, ":");

    int idx1 = p1-s;
    int idx2 = p2-s;

    char *sub = (char*)malloc((50)* sizeof(char));
    if(sub != NULL){
        if(idx1 > 0){
            get_substring(s, sub, idx1+3, strlen(s));
            trim(sub);
        }else if(idx2 > 0){
            get_substring(s, sub, idx2+1, strlen(s));
            trim(sub);
        }
    }
    return sub;
}

void read_file_grammar(char* arquivo){
    // Create a file pointer and open the file "GFG.txt" in
    // read mode.
    FILE* file = fopen(arquivo, "r");

	int con = 0;
    const int max = 300;
    // Buffer to store each line of the file.
    char line[max];
    char linha_anterior[max];

    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {
			con++;
            // Print each line to the standard output.
            //~ printf("[%d]: %s", con, line);
            trim(line);
            bool comment = ((isBlank(line) != 1) && (line[0] == '#'));
            bool production = (!comment && (isBlank(line) != 1) && (line[0] != '|'));
            bool continue_production = (!comment && (isBlank(line) != 1) && (line[0] == '|'));
            //tokentize... ;

            /*\/ registrar linha que contém o non-terminal; */
            if(production){
                // priLineNonTerm = linha;
                strcpy(linha_anterior, line);
            }

            /*\/ exibir linha que continua com a primeira linha do non-terminal, ou
             não, apenas continua *com a linha completa já registrada; */
            if(continue_production){
                /*\/ linha encontrada pertencente a linha do non-terminal; */
            }else if(production){
            }

        }

        // Close the file stream once all lines have been
        // read.
        fclose(file);
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
	}

}
