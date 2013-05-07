execName = ep2
execOptions =  -g -o $(execName) -lm
objOptions = -g -ansi -pedantic -Wall
objects = main.o PrintASCII.o grade.o rio.o


.PHONY:ascii
ascii: $(objects)
	gcc $(objects) $(execOptions)

main.o: main.c
	gcc -c main.c $(objOptions)

PrintASCII.o: PrintASCII.c
	gcc -c PrintASCII.c $(objOptions)
    
grade.o: grade.c
	gcc -c grade.c $(objOptions)

rio.o: rio.c
	gcc -c rio.c $(objOptions)

clean:
	rm -f *.o $(execName)
