#Makefile
FLAGS = -std=c99 -Wall -O1


all: clean compTuringComplete compPow compFIB runPow runFib
compNrunPow: compPow runPow
compNrunFib: compFib runFib

compTuringComplete:
	gcc ${FLAGS} -o turingComplete turingComplete.c 
compPow:
	gcc ${FLAGS} -o pow powerOf2.c 
compFib:
	gcc ${FLAGS} -o fib first10Fib.c 

runPow: 
	#please supply more then 4500000 bytes
	./turingComplete 4500000 ./pow
runFib:
	#please supply more then 4500000 bytes
	./turingComplete 4500000 ./fib  

clean: 
	rm -f turingComplete
	rm -f fib
	rm -f pow

