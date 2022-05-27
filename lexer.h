#include <stdbool.h>
// char *INTEGER = "INTEGER";
// char *PLUS = "PLUS";
// char *MINUS = "MINUS";
// char *MULTIPLY = "MULTIPLY";
// char *DIVIDE = "DIVIDE";
// char *LPAREN = "LPAREN";
// char *RPAREN = "RPAREN";

typedef struct Token
{
  char *type;
  char *value;
} Token;

bool is_numeric(char c);
Token **lexer(char *stream, int stream_length, int *size);
Token *create_token(char *type, char *value);
void destroy_token(Token *token);
void print_tokens(Token **tokens, int num_tokens);