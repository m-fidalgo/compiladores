/**@<main.c>::**/
#include <stdio.h>
#include <main.h>

FILE *source;

extern double acc;

int main (int argc, const char *argv[])
{
  source = stdin;
  lookahead = gettoken (source);
  mybc();

  return 0;
}
