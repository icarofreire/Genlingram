#include "scanner.hpp"
#include "symbols.hpp"

using namespace std;

bool isPunctuator(char ch)	//check if the given character is a punctuator or not
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
        ch == '&' || ch == '|')
        {
            return true;
        }
    return false;
}

bool isID(const std::string &str)
{
  if(std::isdigit(str[0]))
    return false;
  unsigned int counter = 0;
  if(str[0] == '_')
    counter++;

  for(; counter < str.size(); counter++)
    if(!(isalnum(str[counter])))
      return false;

  return true;
}

bool isComment(const std::string &str)
{
  return str == "/*" || str == "//";
}

bool isDigit(const std::string &str)
{
  return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool isString(const std::string &str)
{
  return str[0] == '"' && str[str.size()-1] == '"';
}

bool isBool(const std::string &str)
{
  return str == "true" || str == "false";
}

bool isLiteral(const std::string &str)
{
  return isDigit(str) || isString(str) || isBool(str);
}

//~ bool isKeyword(const std::string &str)
//~ {
  //~ const vector<std::string> keywords{"int", "float", "auto", "double", "do", "switch", "return"};
  //~ for(const auto& keyword : keywords)
    //~ if (keyword == str)
      //~ return true;

  //~ return false;
//~ }

bool isKeyword(const std::string &str)
{
	string * res = std::find(std::begin(reserved_words), std::end(reserved_words), str);
	if( res != std::end(reserved_words) ){
		return true;
	}
  return false;
}

bool isStatement(const std::string &str)
{
  const vector<std::string> statements{"for", "while"};
  for(const auto& statement : statements)
    if (statement == str)
      return true;

  return false;
}

//~ bool isOperator(const std::string &str)
//~ {
  //~ const vector<std::string> operators{"<", ">", "<=", ">=", "*", "+", "-", "/", "=", "-=", "*=", "+=", "/=", "++", "--", "=="};
  //~ for(const auto& op : operators)
    //~ if (op == str)
      //~ return true;

  //~ return false;
//~ }

bool isOperator(const std::string &str)
{
	string * res = std::find(std::begin(operators), std::end(operators), str);
	if( res != std::end(operators) ){
		return true;
	}
  return false;
}

bool isOperator(const char str)
{
	string * res = std::find(std::begin(operators), std::end(operators), str);
	if( res != std::end(operators) ){
		return true;
	}
  return false;
}

bool isSeparator(const std::string &str)
{
  const vector<std::string> Separators{"{", "}", ",", "(", ")", ";"};
  for(const auto& separate : Separators)
    if (separate == str)
      return true;

  return false;
}

bool isNotLegal(const std::string &str)
{
  return str == " " || str == "\n";
}

void printRoleOfToken(const std::string& token)
{
  if(isOperator(token))
    cout << "(operator, " << token << ")";
  else if(isSeparator(token))
    cout << "(separator, " << token << ")";
  else if(isKeyword(token))
    cout << "(keyword, " << token << ")";
  else if(isStatement(token))
    cout << "(statement, " << token << ")";
  else if(isLiteral(token))
    cout << "(literal, " << token << ")";
  else if(isID(token))
    cout << "(identifier, " << token << ")";
  else if(isComment(token))
    cout << "(comment, " << token << ")";
  else
    throw std::runtime_error("Invalid token: " + token);
}

// Parsing the input STRING.
void parse(string str)
{
	int left = 0, right = 0;
	int len = str.size();

	while (right <= len && left <= right) {
		if (isPunctuator(str[right]) == false)
			right++;

		if (isPunctuator(str[right]) == true && left == right) {
			if (isOperator(str[right]) == true)
				printf("'%c' IS AN OPERATOR\n", str[right]);

			right++;
			left = right;
		} else if ((isPunctuator(str[right]) == true && left != right)
				|| (right == len && left != right)) {
			string subStr = str.substr(left, right - 1);

			if (isKeyword(subStr) == true)
				printf("'%s' IS A KEYWORD\n", subStr);

			else if (isInteger(subStr) == true)
				printf("'%s' IS AN INTEGER\n", subStr);

			else if (isRealNumber(subStr) == true)
				printf("'%s' IS A REAL NUMBER\n", subStr);

			else if (validIdentifier(subStr) == true
					&& isDelimiter(str[right - 1]) == false)
				printf("'%s' IS A VALID IDENTIFIER\n", subStr);

			else if (validIdentifier(subStr) == false
					&& isDelimiter(str[right - 1]) == false)
				printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
			left = right;
		}
	}
	return;
}

void lexicalAnalyze(const std::string &nameOfFile)
{
  char ch;
  std::string buffer;
  std::fstream file(nameOfFile, std::fstream::in);

  if (!file.is_open())
  {
    cout << "error while opening the file\n";
    exit(0);
  }

  bool miltiCm = false, singleCm = false;
  while (file >> std::noskipws >> ch)
  {
    if(singleCm || miltiCm)
    {
      if(singleCm && ch == '\n')
        singleCm = false;

      if(miltiCm && ch == '*')
      {
        file >> ch;
        if(ch == EOF)
          break;

        if(ch == '/')
          miltiCm = false;
      }
      continue;
    }

    if(ch == '/')
    {
      std::string comm(1, ch);
      file >> ch;
      if(ch == EOF)
      {
        printRoleOfToken(comm);
        break;
      }

      if(ch == '*')
      {
        miltiCm = true;
        comm += ch;
      }
      else if(ch == '/')
      {
        singleCm = true;
        comm += ch;
      }
      if(miltiCm || singleCm)
      {
        printRoleOfToken(comm);
        continue;
      }
    }

    if(isNotLegal(std::string(1, ch)))
    {
      if(!buffer.empty())
      {
        printRoleOfToken(buffer);
        buffer = "";
      }
      continue;
    }

    if(isOperator(std::string(1, ch)) && !isOperator(buffer))
    {
      if(!buffer.empty())
      {
        printRoleOfToken(buffer);
        buffer = "";
      }
    }

    if(!isOperator(std::string(1, ch)) && isOperator(buffer))
    {
      printRoleOfToken(buffer);
      buffer = "";
    }

    if(isSeparator(std::string(1, ch)))
    {
      if(!buffer.empty())
      {
        printRoleOfToken(buffer);
        buffer = "";
      }
      if(isSeparator(std::string(1, ch)))
      {
        printRoleOfToken(std::string(1, ch));
        continue;
      }
    }
    buffer += ch;
  }
  file.close();
}
