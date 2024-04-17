#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cerrno>
#include <semaphore.h>
#include "libs/headers/bank.h"

int main(int argc, char** argv)
{
	unsigned long n = static_cast<long>(std::stoul(argv[1]));
	
	//creating shared mem
	const char* sharedMem = "/Bank";

	int sharedFd = shm_open(sharedMem, O_CREAT|O_RDWR|O_TRUNC, 0666);
	if(sharedFd == -1)
	{
		std::cerr << "shm_open: failure at creating\n";
		exit(EXIT_FAILURE);
	}

	std::size_t sizeOfSharedMem = sizeof(Bank) + n*sizeof(Bank_cell);

	int trunc = ftruncate(sharedFd, sizeOfSharedMem);
	if(trunc == -1)
	{
		std::cerr << "truncate: could not truncate\n";
		exit(EXIT_FAILURE);
	}
	
	//filling the shared mem with bank cells
	void* ptr = mmap(nullptr,
		       	sizeOfSharedMem,
		       	PROT_READ|PROT_WRITE,
		       	MAP_SHARED,
			sharedFd,
			0);
	if(ptr == MAP_FAILED)
	{
		std::cerr << "mmap: could not map\n";
		exit(EXIT_FAILURE);
	}
	
	Bank* pBank = (Bank*)ptr;

	*pBank = Bank(n, (Bank_cell*)(pBank + sizeof(Bank)) );

	for(std::size_t i = 0; i < n; ++i)
	{
		pBank->operator[](i) = Bank_cell();//one bilion
	}

	//creating the semaphore
	
	const char* semphName = "/BankSem";

	sem_t* semaph = sem_open(semphName, O_CREAT | O_RDWR , 0666, 10);
	if(semaph == SEM_FAILED)
	{
		std::cerr << "semaphore: failure at creation\n";
		exit(EXIT_FAILURE);
	}

	return 0;	
}
