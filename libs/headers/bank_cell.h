#ifndef BANK_CELLH
#define BANK_CELLH
#include <iostream>
#include <cstddef>

class Bank_cell
{
public:
	Bank_cell();
	
	Bank_cell& operator=(const Bank_cell& bnk) = default;

	void freeze();
	void unfreeze();

	void deposit(long Amount);
	void credit(long Amount);
	
	const long getMax();
	const long getMin();
	const long getCurrent();
	bool isFrozen();

private:
	long minAmount;
	long maxAmount;
	long currentAmount;
	bool frozenState;

};

#endif
