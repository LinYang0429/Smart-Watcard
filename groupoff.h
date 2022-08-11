#ifndef __GROUPOFF_H__
#define __GROUPOFF_H__
#include "watcardoffice.h"
#include "watcard.h"
#include <vector>
#include <uC++.h>

_Task Groupoff {

	Printer &printer;
	unsigned int numStudents;
	unsigned int sodaCost;
	unsigned int groupoffDelay;
	std::vector<WATCard::FWATCard> giftcards;

    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};

#endif // __GROUPOFF_H__
