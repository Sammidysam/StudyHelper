bin=bin
src=src
obj=obj
head=$(src)/boolean.h $(src)/input.h

cc=gcc
prog=$(bin)/StudyHelper

default: init all

init:
	mkdir -p obj
	mkdir -p bin

all: binary
	ln -s $(prog) StudyHelper
	
clean:
	rm -f $(obj)/*.o
	rm -f $(bin)/StudyHelper*
	rm -f StudyHelper*

binary: $(prog)
	
$(obj)/main.o: $(head) $(src)/main.c
	$(cc) -c -o $(obj)/main.o $(src)/main.c -O3
	
$(prog): $(obj)/main.o
	$(cc) -o $(prog) $(obj)/main.o -O3
