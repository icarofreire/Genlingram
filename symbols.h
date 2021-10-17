/* operadores e paravras chaves JavaScript; */

/* tamanho dos elementos de um array */
#define TAMANHO(x) (sizeof(x) / sizeof((x)[0]))

/*\/ TOKEN_OPERADOR*/
char *operators[] = {
" ",
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


enum ini_grammar {
sourceCharacter,
inputElementDiv,
inputElementRegExp,
whiteSpace,
lineTerminator,
comment,
multiLineComment,
multiLineCommentChars,
postAsterikCommentChars,
multiLineNotAsterikChar,
multiLineNotForwardSlashOrAsterikChar,
singleLineComment,
singleLineCommentChars,
singleLineCommentChar,
token,
reservedWord,
keyword,
futureReservedWord,
identifier,
identifierName,
identifierStart,
identifierPart,
unicodeLetter,
unicodeCombiningMark,
unicodeDigit,
unicodeConnectorPunctuation,
unicodeEscapeSequence,
punctuator,
divPunctuator,
literal,
nullLiteral,
booleanLiteral,
numericLiteral,
decimalLiteral,
decimalIntegerLiteralTail,
decimalIntegerLiteral,
decimalDigits,
decimalDigit,
exponentIndicator,
signedInteger,
hexIntegerLiteral,
stringLiteral,
doubleStringCharacters,
singleStringCharacters,
doubleStringCharacter,
singleStringCharacter,
escapeSequence,
characterEscapeSequence,
singleEscapeCharacter,
nonEscapeCharacter,
escapeCharacter,
hexEscapeSequence,
regularExpressionLiteral,
regularExpressionBody,
regularExpressionChars,
regularExpressionFirstChar,
regularExpressionChar,
backslashSequence,
nonTerminator,
regularExpressionFlags,
stringNumericLiteral,
strWhiteSpace,
strWhiteSpaceChar,
strNumericLiteral,
strDecimalLiteral,
strUnsignedDecimalLiteral,
exponentPart,
hexDigit,
primaryExpression,
arrayLiteral,
elementList,
elementListTail,
elision,
objectLiteral,
propertyNameAndValueList,
propertyNameAndValueListTail,
propertyName,
memberExpression,
memberExpressionTail,
newExpression,
callExpression,
callExpressionTail,
arguments,
argumentList,
argumentListTail,
leftHandSideExpression,
postfixExpression,
unaryExpression,
multiplicativeExpression,
multiplicativeExpressionTail,
additiveExpression,
additiveExpressionTail,
shiftExpression,
shiftExpressionTail,
relationalExpression,
relationalExpressionTail,
relationalExpressionNoln,
equalityExpression,
equalityExpressionTail,
equalityExpressionNoln,
equalityExpressionNolnTail,
bitwiseAndExpression,
bitwiseAndExpressionTail,
bitwiseAndExpressionNoln,
bitwiseAndExpressionNolnTail,
bitwiseXorExpression,
bitwiseXorExpressionTail,
bitwiseXorExpressionNoln,
bitwiseXorExpressionNolnTail,
bitwiseOrExpression,
bitwiseOrExpressionTail,
bitwiseOrExpressionNoln,
bitwiseOrExpressionNolnTail,
logicalAndExpression,
logicalAndExpressionNoln,
logicalAndExpressionNolnTail,
logicalOrExpression,
logicalOrExpressionTail,
logicalOrExpressionNoln,
logicalOrExpressionNolnTail,
conditionalExpression,
conditionalExpressionNoln,
assignmentExpression,
assignmentExpressionNoln,
assignmentOperator,
expression,
expressionTail,
expressionNoln,
expressionNolnTail,
statement,
block,
statementList,
variableStatement,
variableDeclarationList,
variableDeclarationTail,
variableDeclarationListNoln,
variableDeclarationListNolnTail,
variableDeclaration,
variableDeclarationNoln,
initialiser,
initialiserNoln,
emptyStatement,
expressionStatement,
ifStatement,
iterationStatement,
continueStatement,
breakStatement,
returnStatement,
withStatement,
switchStatement,
caseBlock,
caseClauses,
caseClause,
defaultClause,
labelledStatement,
throwStatement,
tryStatement,
catch_,
finally_,
functionDeclaration,
functionExpression,
formalParameterList,
formalParameterListTail,
functionBody,
sourceElements,
sourceElement,
uri,
uriCharacters,
uriCharacter,
uriReserved,
uriUnescaped,
uriEscaped,
uriAlpha,
uriMark,
patter,
disjunction,
alternative,
term,
assertion,
quantifier,
quantifierPrefix,
atom,
patternCharacter,
atomEscape,
characterEscape,
controlEscape,
controlLetter,
identityEscape,
characterClassEscape,
decimalEscape,
characterClass,
classRanges,
nonemptyClassRanges,
nonemptyClassRangesNoDash,
classAtom,
classAtomNoDash,
classEscape
};

enum primary_tokens_grammar {
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
insertSemiColon,
TOKEN_PALAVRA_CHAVE,
TOKEN_OPERADOR,
ABRE_BLOCO,
FECHA_BLOCO,
TOKEN_ABRE_PARENTESE,
TOKEN_FECHA_PARENTESE,
DECIMAL_LITERAL,
HEX_INTEGER_LITERAL,
STRING_LITERAL,
BOOLEAN_LITERAL,
NULL_LITERAL,
REGULAR_EXPRESSION_LITERAL,
IDENTIFIER_NAME,
OPCIONAL,
REP_ASTERISCO,
REP_MAIS,
TOKEN_EOF,
code,
java,
TOKEN_INTERROGACAO,
TOKEN_INTERRORACAO,
SLASH,
SLASHASSIGN,
FIM_PARTE_EXPRESSAO
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
