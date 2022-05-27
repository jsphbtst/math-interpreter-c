#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lexer.h"

#define BUFFER_SIZE 4096

/*
10 * (4 / (4 - 2))
{
  type: 'BinaryOperator',
  operator: '*',
  lhs: { type: 'NumericLiteral', value: 10 },
  rhs: {
    type: 'BinaryOperator',
    operator: '/',
    lhs: { type: 'NumericLiteral', value: 4 },
    rhs: {
      type: 'BinaryOperator',
      operator: '-',
      lhs: { type: 'NumericLiteral', value: 4 },
      rhs: { type: 'NumericLiteral', value: 2 }
    }
  }
}
*/
typedef struct ParseObject {
  int value;
  char *type;
  char *operator;
  struct ParseObject *lhs;
  struct ParseObject *rhs;
} ParseObject;

ParseObject *create_parsed_object(Token *token) {
  ParseObject *p = malloc(sizeof(ParseObject));
  p->value = atoi(token->value);
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
  if (strcmp(current_token->type, "INTEGER") == 0) {
    ParseObject *literal = create_parsed_object(current_token);
    eat_token(tokens, cursor, "INTEGER");
    return literal;
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

int evaluate(ParseObject *object) {
  if (strcmp(object->type, "NumericLiteral") == 0) {
    return object->value;
  }

  int lhs = evaluate(object->lhs);
  int rhs = evaluate(object->rhs);
  if (strcmp(object->operator, "+") == 0) {
    return lhs + rhs;
  } else if (strcmp(object->operator, "-") == 0) {
    return lhs - rhs;
  } else if (strcmp(object->operator, "*") == 0) {
    return lhs * rhs;
  } else if (strcmp(object->operator, "/") == 0) {
    return lhs / rhs;
  } else {
    return -1;
  }
}

int main() {
  int num_tokens = 0;
  // char *stream = "1 + 3 - 4 + 100 - 99";
  char *stream = "9 * 9 - 12";
  int stream_length = strlen(stream);
  Token **tokens = lexer(stream, stream_length, &num_tokens);
  ParseObject *ast = parse(tokens, num_tokens);
  int evaluated_value = evaluate(ast);
  printf("evaluated_value: %d\n", evaluated_value);


  // char message[BUFFER_SIZE];
  // while (true) {
  //   printf("Math >  ");
  //   fgets(message, BUFFER_SIZE, stdin);
  //   int stream_length = strlen(message);
  //   message[stream_length - 1] = '\0'; // terminate string early

  //   char *stream = malloc(stream_length * sizeof(char));
  //   memcpy(stream, message, stream_length);

  //   int size = 0;
  //   Token **tokens = lexer(stream, stream_length, &size);
  //   for (int idx = 0; idx < size; idx++) {
  //     printf("%s %s\n", tokens[idx]->type, tokens[idx]->value);  
  //   }
  // }
  return 0;
}