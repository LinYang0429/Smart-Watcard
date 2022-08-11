#include "parent.h"
#include "MPRNG.h"
using namespace std;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay )
	: printer(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {
		printer.print (Printer::Parent, 'S');
}

Parent::~Parent() {}

void Parent::main() {

	for(;;) {
		_Accept(~Parent) {
			break;
		} _Else {
			yield(parentalDelay);
			unsigned int studentid = mprng(0, numStudents-1);
			unsigned int money = mprng(1,3);
			printer.print(Printer::Parent, 'D', studentid, money);
			bank.deposit(studentid, money);
		}
	}

	printer.print(Printer::Parent, 'F');
}
