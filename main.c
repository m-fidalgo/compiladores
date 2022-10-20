/**@<main.c>::**/
#include <stdio.h>
#include <main.h>

FILE *source;

extern double acc;

int main (int argc, const char *argv[])
{
  source = stdin;
  lookahead = gettoken (source);
  E ();
  printf("%lg\n", acc);

  return 0;
}
