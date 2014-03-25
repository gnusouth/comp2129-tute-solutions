#!/bin/bash

# Compare the actual and expected output of the stats program for various inputs.

# Colours
GREENBOLD="\e[1;32m"
REDBOLD="\e[1;31m"
DEFAULT="\e[0;39m"

for testfile in tests/*.in
do
	testname=$(basename --suffix=.in $testfile)
	testoutput="tests/${testname}.out"
	differences=$(./stats < $testfile | sdiff -s $testoutput -)

	# Check the exit code ($?) of the sdiff call above.
	if [ $? -ne 0 ]
	then
		echo -e "$testname [${REDBOLD}failed${DEFAULT}]"
		echo $differences
	else
		echo -e "$testname [${GREENBOLD}passed${DEFAULT}]"
	fi
done
