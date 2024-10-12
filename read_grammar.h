/* Lib ler arquivo BNF/EBNF; */

const char delimiters_grammar[] = {
' ', /* espaço em branco; */
':', /* COLON */
'|' /* OR */
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

void read_file_grammar(char* arquivo){
    // Create a file pointer and open the file "GFG.txt" in
    // read mode.
    FILE* file = fopen(arquivo, "r");

	int con = 0;
    const int max = 300;
    // Buffer to store each line of the file.
    char line[max];

    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {
			con++;
            // Print each line to the standard output.
            //~ printf("[%d]: %s", con, line);
            //tokentize... ;
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
