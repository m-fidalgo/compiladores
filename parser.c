/**@<parser.c>::**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tokens.h>
#include <lexer.h>
#include <parser.h>

#define STACKSIZE 1024
#define SYMTABSIZE 1024

char symtab[SYMTABSIZE][MAXIDLEN+1];
double acc;
double stack[STACKSIZE];
double vmemory[SYMTABSIZE];
int symtab_next = 0;
int sp = -1;
int iaux;
int lookahead;

void push(void) {
	sp++;
	stack[sp] = acc;
}

double pop(void) {
	double aux = stack[sp];
  sp--;
  return aux;
}

int symtab_lookup(char const *name) {
  int i;
  for(i=0; i<symtab_next; i++)
    if(strcmp(symtab[i], name) == 0) return i;
  return -1;
}

int symtab_append(char const *name) {
  strcpy(symtab[symtab_next], name);
  return symtab_next++;
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
  }
  return 0;
}

/* E -> [unary] T { addop T } */
void E (void)
{
	/**/int ominus = 0, oplus = 0, otimes = 0;/**/

  if(unary ()){
    /**/if(lookahead == '-') ominus = lookahead;/**/
    match(lookahead);
  }

_T:
_F:
  F();
  /**/
  if(otimes) {
    switch(otimes) {
      case '*':
        acc = pop() * acc;
        break;
      default:
        acc = pop() / acc;
        break;
    }
    otimes = 0;
  }  
  /**/

  if (mulop ()) {
    /**/otimes = lookahead; push();/**/
    match (lookahead);
    goto _F;
	}

  /**/
  if(ominus) {
    acc *= -1;
    ominus = 0;
  }
  /**/

  /**/
  if(oplus) {
    switch(oplus) {
      case '+':
        acc = pop() + acc;
        break;
      default:
        acc = pop() - acc;
        break;
    }
    oplus = 0;
  }
  /**/

  if(addop ()) {
    /**/oplus = lookahead; push();/**/
    match (lookahead);
    goto _T;
  }
}

/* F -> DEC | OCT | HEX | FLT | ID [ = E ] | (E) */
void F (void)
{
  /**/char varname[MAXIDLEN+1];/**/
  /**/int vaddress;/**/

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
    /**/vaddress = symtab_lookup(varname);/**/
    /**/if(vaddress < 0) vaddress = symtab_append(varname);/**/
    match (ID);
    
    // permitir atribuição
    if(lookahead == '=') {
		  match('=');
		  E();
		  /**/vmemory[vaddress] = acc;/**/ //store
	  } else {
		  /**/acc = vmemory[vaddress];/**/ //recall
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

/* mybc -> E \n mybc | E ; mybc | \n mybc | ; mybc | EOF */
void mybc(void) {
  while(lookahead != EOF) {
    if(lookahead == '\n' || lookahead == ';') {
      match(lookahead);
    } else {
      E();
      /**/printf("%lg\n", acc);/**/
      if(lookahead == '\n') match('\n');
      else match(';');
    }
  }
  //match(EOF); //opcional
}

// match: ver se o token é o esperado
void match (int expected)
{
  if (expected == lookahead) {
    lookahead = gettoken (source);
  }
  else {
    fprintf (stderr, "Token mismatch\n");
    mybc();
  }
}
