LIB = fueldb.c
 
# C++ compiler flags
CCFLAGS = -O2 -Wall
 
# compiler
CCC = gcc
 
.SUFFIXES: .c
 
default: test
 
test:
	$(CCC) $(CCFLAGS) $(LIB) test.c -o test.out
 
clean:
	rm -f *.out