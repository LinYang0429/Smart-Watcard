#include "bank.h"
using namespace std;

Bank::Bank( unsigned int numStudents ) {
	balances = new unsigned int[numStudents];
	for(unsigned int i = 0; i < numStudents; i++) {
		balances[i] = 0;
	}
}

Bank::~Bank() {
	delete [] balances;
}

void Bank::deposit( unsigned int id, unsigned int amount ) {
	balances[id] += amount;
}

void Bank::withdraw( unsigned int id, unsigned int amount ) {
//	while (amount >= balances[id]) {
//		_Accept(deposit);
//	}
	balances -= amount;
}
