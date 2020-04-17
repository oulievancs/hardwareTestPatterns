# ------------------------------------------------------------
# * Authors: Oulis Evangelos & Kalliopi Voudouri
# *          711151051         46577
# ------------------------------------------------------------
all:
	gcc -o prg prg.c add.c binaryToString.c gray_code.c counter.c lfsr.c nfsr.c shift.c -lm -O3 -w
	
	gcc -o prg1 prg1.c -O3
run:
	./prg
clean:
	rm prg

