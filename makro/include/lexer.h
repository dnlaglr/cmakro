#ifndef makro_lexer
#define makro_lexer

typedef enum {
  // Single-character tokens
  TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
  TOKEN_COMMA, TOKEN_DOT, TOKEN_PLUS, TOKEN_MINUS,
  TOKEN_STAR, TOKEN_SLASH, TOKEN_SEMICOLON,
  // One or two character tokens
  TOKEN_BANG, TOKEN_BANG_EQUAL,
  TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER, TOKEN_GREATER_EQUAL,
  TOKEN_LESS, TOKEN_LESS_EQUAL,
  // Literals
  TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
  // Keywords
  TOKEN_AND, TOKEN_CLASS, TOKEN_FOR, TOKEN_IF,
  TOKEN_ELSE, TOKEN_TRUE, TOKEN_FALSE, TOKEN_OR,
  TOKEN_FUN, TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER,
  TOKEN_THIS, TOKEN_WHILE, TOKEN_VAR, TOKEN_NULL,

  TOKEN_ERROR, TOKEN_EOF
} TokenType;

typedef struct {
  TokenType type;
  const char* start;
  int length;
  int line;
} Token;

void initLexer(const char* source);
Token scanToken();

#endif
