#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"
//~ #include "tokens_grammar.h"

#define TAM_X 105
#define TAM_Y 100

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


int se_token_primario(int tokens_primarios_gramatica[TAM_XP], int token){
	int i;
	for(i=0; i<TAM_XP; i++){
		if( tokens_primarios_gramatica[i] == token ){
			return i;
		}
	}
	return -1;
}


// DRIVER FUNCTION
int main()
{
	// maximum legth of string is 100 here
	//~ char str[100] = "int a = b + 1c; if 0x98";
	//~ parse(str);

	//~ char *str[] = {"ok", "teste"};

	const int tam_linha = 11;
	//~ int linha[11] = {4, 5, 6, 7, 8, 9, 6, 5, 5, 4};
	int linha[11] = {Finally, TOKEN_PALAVRA_CHAVE, Block, FIM_PARTE_EXPRESSAO};
	
	//~ printf("%d\n", Name );
	//~ printf("%d\n", se_token_primario(tokens_primarios_gramatica, Name) );
	
	int i=0;
	int acertos = 0;
	for(i=0; i<tam_linha; i++){
		int indice_token_primario = se_token_primario(tokens_primarios_gramatica, linha[i]);
		if( (linha[i] != 0) && indice_token_primario != -1 ){
			acertos++;
			int ini = indice_token_primario;
			int g; // << coluna_gramatica;
			int i2 = i+1;
			for(g=1; g<100; g++){
				if( (grammar[ini][g] != FIM_PARTE_EXPRESSAO ) && (linha[i2] != 0) && grammar[ini][g] == linha[i2] ){
					acertos++;
					printf("l[%d]\n", g );
					printf("i2[%d]\n", i2 );
					i2++;
					//~ printf("l[%d]\n", grammar[ini][g] );
				}
			}
			
			printf("%d\n", ini );
			
		} 
		printf(">>%d\n", acertos );
		acertos = 0;
	}
	
	
	
	


	//~ parse(str); // calling the parse function

	return (0);
}
