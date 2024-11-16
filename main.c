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

int str_lang_to_const_enum(const char* lang){
	if(strcmp(lang, "python")) return PYTHON;
	else if(strcmp(lang, "ruby")) return RUBY;
	else if(strcmp(lang, "js")) return JS;
	else if(strcmp(lang, "java")) return JAVA;
	return -1;
}

char* get_extension_lang(const int lang){
	char* ext = (char *)malloc((10) * sizeof(char));
	switch(lang){
		case PYTHON:
			strcpy(ext, "py");
			ext[2] = '\0';
			break;
		case RUBY:
			strcpy(ext, "rb");
			ext[2] = '\0';
			break;
		case JS:
			strcpy(ext, "js");
			ext[2] = '\0';
			break;
		case JAVA:
			strcpy(ext, "java");
			ext[4] = '\0';
			break;
	}
	return ext;
}

void apply_rules_in_project(char* dir_project, char* dir_rules, const int lang){

	char* extension = get_extension_lang(lang);

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
				apply_files_rule(file_code, file_rule, lang);
			}
		}
	}

	free_strings(files_rules, len_array_files_rules);
	free_strings(files, len_array_files);
	free(extension);
}

void filter_commands(int argc, char **argv){
	char *cmd = NULL;
	char proj[100];
	char lang[50];
	char rules[100];
	for (int i = 0; i < argc; i++) {

		char* opt = "-proj=";
		cmd = strstr(argv[i], opt);
		if(cmd != NULL){
			int len = strlen(argv[i]) - strlen(opt);
			memcpy(proj, argv[i]+strlen(opt), len);
			proj[len] = '\0';
		}

		opt = "-rules=";
		cmd = strstr(argv[i], opt);
		if(cmd != NULL){
			int len = strlen(argv[i]) - strlen(opt);
			memcpy(rules, argv[i]+strlen(opt), len);
			rules[len] = '\0';
		}

		opt = "-lang=";
		cmd = strstr(argv[i], opt);
		if(cmd != NULL){
			int len = strlen(argv[i]) - strlen(opt);
			memcpy(lang, argv[i]+strlen(opt), len);
			lang[len] = '\0';
		}
    }

	if(
		strcmp(proj, "") != 0 &&
		strcmp(lang, "") != 0 &&
		strcmp(rules, "") != 0
	){
		int lang_num = str_lang_to_const_enum(lang);
		if(lang_num != -1){
			apply_rules_in_project(proj, rules, lang_num);
		}
	}
}

// DRIVER FUNCTION
int main(int argc, char **argv)
{
	printf("Genlingram. ;)\n");

	filter_commands(argc, argv);

	// char *file_code = "testes/code-input.txt";
	// char *file_code = "testes/AStarSearch.txt";
	// char *file_code = "testes/code-js-2.txt";
	// char *file_code = "testes/prisioners-js.txt";
	// char *file_code = "testes/code-example-js.txt";
	// apply_files_rule("testes/code-example-js.txt", "rules/code-example-js.txt", JS);

	// apply_rules_in_project("rules", "rules", JS);


	return (0);
}
