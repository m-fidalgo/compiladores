<h1 align="center">Aula 01</h1>

<h3>Anotações</h3>

<h3>Makefile</h3>

```
CFLAGS = -I. -g
expr: main.o lexer.o parser.o
	$(CC) -o $@ $^

clean:
	$(RM) *.o
	
mostlyclean: clean
	$(RM) expr *-
```

<h3>Executar</h3>

```
echo "a + b" | ./expr
./expr a + b
```