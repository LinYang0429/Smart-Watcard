#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "printer.h"
#include "bank.h"
#include "watcard.h"
#include <queue>
#include <uC++.h>

_Task WATCardOffice {

    struct Job {                              // marshalled arguments and return future
        unsigned int sid;
        unsigned int amount;
        WATCard *watcard;                           // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;             // return future
	Job( unsigned int sid, unsigned int amount, WATCard *watcard ) : sid(sid), amount(amount), watcard(watcard) {}
    };
    _Task Courier {                             // communicates with bank
        Printer &printer;
        Bank &bank;
        WATCardOffice &watcardoffice;
        unsigned int id;

        void main();
    public:
        Courier(Printer &prt, Bank &bank, WATCardOffice &watcardoffice, unsigned int id);
        ~Courier();
    };                    

    Printer &printer;
    Bank &bank;
    unsigned int numCouriers;
    std::queue<Job*> requests;
    Courier **couriers;
    Job *job;


    void main();
  public:
    _Event Lost {};                           // lost WATCard
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    ~WATCardOffice();
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif // __WATCARDOFFICE_H__
