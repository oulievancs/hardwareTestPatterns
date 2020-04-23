#!/bin/bash

for i in {11..12}
do
	let ii=i-9
	for j in $(seq 2 1 $ii)
	do
		./prg -m 19 -bit 9 -n $j -k $i -onlypatterns
		printf "\t"
	done
	printf "\n"
done
