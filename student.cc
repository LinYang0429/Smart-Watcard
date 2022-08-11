#include "student.h"
#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "groupoff.h"
#include "watcard.h"
#include "vendingmachine.h"
#include "MPRNG.h"
using namespace std;

extern MPRNG mprng;

void Student::main() {
	unsigned int numPurchases = mprng( 1, maxPurchases );
	VendingMachine::Flavours favFlavour = static_cast<VendingMachine::Flavours>(mprng( 0, 3 ));
	prt.print( Printer::Student, id, 'S', favFlavour, numPurchases );

	WATCard::FWATCard watCard = cardOffice.create( id, 5 );
	WATCard::FWATCard giftCard = groupoff.giftCard();
	VendingMachine * a_machine = nameServer.getMachine( id ); // gets the Vending Machine for the student id
	prt.print( Printer::Student, id, 'V', a_machine->getId() );
//	unsigned int cost = a_machine->cost();
//	bool deleted_giftcard = false;

	for( unsigned int purchaseNum = 0; purchaseNum < numPurchases; purchaseNum++ ) {
		yield( mprng( 1, 10 ) );
		for(unsigned int i = 0; i < 1; i++) {
			_Select( watCard ) {
				try {
					_Enable {
						a_machine->buy( favFlavour, *( watCard() ));
						prt.print( Printer::Student, id, 'B', favFlavour, watCard()->getBalance() );
					}
				} catch( WATCardOffice::Lost &e ) {
					prt.print( Printer::Student, id, 'L' );
					watCard = cardOffice.create( id, 5 );
					i--; // Since buy does not actually occur
					continue;
				} catch( VendingMachine::Free &e ) {
					prt.print( Printer::Student, id, 'A', favFlavour, watCard()->getBalance() );
					yield( 4 );
					continue;
				} catch( VendingMachine::Funds &e ) {
					watCard = cardOffice.transfer( id, 5, watCard );
					purchaseNum--;
					continue;
				} catch( VendingMachine::Stock &e ) {
					a_machine = nameServer.getMachine( id ); // get new Machine
					prt.print( Printer::Student, id, 'V', a_machine->getId() );
					purchaseNum--;
					continue;
				} // Otherwise, it means that the soda has been successfully purchased
			} or _Select( giftCard ) {
				try {
					_Enable {
						a_machine->buy( favFlavour, *( giftCard() ));
						prt.print( Printer::Student, id, 'G', favFlavour, giftCard()->getBalance() );
						//delete giftCard();
						giftCard.reset();
						//deleted_giftcard = true;
					}
				} catch( VendingMachine::Free &e ) { // if free, then no need to reset card
					prt.print( Printer::Student, id, 'a', favFlavour, giftCard()->getBalance() );
					yield( 4 );
					continue;
				} catch( VendingMachine::Funds &e ) { // should never happen
					purchaseNum--;
					continue;
				} catch( VendingMachine::Stock &e ) {
					a_machine = nameServer.getMachine( id ); // get new Machine
					prt.print( Printer::Student, id, 'V', a_machine->getId() );
					purchaseNum--;
					continue;
				} // Otherwise, it means that the soda has been successfully purchased
			}
		}
	}
	
	prt.print( Printer::Student, id, 'F' );

	try {
		delete watCard();
	} catch( WATCardOffice::Lost &e ) {
	}
/*
	if ( deleted_giftcard == false ) {
		_Select(giftCard) {
			delete giftCard(); 	// might be impossible to detect whether giftcard has been created yet
								// without a flag variable
		}
	}
*/
}

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
	unsigned int id, unsigned int maxPurchases ) : prt( prt ), nameServer( nameServer ), 
cardOffice( cardOffice ), groupoff( groupoff ), id( id ), maxPurchases( maxPurchases ) {
	//nameserver.getMachine( unsigned int id );
}
