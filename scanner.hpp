#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isID(const std::string &str);
bool isComment(const std::string &str);
bool isDigit(const std::string &str);
bool isString(const std::string &str);
bool isBool(const std::string &str);
bool isLiteral(const std::string &str);
bool isKeyword(const std::string &str);
bool isStatement(const std::string &str);
bool isOperator(const std::string &str);
bool isOperator(const std::string &str, string []);
bool isSeparator(const std::string &str);
bool isNotLegal(const std::string &str);
void printRoleOfToken(const vector<std::string>& tokens);
void lexicalAnalyze(const std::string &nameOfFile);
