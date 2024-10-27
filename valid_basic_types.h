#include <string.h>
#include <ctype.h>

/* Lib interpreter primitive data types; */

/*\/ Primitive data types; */
enum Primitive_types {
CHAR,
STRING,
INT,
REAL_NUMBER,
IDENTIFIER,
BINARY,
BOOL,
NULL_TYPE,
NIL,
NONE,
UNDEFINED,
OCTAL,
HEX
};

void toLower(char* s) {
    for(char *p=s; *p; p++) *p=tolower(*p);
}

bool isChar(const char *str)
{
    int fim = strlen(str);
    if(
        ((str[0] == '\'') && (str[fim-1] == '\'')) &&
        (fim == 3)
    ){
        return true;
    }else{
        return false;
    }
}

bool isString(const char *str)
{
  int fim = strlen(str);
  if(
	(str[0] == '"' || str[0] == '\'') &&
	(str[fim-1] == '"' || str[fim-1] == '\'')
   ){
	return true;
   }else{
	return false;
   }
}

int validIdentifier( char *s )
{
	int ind = 0;
    unsigned char c;
    char *p = s;
    while( (c = *p) && (isalpha(c) || (c == '_') || ((ind > 0) && (c == '-')) || ((ind > 0) && (c >= '0' && c <= '9'))) ) {
		++p;
		ind++;
	}
    return *p == '\0';
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(const char* str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if ((str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9') || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(const char* str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if ((str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.') ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

// Returns 'true' if the string is a BINARY NUMBER.
bool isBinaryNumber(const char* str)
{
	int i, len = strlen(str);
	bool fb1 = false, fb2 = true;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'b') || (str[0] == '0' && str[1] == 'B') ){ fb1 = true; }
	for (i = 2; i < len; i++) {
		if ((str[i] != '0' && str[i] != '1')){
			fb2 = false;
		}
	}
	return (fb1 && fb2);
}

bool isBooleanNumber(char* str)
{
	int len = strlen(str);
	bool f = false;

	if (len == 0) return (false);

    toLower(str);
	if ((strcmp(str, "true") == 0) || (strcmp(str, "false") == 0)){ f = true; }
	return (f);
}

bool isNullLiteral(char* str)
{
	int len = strlen(str);
	bool f = false;

	if (len == 0) return (false);

    toLower(str);
	if ((strcmp(str, "null") == 0)){ f = true; }
	return (f);
}

bool isNilLiteral(char* str)
{
    int len = strlen(str);
    bool f = false;

    if (len == 0) return (f);

    toLower(str);
    if ((strcmp(str, "nil") == 0)){ f = true; }
    return (f);
}

bool isNoneLiteral(char* str)
{
    int len = strlen(str);
    bool f = false;

    if (len == 0) return (f);

    toLower(str);
    if ((strcmp(str, "none") == 0)){ f = true; }
    return (f);
}

bool isUndefinedLiteral(char* str)
{
    int len = strlen(str);
    bool f = false;

    if (len == 0) return (f);

    toLower(str);
    if ((strcmp(str, "undefined") == 0)){ f = true; }
    return (f);
}

bool isOctalNumber(const char* str)
{
	int i, len = strlen(str);
	bool f1 = false, f2 = true;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'o') || (str[0] == '0' && str[1] == 'O') ){ f1 = true; }
	for (i = 2; i < len; i++) {
		if( isdigit(str[i]) == 0 ){
			f2 = false;
		}
	}
	return (f1 && f2);
}

bool isHexNumber(const char* str)
{
	int i, len = strlen(str);
	bool f1 = false, f2 = false;

	if (len == 0) return (false);

	if( (str[0] == '0' && str[1] == 'x') || (str[0] == '0' && str[1] == 'X') ){ f1 = true; }
	for (i = 2; i < len; i++) {
		if( (isdigit(str[i]) > 0) &&
		( str[i] != 'a' && str[i] != 'b' && str[i] != 'c' && str[i] != 'd' && str[i] != 'e' && str[i] != 'f' &&
		  str[i] != 'A' && str[i] != 'B' && str[i] != 'D' && str[i] != 'E' && str[i] != 'F'
		)
		){
			f2 = true;
		}
	}
	return (f1 == true && f2 == true);
}

int identify_identifier(char* token){
	if(validIdentifier(token)){
		return IDENTIFIER;
	}
	return -1;
}

int identify_types(char* token)
{
    if(isChar(token)){
        return CHAR;
    }
	if(isString(token)){
        return STRING;
	}
	if(isInteger(token)){
        return INT;
	}
	if(isRealNumber(token)){
        return REAL_NUMBER;
	}
	if(isBinaryNumber(token)){
        return BINARY;
	}
	if(isBooleanNumber(token)){
        return BOOL;
	}
	if(isNullLiteral(token)){
        return NULL_TYPE;
	}
	if(isNilLiteral(token)){
        return NIL;
    }
    if(isNoneLiteral(token)){
        return NONE;
    }
    if(isUndefinedLiteral(token)){
        return UNDEFINED;
    }
	if(isOctalNumber(token)){
        return OCTAL;
	}
	if(isHexNumber(token)){
        return HEX;
	}
	return -1;
}
