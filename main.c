#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "read_file_code.h"


/*
 <P> ::= <S>      # the start *rule
 <S> ::= <S> "+" <M> | <M>
 <M> ::= <M> "*" <T> | <T>
 <T> ::= "1" | "2" | "3" | "4"
*/
enum example{
P,//0
S,//1
M,//2
T,//3
PLUS,//4
MULT,//5
NUM,//6
};

void teste_earley(){
	/*
	/ / int len_tokens_i*nput = 5;
	int tokens_input[] = {NUM, PLUS, NUM, MULT, NUM};
	// int tokens_input[] = {MULT, MULT, MULT, MULT, NUM};

	int nomTerm[] = {S,M,T};
	struct Graph *G2 = createGraph();
	insertNode(G2, P);
	insertNode(G2, S);
	insertNode(G2, M);
	insertNode(G2, T);
	insertNode(G2, PLUS);
	insertNode(G2, MULT);
	insertNode(G2, NUM);

	insertEdge(G2, P, S);// # the start rule;
	insertEdge(G2, S, S);
	insertEdge(G2, S, PLUS);
	insertEdge(G2, S, M);

	insertEdge(G2, M, M);
	insertEdge(G2, M, MULT);
	insertEdge(G2, M, T);

	insertEdge(G2, T, NUM);

	struct Graph *ast = createGraph();
	*/
	// EARLEY_PARSE(G2, tokens_input, TAMANHO(tokens_input), nomTerm[0], nomTerm, TAMANHO(nomTerm), S, ast);

	// printGraph(G2);
	// printf("Path: %d\n", isPath(G2, 4, 6) );
	// printf("\n***\nAST:");
	// printGraph(ast);
}

// DRIVER FUNCTION
int main()
{
	printf("Genlingram. ;)\n");

	apply_earley_in_code("testes/code-input.txt", RUBY);
	// apply_earley_in_code("testes/AStarSearch.txt", PYTHON);
	// apply_earley_in_code("testes/code-example-js.txt", JS);

	
	return (0);
}
