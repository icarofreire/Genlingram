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

// DRIVER FUNCTION
int main()
{
	printf("Genlingram. ;)\n");

	// char *file_code = "testes/code-input.txt";
	// char *file_code = "testes/AStarSearch.txt";
	// char *file_code = "testes/code-js-2.txt";
	// char *file_code = "testes/prisioners-js.txt";
	// char *file_code = "testes/code-example-js.txt";
	apply_files_rule("testes/code-example-js.txt", "rules/code-example-js.txt", JS);
	
	return (0);
}
