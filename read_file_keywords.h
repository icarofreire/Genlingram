/* Lib read keywords of lang; */

char **read_file_keywords(char* arquivo, int *reftam){
    // Create a file pointer and open the file "GFG.txt" in
    // read mode.
    FILE* file = fopen(arquivo, "r");
    const int max = 300;
    // Buffer to store each line of the file.
    char line[max];
    
    int max_allocated = 100;
    char **strings = (char**)malloc(max_allocated * sizeof(char*));

    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        int i = 0;
        while (fgets(line, sizeof(line), file)) {
            // Print each line to the standard output.
            trim(line);
            strings[i] = (char*)malloc((strlen(line) + 1) * sizeof(char));
            if(strings[i] != NULL){
                strcpy(strings[i], line);
                i++;
            }
        }
        // Close the file stream once all lines have been
        // read.
        fclose(file);

        if(i > 0) *reftam = i;
        return strings;
    }
    else {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        fprintf(stderr, "Unable to open file!\n");
	}
	return NULL;
}

char **read_keywords(int *reftam, const int lang){
    char **strings = NULL;
    switch(lang){
        case RUBY: strings = read_file_keywords("grammars/ruby-keywords.txt", reftam); break;
        case PYTHON: strings = read_file_keywords("grammars/python-keywords.txt", reftam); break;
        case JS: strings = read_file_keywords("grammars/js-keywords.txt", reftam); break;
    }
    return strings;
}
