run: main

bank_cell.o: libs/bank_cell.cpp headers/bank_cell.h
	g++ bank_cell.cpp -c

bank.o: libs/bank.cpp headers/bank.h
	g++ bank.cpp -c

bank_init.o: bank_init.cpp
	g++ bank_init.cpp -c

main: bank.o bank_cell.o bank_init.o
	g++ bank_init.o bank.o bank_cell.o -o bank_init
	rm *.o

clean: 
	rm bank_init
