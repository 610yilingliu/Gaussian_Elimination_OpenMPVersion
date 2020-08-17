OBJ     =   main.o eliminate.o generator.o swap.o
PROJECT =   ge
CFLAGS = -fopenmp
C99 = gcc -std=c99
INC = -I./heads

$(PROJECT) : $(OBJ)
	$(C99) $(CFLAGS) $(INC) -o $(PROJECT) $(OBJ) -lm

main.o : main.c
	$(C99) $(CFLAGS) -c main.c

eliminate.o : eliminate.c
	$(C99) $(CFLAGS) -c eliminate.c

generator.o : generator.c
	$(C99) $(CFLAGS) -c generator.c

swap.o : swap.c
	$(C99) $(CFLAGS) -c swap.c
clean:
	@echo "Cleaning up..."
	rm *.o
	rm *.exe