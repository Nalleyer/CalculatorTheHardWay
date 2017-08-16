# Calculate The Hard Way

a simple arithmetic calculator, written in c++, implementing a lexer, a recursive decent ll(2) parser, and a visitor for compiling ast.

# Usage

```
./PROG_NAME input.txt
```

# example

input.txt:

```
pi = 3.1416
r = 123
area = pi * ( r * r )
area
```

(assuming that the excutable is named calc.exe)

```
> calc.exe input.txt
> 229998.995232
```

you will get

