#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "bank.h"
#include <cerrno>

int main(int argc, char** argv)
{
	unsigned long n = static_cast<long>(std::stoul(argv[1]));
	
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

	for(std::size_t i = 0; i < 1; ++i)
	{
		pBank->operator[](i) = Bank_cell();//one bilion
	}

	return 0;	
}
