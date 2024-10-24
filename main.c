#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"
#include "earley.h"
#include "read_grammar.h"

//~ #include "Lib-Adjacency-List.h"
//~ #include "adjacency-list-lib2.h"
//~ #include "tokens_grammar.h"
//~ #include "DoublyLinkedList.h"
//~ #include "tokenization.h"

#define TAM_X 105
#define TAM_Y 100

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/* \/ grammar; */
int grammar[TAM_X][TAM_Y] = {
{ PrimaryExpression, TOKEN_PALAVRA_CHAVE, ObjectLiteral, ABRE_BLOCO, TOKEN_ABRE_PARENTESE, Expression, TOKEN_FECHA_PARENTESE, FECHA_BLOCO, Identifier, ArrayLiteral, Literal, FIM_PARTE_EXPRESSAO},
{ Literal, ABRE_BLOCO, DECIMAL_LITERAL, HEX_INTEGER_LITERAL, STRING_LITERAL, BOOLEAN_LITERAL, NULL_LITERAL, REGULAR_EXPRESSION_LITERAL, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ Identifier, IDENTIFIER_NAME, FIM_PARTE_EXPRESSAO},
{ ArrayLiteral, TOKEN_OPERADOR, ABRE_BLOCO, ABRE_BLOCO, Elision, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, ElementList, Elision, TOKEN_OPERADOR, ABRE_BLOCO, ElementList, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ ElementList, ABRE_BLOCO, Elision, FECHA_BLOCO, OPCIONAL, AssignmentExpression, ABRE_BLOCO, Elision, AssignmentExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ Elision, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, REP_MAIS, FIM_PARTE_EXPRESSAO},
{ ObjectLiteral, TOKEN_OPERADOR, ABRE_BLOCO, PropertyNameAndValueList, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ PropertyNameAndValueList, PropertyNameAndValue, ABRE_BLOCO, TOKEN_OPERADOR, PropertyNameAndValue, TOKEN_OPERADOR, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ PropertyNameAndValue, PropertyName, TOKEN_OPERADOR, AssignmentExpression, FIM_PARTE_EXPRESSAO},
{ PropertyName, Identifier, STRING_LITERAL, DECIMAL_LITERAL, FIM_PARTE_EXPRESSAO},
{ MemberExpression, ABRE_BLOCO, ABRE_BLOCO, FunctionExpression, PrimaryExpression, FECHA_BLOCO, ABRE_BLOCO, MemberExpressionPart, FECHA_BLOCO, REP_ASTERISCO, FECHA_BLOCO, AllocationExpression, FIM_PARTE_EXPRESSAO},
{ MemberExpressionForIn, ABRE_BLOCO, ABRE_BLOCO, FunctionExpression, PrimaryExpression, FECHA_BLOCO, ABRE_BLOCO, MemberExpressionPart, FECHA_BLOCO, REP_ASTERISCO, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ AllocationExpression, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, MemberExpression, ABRE_BLOCO, ABRE_BLOCO, Arguments, ABRE_BLOCO, MemberExpressionPart, FECHA_BLOCO, REP_ASTERISCO, FECHA_BLOCO, REP_ASTERISCO, FECHA_BLOCO, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ MemberExpressionPart, ABRE_BLOCO, TOKEN_OPERADOR, Expression, TOKEN_OPERADOR, FECHA_BLOCO, ABRE_BLOCO, TOKEN_OPERADOR, Identifier, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ CallExpression, MemberExpression, Arguments, ABRE_BLOCO, CallExpressionPart, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ CallExpressionForIn, MemberExpressionForIn, Arguments, ABRE_BLOCO, CallExpressionPart, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ CallExpressionPart, Arguments, ABRE_BLOCO, TOKEN_OPERADOR, Expression, TOKEN_OPERADOR, FECHA_BLOCO, ABRE_BLOCO, TOKEN_OPERADOR, Identifier, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ Arguments, TOKEN_ABRE_PARENTESE, ABRE_BLOCO, ArgumentList, FECHA_BLOCO, OPCIONAL, TOKEN_FECHA_PARENTESE, FIM_PARTE_EXPRESSAO},
{ ArgumentList, AssignmentExpression, ABRE_BLOCO, TOKEN_OPERADOR, AssignmentExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ LeftHandSideExpression, CallExpression, MemberExpression, FIM_PARTE_EXPRESSAO},
{ LeftHandSideExpressionForIn, CallExpressionForIn, MemberExpressionForIn, FIM_PARTE_EXPRESSAO},
{ PostfixExpression, LeftHandSideExpression, ABRE_BLOCO, PostfixOperator, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ PostfixOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ UnaryExpression, ABRE_BLOCO, PostfixExpression, ABRE_BLOCO, UnaryOperator, UnaryExpression, FECHA_BLOCO, REP_MAIS, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ UnaryOperator, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_PALAVRA_CHAVE, TOKEN_PALAVRA_CHAVE, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ MultiplicativeExpression, UnaryExpression, ABRE_BLOCO, MultiplicativeOperator, UnaryExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ MultiplicativeOperator, ABRE_BLOCO, TOKEN_OPERADOR, SLASH, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ AdditiveExpression, MultiplicativeExpression, ABRE_BLOCO, AdditiveOperator, MultiplicativeExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ AdditiveOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ ShiftExpression, AdditiveExpression, ABRE_BLOCO, ShiftOperator, AdditiveExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ ShiftOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ RelationalExpression, ShiftExpression, ABRE_BLOCO, RelationalOperator, ShiftExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ RelationalOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_PALAVRA_CHAVE, TOKEN_PALAVRA_CHAVE, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ RelationalExpressionNoIn, ShiftExpression, ABRE_BLOCO, RelationalNoInOperator, ShiftExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ RelationalNoInOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_PALAVRA_CHAVE, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ EqualityExpression, RelationalExpression, ABRE_BLOCO, EqualityOperator, RelationalExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ EqualityExpressionNoIn, RelationalExpressionNoIn, ABRE_BLOCO, EqualityOperator, RelationalExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ EqualityOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ BitwiseANDExpression, EqualityExpression, ABRE_BLOCO, BitwiseANDOperator, EqualityExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ BitwiseANDExpressionNoIn, EqualityExpressionNoIn, ABRE_BLOCO, BitwiseANDOperator, EqualityExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ BitwiseANDOperator, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ BitwiseXORExpression, BitwiseANDExpression, ABRE_BLOCO, BitwiseXOROperator, BitwiseANDExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ BitwiseXORExpressionNoIn, BitwiseANDExpressionNoIn, ABRE_BLOCO, BitwiseXOROperator, BitwiseANDExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ BitwiseXOROperator, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ BitwiseORExpression, BitwiseXORExpression, ABRE_BLOCO, BitwiseOROperator, BitwiseXORExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ BitwiseORExpressionNoIn, BitwiseXORExpressionNoIn, ABRE_BLOCO, BitwiseOROperator, BitwiseXORExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ BitwiseOROperator, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ LogicalANDExpression, BitwiseORExpression, ABRE_BLOCO, LogicalANDOperator, BitwiseORExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ LogicalANDExpressionNoIn, BitwiseORExpressionNoIn, ABRE_BLOCO, LogicalANDOperator, BitwiseORExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ LogicalANDOperator, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ LogicalORExpression, LogicalANDExpression, ABRE_BLOCO, LogicalOROperator, LogicalANDExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ LogicalORExpressionNoIn, LogicalANDExpressionNoIn, ABRE_BLOCO, LogicalOROperator, LogicalANDExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ LogicalOROperator, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ ConditionalExpression, LogicalORExpression, ABRE_BLOCO, TOKEN_INTERRORACAO, AssignmentExpression, TOKEN_OPERADOR, AssignmentExpression, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ ConditionalExpressionNoIn, LogicalORExpressionNoIn, ABRE_BLOCO, TOKEN_INTERRORACAO, AssignmentExpression, TOKEN_OPERADOR, AssignmentExpressionNoIn, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ AssignmentExpression, ABRE_BLOCO, LeftHandSideExpression, AssignmentOperator, AssignmentExpression, ConditionalExpression, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ AssignmentExpressionNoIn, ABRE_BLOCO, LeftHandSideExpression, AssignmentOperator, AssignmentExpressionNoIn, ConditionalExpressionNoIn, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ AssignmentOperator, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, SLASHASSIGN, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ Expression, AssignmentExpression, ABRE_BLOCO, TOKEN_OPERADOR, AssignmentExpression, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ ExpressionNoIn, AssignmentExpressionNoIn, ABRE_BLOCO, TOKEN_OPERADOR, AssignmentExpressionNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ Statement, Block, JScriptVarStatement, VariableStatement, EmptyStatement, LabelledStatement, ExpressionStatement, IfStatement, IterationStatement, ContinueStatement, BreakStatement, ImportStatement, ReturnStatement, WithStatement, SwitchStatement, ThrowStatement, TryStatement, FIM_PARTE_EXPRESSAO},
{ Block, TOKEN_OPERADOR, ABRE_BLOCO, StatementList, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ StatementList, ABRE_BLOCO, Statement, FECHA_BLOCO, REP_MAIS, FIM_PARTE_EXPRESSAO},
{ VariableStatement, TOKEN_PALAVRA_CHAVE, VariableDeclarationList, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ VariableDeclarationList, VariableDeclaration, ABRE_BLOCO, TOKEN_OPERADOR, VariableDeclaration, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ VariableDeclarationListNoIn, VariableDeclarationNoIn, ABRE_BLOCO, TOKEN_OPERADOR, VariableDeclarationNoIn, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ VariableDeclaration, Identifier, ABRE_BLOCO, Initialiser, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ VariableDeclarationNoIn, Identifier, ABRE_BLOCO, InitialiserNoIn, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ Initialiser, TOKEN_OPERADOR, AssignmentExpression, FIM_PARTE_EXPRESSAO},
{ InitialiserNoIn, TOKEN_OPERADOR, AssignmentExpressionNoIn, FIM_PARTE_EXPRESSAO},
{ EmptyStatement, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ ExpressionStatement, Expression, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ IfStatement, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, Expression, TOKEN_FECHA_PARENTESE, Statement, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, Statement, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ IterationStatement, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, Statement, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, Expression, TOKEN_FECHA_PARENTESE, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FECHA_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, Expression, TOKEN_FECHA_PARENTESE, Statement, FECHA_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, ABRE_BLOCO, ExpressionNoIn, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, ABRE_BLOCO, Expression, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, ABRE_BLOCO, Expression, FECHA_BLOCO, OPCIONAL, TOKEN_FECHA_PARENTESE, Statement, FECHA_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, TOKEN_PALAVRA_CHAVE, VariableDeclarationList, TOKEN_OPERADOR, ABRE_BLOCO, Expression, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, ABRE_BLOCO, Expression, FECHA_BLOCO, OPCIONAL, TOKEN_FECHA_PARENTESE, Statement, FECHA_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, TOKEN_PALAVRA_CHAVE, VariableDeclarationNoIn, TOKEN_PALAVRA_CHAVE, Expression, TOKEN_FECHA_PARENTESE, Statement, FECHA_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, LeftHandSideExpressionForIn, TOKEN_PALAVRA_CHAVE, Expression, TOKEN_FECHA_PARENTESE, Statement, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ ContinueStatement, TOKEN_PALAVRA_CHAVE, ABRE_BLOCO, Identifier, FECHA_BLOCO, OPCIONAL, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ BreakStatement, TOKEN_PALAVRA_CHAVE, ABRE_BLOCO, Identifier, FECHA_BLOCO, OPCIONAL, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ ReturnStatement, TOKEN_PALAVRA_CHAVE, ABRE_BLOCO, Expression, FECHA_BLOCO, OPCIONAL, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ WithStatement, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, Expression, TOKEN_FECHA_PARENTESE, Statement, FIM_PARTE_EXPRESSAO},
{ SwitchStatement, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, Expression, TOKEN_FECHA_PARENTESE, CaseBlock, FIM_PARTE_EXPRESSAO},
{ CaseBlock, TOKEN_OPERADOR, ABRE_BLOCO, CaseClauses, FECHA_BLOCO, OPCIONAL, ABRE_BLOCO, TOKEN_OPERADOR, DefaultClause, ABRE_BLOCO, CaseClauses, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ CaseClauses, ABRE_BLOCO, CaseClause, FECHA_BLOCO, REP_MAIS, FIM_PARTE_EXPRESSAO},
{ CaseClause, ABRE_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, Expression, TOKEN_OPERADOR, FECHA_BLOCO, FECHA_BLOCO, ABRE_BLOCO, StatementList, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ DefaultClause, ABRE_BLOCO, ABRE_BLOCO, TOKEN_PALAVRA_CHAVE, TOKEN_OPERADOR, FECHA_BLOCO, FECHA_BLOCO, ABRE_BLOCO, StatementList, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ LabelledStatement, Identifier, TOKEN_OPERADOR, Statement, FIM_PARTE_EXPRESSAO},
{ ThrowStatement, TOKEN_PALAVRA_CHAVE, Expression, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ TryStatement, TOKEN_PALAVRA_CHAVE, Block, ABRE_BLOCO, ABRE_BLOCO, Finally, Catch, ABRE_BLOCO, Finally, FECHA_BLOCO, OPCIONAL, FECHA_BLOCO, FECHA_BLOCO, FIM_PARTE_EXPRESSAO},
{ Catch, TOKEN_PALAVRA_CHAVE, TOKEN_ABRE_PARENTESE, Identifier, TOKEN_FECHA_PARENTESE, Block, FIM_PARTE_EXPRESSAO},
{ Finally, TOKEN_PALAVRA_CHAVE, Block, FIM_PARTE_EXPRESSAO},
{ FunctionDeclaration, TOKEN_PALAVRA_CHAVE, Identifier, ABRE_BLOCO, TOKEN_ABRE_PARENTESE, ABRE_BLOCO, FormalParameterList, FECHA_BLOCO, OPCIONAL, TOKEN_FECHA_PARENTESE, FECHA_BLOCO, FunctionBody, FIM_PARTE_EXPRESSAO},
{ FunctionExpression, TOKEN_PALAVRA_CHAVE, ABRE_BLOCO, Identifier, FECHA_BLOCO, OPCIONAL, ABRE_BLOCO, TOKEN_ABRE_PARENTESE, ABRE_BLOCO, FormalParameterList, FECHA_BLOCO, OPCIONAL, TOKEN_FECHA_PARENTESE, FECHA_BLOCO, FunctionBody, FIM_PARTE_EXPRESSAO},
{ FormalParameterList, Identifier, ABRE_BLOCO, TOKEN_OPERADOR, Identifier, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ FunctionBody, TOKEN_OPERADOR, ABRE_BLOCO, SourceElements, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ Program, ABRE_BLOCO, SourceElements, FECHA_BLOCO, OPCIONAL, TOKEN_EOF, FIM_PARTE_EXPRESSAO},
{ SourceElements, ABRE_BLOCO, SourceElement, FECHA_BLOCO, REP_MAIS, FIM_PARTE_EXPRESSAO},
{ SourceElement, FunctionDeclaration, Statement, FIM_PARTE_EXPRESSAO},
{ ImportStatement, TOKEN_PALAVRA_CHAVE, Name, ABRE_BLOCO, TOKEN_OPERADOR, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, TOKEN_OPERADOR, FIM_PARTE_EXPRESSAO},
{ Name, IDENTIFIER_NAME, ABRE_BLOCO, TOKEN_OPERADOR, IDENTIFIER_NAME, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ JScriptVarStatement, TOKEN_PALAVRA_CHAVE, JScriptVarDeclarationList, ABRE_BLOCO, TOKEN_OPERADOR, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ JScriptVarDeclarationList, JScriptVarDeclaration, ABRE_BLOCO, TOKEN_OPERADOR, JScriptVarDeclaration, FECHA_BLOCO, REP_ASTERISCO, FIM_PARTE_EXPRESSAO},
{ JScriptVarDeclaration, Identifier, TOKEN_OPERADOR, IDENTIFIER_NAME, ABRE_BLOCO, Initialiser, FECHA_BLOCO, OPCIONAL, FIM_PARTE_EXPRESSAO},
{ insertSemiColon, java, code, FIM_PARTE_EXPRESSAO}
};


int se_token_primario(const int tokens_primarios_gramatica[TAM_XP], int token){
	int i;
	for(i=0; i<TAM_XP; i++){
		if( tokens_primarios_gramatica[i] == token ){
			return i;
		}
	}
	return -1;
}

int se_token_primario_matriz(const int grammar[TAM_X][TAM_Y], int token){
	int i;
	for(i=0; i<TAM_XP; i++){
		if( grammar[i][0] == token ){
			return i;
		}
	}
	return -1;
}

/*\/ procura se cada token de uma linha, pertence a primeira linha da gramatica,
 * e se cada token subsequente ao token anterior, pertencem a mesma sequencia definida
 * na gramatica do token da primeira linha na gramatica; 
 * 
 * ******************
 * (1) {A -> Z -> Y -> K}
 * (2) {B -> A -> T -> J}
 * (3) {C -> B -> A -> Z} << 'B' é subsequente de 'C'(3), que na sequencia 'A' é subsequente de 'B'(2); Que na sequencia 'Z' é subsequente de 'A'(1);
 *  O que torna toda a sequencia (3) correta.
 * ******************
 * 
 * */
int transversal_grammar(const int linha[], const int tam_linha){
	int i, err=0;
	const int tam_linha_varrer = 100;
	int acertos = 0, acertos_totais = 0;
	//~ int erros[100] = {0};
	for(i=0; i<tam_linha; i++){
		int indice_token_primario = se_token_primario(tokens_primarios_gramatica, linha[i]);
		if( (linha[i] != 0) && indice_token_primario != -1 ){
			printf("T: %d\n", linha[i] );
			acertos++;
			int ini = indice_token_primario;
			int g; // << coluna_gramatica;
			int i2 = i+1;
			for(g=1; g<tam_linha_varrer; g++){
				if( (grammar[ini][g] != FIM_PARTE_EXPRESSAO ) && (linha[i2] != 0) && grammar[ini][g] == linha[i2] ){
					acertos++;
					printf("[%d] - [%d] => g[%d] - l[%d]\n", g, i2, grammar[ini][g], linha[i2] );
					i2++;
				}
			}
		/*\/ se determinado token da linha não se encontra predefinido no inicio da gramatica de tokens (grammar); */
		}else if( (linha[i] != 0) && (linha[i] != FIM_PARTE_EXPRESSAO) && (indice_token_primario == -1)){
			printf("Erro: [%d] -> (%d)\n", i, linha[i] );
			//~ erros[err] = i;
			err++;
		} 
		printf(">>%d\n", acertos );
		acertos_totais += acertos;
		acertos = 0;
	}
	printf("total -> %d\n", acertos_totais );
	return acertos_totais;
}

int transversal_grammar_matriz(const int linha[], const int tam_linha){
	int i, err=0;
	const int tam_linha_varrer = 100;
	int acertos = 0, acertos_totais = 0;
	//~ int erros[100] = {0};
	int visi[100] = {0};
	for(i=0; i<tam_linha; i++){
		int indice_token_primario = se_token_primario_matriz(grammar, linha[i]);
		if( (linha[i] != 0) && indice_token_primario != -1 ){
			printf("T: %d\n", linha[i] );
			visi[indice_token_primario] = 1;
			acertos++;
			int ini = indice_token_primario;
			int g; // << coluna_gramatica;
			int i2 = i+1;
			for(g=1; g<tam_linha_varrer; g++){
				if( (grammar[ini][g] != FIM_PARTE_EXPRESSAO ) && (linha[i2] != 0) && grammar[ini][g] == linha[i2] ){
					acertos++;
					printf("[%d] - [%d] => g[%d] - l[%d]\n", g, i2, grammar[ini][g], linha[i2] );
					i2++;
				}else if( (grammar[ini][g] != FIM_PARTE_EXPRESSAO ) && (linha[i2] != 0) && se_token_primario_matriz(grammar, grammar[ini][g]) != -1 && visi[grammar[ini][g]] == 0 ){
					visi[grammar[ini][g]] = 1;
					printf("<< retoma [%d][%d];\n", ini, g);
					ini = se_token_primario_matriz(grammar, grammar[ini][g]);
					g = 1;
					//~ linha[i2] = 0; // << retira da expressão;
					
				}
			}
		/*\/ se determinado token da linha não se encontra predefinido no inicio da gramatica de tokens (grammar); */
		}else if( (linha[i] != 0) && (linha[i] != FIM_PARTE_EXPRESSAO) && (indice_token_primario == -1)){
			printf("Erro: [%d] -> (%d)\n", i, linha[i] );
			//~ erros[err] = i;
			err++;
		} 
		printf(">>%d\n", acertos );
		acertos_totais += acertos;
		acertos = 0;
	}
	printf("total -> %d\n", acertos_totais );
	return acertos_totais;
}

void read_input(char* arquivo){
    // Create a file pointer and open the file "GFG.txt" in
    // read mode.
    FILE* file = fopen(arquivo, "r");
    
    struct NodeDLL *nodeDLL = createNodeDLL("");
	struct Graph* graph = createGraph();

	int con = 0;
    // Buffer to store each line of the file.
    char line[256];

    // Check if the file was opened successfully.
    if (file != NULL) {
        // Read each line from the file and store it in the
        // 'line' buffer.
        while (fgets(line, sizeof(line), file)) {
			con++;
            // Print each line to the standard output.
            //~ printf("[%d]: %s", con, line);
            tokentize(line, con, nodeDLL);
        }
        create_graph(nodeDLL, graph);
		//~ printList(nodeDLL);
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

int get_literal_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = identify_types(token);
	if(tokenType != -1){
		switch(lang){
			case RUBY: tokenType = get(gsymbols->symbolNum, "LITERAL"); break;
			case PYTHON: tokenType = get(gsymbols->symbolNum, "literal_pattern"); break;
			case JS: tokenType = get(gsymbols->symbolNum, "Literal"); break;
		}
	}
	return tokenType;
}


int get_identifier_tokenType_lang(struct grammar_symbols* gsymbols, char *token, const int lang){
	int tokenType = identify_identifier(token);
	if(tokenType != -1){
		switch(lang){
			case RUBY: tokenType = get(gsymbols->symbolNum, "IDENTIFIER"); break;
			case PYTHON: tokenType = get(gsymbols->symbolNum, "NAME"); break;
			case JS: tokenType = get(gsymbols->symbolNum, "Identifier"); break;
		}
	}
	return tokenType;
}

char *insert_aspas(char *str, bool aspa_simples){
	char tipo_aspa = (aspa_simples) ? ('\'') : ('\"');
	int tam = strlen(str);
	char *copy = (char*)malloc((tam + 3)* sizeof(char));
	copy[0] = tipo_aspa;
	memcpy(copy+1, str, strlen(str));
	copy[tam+1] = tipo_aspa;
	copy[tam+2] = '\0';
	return copy;
}

int get_nonTerminals_tokenType_lang(struct grammar_symbols* gsymbols, char *token){
	char *token_aspas_s = insert_aspas(token, true);
	char *token_aspas_d = insert_aspas(token, false);

	int sym = get(gsymbols->symbolNum, token_aspas_s);
	if(sym != -1){
		return sym;
	}
	sym = get(gsymbols->symbolNum, token_aspas_d);
	if(sym != -1){
		return sym;
	}

	free(token_aspas_s);
	free(token_aspas_d);
	return -1;
}

void read_code_tokenize(char* arquivo, struct grammar_symbols* gsymbols, vector *tokenTypes, const int lang){
	// Create a file pointer and open the file "GFG.txt" in
	// read mode.
	FILE* file = fopen(arquivo, "r");

	// Buffer to store each line of the file.
	char line[300];

	// Check if the file was opened successfully.
	if (file != NULL) {
		// Read each line from the file and store it in the
		// 'line' buffer.
		while (fgets(line, sizeof(line), file)) {
			// Print each line to the standard output.

			/*\/ inserir simbolos registrados(token types) em um vetor para análise; */
			int tam = 0;
			char **tokens = process_tokens(line, delimiters, &tam, true);
			for(int i=0; i<tam; i++){
				trim(tokens[i]);

				/*\/ identificar literal tokentype; */
				int tokenType_literal = get_literal_tokenType_lang(gsymbols, tokens[i], lang);
				if(tokenType_literal != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], tokenType_literal);
					vector_add(tokenTypes, (void *)tokenType_literal);
				}

				/*\/ identificar identifier tokentype; */
				int tokenType_identifier = get_identifier_tokenType_lang(gsymbols, tokens[i], lang);
				if(tokenType_identifier != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], tokenType_identifier);
					vector_add(tokenTypes, (void *)tokenType_identifier);
				}

				/*\/ identificar não-terminais tokentype; */
				int sym = get_nonTerminals_tokenType_lang(gsymbols, tokens[i]);
				if(sym != -1){
					// printf("tk: [%s] = [%d]\n", tokens[i], sym);
					vector_add(tokenTypes, (void *)sym);
				}
			}
			free_strings(tokens, tam);
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

int* vector_to_array(vector *v, int *reftam){
	*reftam = v->total;
	int *dados = (int*)malloc((v->total) * sizeof(int));
	for (int i = 0; i < v->total; i++) {
		dados[i] = (int)v->items[i];
	}
	return dados;
}

void apply_earley_in_code(char *file_code, const int lang){
	struct grammar_symbols* gsymbols = read_grammar(lang);
	vector tokenTypes;
	vector_init(&tokenTypes);
	read_code_tokenize(file_code, gsymbols, &tokenTypes, RUBY);

	/*\/ to array; */
	int sizeTokenTypes = 0;
	int *ptokenTypes = vector_to_array(&tokenTypes, &sizeTokenTypes);

	int sizeNonTerm = 0;
	int *pNonTerminals = getValues(gsymbols->nonTerminals, &sizeNonTerm);

	struct Graph *ast = createGraph();
	EARLEY_PARSE(gsymbols->grammar, ptokenTypes, sizeTokenTypes, pNonTerminals[0], pNonTerminals, sizeNonTerm, pNonTerminals[0], ast);

	printGraph(ast);

	free(ptokenTypes);
	free(pNonTerminals);
	vector_free(&tokenTypes);
	deleteAllGraph(ast);
	free(ast);
}

void test_get_strings(char str[]){
	int len = 0;
	char **strings = get_strings_in_string(str, &len);
	printf("len [%d]\n", len);
	if(len > 0){
		for(int i=0; i<len; i++){
			if(strings[i] != NULL) printf("[%s]\n", strings[i]);
		}
	}
	free_strings(strings, len);
}

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
// DRIVER FUNCTION
int main()
{
	//~ // maximum legth of string is 100 here
	//~ char str[100] = "function int a = b + 18; if teste * 0x98";
	// char str[100] = "else if( (linha[i] != 0) && (linha[i] != FIM_PARTE_EXPRESSAO) && (indice_token_primario == -1)){";
	//~ parse(str);
	//~ parse2(str);


    // read_input("code-input.txt");
	printf("teste make ok 2;)\n");
	/*
	// int len_tokens_input = 5;
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

	// int tam = 0;
	// char **parts = process_tokens(str, delimiters, &tam, false);
	// for(int i=0; i<tam; i++){
	// 	if(parts[i] != NULL) printf("-> [%s]\n", parts[i]);
	// }
	// free_strings(parts, tam);

	// struct grammar_symbols* gsymbols = read_grammar(RUBY);
	// vector tokenTypes;
	// vector_init(&tokenTypes);
	// read_code_tokenize("code-input.txt", gsymbols, &tokenTypes, RUBY);
	// printf("[%d]\n", get(gsymbols->symbolNum, "=="));
	// printf("[%d]\n", get(gsymbols->symbolNum, "!="));
	// printf("[%d]\n", get(gsymbols->symbolNum, "+="));
	// printf("[%d]\n", get(gsymbols->symbolNum, "')]'"));

	/*\/ to array; */
	// int sizeTokenTypes = 0;
	// int *ptokenTypes = vector_to_array(&tokenTypes, &sizeTokenTypes);

	// int sizeNonTerm = 0;
	// int *pNonTerminals = getValues(gsymbols->nonTerminals, &sizeNonTerm);


	// char str[] = "|	OP_ASGN		: '+=' | '-=' | '*=' | '/=' | '%=' | '**='   ''' \"\"\"  \"teste g  gds gd sd\" '\"' any_char* '\"' ')'] ";
	// char str[] = "		| return ['(' [CALL_ARGS] ')']";
	// char str[] = "ARGLIST		: IDENTIFIER(','IDENTIFIER)*[',' '*'[IDENTIFIER]][',' '&'IDENTIFIER]";
	// test_get_strings(str);

	// printMap(gsymbols->symbolNum);
	// printMap(gsymbols->nonTerminals);
	// printGraph(gsymbols->grammar);


	apply_earley_in_code("code-input.txt", RUBY);

/*
	int tam_operators = 50;
	char *buff_string_delimiters[TAMANHO(delimiters) + tam_operators];
	//~ for(int i=0; i<tam_operators; i++) buff_string_delimiters[i] = NULL;
	int ocuped = uni_delimiters(delimiters, TAMANHO(delimiters), operators, tam_operators, buff_string_delimiters);
	for(int i=0; i<ocuped; i++){
		printf(">> %s\n", buff_string_delimiters[i]);
	}
	for(int i=0; i<TAMANHO(delimiters); i++){
		free(buff_string_delimiters[i]);
	}
*/
/*
struct NodeDLL *nodeDLL = createNodeDLL("teste");
insertEnd(nodeDLL, "teste2rs");
forwardTraversal(nodeDLL);
*/


	/* -- split with delimiters; */
	/*int tam_delimiters = 4;
	const int tam_sep = 1000;
	char sep[tam_sep][tam_sep];
	int num = __strsep6(&in_Ptr, delimiters, tam_delimiters, tam_sep, sep);
	
	for(int i=0; i<num; i++){
		printf("-> %s\n", sep[i]);
	}*/
	/* -- split with delimiters; */


	//~ char *str[] = {"ok", "teste"};

	//~ const int tam_linha = 11;
	//~ int linha[11] = {4, 5, 6, 7, 8, 9, 6, 5, 5, 4};
	//~ int linha[11] = {LeftHandSideExpression, CallExpression, MemberExpression, FIM_PARTE_EXPRESSAO};
	//~ int linha[11] = {ArrayLiteral, TOKEN_OPERADOR, ABRE_BLOCO, ABRE_BLOCO, FECHA_BLOCO};
	
	//~ transversal_grammar(linha, tam_linha);
	//~ transversal_grammar_matriz(linha, tam_linha);
	
	return (0);
}
