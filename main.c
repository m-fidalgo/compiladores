/**@<main.c>::**/
#include <stdio.h>
#include <main.h>

FILE *source;

int main (int argc, const char *argv[])
{
  source = stdin;
  lookahead = gettoken (source);
  E ();

  return 0;
}
