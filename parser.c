/**@<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>
#include <lexer.h>
#include <parser.h>

int lookahead;

/***
 * gramática:
 * E -> [unary] DEC | ID | (E) { mulop DEC | ID | (E) } { addop T }
 * unary = '+' | '-'
 * addop = '+' | '-'
 * mulop = '*' | '/'
***/

/* unary = '+' | '-' */
int unary (void)
{
  switch (lookahead) {
  case '+':
  case '-':
    return 1;
  }
  return 0;
}

/* addop = '+' | '-' */
int addop (void)
{
  switch (lookahead) {
  case '+':
  case '-':
    return 1;
  default:
    break;
  }
  return 0;
}

/* mulop = '*' | '/' */
int mulop (void)
{
  switch (lookahead) {
  case '*':
  case '/':
    return 1;
  default:
    break;
  }
  return 0;
}

/* E -> [unary] T R */
void E (void)
{
  /**/int ominus = 0, oplus = 0, otimes = 0;/**/
  
  if (unary ()){
	/**/ominus = lookahead;/**/
    match (lookahead);
  }
 
_T:
_F:
  // lookahead: var que o parser usa para identificar os tokens
  switch (lookahead) {
  case DEC:
    fprintf (stderr, "decimal\n");
    printf("%s ", lexeme);
    match (DEC);
    break;
  case OCT:
    fprintf (stderr, "octal\n");
    printf("%s ", lexeme);
    match (OCT);
    break;
  case HEX:
    fprintf (stderr, "hexadecimal\n");
    printf("%s ", lexeme);
    match (HEX);
    break;
  case FLT:
    fprintf (stderr, "float\n");
    printf("%s ", lexeme);
    match (FLT);
    break;
  case ID:
    fprintf (stderr, "ID\n");
    printf("%s ", lexeme);
    match (ID);
    break;
  default:
    match ('(');
    E ();
    match (')');
    break;
  }
  
  // antes de chamar mulop de novo: recebeu o 2º operando
  /**/
  if(otimes) {
	  printf("%c ", otimes);
	  otimes = 0;
  }
  /**/

  if (mulop ()) {
	/**/otimes = lookahead;/**/
    match (lookahead);
    goto _F;
  }
  
  //fim de T: imprime ominus
  /**/
  if(ominus) {
	   if(ominus == '-') printf("%c ", ominus);
	   // "desligar" a flag
	   ominus = 0;
  }
  /**/

  // antes de chamar addop de novo
  if(oplus) {
	  printf("%c ", oplus);
	  oplus = 0;
  }

  if (addop ()) {
	/**/oplus = lookahead;/**/
    match (lookahead);
    goto _T;
  }
}

// match: ver se o token é o esperado
void match (int expected)
{
  if (expected == lookahead) {
    lookahead = gettoken (source);
  }
  else {
    // erro
    fprintf (stderr, "Token mismatch\n");
    exit (-2);
  }
}
