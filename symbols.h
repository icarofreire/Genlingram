/* operadores e paravras chaves JavaScript; */

/* tamanho dos elementos de um array */
#define TAMANHO(x) (sizeof(x) / sizeof((x)[0]))

/*\/ TOKEN_OPERADOR*/
char *operators[] = {
"=", /* EQ */
"+", /* ADD */
"-", /* SUB */
"!", /* NOT */
"&", /* AND */
"*", /* MUL */
"/", /* DIV */
"(", /* LPAREN */
")", /* RPAREN */
".", /* DOT */
",", /* COMMA */
"?", /* QUESTION */
"~", /* TILDE */
":", /* COLON */
";", /* SEMICOLON */
"{", /* LBRACE */
"}", /* RBRACE */
"[", /* LBRACK */
"]", /* RBRACK */
"<", /* LESSER */
"|", /* OR */
"^", /* XOR */
"%", /* MOD */
">", /* GREATER */
"==", /* EQEQ */
"+=", /* ADDEQ */
"++", /* INCR */
"-=", /* SUBEQ */
"--", /* DECR */
"!=", /* NOTEQ */
"&=", /* ANDEQ */
"&&", /* LAND */
"|=", /* OREQ */
"||", /* LOR */
"^=", /* XOREQ */
"^^", /* LXOR */
"%=", /* MODEQ */
"/=", /* DIVEQ */
"*=", /* MULEQ */
"<=", /* LESSEREQ */
"<<", /* LSHF */
">=", /* GREATEREQ */
">>", /* RSHF */
"=>", /* FARROW */
"<<=", /* LSHFEQ */
"===", /* EQEQEQ */
"!==", /* NOTEQEQ */
">>=", /* RSHFEQ */
">>>", /* URSHF */
">>>=" /* URSHFEQ */
};

char delimiters[] = {
' ', /* espaço em branco; */
'=', /* EQ */
'+', /* ADD */
'-', /* SUB */
'!', /* NOT */
'&', /* AND */
'*', /* MUL */
'/', /* DIV */
'(', /* LPAREN */
')', /* RPAREN */
'.', /* DOT */
',', /* COMMA */
'?', /* QUESTION */
'~', /* TILDE */
':', /* COLON */
';', /* SEMICOLON */
'{', /* LBRACE */
'}', /* RBRACE */
'[', /* LBRACK */
']', /* RBRACK */
'<', /* LESSER */
'|', /* OR */
'^', /* XOR */
'%', /* MOD */
'>' /* GREATER */
};

/*\/ TOKEN_PALAVRA_CHAVE*/
char *reserved_words[] = {
"do", /* DO */
"in", /* IN */
"of", /* OF */
"if", /* IF */
"for", /* FOR */
"let", /* LET */
"new", /* NEW */
"try", /* TRY */
"var", /* VAR */
"void", /* VOID */
"with", /* WITH */
"this", /* THIS */
"case", /* CASE */
"else", /* ELSE */
"break", /* BREAK */
"catch", /* CATCH */
"class", /* CLASS */
"const", /* CONST */
"super", /* SUPER */
"throw", /* THROW */
"while", /* WHILE */
"yield", /* YIELD */
"delete", /* DELETE */
"export", /* EXPORT */
"import", /* IMPORT */
"return", /* RETURN */
"switch", /* SWITCH */
"typeof", /* TYPEOF */
"default", /* DEFAULT */
"extends", /* EXTENDS */
"finally", /* FINALLY */
"function", /* FUNCTION */
"continue", /* CONTINUE */
"debugger", /* DEBUGGER */
"instanceof" /* INSTANCEOF */
};

char *types[] = {
};

enum primary_tokens_grammar {
/*0 */ PrimaryExpression,
/*1 */ Literal,
/*2 */ Identifier,
/*3 */ ArrayLiteral,
/*4 */ ElementList,
/*5 */ Elision,
/*6 */ ObjectLiteral,
/*7 */ PropertyNameAndValueList,
/*8 */ PropertyNameAndValue,
/*9 */ PropertyName,
/*10 */ MemberExpression,
/*11 */ MemberExpressionForIn,
/*12 */ AllocationExpression,
/*13 */ MemberExpressionPart,
/*14 */ CallExpression,
/*15 */ CallExpressionForIn,
/*16 */ CallExpressionPart,
/*17 */ Arguments,
/*18 */ ArgumentList,
/*19 */ LeftHandSideExpression,
/*20 */ LeftHandSideExpressionForIn,
/*21 */ PostfixExpression,
/*22 */ PostfixOperator,
/*23 */ UnaryExpression,
/*24 */ UnaryOperator,
/*25 */ MultiplicativeExpression,
/*26 */ MultiplicativeOperator,
/*27 */ AdditiveExpression,
/*28 */ AdditiveOperator,
/*29 */ ShiftExpression,
/*30 */ ShiftOperator,
/*31 */ RelationalExpression,
/*32 */ RelationalOperator,
/*33 */ RelationalExpressionNoIn,
/*34 */ RelationalNoInOperator,
/*35 */ EqualityExpression,
/*36 */ EqualityExpressionNoIn,
/*37 */ EqualityOperator,
/*38 */ BitwiseANDExpression,
/*39 */ BitwiseANDExpressionNoIn,
/*40 */ BitwiseANDOperator,
/*41 */ BitwiseXORExpression,
/*42 */ BitwiseXORExpressionNoIn,
/*43 */ BitwiseXOROperator,
/*44 */ BitwiseORExpression,
/*45 */ BitwiseORExpressionNoIn,
/*46 */ BitwiseOROperator,
/*47 */ LogicalANDExpression,
/*48 */ LogicalANDExpressionNoIn,
/*49 */ LogicalANDOperator,
/*50 */ LogicalORExpression,
/*51 */ LogicalORExpressionNoIn,
/*52 */ LogicalOROperator,
/*53 */ ConditionalExpression,
/*54 */ ConditionalExpressionNoIn,
/*55 */ AssignmentExpression,
/*56 */ AssignmentExpressionNoIn,
/*57 */ AssignmentOperator,
/*58 */ Expression,
/*59 */ ExpressionNoIn,
/*60 */ Statement,
/*61 */ Block,
/*62 */ StatementList,
/*63 */ VariableStatement,
/*64 */ VariableDeclarationList,
/*65 */ VariableDeclarationListNoIn,
/*66 */ VariableDeclaration,
/*67 */ VariableDeclarationNoIn,
/*68 */ Initialiser,
/*69 */ InitialiserNoIn,
/*70 */ EmptyStatement,
/*71 */ ExpressionStatement,
/*72 */ IfStatement,
/*73 */ IterationStatement,
/*74 */ ContinueStatement,
/*75 */ BreakStatement,
/*76 */ ReturnStatement,
/*77 */ WithStatement,
/*78 */ SwitchStatement,
/*79 */ CaseBlock,
/*80 */ CaseClauses,
/*81 */ CaseClause,
/*82 */ DefaultClause,
/*83 */ LabelledStatement,
/*84 */ ThrowStatement,
/*85 */ TryStatement,
/*86 */ Catch,
/*87 */ Finally,
/*88 */ FunctionDeclaration,
/*89 */ FunctionExpression,
/*90 */ FormalParameterList,
/*91 */ FunctionBody,
/*92 */ Program,
/*93 */ SourceElements,
/*94 */ SourceElement,
/*95 */ ImportStatement,
/*96 */ Name,
/*97 */ JScriptVarStatement,
/*98 */ JScriptVarDeclarationList,
/*99 */ JScriptVarDeclaration,
/*100 */ insertSemiColon,
/*101 */ TOKEN_PALAVRA_CHAVE,
/*102 */ TOKEN_OPERADOR,
/*103 */ ABRE_BLOCO,
/*104 */ FECHA_BLOCO,
/*105 */ TOKEN_ABRE_PARENTESE,
/*106 */ TOKEN_FECHA_PARENTESE,
/*107 */ DECIMAL_LITERAL,
/*108 */ HEX_INTEGER_LITERAL,
/*109 */ STRING_LITERAL,
/*110 */ BOOLEAN_LITERAL,
/*111 */ NULL_LITERAL,
/*112 */ REGULAR_EXPRESSION_LITERAL,
/*113 */ IDENTIFIER_NAME,
/*114 */ OPCIONAL,
/*115 */ REP_ASTERISCO,
/*116 */ REP_MAIS,
/*117 */ TOKEN_EOF,
/*118 */ code,
/*119 */ java,
/*120 */ TOKEN_INTERROGACAO,
/*121 */ TOKEN_INTERRORACAO,
/*122 */ SLASH,
/*123 */ SLASHASSIGN,
/*124 */ FIM_PARTE_EXPRESSAO
};

enum token_delimiters {
EQ, /* '=' */
ADD, /* '+' */
SUB, /* '-' */
NOT, /* '!' */
AND, /* '&' */
MUL, /* '*' */
DIV, /* '/' */
LPAREN, /* '(' */
RPAREN, /* ')' */
DOT, /* '.' */
COMMA, /* ',' */
QUESTION, /* '?' */
TILDE, /* '~' */
COLON, /* ':' */
SEMICOLON, /* ';' */
LBRACE, /* '{' */
RBRACE, /* '}' */
LBRACK, /* '[' */
RBRACK, /* ']' */
LESSER, /* '<' */
OR, /* '|' */
XOR, /* '^' */
MOD, /* '%' */
GREATER /* '>' */
};

#define TAM_XP 105
int tokens_primarios_gramatica[TAM_XP] = {
PrimaryExpression,
Literal,
Identifier,
ArrayLiteral,
ElementList,
Elision,
ObjectLiteral,
PropertyNameAndValueList,
PropertyNameAndValue,
PropertyName,
MemberExpression,
MemberExpressionForIn,
AllocationExpression,
MemberExpressionPart,
CallExpression,
CallExpressionForIn,
CallExpressionPart,
Arguments,
ArgumentList,
LeftHandSideExpression,
LeftHandSideExpressionForIn,
PostfixExpression,
PostfixOperator,
UnaryExpression,
UnaryOperator,
MultiplicativeExpression,
MultiplicativeOperator,
AdditiveExpression,
AdditiveOperator,
ShiftExpression,
ShiftOperator,
RelationalExpression,
RelationalOperator,
RelationalExpressionNoIn,
RelationalNoInOperator,
EqualityExpression,
EqualityExpressionNoIn,
EqualityOperator,
BitwiseANDExpression,
BitwiseANDExpressionNoIn,
BitwiseANDOperator,
BitwiseXORExpression,
BitwiseXORExpressionNoIn,
BitwiseXOROperator,
BitwiseORExpression,
BitwiseORExpressionNoIn,
BitwiseOROperator,
LogicalANDExpression,
LogicalANDExpressionNoIn,
LogicalANDOperator,
LogicalORExpression,
LogicalORExpressionNoIn,
LogicalOROperator,
ConditionalExpression,
ConditionalExpressionNoIn,
AssignmentExpression,
AssignmentExpressionNoIn,
AssignmentOperator,
Expression,
ExpressionNoIn,
Statement,
Block,
StatementList,
VariableStatement,
VariableDeclarationList,
VariableDeclarationListNoIn,
VariableDeclaration,
VariableDeclarationNoIn,
Initialiser,
InitialiserNoIn,
EmptyStatement,
ExpressionStatement,
IfStatement,
IterationStatement,
ContinueStatement,
BreakStatement,
ReturnStatement,
WithStatement,
SwitchStatement,
CaseBlock,
CaseClauses,
CaseClause,
DefaultClause,
LabelledStatement,
ThrowStatement,
TryStatement,
Catch,
Finally,
FunctionDeclaration,
FunctionExpression,
FormalParameterList,
FunctionBody,
Program,
SourceElements,
SourceElement,
ImportStatement,
Name,
JScriptVarStatement,
JScriptVarDeclarationList,
JScriptVarDeclaration,
insertSemiColon
};


/** ***************************************************************** */

typedef enum
{
/*\/ operadores; */
TOKEN_EQ, /* "=" */
TOKEN_ADD, /* "+" */
TOKEN_SUB, /* "-" */
TOKEN_NOT, /* "!" */
TOKEN_AND, /* "&" */
TOKEN_MUL, /* "*" */
TOKEN_DIV, /* "/" */
TOKEN_LPAREN, /* "(" */
TOKEN_RPAREN, /* ")" */
TOKEN_DOT, /* "." */
TOKEN_COMMA, /* "," */
TOKEN_QUESTION, /* "?" */
TOKEN_TILDE, /* "~" */
TOKEN_COLON, /* ":" */
TOKEN_SEMICOLON, /* ";" */
TOKEN_LBRACE, /* "{" */
TOKEN_RBRACE, /* "}" */
TOKEN_LBRACK, /* "[" */
TOKEN_RBRACK, /* "]" */
TOKEN_LESSER, /* "<" */
TOKEN_OR, /* "|" */
TOKEN_XOR, /* "^" */
TOKEN_MOD, /* "%" */
TOKEN_GREATER, /* ">" */
TOKEN_EQEQ, /* "==" */
TOKEN_ADDEQ, /* "+=" */
TOKEN_INCR, /* "++" */
TOKEN_SUBEQ, /* "-=" */
TOKEN_DECR, /* "--" */
TOKEN_NOTEQ, /* "!=" */
TOKEN_ANDEQ, /* "&=" */
TOKEN_LAND, /* "&&" */
TOKEN_OREQ, /* "|=" */
TOKEN_LOR, /* "||" */
TOKEN_XOREQ, /* "^=" */
TOKEN_LXOR, /* "^^" */
TOKEN_MODEQ, /* "%=" */
TOKEN_DIVEQ, /* "/=" */
TOKEN_MULEQ, /* "*=" */
TOKEN_LESSEREQ, /* "<=" */
TOKEN_LSHF, /* "<<" */
TOKEN_GREATEREQ, /* ">=" */
TOKEN_RSHF, /* ">>" */
TOKEN_FARROW, /* "=>" */
TOKEN_LSHFEQ, /* "<<=" */
TOKEN_EQEQEQ, /* "===" */
TOKEN_NOTEQEQ, /* "!==" */
TOKEN_RSHFEQ, /* ">>=" */
TOKEN_URSHF, /* ">>>" */
TOKEN_URSHFEQ, /* ">>>=" */

/*\/ palavras chaves; */
TOKEN_DO, /* "do" */
TOKEN_IN, /* "in" */
TOKEN_OF, /* "of" */
TOKEN_IF, /* "if" */
TOKEN_FOR, /* "for" */
TOKEN_LET, /* "let" */
TOKEN_NEW, /* "new" */
TOKEN_TRY, /* "try" */
TOKEN_VAR, /* "var" */
TOKEN_VOID, /* "void" */
TOKEN_WITH, /* "with" */
TOKEN_THIS, /* "this" */
TOKEN_CASE, /* "case" */
TOKEN_ELSE, /* "else" */
TOKEN_BREAK, /* "break" */
TOKEN_CATCH, /* "catch" */
TOKEN_CLASS, /* "class" */
TOKEN_CONST, /* "const" */
TOKEN_SUPER, /* "super" */
TOKEN_THROW, /* "throw" */
TOKEN_WHILE, /* "while" */
TOKEN_YIELD, /* "yield" */
TOKEN_DELETE, /* "delete" */
TOKEN_EXPORT, /* "export" */
TOKEN_IMPORT, /* "import" */
TOKEN_RETURN, /* "return" */
TOKEN_SWITCH, /* "switch" */
TOKEN_TYPEOF, /* "typeof" */
TOKEN_DEFAULT, /* "default" */
TOKEN_EXTENDS, /* "extends" */
TOKEN_FINALLY, /* "finally" */
TOKEN_FUNCTION, /* "function" */
TOKEN_CONTINUE, /* "continue" */
TOKEN_DEBUGGER, /* "debugger" */
TOKEN_INSTANCEOF, /* "instanceof" */
TOKEN_FIM /* << número de tokens; */
} TokenType;

typedef struct TokenStruct
{ 
  // The parsed value if the token is a literal.
  const int tokenType;
  
  // The beginning of the token, pointing directly into the source.
  const char* identifier;
} TokenStruct;

//~ // The table of reserved words and their associated token types.
static TokenStruct tokens_struct[] =
{
/*\/ operadores e delimitadores; */
{TOKEN_EQ, "="},
{TOKEN_ADD, "+"},
{TOKEN_SUB, "-"},
{TOKEN_NOT, "!"},
{TOKEN_AND, "&"},
{TOKEN_MUL, "*"},
{TOKEN_DIV, "/"},
{TOKEN_LPAREN, "("},
{TOKEN_RPAREN, ")"},
{TOKEN_DOT, "."},
{TOKEN_COMMA, ","},
{TOKEN_QUESTION, "?"},
{TOKEN_TILDE, "~"},
{TOKEN_COLON, ":"},
{TOKEN_SEMICOLON, ";"},
{TOKEN_LBRACE, "{"},
{TOKEN_RBRACE, "}"},
{TOKEN_LBRACK, "["},
{TOKEN_RBRACK, "]"},
{TOKEN_LESSER, "<"},
{TOKEN_OR, "|"},
{TOKEN_XOR, "^"},
{TOKEN_MOD, "%"},
{TOKEN_GREATER, ">"},
{TOKEN_EQEQ, "=="},
{TOKEN_ADDEQ, "+="},
{TOKEN_INCR, "++"},
{TOKEN_SUBEQ, "-="},
{TOKEN_DECR, "--"},
{TOKEN_NOTEQ, "!="},
{TOKEN_ANDEQ, "&="},
{TOKEN_LAND, "&&"},
{TOKEN_OREQ, "|="},
{TOKEN_LOR, "||"},
{TOKEN_XOREQ, "^="},
{TOKEN_LXOR, "^^"},
{TOKEN_MODEQ, "%="},
{TOKEN_DIVEQ, "/="},
{TOKEN_MULEQ, "*="},
{TOKEN_LESSEREQ, "<="},
{TOKEN_LSHF, "<<"},
{TOKEN_GREATEREQ, ">="},
{TOKEN_RSHF, ">>"},
{TOKEN_FARROW, "=>"},
{TOKEN_LSHFEQ, "<<="},
{TOKEN_EQEQEQ, "==="},
{TOKEN_NOTEQEQ, "!=="},
{TOKEN_RSHFEQ, ">>="},
{TOKEN_URSHF, ">>>"},
{TOKEN_URSHFEQ, ">>>="},

/*\/ palavras chaves; */
{TOKEN_DO, "do"},
{TOKEN_IN, "in"},
{TOKEN_OF, "of"},
{TOKEN_IF, "if"},
{TOKEN_FOR, "for"},
{TOKEN_LET, "let"},
{TOKEN_NEW, "new"},
{TOKEN_TRY, "try"},
{TOKEN_VAR, "var"},
{TOKEN_VOID, "void"},
{TOKEN_WITH, "with"},
{TOKEN_THIS, "this"},
{TOKEN_CASE, "case"},
{TOKEN_ELSE, "else"},
{TOKEN_BREAK, "break"},
{TOKEN_CATCH, "catch"},
{TOKEN_CLASS, "class"},
{TOKEN_CONST, "const"},
{TOKEN_SUPER, "super"},
{TOKEN_THROW, "throw"},
{TOKEN_WHILE, "while"},
{TOKEN_YIELD, "yield"},
{TOKEN_DELETE, "delete"},
{TOKEN_EXPORT, "export"},
{TOKEN_IMPORT, "import"},
{TOKEN_RETURN, "return"},
{TOKEN_SWITCH, "switch"},
{TOKEN_TYPEOF, "typeof"},
{TOKEN_DEFAULT, "default"},
{TOKEN_EXTENDS, "extends"},
{TOKEN_FINALLY, "finally"},
{TOKEN_FUNCTION, "function"},
{TOKEN_CONTINUE, "continue"},
{TOKEN_DEBUGGER, "debugger"},
{TOKEN_INSTANCEOF, "instanceof"},
{TOKEN_FIM, NULL} /* << marca o fim do array; */
};
