#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <uC++.h>
#include "printer.h"
#include "watcardoffice.h"
#include "nameserver.h"
#include "groupoff.h"
#include "watcard.h"

_Task Student {
	Printer &prt;
	NameServer &nameServer;
	WATCardOffice &cardOffice;
	Groupoff &groupoff;
    unsigned int id;
    unsigned int maxPurchases;
    //unsigned int numPurchases;
	//unsigned int favFlavour;
	//WATCard watCard;
	//WATCard giftCard;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
};

#endif // __STUDENT_H__
