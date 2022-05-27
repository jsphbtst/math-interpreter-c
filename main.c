#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"

#define BUFFER_SIZE 4096

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
    int evaluated_value = evaluate(ast);
    printf("%d\n", evaluated_value);

  }
  return 0;
}