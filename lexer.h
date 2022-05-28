#include <stdbool.h>

typedef struct Token {
  char *type;
  char *value;
} Token;

bool is_numeric(char c);
bool is_alpha(char c);
Token **lexer(char *stream, int stream_length, int *size);
Token *create_token(char *type, char *value);
void destroy_token(Token *token);
void destroy_tokens(Token **tokens, int num_tokens);
void print_tokens(Token **tokens, int num_tokens);