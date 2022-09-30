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
void unary(void) {
	switch(lookahead) {
		case '+':
		case '-':
			match(lookahead);
			break;
		default:
			break;
	}
}

/* addop = '+' | '-' */
int addop(void) {
	switch(lookahead) {
		case '+':
		case '-':
			match(lookahead);
			return 1;
		default:
			break;
	}
	return 0;
}

/* mulop = '*' | '/' */
int mulop(void) {
	switch(lookahead) {
		case '*':
		case '/':
			match(lookahead);
			return 1;
		default:
			break;
	}
	return 0;
}

/* E -> unary T R */
void E(void) {
	unary(); T(); R();
}

/* T -> F Q */
void T(void) {
	F(); Q();
}

/* F -> DEC | ID | (E) */
void F(void) {
	// lookahead: var que o parser usa para identificar os tokens
	switch(lookahead) {
		case DEC:
			match(DEC);
			break;
		case ID:
			match(ID);
			break;
		default:
			match('(');
			E();
			match(')');
			break;
	}
}

/* R -> addop T R | <empty> */
void R(void) {
	if(addop()) {
		T(); R();
	}
}

/* Q -> mulop F Q | <empty> */
void Q(void) {
	if(mulop()) {
		F(); Q();
	}
}

// match: ver se o token é o esperado
void match(int expected) {
	if(expected == lookahead) {
		lookahead = gettoken(source);
	} else {
		// erro
		fprintf(stderr, "Token mismatch\n");
		exit(-2);
	}
}
