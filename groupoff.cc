#include "groupoff.h"
#include "MPRNG.h"
using namespace std;

extern MPRNG mprng;

Groupoff::Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
	printer(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) {
		printer.print (Printer::Groupoff, 'S');
}

WATCard::FWATCard Groupoff::giftCard() {
	// 

	giftcards.push_back(WATCard::FWATCard());
	return giftcards.back();
}

void Groupoff::main(){

	for(unsigned int i = 0; i < numStudents; i++) {
		_Accept(giftCard) {}
	}

	for(;;) {
		_Accept(~Groupoff) {
			break;
		} _Else {
			yield(groupoffDelay);
			if (giftcards.size() > 0) {
				WATCard *gift = new WATCard();
				printer.print(Printer::Groupoff, 'D', sodaCost);
				gift->deposit(sodaCost);

				unsigned int i = mprng(giftcards.size() - 1);
				giftcards[i].delivery(gift);

				giftcards.erase(giftcards.begin() + i);
			}	
		}
	}
	printer.print(Printer::Groupoff, 'F');
}
