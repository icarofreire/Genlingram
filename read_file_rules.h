/* lib to read file code with rules and examples; */


/*\/ ; */
struct tokens_reads* read_file_rules(char *file_code, const int lang){
	struct grammar_symbols* gsymbols = read_grammar(lang);

	struct tokens_reads* tksReads = read_code_tokenize(file_code, gsymbols, lang);

	/* ... */


	/*\/ free dates for struct grammar_symbols; */
	free_dates_grammar_symbols(gsymbols);
    return tksReads;
}
