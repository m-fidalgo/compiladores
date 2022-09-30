/**@<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>
#include <parser.h>

int lookahead;

/***
 * gramática:
 * E -> [unary] T { addop T }
 * T -> F { mulop F }
 * F -> DEC | ID | (E)
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
  if(unary ()) match(lookahead);
  T ();
  
  // R
  while (addop ()) {
    match (lookahead);
    T ();
  }

  // FOLLOW(R) = { ')', EOF }
  switch (lookahead) {
  case ')':
    break;
  case EOF:
    break;
  default:
    fprintf (stderr,
	     "Token exceeding context in expression, lookahead = %d\n",
	     lookahead);
    exit (-3);
    break;
  }
}

/* T -> F Q */
void T (void)
{
  F ();
  
  // Q
  while (mulop ()) {
    match (lookahead);
    F ();
  }

  // FOLLOW(Q) = { '+', '-', ')', EOF }
  switch (lookahead) {
  case '+':
    break;
  case '-':
    break;
  case ')':
    break;
  case EOF:
    break;
  default:
    fprintf (stderr,
	     "Token exceeding context in term, lookahead = %d\n", lookahead);
    exit (-3);
    break;
  }
}

/* F -> DEC | ID | (E) */
void F (void)
{
  // lookahead: var que o parser usa para identificar os tokens
  switch (lookahead) {
  case DEC:
    //fprintf (stderr, "decimal\n");
    match (DEC);
    break;
  case OCT:
    //fprintf (stderr, "octal\n");
    match (OCT);
    break;
  case HEX:
    //fprintf (stderr, "hexadecimal\n");
    match (HEX);
    break;
  case FLT:
    //fprintf (stderr, "float\n");
    match (FLT);
    break;
  case ID:
    match (ID);
    break;
  default:
    match ('(');
    E ();
    match (')');
    break;
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
