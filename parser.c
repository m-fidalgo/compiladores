/**@<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokens.h>
#include <lexer.h>
#include <parser.h>

#define STACKSIZE 1024

double acc;
double stack[STACKSIZE];
int sp = -1;
int iaux;
int lookahead;

void push(void) {
	sp++;
	stack[sp] = acc;
}

double pop(void) {
	return stack[sp--];
}


/***
 * gramática:
 * E -> unary T R | T R
 * T -> F Q
 * F -> DEC | OCT | HEX | FLT | ID [ = E ] | (E)
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
    /**/if(op) acc *= -1;/**/
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

/* F -> DEC | OCT | HEX | FLT | ID [ = E ] | (E) */
void F (void)
{
  /**/char varname[MAXIDLEN+1];/**/
  // lookahead: var que o parser usa para identificar os tokens
  switch (lookahead) {
  case DEC:
	/**/acc = atoi(lexeme);/**/
    match (DEC);
    break;
  case OCT:
	/**/sscanf(lexeme, "%o", iaux);/**/
	/**/acc = iaux;/**/
    match (OCT);
    break;
  case HEX:
	/**/sscanf(lexeme, "%x", iaux);/**/
	/**/acc = iaux;/**/
    match (HEX);
    break;
  case FLT:
	/**/acc = atof(lexeme);/**/
    match (FLT);
    break;
  case ID:
    /**/strcpy(varname, lexeme);/**/
    match (ID);
    
    // permitir atribuição
    if(lookahead == '=') {
		match('=');
		E();
		/**/printf("%s store ", varname);/**/
	} else {
		/**/printf("%s ", varname);/**/
		;
	}
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
	/**/op = lookahead; push();/**/
    match (lookahead);
    T ();
    /**/
	switch(op) {
		case '+':
			acc = pop() + acc;
			break;
		default:
			acc = pop() - acc;
			break;
	}
    /**/
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
    /**/op = lookahead; push();/**/
    match (lookahead);
    F ();
    /**/
	switch(op) {
		case '*':
			acc = pop() * acc;
			break;
		default:
			acc = pop() / acc;
			break;
	}
    /**/
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
