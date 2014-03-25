#!/bin/bash

for cfile in *.c
do
	nlines=$(wc -l < $cfile)
	total=$(($total + $nlines))
done

echo "$total"
