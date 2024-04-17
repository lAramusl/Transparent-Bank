#include <iostream>
#include "libs/headers/bank.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <semaphore.h>
#include <string>
#include <vector>
#include <algorithm>

void BankAction(const std::string& cmd, Bank*& bnk)
{
	static const std::vector<std::string> commands = 
	{ "get_max", "get_min", "get_ballance", 
	  "transfer", 
	  "freeze", "unfreeze", "isfrozen",
	  "credit_from", "deposit_to",
	  "credit", "deposit"};

	auto it = std::find(commands.begin(), commands.end(), cmd);

	if(it == commands.end())
	{
		std::cout << "Invalid operation\n";
		return;
	}
	std::size_t index = it - commands.begin();

	switch(index)
	{
		case 0:
		{
			std::size_t cellNum = 0;
			std::cin >> cellNum;
                        std::cout << "The max balance of cell " << cellNum << " is " << bnk->getMaxBalance(cellNum) << std::endl;
		}
		case 1:
		{
			std::size_t cellNum = 0;
                        std::cin >> cellNum;
                        std::cout << "The min balance of cell " << cellNum << " is " << bnk->getMinBalance(cellNum) << std::endl;
		}
		case 2:
		{
			std::size_t cellNum = 0;
                        std::cin >> cellNum;
                        std::cout << "The current balance of cell " << cellNum << " is " << bnk->getBalance(cellNum) << std::endl;
		}
	}

}

int main(int argc,char** argv)
{
	const char* semaphName = "/BankSem";

	sem_t* semaph = sem_open (semaphName, O_RDWR);
	int x = 0;
	sem_getvalue(semaph, &x);
	if(x == 0)
	{
		sem_close(semaph);
		std::cout << "No free spaces to operate the bank currently.\nPlease try again Later.\n";
		return 0;
	}
	

	const char* shmName = "/Bank"; 
	std::size_t numberOfCells = std::stoull(argv[1]);
	std::size_t shmSize = sizeof(Bank) + numberOfCells*sizeof(Bank_cell);

	int shmFd = shm_open(shmName, O_RDWR, 0666);

	void* bankptr = mmap(nullptr, shmSize, PROT_READ|PROT_WRITE, MAP_SHARED, shmFd, 0);

	Bank* bnk = (Bank*)bankptr;
	
	std::cout << bnk->getMaxBalance(0);

	//while(true)
	//{
	//	std::string cmd;
	//	std::cin >> cmd;
	//	BankAction(cmd, bnk);
	//}
				
}
