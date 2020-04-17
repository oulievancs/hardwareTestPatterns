#!/bin/bash

for i in {3..14}
do
	for j in $(seq 2 1 $i)
	do
		./prg -m 16 -n $j -k $i -onlycoverage
		printf "\t"
	done
	printf "\n"
done
