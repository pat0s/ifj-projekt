#!/bin/bash

EXECUTABLE=$1 
if [ $2 == "yes" ]; then 
	make
fi

BASIC_TESTS="tests/input"
IFJ_TESTS="tests/input_ifj"
LOG="tests/tests_output.log"
rm $LOG
touch $LOG


function to_file()
{
	echo $1 >> $LOG	
}


to_file "------------ LEX testy ------------"
to_file ""
lines=("%Ahoj" "&Ahoj" "89e" "89e+" "89e-" "8ea9")
LEX_OK=("ahoj" "_cau" "AhoK_d" "ahoj_98" "98" "08.0" "98.0") 
for each in "${lines[@]}"; do
	to_file "Vstup: $each"
	echo $each |./$EXECUTABLE
	if [ $? -eq 1 ]; then
		to_file "Chybovy kod - OK" 
	else
		to_file "Chybovy kod - X"
		to_file "vas chybovy kod: $?"
	fi
done

for each in "${LEX_OK[@]}"; do
	to_file "Vstup: $each"
	echo $each |./$EXECUTABLE
	if [ $? -eq 2 ]; then
		to_file "Chybovy kod - OK"
	else
		to_file "Chybovy kod - X"
		to_file "vas chybovy kod: $?"
	fi
done


to_file ""
to_file "------------ Basic testy ------------"
to_file "Vsetky by mali skoncit s chybovym kodom 0!"
to_file ""
for i in `seq 1 12`; do
	./$EXECUTABLE < $BASIC_TESTS$i
	ERROR_CODE=$? 
	case $ERROR_CODE in
		0)
	  to_file "-- test c.$i - OK"
	  ;;
		139)
	  to_file "-- test c.$i - X (SIGSEGV)"
	  ;;
		134)
	  to_file "-- test c.$i - X (SIGABRT)"
	  ;;
		*)
	  to_file "-- test c.$i - X"
	  to_file "ocakavany vystup: 0, vas vystup: $ERROR_CODE"
	  ;;
	esac
done

to_file ""
to_file "---------- Testy zo zadania ifj projektu ----------"
to_file "Vsetky by mali skoncit s chybovym kodom 0!"
to_file ""
for i in `seq 1 3`; do
	./$EXECUTABLE < $IFJ_TESTS$i	
	ERROR_CODE=$? 
	case $ERROR_CODE in
		0)
	  to_file "-- test c.$i - OK"
	  ;;
		139)
	  to_file "-- test c.$i - X (SIGSEGV)"
	  ;;
		134)
	  to_file "-- test c.$i - X (SIGABRT)"
	  ;;
		*)
	  to_file "-- test c.$i - X"
	  to_file "ocakavany vystup: 0, vas vystup: $ERROR_CODE"
	  ;;
	esac
done
