/**@<parser.h>::**/
extern FILE *source;
extern int lookahead;

extern int gettoken(FILE *);
extern int unary(void);
extern int addop(void);
extern int mulop(void);
extern void E(void);
extern void T(void);
extern void F(void);
extern void R(void);
extern void Q(void);
extern void match(int expected);
