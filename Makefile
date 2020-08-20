#Mekefile 
CC = clang
CFLAGS = -Wall
OBJ = hospital
all:
    $(CC) $(CFLAGS) -wall hospitalTarea1.c -o $(OBJ)
exec:
    ./hospital
clean:
    rm -rf hospital
    rm -rf *.exe
    rm -rf *.o