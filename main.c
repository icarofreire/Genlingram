#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dir.h"
#include "read_file_code.h"
#include "verify_ast.h"


void apply_files_rule(char *file_code, char *file_rules, const int lang){
	struct grammar_symbols* gsymbols = read_grammar(lang);

	/*\/ read e apply in file code; */
	struct tokens_reads* tokensFileCode = read_code_tokenize(file_code, gsymbols, lang);
	struct NodeDLL *tree = apply_earley_in_code(gsymbols, tokensFileCode, lang);


	/*\/ read e apply in file rules; */
	struct tokens_reads* tokensRules = read_file_rules(file_rules, lang);
	/*\/ aplicar earley em arquivo de regras para analise; */
	struct NodeDLL *treeFileRules = apply_earley_in_code(gsymbols, tokensRules, lang);


	/*\/ criando arquivos .dot(graphviz) para analise; */
	create_file_dot_tree(gsymbols, tree, "ast.dot");
	struct NodeDLL *reduceTree = reduce_tree_term(tree, tokensFileCode->pTokenTypes, tokensFileCode->sizePtokenTypes);
	create_file_dot_tree(gsymbols, reduceTree, "tree.dot");


	/*\/ criando .txt arvore para analise; */
	gerate_txt_tree(gsymbols, tree);

	/*\/ verificação por ast; */
	verify(gsymbols, tree, tokensFileCode, tokensRules, file_code);

	/*\/ verificação por padrões lineares; */
	verificar_trechos_lineares(tokensFileCode, tokensRules, file_code);


	free(treeFileRules);
	free_tokens_reads(tokensRules);

	deleteAllNodes(&tree);
	free(tree);
	free_tokens_reads(tokensFileCode);

	/*\/ free dates for struct grammar_symbols; */
	free_dates_grammar_symbols(gsymbols);
}

void apply_rules_in_project(char* dir_project, char* dir_rules, const char *extension, const int lang){

	int len_array_files = 0;
	char** files = get_files_recursive(dir_project, &len_array_files, extension);

	int len_array_files_rules = 0;
	char** files_rules = get_files_recursive(dir_rules, &len_array_files_rules, extension);

	if(len_array_files_rules > 0 && len_array_files > 0){
		for(int i=0; i<len_array_files; i++){
			char* file_code = files[i];
			for(int j=0; j<len_array_files_rules; j++){
				char* file_rule = files_rules[j];
				// printf(">> file: [%s] -> [%s]\n", file_code, file_rule);
				// apply_files_rule(file_code, file_rule, lang);
			}
		}
	}

	free_strings(files_rules, len_array_files_rules);
	free_strings(files, len_array_files);
}

// DRIVER FUNCTION
int main()
{
	printf("Genlingram. ;)\n");

	// char *file_code = "testes/code-input.txt";
	// char *file_code = "testes/AStarSearch.txt";
	// char *file_code = "testes/code-js-2.txt";
	// char *file_code = "testes/prisioners-js.txt";
	// char *file_code = "testes/code-example-js.txt";
	// apply_files_rule("testes/code-example-js.txt", "rules/code-example-js.txt", JS);

	// get_files_rules("rules");
	// list_files_project("rules", "txt");
	apply_rules_in_project("rules", "rules", "txt", JS);
	
	// int len_array_files = 0;
	// char** files = get_files_recursive("rules", &len_array_files, "txt");
	// for(int i=0; i<len_array_files; i++){
	// 	printf(">> [%s]\n", files[i]);
	// }

	return (0);
}
