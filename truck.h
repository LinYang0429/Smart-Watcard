#ifndef __TRUCK_H__
#define __TRUCK_H__

#include <uC++.h>
#include "printer.h"
#include "nameserver.h"
#include "vendingmachine.h"

_Task BottlingPlant;

_Task Truck {
	Printer &prt;
	NameServer &nameServer;
	BottlingPlant &plant;
	unsigned int numVendingMachines;
	unsigned int maxStockPerFlavour;
	unsigned int * cargo;
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif // __TRUCK_H__
