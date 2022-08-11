#include <iostream>
#include <fstream>
#include "MPRNG.h"
#include "config.h"
#include "printer.h"
#include "bank.h"
#include "student.h"
#include "parent.h"
#include "groupoff.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "watcardoffice.h"
#include "bottlingplant.h"
using namespace std;

MPRNG mprng;

bool convert( char *buffer ) {                // convert C string to integer
    while ( *buffer == '0') {
    	buffer++;
    }
    if (*buffer == '\0') return false;
    while ( *buffer !=  '\0') {
    	if ( *buffer < '0' || *buffer > '9') {
    		return false;
    	}
    	buffer++;
    }
    return true;
} // convert

void usage( char *argv ) {
    cerr << "Usage: " << argv
         << " [ config-file [ random-seed (>0) ] ]" << endl;
    exit( EXIT_FAILURE );                               // TERMINATE
} // usage

void uMain::main() {
	unsigned int seed = getpid();
	ConfigParms config;

	switch ( argc ) {
        case 3:
            if ( ! convert( argv[2] ) ) { // invalid integer ?
                usage( argv[0] );
            } // if
            seed = atoi( argv[2] );
        case 2:
            processConfigFile( argv[1], config);
            break;
        case 1:   
            processConfigFile( "soda.config", config);                                      // all defaults
            break;
        default:                                        // wrong number of options
            usage( argv[0] );
    } // switch

    mprng.set_seed(seed);

    unsigned int numStudents = config.numStudents;
    unsigned int numVendingMachines = config.numVendingMachines;
    unsigned int numCouriers = config.numCouriers;
    unsigned int sodaCost = config.sodaCost;
    unsigned int maxPurchases = config.maxPurchases;
    unsigned int maxStockPerFlavour = config.maxStockPerFlavour;
    unsigned int maxShippedPerFlavour = config.maxShippedPerFlavour;
    unsigned int timeBetweenShipments = config.timeBetweenShipments;
    unsigned int groupoffDelay = config.groupoffDelay;
    unsigned int parentalDelay = config.parentalDelay;

    Printer printer(numStudents, numVendingMachines, numCouriers);
    Bank bank(numStudents);
    Parent parent (printer, bank, numStudents, parentalDelay);
    WATCardOffice watcardoffice(printer, bank, numCouriers);
    NameServer nameserver(printer, numVendingMachines, numStudents);
    Groupoff groupoff(printer, numStudents, sodaCost, groupoffDelay);

    VendingMachine *vendingmachines[numVendingMachines];
	for (unsigned int i = 0; i <  numVendingMachines; i++) {
		vendingmachines[i] = new VendingMachine(printer, nameserver, i, sodaCost, maxStockPerFlavour);
	}

	BottlingPlant * plant = new BottlingPlant(printer, nameserver, numVendingMachines, maxShippedPerFlavour, 
		maxStockPerFlavour, timeBetweenShipments); 
	
	Student *students[numStudents];
	for (unsigned int i = 0; i <  numStudents; i++) {
		students[i] = new Student(printer, nameserver, watcardoffice, groupoff, i, maxPurchases);
	}



	for (unsigned int i = 0; i < numStudents; i++) {
		delete students[i];
	}

	delete plant;

	for (unsigned int i = 0; i < numVendingMachines; i++) {
		delete vendingmachines[i];
	}
}
