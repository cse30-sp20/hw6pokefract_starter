#
# CSE30 Makefile
#
# we declare the object we want to build in the variable EXE
# we list the objects we want to compile (from c) in OBJS
#
# we provide a phony target clean to rm all the .o files
#

EXE = fract
OBJS = main.o fractals.o copyTriangle.o
LIBS = 
CC = gcc 
CFLAGS = -g -O0
CFLAGS +=  --std=gnu99

.PHONY: clean

$(EXE) : $(OBJS)
	gcc -o $@ $(CFLAGS) $(OBJS) $(LIBS)
	rm -f $(OBJS)

main.o : main.c fractals.o copyTriangle.o
fractals.o: fractals.c copyTriangle.o 
copyTriangle.o: copyTriangle.S
	gcc -c $(CFLAGS) -gstabs+ copyTriangle.S

clean :
	rm -f $(OBJS)
	rm $(EXE)