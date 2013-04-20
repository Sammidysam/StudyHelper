bin=bin
src=src
obj=obj
head=$(src)/boolean.h $(src)/input.h

cc=gcc
prog=$(bin)/StudyHelper

all: binary

binary: $(prog)
	
$(obj)/main.o: $(head) $(src)/main.c
	$(cc) -c -o $(obj)/main.o $(src)/main.c -O3
	
$(prog): $(obj)/main.o
	$(cc) -o $(prog) $(obj)/main.o -O3