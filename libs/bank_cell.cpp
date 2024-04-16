#include "headers/bank_cell.h"

Bank_cell::Bank_cell() : 
	minAmount(0), 
	maxAmount(1000000000),
	currentAmount(0),
	frozenState(false)
{}

void Bank_cell::freeze()
{
	frozenState = true;
}

void Bank_cell::unfreeze()
{
	frozenState = false;
}

void Bank_cell::deposit(long Amount)
{
	currentAmount += Amount;
}

void Bank_cell::credit(long Amount)
{
	currentAmount -= Amount;
}

const long Bank_cell::getMax()
{
	return maxAmount;
}

const long Bank_cell::getMin()
{
	return minAmount;
}

const long Bank_cell::getCurrent()
{
	return currentAmount;
}

bool Bank_cell::isFrozen()
{
	return frozenState;
}
