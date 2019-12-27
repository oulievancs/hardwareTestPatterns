all:
	gcc -o prg prg.c add.c binaryToString.c -lm -O3
	./prg -f accumulator.test
clean:
	rm prg
