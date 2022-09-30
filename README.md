<h1 align="center">Compiladores</h1>
<p align="center"><img src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C" /></p>

<h3>Sobre</h3>
<p>As aulas trabalham sobre a gramática de expressões</p>

```
E -> unary T R
T -> F Q
F -> DEC | ID | (E)
R -> addop T R | <empty>
Q -> mulop F Q | <empty>
unary = '+' | '-'
addop = '+' | '-'
mulop = '*' | '/'
```

<h3>Aulas</h3>
<ul>
<li>Aula 01: Funções básicas do lexer e parser</li>
</ul>