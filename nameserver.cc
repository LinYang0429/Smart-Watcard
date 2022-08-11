#include "nameserver.h"
using namespace std;


NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
	printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), vmcount(0) {
		printer.print(Printer::NameServer, 'S');
		machines = new VendingMachine*[numVendingMachines];
		students = new unsigned int[numStudents];
		for(unsigned int i = 0; i < numStudents; i++) {
			students[i] = i % numStudents;
		}
}

NameServer::~NameServer() {
	/*for(unsigned int i = 0; i < numVendingMachines; i++) {
		delete machines[i];
	}
	*/
	delete [] students;
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
	machines[vmcount++] = vendingmachine;
	printer.print(Printer::NameServer, 'R', vendingmachine->getId());
}

VendingMachine * NameServer::getMachine( unsigned int id ) {
	students[id] = (students[id] + 1) % numVendingMachines;
	printer.print(Printer::NameServer, 'N', id, students[id]);
	return machines[students[id]];
}

VendingMachine **NameServer::getMachineList() {
	return machines;
}

void NameServer::main() {

	for(unsigned int i = 0; i < numVendingMachines; i++) {
		_Accept(VMregister);
	}

	for(unsigned int i = 0; i < numStudents; i++) {
		students[i] = i % numVendingMachines;
	}

	while (true) {
		_Accept(~NameServer) {
			break;
		} or _Accept(getMachine, getMachineList);
	}

	printer.print(Printer::NameServer, 'F');
}
