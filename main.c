#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "read_file_code.h"
#include "verify_ast.h"


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

void testeGRaph(){
	struct Graph* G2 = createGraph();

insertNode(G2, 0);
insertNode(G2, 1);
insertNode(G2, 2);
insertNode(G2, 3);
insertNode(G2, 4);
insertNode(G2, 5);
insertNode(G2, 6);
insertNode(G2, 7);
insertNode(G2, 8);
insertNode(G2, 9);
insertNode(G2, 10);
insertNode(G2, 11);
insertNode(G2, 12);
insertNode(G2, 13);

// ***

insertEdge(G2, 3, 1);
insertEdge(G2, 1, 0);
insertEdge(G2, 3, 7);
insertEdge(G2, 7, 9);
insertEdge(G2, 3, 4);
insertEdge(G2, 3, 2);
insertEdge(G2, 4, 5);
insertEdge(G2, 4, 12);
insertEdge(G2, 4, 8);
insertEdge(G2, 12, 13);
insertEdge(G2, 2, 10);
insertEdge(G2, 2, 6);
insertEdge(G2, 10, 11);

removeEdge(G2, 10, 11);
// removeEdge(G2, 3, 2);

printGraph(G2);
}

void	exampleB()
{
	// 1 <-> 2 <-> 3
    struct NodeDLL *head = createNodeDLL(1);
	append(&head, 2);
	append(&head, 3);

	add_date_in_array_node(head, 2, 55);
	add_date_in_array_node(head, 3, 56);
	add_date_in_array_node(head, 3, 57);

	append(&head, 55);
	add_date_in_array_node(head, 55, 99);

	// printList(head);
	printListAndChildrens(head);
}

// DRIVER FUNCTION
int main()
{
	printf("Genlingram. ;)\n");

	// apply_earley_in_code("testes/code-input.txt", RUBY);
	// apply_earley_in_code("testes/AStarSearch.txt", PYTHON);
	struct NodeDLL *tree = apply_earley_in_code("testes/code-example-js.txt", JS);
	// apply_earley_in_code("testes/code-js-2.txt", JS);
	// apply_earley_in_code("testes/prisioners-js.txt", JS);
	// testeGRaph();
	// exampleB();

	/*\/ read file rules; */
	// int sizeNonTerm = 0;
	// int *pNonTerminals = read_file_code_rules("rules/code-example-js.txt", JS, &sizeNonTerm);
	
	return (0);
}
