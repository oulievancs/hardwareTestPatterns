#!/bin/bash

for i in {3..14}
do
	for j in {3..16}
	do
		./prg -m 15 -n $j -k $i -onlycoverage
		printf " "
	done
	printf "\n"
done
