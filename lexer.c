/**@<lexer.c>::**/
#include <stdio.h>
#include <ctype.h>
#include <tokens.h>
#include <lexer.h>

// contador de linhas
int lineNumber = 0;

void skipSpaces (FILE * tape)
{
  int head;
  while (isspace (head = getc (tape))) {
    if (head == '\n')
      lineNumber++;
  }
  ungetc (head, tape);
}

/** ID = [A-Za-z][A-Za-z0-9]* **/
int isID (FILE * tape)
{
  int head;
  if (isalpha (head = getc (tape))) {
    // fecho de kleene
    while (isalnum (head = getc (tape)));
    ungetc (head, tape);
    return ID;
  }
  ungetc (head, tape);
  return 0;
}

// DEC, OCT ou HEX
int isINT (FILE * tape)
{
  int head;

  if (isdigit (head = getc (tape))) {
    if (head == '0') {
      // octal: 0[0-7][0-7]*
      if ('0' <= (head = getc (tape)) && head <= '8') {
	while ('0' <= (head = getc (tape)) && head <= '8');
	ungetc (head, tape);
	return OCT;
      }
      ungetc (head, tape);

      // hexadecimal: 0[xX][0-9A-Fa-f][0-9A-Fa-f]*
      int x = getc (tape);
      if (toupper (x) == 'X') {
	if (isxdigit (x = getc (tape))) {
	  while (isxdigit (head = getc (tape)));
	  ungetc (head, tape);
	  return HEX;
	}
	ungetc (head, tape);
      }
      ungetc (x, tape);
      return DEC;
    }

    // fecho de kleene
    while (isdigit (head = getc (tape)));
    ungetc (head, tape);
    return DEC;
  }
  ungetc (head, tape);
  return 0;
}

// EE = [eE] ['+''-']? [0-9][0-9]*
int isEE (FILE * tape)
{
  int ch, e, pm;

  if (toupper (e = getc (tape)) == 'E') {
    if ((pm = getc (tape)) != '+' && pm != '-') {
      ungetc (pm, tape);
      pm = 0;
    }

    if (isdigit (ch = getc (tape))) {
      while (isdigit (ch = getc (tape)));
      ungetc (ch, tape);
      return 1;
    }

    ungetc (ch, tape);
    if (pm)
      ungetc (pm, tape);
  }

  ungetc (e, tape);
  return 0;
}

// NUM = ( DEC | DEC '.'[0-9]* | '.'[0-9][0-9]* ) EE?
int isNUM (FILE * tape)
{
  int dec = isINT (tape);
  int token = 0;
  int ch;

  switch (dec) {
  case OCT:
  case HEX:
    return dec;
  }

  if (dec) {
    token = dec;
    if ((ch = getc (tape)) == '.') {
      token = FLT;
      while (isdigit (ch = getc (tape)));
      ungetc (ch, tape);
    }
    else {
      ungetc (ch, tape);
    }
  }
  else {
    if ((ch = getc (tape)) == '.') {
      if (isdigit (ch = getc (tape))) {
	token = FLT;
	while (isdigit (ch = getc (tape)));
	ungetc (ch, tape);
      }
      else {
	ungetc (ch, tape);
	ungetc ('.', tape);
      }
    }
    else {
      ungetc (ch, tape);
    }

  }
  if (token) {
    if (isEE (tape)) {
      token = FLT;
    }
  }
  return token;
}

int gettoken (FILE * source)
{
  int token;
  skipSpaces (source);

  if (token = isID (source))
    return token;
  if (token = isNUM (source))
    return token;

  token = getc (source);
  return token;
}
