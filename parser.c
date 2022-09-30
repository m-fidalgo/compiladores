/**@<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <tokens.h>
#include <lexer.h>
#include <parser.h>

int lookahead;

/***
 * gramática:
 * E -> unary T R | T R
 * T -> F Q
 * F -> DEC | OCT | HEX | FLT | ID | (E)
 * R -> addop T R | <empty>
 * Q -> mulop F Q | <empty>
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
    return lookahead;
  default:
    break;
  }
  return 0;
}

/* addop = '+' | '-' */
int addop (void)
{
  switch (lookahead) {
  case '+':
  case '-':
    return lookahead;
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
    return lookahead;
  default:
    break;
  }
  return 0;
}

/* E -> unary T R | T R */
void E (void)
{
	/**/int op = 0;/**/
  if(unary ()){
    if(lookahead == '-') op = lookahead;
    match(lookahead);
    T();
    /**/if(op) printf("%c ", op);/**/
    R();
  } else {
    T ();
    R ();
  }
}

/* T -> F Q */
void T (void)
{
  F ();
  Q ();
}

/* F -> DEC | OCT | HEX | FLT | ID | (E) */
void F (void)
{
  // lookahead: var que o parser usa para identificar os tokens
  switch (lookahead) {
  case DEC:
    //fprintf (stderr, "decimal\n");
    /**/printf("%s ", lexeme);/**/
    match (DEC);
    break;
  case OCT:
    //fprintf (stderr, "octal\n");
    /**/printf("%s ", lexeme);/**/
    match (OCT);
    break;
  case HEX:
    //fprintf (stderr, "hexadecimal\n");
    /**/printf("%s ", lexeme);/**/
    match (HEX);
    break;
  case FLT:
    //fprintf (stderr, "float\n");
    /**/printf("%s ", lexeme);/**/
    match (FLT);
    break;
  case ID:
    //fprintf (stderr, "ID\n");
    /**/printf("%s ", lexeme);/**/
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
	/**/int op = 0;/**/
  if (addop ()) {
		/**/op = lookahead;/**/
    match (lookahead);
    T ();
    /**/printf("%c ", op);/**/
    R ();
  } else {
		;
	}
}

/* Q -> mulop F Q | <empty> */
void Q (void)
{
	/**/int op = 0;/**/
  if (mulop ()) {
    /**/op = lookahead;/**/
    match (lookahead);
    F ();
    /**/printf("%c ", op);/**/
    Q ();
  } else {
		;
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
