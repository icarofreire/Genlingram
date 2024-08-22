#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"
#include "Lib-Adjacency-List.h"
//~ #include "tokens_grammar.h"

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

void trimString(char *str) {
	while (isspace((unsigned char)str[0])){
		memmove(str, str + 1, strlen(str));   
	}
	while (isspace((unsigned char)str[strlen(str) - 1])){
		str[strlen(str) - 1] = '\0';
	}
}

// C substring function definition
void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}

int
__strsep5 (char **stringp, const char *delim[], int tamDel, int tam_sep, char sep[tam_sep][tam_sep])
{
	char *begin;
	begin = *stringp;

	//~ int tamxx = (strlen(begin)/tamDel)+(tamDel*2);
	//~ char sep[tamxx][tamxx];
	int consep = 0;

	int con = 0;
	int idx = strcspn(begin, *delim);
	char sub[strlen(*delim)];
	substring(begin, sub, 1, idx);
	begin+=idx;
	//~ printf("[%s -> %s]\n", (*delim), sub);
	printf("[%s -> %s] : %d - %d\n", (*delim), sub, idx, strlen(begin));
	trimString(sub);
	if(strcmp(sub, " ") != 0) strcpy(sep[consep++], sub);
	if(strcmp(*delim, " ") != 0) strcpy(sep[consep++], *delim);
	while((strlen(begin) > 0) && idx < strlen(begin)/*&& con < tamDel-1 *//*(strlen(begin) > 0)*/ ){
		idx = strcspn(begin, *++delim);

		char subl[strlen(*delim)];
		substring(begin, subl, 2, (idx-1));
		begin+=idx;
		trimString(subl);
		printf("[%s -> %s] : %d - %d: %s\n", (*delim), subl, idx, strlen(begin), begin);
		//~ if(strcmp(subl, " ") != 0) strcpy(sep[consep++], subl);
		//~ if(strcmp(sub, " ") != 0) strcpy(sep[consep++], *delim);
		con++;
	}
	
	//~ for(int i=0; i<consep; i++){
		//~ printf("-> %s\n", sep[i]);
	//~ }
	return consep;
}

void str_replace(char *target, const char *needle, const char *replacement)
{
    char buffer[1024] = { 0 };
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);

        // walked past last occurrence of needle; copy remaining part
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }

        // copy part before needle
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;

        // copy replacement string
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;

        // adjust pointers, move on
        tmp = p + needle_len;
    }

    // write altered string back to target
    strcpy(target, buffer);
}

void replace_all(char *target, const char *needle, const char *replacement){
	char* ppos = strstr(target, needle);
	if(ppos != NULL){
		target = realloc(target, (strlen(target)+strlen(replacement)) * sizeof(char));
		str_replace(target, needle, replacement);
	}
}

void replace_all_deli(char *target, char **delimiters, int tam_delimiters){
	for(int i = 0; i<tam_delimiters; i++){
		char* p_in_target = strstr(target, delimiters[i]);
		if(strcmp(delimiters[i], " ") != 0 && p_in_target != NULL){
			char *subs = malloc(sizeof(char) * (strlen(delimiters[i]) + 2));
			strcpy(subs, " ");
			strcat(subs, delimiters[i]);
			strcat(subs, " ");
			printf("rep: '%s' por '%s' in '%s'\n", delimiters[i], subs, target);
			replace_all(target, delimiters[i], subs);
			free(subs);
			//~ printf("rep: '%s' por '%s' \n", delimiters[0], target);
		}
	}
}

int uni_delimiters(char delimiters[], int tam_delimiters, char *operators[], int tam_operators, char *buff_string_delimiters[]){
	int i = 0;
	for(; i<tam_delimiters; i++){
		char *ss = malloc(2);
		ss[0] = delimiters[i];
		ss[1] = '\0';
		buff_string_delimiters[i] = ss;
	}
	//~ printf("fim: %d\n", i);
	int j = 0;
	for(; j<tam_operators; j++){
		buff_string_delimiters[i+j] = operators[j];
		//~ printf("->: %s, %d\n", operators[j], (i+j));
	}
	//~ printf("fim2: %d\n", (i+j));
	return (i+j);
}

void
__strsep6 (char *begin, char *delim[], int tamDel)
{
	//~ printf("len: %d\n", strlen(begin));
	char *mbegin = malloc(sizeof(char) * strlen(begin));
	strcpy(mbegin, begin);

	replace_all_deli(mbegin, delim, tamDel);
	printf("begin : %s\n", mbegin );
	//~ printf("len: %d\n", strlen(buffer));
	free(mbegin);
}

void apply_uni_tokentize(char *stringp){
	int tam_operators = 50;
	char *buff_string_delimiters[TAMANHO(delimiters) + tam_operators];
	//~ for(int i=0; i<tam_operators; i++) buff_string_delimiters[i] = NULL;
	int ocuped = uni_delimiters(delimiters, TAMANHO(delimiters), operators, tam_operators, buff_string_delimiters);
	//~ for(int i=0; i<ocuped; i++){
		//~ printf(">> %s\n", buff_string_delimiters[i]);
	//~ }
	
	__strsep6(stringp, buff_string_delimiters, ocuped);
	
	for(int i=0; i<TAMANHO(delimiters); i++){
		free(buff_string_delimiters[i]);
	}
}

struct tokenStruct {
	char* token;
	char* delimiter;
};

/** alteração de uma implementação de strtok.c em Libc;
 * https://opensource.apple.com/source/Libc/Libc-167/string.subproj/strtok.c.auto.html
 *  */
struct tokenStruct
__strtok_struct(
	register char *s,
	register const char *delim)
{
	register char *spanp;
	register int c, sc;
	char *tok;
	static char *last;
	struct tokenStruct nulret = {NULL, NULL};

	if (s == NULL && (s = last) == NULL)
		return (nulret);//(NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc)
			goto cont;
	}

	if (c == 0) {		/* no non-delimiter characters */
		last = NULL;
		return (nulret);//(NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0; /* Pointer Equivalent: *(array-1); */
				last = s;

				char temp_str_delimiter[] = {sc, '\0'};
				struct tokenStruct tokenStru = {tok, temp_str_delimiter};
				printf("tok: '%s', '%c', '%s'\n", tok, sc, spanp);
				spanp = (char *)delim;
				sc = 0;
				//~ return (tok);
				return (tokenStru);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}

/**
 *_strcmp - A special compare function that compares is sub
 * is aubset of fstring. for example if fstring is "hello"
 * "h", "he", ... but not "hello" are all subsets and
 * in such a case a 1 will be returned
 *@fstring: fstring
 *@sub: subset
 *Return: 1 on success and -1 on faliur
 */
int _strcmp(char *fstring, const char *sub)
{
	if (!fstring || !sub)
		return (-1);
	if (strlen(fstring) < strlen(sub))
		return (-1);
	while (*sub && *fstring)
	{
		if (*sub != *fstring)
			return (-1);
		sub++, fstring++;
	}
	return (1);
}
/**
 * _strtok - tokenizes a string according to a certain delimiter
 * it doesnt creat a new string to hold the tokens but rather creats a
 * a static variable that will directly copy str and puts the null
 * terminator everytime it finds the delimeter, the default str will be
 * manipulated so beware
 * for example if you have a string str = "helo; now; bo"
 * when _strtok is called for the first time (_strtok(str, ";")) it will put
 * \0 (a null terminator in the first location of the delimeter so the str
 * variable will be "helo\0 nowo; bo", ";" and it will be returned and the
 * static variable save would hold " nowo; bo" and when _strtok is called
 * for the second time _strtok(NULL, ";"); the same cyle continue
 * but this time instead of str save will be manipulated. This
 *cycle continues untile save == NULL
 * @str: the string to be tokenized
 * @delimeter: the delimiter to separate tokens
 * Return: a character pointer to the current delimited token
 */
char *_strtok_nat(char *str, const char *delimeter)
{
	static char *save;
	char *_new = NULL;
	int i = 0;

	if (!str || !*str)
	{
		if (!save || !*save)
			return (NULL);

		while (_strcmp(save + i, delimeter) != 1 && *(save + i) != '\0')
			i++;
		if (*(save + i) == '\0')
		{
			save = NULL;
			return (save);
		}

		_new = save;
		*(save + i) = '\0';
		save = save + i + strlen(delimeter);

		return (_new);

	}
	while (_strcmp(str + i, delimeter) != 1 && *(str + i) != '\0')
		i++;
	if (*(str + i) == '\0')
		return (str);

	save = str + i + strlen(delimeter);
	*(str + i) = '\0';

	return (str);
}

void run_strtok(char* str, char* delimiters){
    struct tokenStruct tokenStru = __strtok_struct(str, delimiters);
    while(tokenStru.token){
		printf(">> %s -> '%s'\n", tokenStru.token, tokenStru.delimiter);
		tokenStru = __strtok_struct(NULL, delimiters);
	}
}

void run_strtok_nested(char* str){
	char* ini_delim = "=+-!&*/().,?~:;{}[]<|^%>";
	
	char temp_str[strlen(str)];
	strcpy(temp_str, str);
    struct tokenStruct tokenStru = __strtok_struct(str, ini_delim);
    while(tokenStru.token){
		//~ printf(">> %s -> '%s'\n", tokenStru.token, tokenStru.delimiter);


		//~ if(strcspn(tokenStru.token, delimiters) < strlen(tokenStru.token)){
			//~ char copy[strlen(tokenStru.token)];
			//~ strcpy(copy, tokenStru.token);
			//~ run_strtok(copy, "=+-!&*/().,?~:;{}[]<|^%>");
			//~ printf("iner: %s\n", temp_str);

			//~ strcpy(str, temp_str);
			//~ tokenStru = __strtok_struct(str, ini_delim);
		//~ }
		//~ strcpy(temp_str, str);
		tokenStru = __strtok_struct(NULL, ini_delim);
	}
}

int next_index_delimiter(char *str, int lim){
	lim = ((lim > 0) ? (lim) : (strlen(str)));
	for(int i=0; i<lim; i++){
		if(isDelimiter(str[i])){
			return i;
		}
	}
	return -1;
}

struct tokensStruct {
	char **tokens;
	int size;
};

void realoc_add(struct tokensStruct *tk, char *word){
	if(tk->size == 0){
		tk->tokens = (char**)malloc(1 * sizeof(char*));
	}
	tk->size++;
	tk->tokens = (char**) realloc(tk->tokens, tk->size * sizeof(int));
	tk->tokens[tk->size-1] = (char*)malloc((strlen(word)+1) * sizeof(char));
	strcpy(tk->tokens[tk->size-1], word);
}

struct tokensStruct my_tokentize(char *str){
	struct tokensStruct tk;
	tk.size = 0;

    for(; (*str) != '\0'; str++){
		int index_deli = next_index_delimiter(str, 0);
		if(index_deli != -1){
			char delimiter = str[index_deli];
			char word[index_deli+1];
			substring(str, word, 1, index_deli);
			trimString(word);
			//~ printf(">> '%s' -> '%c'\n", word, delimiter);
			if(strcmp(word, "") != 0){
				//~ printf(">> '%s'\n", word);
				/*\/ realocar memória para o array de strings, e para o array que conterá a string; */
				realoc_add(&tk, word);
			}
			if(delimiter != ' '){
				//~ printf(">> '%c'\n", delimiter);
				/*\/ realocar memória para o array de strings, e para o array que conterá a string; */
				char temp_str_delimiter[] = {delimiter, '\0'};
				realoc_add(&tk, temp_str_delimiter);
			}
			str+=index_deli;
		}
		else if(index_deli == -1){
			int index_prox_fim = next_index_delimiter(str, index_deli);
			if(index_prox_fim == -1){
				char word_fim[index_prox_fim+1];
				substring(str, word_fim, 1, strlen(str));
				realoc_add(&tk, word_fim);
				str+=strlen(str)-1;
				//~ printf("FIM: %s\n", word_fim);
			}
		}
	}
	return tk;
}

// DRIVER FUNCTION
int main()
{
	//~ // maximum legth of string is 100 here
	//~ char str[100] = "function int a = b + 18; if teste * 0x98";
	//~ char str[100] = "else if( (linha[i] != 0) && (linha[i] != FIM_PARTE_EXPRESSAO) && (indice_token_primario == -1)){";
	//~ parse(str);
	//~ parse2(str);
	
	//~ char *t = "function int a = b + 18; if teste * 0x98";
	
	char s_in[] = "function int a=b + 18; if teste * 0x98";
	//~ char s_in[50] = "int a=b+18;";
	//~ char s_in[200] = "else if( (linha[i+1] != 0) && (linha[i] != FIM_PARTE_EXPRESSAO) && (indice_token_primario == -1)){";
    //~ char del[20] = "=+;";
    //~ char *delimiters[] = {" ", "=", "+", ";"};
    //~ char* in_Ptr = s_in;  
    //~ char* o_Ptr;  
	//~ apply_uni_tokentize(s_in);
	//~ __strsep6(s_in, delimiters, 4);
    //~ while ((o_Ptr = __strsep3(&in_Ptr, del)) != NULL) {  
        //~ printf("%s\n", o_Ptr);  
    //~ }  
    
    //~ run_strtok_nested(s_in);
    //~ run_strtok(s_in, delimiters);
    //~ run_strtok(s_in, "=+-!&*/().,?~:;{}[]<|^%>");
    
    //~ char *tok = _strtok_nat(s_in, " ");
    //~ while(tok){
		//~ printf(">> %s -> 'x'\n", tok);
		//~ tok = _strtok_nat(NULL, " ");
	//~ }
    

    //~ char *str = s_in;
	
	//~ struct tokensStruct tk = my_tokentize(str);
	//~ for(int i=0; i<tk.size; i++){
		//~ if(tk.tokens[i])printf(">> '%s'\n", tk.tokens[i]);
	//~ }
	
	//~ /*\/ remover; */
	//~ for(int i=0; i<tk.size; i++){
		//~ free(tk.tokens[i]);
	//~ }free(tk.tokens);
    
    
    // Create an undirected adjList with 3 vertices
    struct AdjacencyList* undirectedAdjacencyList = createAdjacencyList(3);

    // Add edges to the undirected adjList
    //~ addEdge(undirectedAdjacencyList, 0, 1);
    //~ addEdge(undirectedAdjacencyList, 0, 2);
    //~ addEdge(undirectedAdjacencyList, 1, 2);

    //~ printf("Adjacecncy List for Undirected AdjacencyList:\n");
    //~ printAdjacencyList(undirectedAdjacencyList);

    // Create a directed adjList with 3 vertices
    struct AdjacencyList* directedAdjacencyList = createAdjacencyList(3);

    // Add edges to the directed adjList
    addEdge(directedAdjacencyList, 1, 0);
    addEdge(directedAdjacencyList, 1, 2);
    addEdge(directedAdjacencyList, 2, 0);

    printf("\nAdjacecncy List for Directed AdjacencyList:\n");
    printAdjacencyList(directedAdjacencyList);
    
    BFS_TraversalStarting(undirectedAdjacencyList, 2);
    
    
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
