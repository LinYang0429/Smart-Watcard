#include "bottlingplant.h"
#include "printer.h"
#include "nameserver.h"
#include "vendingmachine.h"
#include "truck.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

void BottlingPlant::main() {
	prt.print( Printer::BottlingPlant, 'S');
	Truck truck( prt, nameServer, *this, numVendingMachines, maxStockPerFlavour );
	for(;;) {
		int total = 0;
		for( int i = 0; i < 4; i++ ) {	// production run of soda
			stock[i] = mprng( 1, maxShippedPerFlavour );
			total += stock[i];
		}
		yield( timeBetweenShipments );
		prt.print( Printer::BottlingPlant, 'G', total );
		_Accept( ~BottlingPlant ) {
			shutdown = true;
			_Accept( getShipment ) {
				break;
			}
		} or _Accept( getShipment ) {
			prt.print( Printer::BottlingPlant, 'P');
		}
	}
	delete [] stock;
	prt.print( Printer::BottlingPlant, 'F');
}

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments ) : prt( prt ), nameServer( nameServer ), 
				 numVendingMachines( numVendingMachines ), maxShippedPerFlavour( maxShippedPerFlavour ),
				 maxStockPerFlavour( maxStockPerFlavour ), timeBetweenShipments( timeBetweenShipments ),
				 shutdown( false ) {
	stock = new unsigned int[4];
	for( int i = 0; i < 4; i++ ) {
		stock[i] = 0;
	}
}

void BottlingPlant::getShipment( unsigned int cargo[] ) {
	if ( shutdown ) {
		truckTask = &uThisCoroutine();
		_Resume Shutdown() _At *truckTask;
		return;
	}
	for( int i = 0; i < 4; i++ ) {
		cargo[i] = stock[i];
	}
}
