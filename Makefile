all:
	gcc -o prg prg.c nor.c and.c -lm -O3
	./prg
clean:
	rm prg
