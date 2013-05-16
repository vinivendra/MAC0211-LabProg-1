execName = ep2
execOptions =  -g -o $(execName) -lm -lc
objOptions = -g -pedantic -Wall -lm -lc
objects = main.o PrintASCII.o grade.o rio.o util.o pixel.o


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

pixel.o: pixel.c
	gcc -c pixel.c $(objOptions)

teste: teste.o rotinasTeste.o
	gcc -Wall -pedantic -g rotinasTeste.o grade.o rio.o util.o pixel.o teste.o -o teste -lm -lc

teste.o: teste.c
	gcc -c teste.c $(objOptions)

rotinasTeste.o: rotinasTeste.c
	gcc -c rotinasTeste.c $(objOptions)

clean:
	rm -f *.o $(execName)
