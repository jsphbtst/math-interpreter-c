#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexer.h"

void print_tokens(Token **tokens, int num_tokens) {
  for (int i = 0; i < num_tokens; i++) {
    printf("%s %s\n", tokens[i]->type, tokens[i]->value);
  }  
}

bool is_numeric(char c) {
  int char_code = (int)c;
  return char_code >= 48 & char_code <= 57;
}

Token *create_token(char *type, char *value) {
  Token *token = malloc(sizeof(token));
  token->type = type;
  token->value = value;
  return token;
}

void destroy_token(Token *token) {
  free(token);
}

void destroy_tokens(Token **tokens, int num_tokens) {
  for (int i = 0; i < num_tokens; i++) {
    free(tokens[i]);
  }
  free(tokens);
}

Token **lexer(char *stream, int stream_length, int *size) {
  int num_tokens = 0;
  Token **tokens = malloc(num_tokens * sizeof(Token *));;
  
  int cursor = 0;
  while (cursor < stream_length) {
    char c = stream[cursor];
    switch (c) {
      case '+':
        {
          Token* t = create_token("PLUS", "+");
          num_tokens++;
          tokens = realloc(tokens, num_tokens * sizeof(Token *));
          tokens[num_tokens - 1] = t;          
        }
        break;
      case '-':
        {
          Token* t = create_token("MINUS", "-");
          num_tokens++;
          tokens = realloc(tokens, num_tokens * sizeof(Token *));
          tokens[num_tokens - 1] = t;          
        }
        break;
      case '*':
        {
          Token* t = create_token("MULTIPLY", "*");
          num_tokens++;
          tokens = realloc(tokens, num_tokens * sizeof(Token *));
          tokens[num_tokens - 1] = t;          
        }
        break;
      case '/':
        {
          Token* t = create_token("DIVIDE", "/");
          num_tokens++;
          tokens = realloc(tokens, num_tokens * sizeof(Token *));
          tokens[num_tokens - 1] = t;          
        }
        break;
      case '(':
        {
          Token* t = create_token("LPAREN", "(");
          num_tokens++;
          tokens = realloc(tokens, num_tokens * sizeof(Token *));
          tokens[num_tokens - 1] = t;          
        }
        break;
      case ')':
        {
          Token* t = create_token("RPAREN", ")");
          num_tokens++;
          tokens = realloc(tokens, num_tokens * sizeof(Token *));
          tokens[num_tokens - 1] = t;          
        }
        break;
      default:
        if (is_numeric(c)) {
          char *str_num = malloc(sizeof(char));
          int buffer_idx = 0;
          while ((is_numeric(c) || c == '.') & (cursor < stream_length)) {
            str_num[buffer_idx] = c;
            cursor++;
            buffer_idx++;
            c = stream[cursor];
            str_num = realloc(str_num, buffer_idx* sizeof(char));
          }

          {
            Token* t = create_token("NUMBER", str_num);
            num_tokens++;
            tokens = realloc(tokens, num_tokens * sizeof(Token *));
            tokens[num_tokens - 1] = t;
          }
          cursor--;
        }      
    }
    cursor++;
  }

  *size = num_tokens;
  return tokens;
}