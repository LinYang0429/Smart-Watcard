#include "truck.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "vendingmachine.h"
#include "MPRNG.h"
#include <iostream>
using namespace std;
extern MPRNG mprng;

void Truck::main() {
	prt.print( Printer::Truck, 'S');
	VendingMachine ** machinelist = nameServer.getMachineList();
	int onVendingMachine = 0;
	for(;;) {
		try {
			_Enable {
				yield( mprng( 1, 10 ) );
				plant.getShipment( cargo );
			}
		} catch (BottlingPlant::Shutdown &e) {
			break;
		}
		unsigned int shipment = cargo[0] + cargo[1] + cargo[2] + cargo[3];
		prt.print( Printer::Truck, 'P', shipment);
		for( unsigned int i = 0; i < numVendingMachines; i++ ) {
			if ( shipment == 0 ) {
    			break;
    		}
    		prt.print( Printer::Truck, 'd', onVendingMachine, shipment );
			VendingMachine * machine = machinelist[ onVendingMachine ];
			unsigned int * machineinventory = machine->inventory();
			int not_replenished = 0;
			for( unsigned int i = 0; i < 4; i++ ) { // intializes cargo
				if ( machineinventory[i] != maxStockPerFlavour ) {
					if ( cargo[i] + machineinventory[i] <= maxStockPerFlavour ) {
						not_replenished += maxStockPerFlavour - machineinventory[i];
						machineinventory[i] += cargo[i];
						cargo[i] = 0;
					} else {
						cargo[i] -= maxStockPerFlavour - machineinventory[i];
						machineinventory[i] = maxStockPerFlavour;
					}
				}
			}
			prt.print( Printer::Truck, 'U', onVendingMachine, not_replenished );
			shipment = cargo[0] + cargo[1] + cargo[2] + cargo[3];
			prt.print( Printer::Truck, 'D', onVendingMachine, shipment );
    		machine->restocked();
			onVendingMachine = ( onVendingMachine + 1 ) % numVendingMachines; // set for next machine
		}
	}
	prt.print( Printer::Truck, 'F');
	delete [] cargo;
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : 
	prt( prt ), nameServer( nameServer ), plant( plant ), numVendingMachines( numVendingMachines ),
	maxStockPerFlavour( maxStockPerFlavour ) {
	cargo = new unsigned int[4];
	for( int i = 0; i < 4; i++ ) { // intializes cargo
		cargo[i] = 0;
	}
}
