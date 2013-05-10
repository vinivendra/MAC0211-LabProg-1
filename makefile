execName = ep2
execOptions =  -g -o $(execName) -lm -lc
objOptions = -g -ansi -pedantic -Wall -lm -lc
objects = main.o PrintASCII.o grade.o rio.o util.o


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

util.o: util.c
	gcc -c util.c $(objOptions)

clean:
	rm -f *.o $(execName)
