#!/bin/bash

for i in {12..14}
do
	for j in {14..16}
	do
		./prg -m 7 -bit 1 -n $j -k $i -onlycoverage
		printf "\t"
	done
	printf "\n"
done
