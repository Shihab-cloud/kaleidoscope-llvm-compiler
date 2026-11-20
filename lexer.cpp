#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

/// gettok - Return the next token from standard input.
static int gettok() {
    static int LastChar = ' ';

  // Skip any whitespace.
    while (isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
            IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;
    return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {   // Number: [0-9.]+
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
         return tok_number;
    }

    if (LastChar == '#') {
        // Comment until end of line.
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
    return gettok();
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF)
        return tok_eof;
    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

int main() {
  while (true) {                    // keep reading tokens
    int tok = gettok();             // ask the lexer for the next token
    switch (tok) {                  // print which kind of token it is
    case tok_eof:        printf("tok_eof\n"); return 0;   // input finished: stop
    case tok_def:        printf("tok_def\n"); break;
    case tok_extern:     printf("tok_extern\n"); break;
    case tok_identifier: printf("tok_identifier  \"%s\"\n", IdentifierStr.c_str()); break;
    case tok_number:     printf("tok_number      %g\n", NumVal); break;
    default:             printf("character       '%c'\n", tok); break;  // e.g. + ( ;
    }
  }
}