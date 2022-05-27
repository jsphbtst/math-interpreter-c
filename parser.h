#include "lexer.h"

typedef struct ParseObject {
  int value;
  char *type;
  char *operator;
  struct ParseObject *lhs;
  struct ParseObject *rhs;
} ParseObject;

ParseObject* create_parsed_object(Token *token);
ParseObject* parse_factor(Token **tokens, int num_tokens, int *cursor);
ParseObject* parse_term(Token **tokens, int num_tokens, int *cursor);
ParseObject* parse_expression(Token **tokens, int num_tokens, int *cursor);
ParseObject* parse(Token **tokens, int num_tokens);
void eat_token(Token **tokens, int *cursor, char *token_type);
void destroy_ast(ParseObject *ast);