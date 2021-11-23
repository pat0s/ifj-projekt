#!/bin/bash

#//set -e

EXECUTABLE=$1 
if [ $2 == "yes" ]; then 
	make
fi

BASIC_TESTS="tests/input"
IFJ_TESTS="tests/input_ifj"

echo "------------ Basic testy ------------"
echo "Vsetky by mali skoncit s chybovym kodom 1!"
echo ""
lines=("%Ahoj" "&Ahoj" "89e" "89e+" "89-a" "8a9")
for each in "${lines[@]}"; do
	echo "Vstup: $each"
	echo $each |./$EXECUTABLE
	if [ $? -eq 1 ]; then
		echo "Chybovy kod - OK"
	else
		echo "Chybovy kod - X"
		echo "vas chybovy kod: $?"
	fi
done

echo "------------ Basic testy ------------"
echo "Vsetky by mali skoncit s chybovym kodom 0!"
echo ""
for i in `seq 1 10`; do
	./$EXECUTABLE < $BASIC_TESTS$i
	if [ $? -eq 0 ]; then
		echo "-- test c.$i - OK"
	else
		echo "test c.$i - X"
		echo "ocakavany vystup: 0, vas vystup: $?"
	fi
done

echo "Testy zo zadania ifj projektu"
echo "Vsetky by mali skoncit s chybovym kodom 0!"
echo ""
#for i in `seq 1 5`; do
#	./$EXECUTABLE < $IFJ_TESTS$i
#done
