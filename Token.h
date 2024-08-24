/* struct Token; */

struct Token
{
  // The beginning of the token, pointing directly into the source.
  char* identifier;

  // The 1-based line where the token appears.
  int line;
  
  // The parsed value if the token is a literal.
  int tokenType;
};
