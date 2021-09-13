This is an implementation of Hierholzers algorithm used to find a path.

The program expects to read from a text file with nodes written line by line,
followed by a blank line, followed by the connections, separated by a tab.
Here is an example:
A
B
C
D
E

A	E
A	B
B	C
C	D
D	E
In this instance, the program will create the file answers.txt
with the path A->E->D->C->B->A

To the program comes bundled with a makefile and a file structure,
but this can be changed at will if you use the program.