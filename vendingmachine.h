#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__
#include "printer.h"
#include "watcard.h"
#include <uC++.h>

_Task NameServer;

_Task VendingMachine {
    Printer & prt;
    NameServer & nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int * stock;
    uBaseTask *student;
    uCondition block;
    void main();
  public:
    enum Flavours { Coke, Sprite, GingerAle, IcedTea };     // flavours of soda (YOU DEFINE)
    _Event Free {};                                         // free, advertisement
    _Event Funds {};                                    // insufficient funds
    _Event Stock {};                                    // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif // __VENDINGMACHINE_H__
