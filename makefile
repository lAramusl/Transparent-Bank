run: main

bank_cell.o: libs/bank_cell.cpp libs/headers/bank_cell.h
	g++ libs/bank_cell.cpp -c

bank.o: libs/bank.cpp libs/headers/bank.h
	g++ libs/bank.cpp -c

bank_init.o: bank_init.cpp
	g++ bank_init.cpp -c -pthread

main: bank.o bank_cell.o bank_init.o
	g++ bank_init.o bank.o bank_cell.o -pthread -o bank_init
	rm *.o

clean: 
	rm bank_init
