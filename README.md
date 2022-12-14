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

<h3>Rodar</h3>

```
echo "a + b" | ./expr
./expr a + b
```

<h3>Aulas</h3>
<ul>
<li><a href="https://github.com/m-fidalgo/compiladores/tree/aula-01">Aula 01</a>: Funções básicas do lexer e parser</li>
<li>Aula 03: <a href="https://github.com/m-fidalgo/compiladores/tree/aula-03">Versão 0</a>, <a href="https://github.com/m-fidalgo/compiladores/tree/aula-03.1">Versão 1</a> e <a href="https://github.com/m-fidalgo/compiladores/tree/aula-03.2">Versão 2</a></li>
<li><a href="https://github.com/m-fidalgo/compiladores/tree/aula-04">Aula 04</a>: uso de <b>lexeme</b></li>
<li>Aula 05: implementação de um compilador posfixo, com uso de diagramas sintáticos com a gramática LL(1) (<a href="https://github.com/m-fidalgo/compiladores/tree/aula-05">Versão 0</a>) e com a gramática na forma EBNF (<a href="https://github.com/m-fidalgo/compiladores/tree/aula-05.1">Versão 1</a>)</li>
<li>Aula 06: na <a href="https://github.com/m-fidalgo/compiladores/tree/aula-06">Versão 0</a> foi incrementado o compilador posfixo da Aula 05, adicionando atribuição. Na <a href="https://github.com/m-fidalgo/compiladores/tree/aula-06.1">Versão 1</a>, foi implementada uma calculadora simples, usando a forma EBNF na <a href="https://github.com/m-fidalgo/compiladores/tree/aula-06.2">Versão 2</a>.</li>
<li>Aula 07: na <a href="https://github.com/m-fidalgo/compiladores/tree/aula-07">Versão 0</a> foi trabalhada a calculadora simples da Aula 06, com uso de tabela de símbolos. Na <a href="https://github.com/m-fidalgo/compiladores/tree/aula-07.1">Versão 1</a> e <a href="https://github.com/m-fidalgo/compiladores/tree/aula-07.2">Versão 2</a>, ela foi alterada para uso da forma EBNF (parcial e total)</li>
</ul>
