#include "vendingmachine.h"
#include "student.h"
#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "groupoff.h"
#include "watcard.h"
#include "MPRNG.h"

extern MPRNG mprng;

void VendingMachine::main() {
	prt.print( Printer::Vending, id, 'S', sodaCost );
	for (;;) {
		_Accept( ~VendingMachine ) {
			break;
		} or _Accept( buy ) {
			block.signalBlock();
		} or _Accept( inventory ) {
			prt.print( Printer::Vending, id, 'r' );
			_Accept( restocked ) {
			}
		}
	}
	prt.print( Printer::Vending, id, 'F');
	delete [] stock;
}

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
	unsigned int maxStockPerFlavour ) : prt( prt ), nameServer( nameServer ), id( id ), sodaCost( sodaCost ),
	maxStockPerFlavour( maxStockPerFlavour ) {
	nameServer.VMregister(this);
	stock = new unsigned int[4];
	for( int i = 0; i < 4; i++ ) {
		stock[i] = 0;
	}
}

VendingMachine::~VendingMachine() {}

void VendingMachine::buy( Flavours flavour, WATCard &card ) {
	student = &uThisTask();
	unsigned int watCardBalance = card.getBalance();
	if ( watCardBalance < sodaCost ) {
		_Resume Funds() _At *student;
	} else if ( stock[( int ) flavour] == 0 ) {
		_Resume Stock() _At *student;
	} else if ( mprng( 1, 5 ) == 1 ) {
		stock[ ( int ) flavour ]--;
		_Resume Free() _At *student;
	} else {
		card.withdraw( sodaCost );
		stock[ ( int ) flavour ]--;
		prt.print( Printer::Vending, id, 'B', ( int ) flavour, stock[ ( int ) flavour ] );
	}
	block.wait();
}

unsigned int *VendingMachine::inventory() {
	// start reloading print in main function
	return stock;
}

void VendingMachine::restocked() {
	prt.print( Printer::Vending, id, 'R' );
}

_Nomutex unsigned int VendingMachine::cost() {
	return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId() {
	return id;
}
