rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

bin=bin
src=src
obj=obj
flags=-Wall -std=c11 -ggdb -O3

dirs:=$(sort $(dir $(call rwildcard,$(src)/*/,*)))

prog=$(bin)/StudyHelper

default: cleanobj init all move

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
	-rm $(bin)/Lesson*
	-rm ./StudyHelper*
	-rm ./Lesson*
	-del $(obj)\*.o
	-del $(bin)\*.exe
	-del .\*.exe

cleanobj:
	-rm $(obj)/*.o
	-del $(obj)\*.o

binary: $(prog)
	$(foreach x,$(dirs),$(call innerprogram,$(x)))
	
$(obj)/main.o: $(src)/main.c
	gcc -c -o $(obj)/main.o $(src)/main.c $(flags)
	
$(prog): $(obj)/main.o
	gcc -o $(prog) $(obj)/main.o $(flags)
	
define innerprogram

-rm $(obj)/*.o
-del $(obj)\*.o
gcc -c -o $(obj)/$(patsubst %.c,%.o,$(notdir $(call rwildcard,$1,*.c))) $(call rwildcard,$1,*.c) $(flags)
gcc -o $(bin)/Lesson$(notdir $(patsubst %/,%,$1)) $(obj)/*.o $(flags)
	
endef
	
		
