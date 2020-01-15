# ------------------------------------------------------------
# * Authors: Oulis Evangelos & Kalliopi Voudouri
# *          711151051         46577
# ------------------------------------------------------------
all:
	gcc -o prg prg.c add.c binaryToString.c gray_code.c counter.c lfsr.c -lm -O3 -w
	./prg
run:
	./prg
clean:
	rm prg
