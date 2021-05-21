/**
 File: lexer.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "lexer.h"

extern Token* tk;

Lexer* lexer_init(char *filename, char *input)
{
  #ifdef DEBUG
    printf("[lexer_init]\n");
  #endif

  Lexer* lex = malloc(sizeof(Lexer));
  lex->f = filename;
  lex->s = input;
  lex->tokens = vector_create();

  #ifdef DEBUG
    printf("-->%s\n", lex->s);
    printf("-->%s\n", lex->f);
    printf("\n");
  #endif

  return lex;
}

void lexer_get(Lexer* lex)
{
  token_init(lex);

  #ifdef DEBUG
    printf("[lexer_get]\n");
  #endif

  Token *t;
  while(token_is_end(lex) == true) {
    t = token_getnext(lex);
    vector_add(&lex->tokens, t);

    #ifdef DEBUG
      printf("[lexer_get]");
      tok_log(t);
    #endif
  }
}

void lexer_except(Lexer* lex, char tt)
{
  Token* t = token_get(lex);
  if(t->type == tt) token_getnext(lex);
  else
    error("Except token %c but we get %c", tt, t->type);
}

// Lexer

void lexer_statement(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_statement]");
    tok_log(tk);
  #endif
  token_getnext(lex);
}

void lexer_statements(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_statements]\n");
  #endif
  lexer_except(lex, '{');
  while(tk->type != '}') {
    lexer_statement(lex);
  }

  #ifdef DEBUG
    printf("\n");
  #endif
}

void lexer_start(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_start]\n");
  #endif

  lexer_get(lex);
  scanner_parse(lex);
}