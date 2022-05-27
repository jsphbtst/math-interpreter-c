#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

ParseObject* create_parsed_object(Token *token) {
  ParseObject *p = malloc(sizeof(ParseObject));
  p->value = atof(token->value);
  p->type = "NumericLiteral";
  return p;
}

void eat_token(Token **tokens, int *cursor, char *token_type) {
  Token *current_token = tokens[(*cursor)];
  if (strcmp(current_token->type, token_type) == 0) {
    (*cursor) += 1;
  } else {
    printf("SyntaxError: Expected token of type %s but instead got %s\n", token_type, current_token->type);
    exit(0);
  }
}

ParseObject* parse_factor(Token **tokens, int num_tokens, int *cursor) {
  Token *current_token = tokens[(*cursor)];
  if (strcmp(current_token->type, "NUMBER") == 0) {
    ParseObject *literal = create_parsed_object(current_token);
    eat_token(tokens, cursor, "NUMBER");
    return literal;
  } 

  if (strcmp(current_token->type, "LPAREN") == 0) {
    eat_token(tokens, cursor, "LPAREN");
    ParseObject *expr = parse_expression(tokens, num_tokens, cursor);
    eat_token(tokens, cursor, "RPAREN");
    return expr;
  }

  printf("SyntaxError: Expected parenthesis or integer input but instead received %s\n", current_token->value);
  exit(0);
}

ParseObject* parse_term(Token **tokens, int num_tokens, int *cursor) {
  ParseObject *lhs = parse_factor(tokens, num_tokens, cursor);
  if ((*cursor) >= num_tokens) {
    return lhs;
  };
  Token *current_token = tokens[(*cursor)];
  while (
    strcmp(current_token->type, "DIVIDE") == 0 ||
    strcmp(current_token->type, "MULTIPLY") == 0
  ) {
    
    if (strcmp(current_token->type, "DIVIDE") == 0) {
      eat_token(tokens, cursor, "DIVIDE");
    } else {
      eat_token(tokens, cursor, "MULTIPLY");
    }
    
    ParseObject *rhs = parse_factor(tokens, num_tokens, cursor);
    ParseObject *old_lhs = lhs;
    char *operator = current_token->value;
    lhs = malloc(sizeof(ParseObject));
    lhs->operator = operator;
    lhs->lhs = old_lhs;
    lhs->type = "BinaryOperator";
    lhs->rhs = rhs;
    
    if ((*cursor) >= num_tokens) {
      break;
    } else {
      current_token = tokens[(*cursor)];
    }
  }  
  return lhs;
}

ParseObject* parse_expression(Token **tokens, int num_tokens, int *cursor) {
  ParseObject *lhs = parse_term(tokens, num_tokens, cursor);
  if ((*cursor) >= num_tokens) {
    return lhs;
  };
  Token *current_token = tokens[(*cursor)];
  while (
    strcmp(current_token->type, "PLUS") == 0 ||
    strcmp(current_token->type, "MINUS") == 0
  ) {
    if (strcmp(current_token->type, "PLUS") == 0) {
      eat_token(tokens, cursor, "PLUS");
    } else {
      eat_token(tokens, cursor, "MINUS");
    }
    
    ParseObject *rhs = parse_term(tokens, num_tokens, cursor);
    ParseObject *old_lhs = lhs;
    char *operator = current_token->value;
    lhs = malloc(sizeof(ParseObject));
    lhs->operator = operator;
    lhs->lhs = old_lhs;
    lhs->type = "BinaryOperator";
    lhs->rhs = rhs;
    if ((*cursor) >= num_tokens) {
      break;
    } else {
      current_token = tokens[(*cursor)];
    }
  }
  return lhs;
}

ParseObject* parse(Token **tokens, int num_tokens) {
  int cursor = 0;
  ParseObject *result = parse_expression(tokens, num_tokens, &cursor);
  return result;
}

void destroy_ast(ParseObject *ast) {
  if (strcmp(ast->type, "NumericLiteral") == 0) {
    free(ast);
    return;
  }

  destroy_ast(ast->lhs);
  destroy_ast(ast->rhs);
}