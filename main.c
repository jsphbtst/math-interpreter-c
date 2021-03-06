#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "parser/parser.h"

#define BUFFER_SIZE 4096

double evaluate(ParseObject *object);

int main() {
  char message[BUFFER_SIZE];
  while (true) {
    printf("Math >  ");
    fgets(message, BUFFER_SIZE, stdin);
    int stream_length = strlen(message);
    message[stream_length - 1] = '\0'; // terminate string early

    char *stream = malloc(stream_length * sizeof(char));
    memcpy(stream, message, stream_length);

    if (strcmp(stream, "exit") == 0) {
      printf("Exiting program...\n");
      return 1;
    }

    int size = 0;
    Token **tokens = lexer(stream, stream_length, &size);
    ParseObject *ast = parse(tokens, size);
    double evaluated_value = evaluate(ast);
    printf("%.6g\n", evaluated_value);
    free(stream);
    destroy_tokens(tokens, size);
    destroy_ast(ast);
  }
  return 0;
}

double evaluate(ParseObject *ast) {
  if (strcmp(ast->type, "NumericLiteral") == 0) {
    return ast->value;
  }

  if (strcmp(ast->type, "TrigOp") == 0) {
    double expression_value = evaluate(ast->expr);
    if (is_sin(ast->operator)) {
      return sin(expression_value);
    } else if (is_cos(ast->operator)) {
      return cos(expression_value);
    } else if (is_tan(ast->operator)) {
      return tan(expression_value);
    } else {
      return sin(expression_value);
    }
  }

  if (strcmp(ast->type, "ExpOp") == 0) {
    double expression_value = evaluate(ast->expr);
    if (strcmp(ast->operator, "exp") == 0) {
      return exp(expression_value);
    } else if ((strcmp(ast->operator, "ln") == 0) | (strcmp(ast->operator, "log") == 0)) {
      return log(expression_value);
    } else {
      return exp(expression_value);
    }
  }

  double lhs = evaluate(ast->lhs);
  double rhs = evaluate(ast->rhs);
  if (strcmp(ast->operator, "+") == 0) {
    return lhs + rhs;
  } else if (strcmp(ast->operator, "-") == 0) {
    return lhs - rhs;
  } else if (strcmp(ast->operator, "*") == 0) {
    return lhs * rhs;
  } else if (strcmp(ast->operator, "/") == 0) {
    return lhs / rhs;
  } else {
    return -1;
  }
}