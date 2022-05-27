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
  int num_tokens = 0;
  // char *stream = "1 + 3 - 4 + 100 - 99";
  char *stream = "(12 + 12) - 6 * 4";
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