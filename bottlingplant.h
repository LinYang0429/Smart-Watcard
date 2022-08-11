#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include <uC++.h>
#include "bottlingplant.h"
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

_Task BottlingPlant {
	Printer &prt;
	NameServer &nameServer;
	unsigned int numVendingMachines;
	unsigned int maxShippedPerFlavour;
	unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int * stock;
    bool shutdown;
    uBaseCoroutine *truckTask;
    uCondition block;
    void main();
  public:
    _Event Shutdown {};                       // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif // __BOTTLINGPLANT_H__
