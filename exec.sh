#!/bin/bash

for i in {3..14}
do
	#let ii=i-5
	for j in $(seq 3 1 16)
	do
		./prg -m 14 -n $j -k $i -onlycoverage
		printf "\t"
	done
	printf "\n"
done
