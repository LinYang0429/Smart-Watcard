#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__
#include "printer.h"
#include "vendingmachine.h"
#include <uC++.h>
using namespace std;

_Task NameServer {

	Printer &printer;
	unsigned int numVendingMachines;
	unsigned int numStudents;
	unsigned int vmcount;
	VendingMachine **machines;
	unsigned int *students;

    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif // __NAMESERVER_H__
