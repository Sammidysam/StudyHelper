rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

bin=bin
src=src
obj=obj
sources:=$(call rwildcard,$(src)/*/,*.c)
headers:=$(call rwildcard,$(src)/*/,*.h)
innerprogram=$(bin)/Spanish

prog=$(bin)/StudyHelper

default: init all move

init:
	-mkdir obj
	-mkdir bin

all: binary
	
move:
	-cp $(bin)/* .
	-copy $(bin)\* .
	
clean:
	-rm $(obj)/*.o
	-rm $(bin)/StudyHelper*
	-rm ./StudyHelper*
	-del $(obj)\*.o
	-del $(bin)\StudyHelper*
	-del .\StudyHelper*

binary: $(prog) $(innerprogram)

test:
	echo $(sources)
	echo $(headers)
	
$(obj)/main.o: $(src)/main.c
	gcc -c -o $(obj)/main.o $(src)/main.c -O3
	
$(prog): $(obj)/main.o
	gcc -o $(prog) $(obj)/main.o -O3
	
$(obj)/lesson.o: $(sources) $(headers)
	gcc -c -o $(obj)/lesson.o $(sources) -O3

$(innerprogram): $(obj)/lesson.o
	gcc -o $(innerprogram) $(obj)/lesson.o -O3
