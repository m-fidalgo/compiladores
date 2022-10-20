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
 * E -> [unary] T { addop T }
 * T -> F { mulop F } 
 * F -> DEC | OCT | HEX | FLT | ID [ = E ] | (E)
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

/* E -> [unary] T { addop T } */
void E (void)
{
	/**/int ominus = 0, oplus = 0;/**/

  if(unary ()){
    /**/if(lookahead == '-') ominus = lookahead;/**/
    match(lookahead);
  }

  T();

  /**/
  if(ominus) {
    acc *= -1;
    ominus = 0;
  }
  /**/

  while(addop ()) {
    /**/oplus = lookahead; push();/**/
    match (lookahead);
    T ();
  
  /**/
  switch(oplus) {
		case '+':
			acc = pop() + acc;
			break;
		default:
			acc = pop() - acc;
			break;
	}
  /**/
  }
}

/* T -> F { mulop F } */
void T (void)
{
  /**/int otimes = 0;/**/

  F();

  while (mulop ()) {
    /**/otimes = lookahead; push();/**/
    match (lookahead);
    F ();

  /**/
	switch(otimes) {
		case '*':
			acc = pop() * acc;
			break;
		default:
			acc = pop() / acc;
			break;
	}
  /**/
	}
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

// match: ver se o token é o esperado
void match (int expected)
{
  if (expected == lookahead) {
    lookahead = gettoken (source);
  }
  else {
    fprintf (stderr, "Token mismatch\n");
    exit (-2);
  }
}
