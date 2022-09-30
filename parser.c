/**@<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>
#include <parser.h>

int lookahead;

/***
 * gramática:
 * E -> unary T R
 * T -> F Q
 * F -> DEC | ID | (E)
 * R -> addop T R | <empty>
 * Q -> mulop F Q | <empty>
 * unary = '+' | '-'
 * addop = '+' | '-'
 * mulop = '*' | '/'
***/

/* unary = '+' | '-' */
void unary (void)
{
  switch (lookahead) {
  case '+':
  case '-':
    match (lookahead);
    break;
  default:
    break;
  }
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

/* E -> unary T R */
void E (void)
{
  unary ();
  T ();
  R ();
}

/* T -> F Q */
void T (void)
{
  F ();
  Q ();
}

/* F -> DEC | ID | (E) */
void F (void)
{
  // lookahead: var que o parser usa para identificar os tokens
  switch (lookahead) {
  case DEC:
    fprintf (stderr, "decimal\n");
    match (DEC);
    break;
  case OCT:
    fprintf (stderr, "octal\n");
    match (OCT);
    break;
  case HEX:
    fprintf (stderr, "hexadecimal\n");
    match (HEX);
    break;
  case FLT:
    fprintf (stderr, "float\n");
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

/* R -> addop T R | <empty> */
void R (void)
{
  if (addop ()) {
    match (lookahead);
    T ();
    R ();
  }
  else {
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
}

/* Q -> mulop F Q | <empty> */
void Q (void)
{
  if (mulop ()) {
    match (lookahead);
    F ();
    Q ();
  }
  else {
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
	       "Token exceeding context in term, lookahead = %d\n",
	       lookahead);
      exit (-3);
      break;
    }
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
