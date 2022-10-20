CFLAGS = -I. -g

expr: main.o lexer.o parser.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o
	
mostlyclean: clean
	$(RM) expr *~
