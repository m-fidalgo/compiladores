/**@<lexer.c>::**/
#include <stdio.h>
#include <ctype.h>
#include <tokens.h>
#include <lexer.h>

// contador de linhas
int lineNumber = 0;

void skipSpaces(FILE *tape) {
	int head;
	while (isspace(head = getc(tape))) {
		if(head == '\n') lineNumber++;
	}
	ungetc(head, tape);
}

/** ID = [A-Za-z][A-Za-z0-9]* **/
int isID(FILE *tape) {
	int head;
	if (isalpha(head = getc(tape))) {
		// fecho de kleene
		while (isalnum(head = getc(tape)));
		ungetc(head, tape);
		return ID;
	}
	ungetc(head, tape);
	return 0;
}

/** DEC = [1-9][0-9]* **/
int isNum(FILE *tape) {
	int head;
	if (isdigit(head = getc(tape))) {
		if (head == '0') {
			if ('0'<= (head = getc(tape)) && head <= '8') {
				while ('0' <= (head = getc(tape)) && head <= '8');
				ungetc(head, tape);
				return OCT;
			}

			if(isxdigit(head = getc(tape))) {
				while(isxdigit(head = getc(tape)));
				ungetc(head, tape);
				return HEX;	
			}
			return DEC;
		}
		
		// fecho de kleene
		while(isdigit(head = getc(tape)));
		ungetc(head, tape);
		return DEC;
	}
	ungetc(head, tape);
	return 0;
}

int gettoken(FILE *source) {
	int token;
	skipSpaces(source);

	if (token = isID(source)) return token;
	if (token = isNum(source)) return token;

	token = getc(source);
	return token;
}
