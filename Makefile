# ------------------------------------------------------------
# * Authors: Oulis Evangelos & Kalliopi Voudouri
# *          711151051         46577
# ------------------------------------------------------------
all:
	gcc -o prg prg.c add.c binaryToString.c -lm -O3 -w
	./prg
clean:
	rm prg
