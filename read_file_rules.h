/* lib to read file code with rules and examples; */


/*\/ ; */
int *read_file_code_rules(char *file_code, const int lang, int *size){
	struct grammar_symbols* gsymbols = read_grammar(lang);

	int sizePtokenTypes = 0;
	int *pTokenTypes = read_code_tokenize(file_code, gsymbols, &sizePtokenTypes, lang);

    *size = sizePtokenTypes;
	/* ... */


	/*\/ free dates for struct grammar_symbols; */
	free_dates_grammar_symbols(gsymbols);
    return pTokenTypes;
}
