# source files.
SRC = fueldb.c
 
OBJ = $(SRC:.c=.o)
 
OUT = libfueldb.a
 
.SUFFIXES: .c
 
default: $(OUT)
 
$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
 
clean:
	rm -f $(OBJ) $(OUT)