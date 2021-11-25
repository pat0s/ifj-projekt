#!/bin/bash

EXECUTABLE=$1 
if [ $2 == "yes" ]; then 
	make
fi

BASIC_TESTS="tests/input"
IFJ_TESTS="tests/input_ifj"
SYN_ERR_TESTS="tests/input_syn_err"
SEM_ERR_TESTS="tests/input_sem_err"
LOG="tests/tests_output.log"
rm $LOG
touch $LOG


function to_file()
{
	echo $1 >> $LOG	
}


to_file "------------ LEX testy (ERR) ------------"
lines=(".=" "%Ahoj" "&Ahoj" "89e" "89e+" "89e-" "8ea9")
LEX_OK=(".."  "==" "ahoj " "_cau" "AhoK_d" "ahoj_98" "98" "08.0" "98.0") 

i=1
for each in "${lines[@]}"; do
	echo $each |./$EXECUTABLE
	if [ $? -eq 1 ]; then
		to_file "-- test c.$i - OK" 
	else
		to_file "-- test c.$i - X (vas chybovy kod: $?)"
	fi
	let "i++"
done

to_file ""
to_file "------------ LEX testy (OK) ------------"
i=1
for each in "${LEX_OK[@]}"; do
	echo $each |./$EXECUTABLE
	if [ $? -eq 2 ]; then
		to_file "-- test c.$i - OK" 
	else
		to_file "-- test c.$i - X (vas chybovy kod: $?)"
	fi
	let "i++"
done


function check_error_code()
{
	ERROR_CODE=$1
	EXPECTED=$2
	N=$3

	if [ $ERROR_CODE -eq $EXPECTED ]; then
		to_file "-- test c.$N - OK"
	else
		ERROR_MSG=""
		case $ERROR_CODE in
			0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 99)
	  	ERROR_MSG="(ocakavany vystup: $EXPECTED, vas vystup: $ERROR_CODE)"
	  	;;		
			139)
	  	ERROR_MSG="(SIGSEGV)"
	  	;;
			134)
	  	ERROR_MSG="(SIGABRT)"
	  	;;
			*)
		ERROR_MSG="(unknown)"
	  	;;
		esac
		to_file "-- test c.$N - X $ERROR_MSG"
	fi
}

to_file ""
to_file "------------ Basic testy ------------"
to_file "Vsetky by mali skoncit s chybovym kodom 0!"
for i in `seq 1 16`; do
	./$EXECUTABLE < $BASIC_TESTS$i
	check_error_code $? 0 $i
done

to_file ""
to_file "---------- Testy syntaktickych chyb ----------"
to_file "Vsetky by mali skoncit s chybovym kodom 2!"
for i in `seq 1 10`; do
	./$EXECUTABLE < $SYN_ERR_TESTS$i	
	check_error_code $? 2 $i
done

to_file ""
to_file "---------- Testy semantickych chyb (3)----------"
for i in `seq 1 9`; do
	./$EXECUTABLE < $SEM_ERR_TESTS$i	
	check_error_code $? 3 $i
done

to_file ""
to_file "---------- Testy semantickych chyb (4)----------"
for i in `seq 14 17`; do
	./$EXECUTABLE < $SEM_ERR_TESTS$i	
	check_error_code $? 4 $i
done

to_file ""
to_file "---------- Testy semantickych chyb (5)----------"
for i in `seq 18 20`; do
	./$EXECUTABLE < $SEM_ERR_TESTS$i	
	check_error_code $? 5 $i
done

to_file ""
to_file "---------- Testy semantickych chyb (6)----------"
for i in `seq 10 13`; do
	./$EXECUTABLE < $SEM_ERR_TESTS$i	
	check_error_code $? 6 $i
done

to_file ""
to_file "---------- Testy semantickych chyb (9)----------"
to_file "Delenie nulou ako konstantou 0 a 0.0"
i=0
./$EXECUTABLE < $SEM_ERR_TESTS$i
check_error_code $? 9 1
./$EXECUTABLE < $SEM_ERR_TESTS$i$i
check_error_code $? 9 2

to_file ""
to_file "---------- Testy zo zadania ifj projektu ----------"
to_file "Vsetky by mali skoncit s chybovym kodom 0!"
for i in `seq 1 5`; do
	./$EXECUTABLE < $IFJ_TESTS$i	
	check_error_code $? 0 $i
done

#-- End of file run_tests.sh --#

