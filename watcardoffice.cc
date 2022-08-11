#include "watcardoffice.h"
#include <uFuture.h>
#include "MPRNG.h"
#include <iostream>
using namespace std;

extern MPRNG mprng;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : printer(prt), bank(bank), numCouriers(numCouriers) {
		couriers = new Courier*[numCouriers];
		for(unsigned int i = 0; i <numCouriers; i++) {
			couriers[i] = new Courier(printer, bank, *this, i);
		}
		printer.print(Printer::WATCardOffice, 'S');
	}

WATCardOffice::~WATCardOffice() {
	for(unsigned int i = 0; i < numCouriers; i++) {
		requests.push(NULL);
		_Accept(requestWork);
	}
	delete [] couriers;
}

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
	job = new Job(sid, amount, new WATCard());
	requests.push(job);
	printer.print(Printer::WATCardOffice, 'C', sid, amount);
	return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card ) {
	job = new Job(sid, amount, card);
	requests.push(job);
	printer.print(Printer::WATCardOffice, 'T', sid, amount);
	return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork() {
	Job *job = requests.front();
	requests.pop();
	return job;
}

void WATCardOffice::main() {
	for(;;) {
		_Accept (~WATCardOffice) {
			break;
		} or _Accept(create) {
		} or _Accept(transfer) {
		} or _When (requests.size() > 0) _Accept(requestWork) {
			printer.print(Printer::WATCardOffice, 'W');
		} 
	}
	printer.print(Printer::WATCardOffice, 'F');
}

WATCardOffice::Courier::Courier(Printer &prt, Bank &bank, WATCardOffice &watcardoffice, unsigned int id) :
	printer(prt), bank(bank), watcardoffice(watcardoffice), id(id) {
		printer.print(Printer::Courier, id, 'S');
	}

WATCardOffice::Courier::~Courier(){}

void WATCardOffice::Courier::main() {
	WATCardOffice::Job *j = NULL;
	for(;;) {
		j = watcardoffice.requestWork();
		if(j == NULL) break;

		printer.print(Printer::Courier, id, 't', j->sid, j->amount);
		bank.withdraw(j->sid, j->amount);
		j->watcard->deposit(j->amount);
		bool islost = (mprng(0, 5) == 0);
		if(islost) {
			delete j->watcard;
			j->result.exception(new Lost());
			printer.print(Printer::Courier, id, 'L', j->sid);
		} else {
			j->result.delivery(j->watcard);
			printer.print(Printer::Courier, id, 'T', j->sid, j->amount);
		}

	}
	printer.print(Printer::Courier, id, 'F');
}
