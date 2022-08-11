#include "printer.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------------------------
// Printer::resetbuffer is used to reset the buffer.
//------------------------------------------------------------------------------------------------------------------
void Printer::resetbuffer() {
    last_one = 0;						// there are no items in buffer now
    for ( unsigned int i = 0; i < totalRows; i++ ) {		// resets values in array
    	buffer[i].valid = false;
        buffer[i].state = NULL;
        buffer[i].numValues = 0;
        buffer[i].value_1 = 0;
        buffer[i].value_2 = 0;
    }
}

//------------------------------------------------------------------------------------------------------------------
// Printer::printbuffer is used to print the buffer.
//------------------------------------------------------------------------------------------------------------------
void Printer::printbuffer() {
	for ( unsigned int i = 0; i < totalRows; i++ ) {
		Action ItemInfo = buffer[i];
		if ( ItemInfo.valid == false ) {
            if ( i >= last_one ) {					// no tabs if last in line
                break;
            }
            if ( i != totalRows - 1 ) {
                cout << '\t';
            }
			continue;
		}
		if ( ItemInfo.state != NULL ) {				// If there is a state
			cout << ItemInfo.state;
			if ( ItemInfo.numValues == 1 ) {		// 1 items
				cout << ItemInfo.value_1;
			} else if ( ItemInfo.numValues == 2 ) {		// 2 items
				cout << ItemInfo.value_1;
				cout << "," << ItemInfo.value_2;
			}
		}
        if (( i != totalRows - 1 ) && ( i != last_one )) {		// no tabs if last in line
            cout << '\t';
        }
	}
	cout << endl;
}

//------------------------------------------------------------------------------------------------------------------
// Printer::Printer is used to initialize the printer.
//------------------------------------------------------------------------------------------------------------------
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
		numStudents( numStudents ), numVendingMachines( numVendingMachines ), numCouriers( numCouriers ),
		totalRows( numStudents + numVendingMachines + numCouriers + 6 ), numDone( 0 ), last_one( 0 ) {
	buffer = new Action[numStudents + numVendingMachines + numCouriers]; 	// initialize buffer
	resetbuffer();
	cout << "Parent";							// Prints the table header
	cout << '\t' << "Gropoff";
	cout << '\t' << "WATOff";
	cout << '\t' << "Names";
	cout << '\t' << "Truck";
	cout << '\t' << "Plant";
	cout << '\t' << "Stud0";
	for ( unsigned int i = 1; i < numStudents; i++ ) {			// Prints the Stud headers				
		cout << '\t' << "Stud" << i;
	}
	cout << '\t' << "Mach0";
	for ( unsigned int i = 1; i < numVendingMachines; i++ ) {		// Prints the Mach headers
		cout << '\t' << "Mach" << i;
	}
	cout << '\t' << "Cour0";
	for ( unsigned int i = 1; i < numCouriers; i++ ) {			// Prints the Cour headers
		cout << '\t' << "Cour" << i;
	}
	cout << endl;

	cout << "*******";
	for ( unsigned int i = 1; i < totalRows; i++ ) { 			// Prints the *
		cout << '\t' << "*******";
	}
	cout << endl;
}

//------------------------------------------------------------------------------------------------------------------
// Printer::~Printer is used to free up any information left in the list.
//------------------------------------------------------------------------------------------------------------------
Printer::~Printer() {
	delete buffer;
}

//------------------------------------------------------------------------------------------------------------------
// Printer::print is used to process states with no num values into buffer.
//------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, char state ) {

	unsigned int index = 0;
	switch( kind ) {					// Matches up with index in buffer
		case Kind::Parent:
			index = 0;
			break;
		case Kind::Groupoff:
			index = 1;
			break;
		case Kind::WATCardOffice:
			index = 2;
			break;
		case Kind::NameServer:
			index = 3;
			break;
		case Kind::Truck: 
			index = 4;
			break;
		case Kind::BottlingPlant:
			index = 5;
			break;
		default:
			exit(EXIT_FAILURE);
	}
	if ( buffer[index].valid == true ) {			// If buffer is full
		printbuffer();
		resetbuffer();
	}
	if ( index > last_one ) {					// If this is the end item in current buffer
        last_one = index;
    }
	buffer[index].valid = true;				// Sets values
	buffer[index].state = state;
	buffer[index].numValues = 0;

	if ( state == 'F' ) {					// If state is "Finished"
		numDone++;
		if ( numDone == totalRows ) {			// Check if all rows are done
			printbuffer();
			cout << "*****************" << endl;
		}
	}
//printbuffer();
}

//------------------------------------------------------------------------------------------------------------------
// Printer::print is used to process states with 1 num value into buffer.
//------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, char state, int value1 ) {

	unsigned int index = 0;
	switch( kind ) {						// Matches up with index in buffer
		case Kind::Parent:
			index = 0;
			break;
		case Kind::Groupoff:
			index = 1;
			break;
		case Kind::WATCardOffice:
			index = 2;
			break;
		case Kind::NameServer:
			index = 3;
			break;
		case Kind::Truck: 
			index = 4;
			break;
		case Kind::BottlingPlant:
			index = 5;
			break;
		default:
			exit(EXIT_FAILURE);
	}
	if ( buffer[index].valid == true ) {				// If buffer is full
		printbuffer();
		resetbuffer();
	}
	if ( index > last_one ) {						// If this is the end item in current buffer
        last_one = index;
    }
	buffer[index].valid = true;					// Sets values
	buffer[index].state = state;
	buffer[index].numValues = 1;
	buffer[index].value_1 = value1;
//printbuffer();
}

//------------------------------------------------------------------------------------------------------------------
// Printer::print is used to process states with 2 num values into buffer.
//------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, char state, int value1, int value2 ) {

	unsigned int index = 0;
	switch( kind ) {						// Matches up with index in buffer
		case Kind::Parent:
			index = 0;
			break;
		case Kind::Groupoff:
			index = 1;
			break;
		case Kind::WATCardOffice:
			index = 2;
			break;
		case Kind::NameServer:
			index = 3;
			break;
		case Kind::Truck: 
			index = 4;
			break;
		case Kind::BottlingPlant:
			index = 5;
			break;
		default:
			exit(EXIT_FAILURE);
	}

	if ( buffer[index].valid == true ) {				// If buffer is full
		printbuffer();
		resetbuffer();
	}
	if ( index > last_one ) {						// If this is the end item in current buffer
        last_one = index;
    }

	buffer[index].valid = true;					// Sets values
	buffer[index].state = state;
	buffer[index].numValues = 2;
	buffer[index].value_1 = value1;
	buffer[index].value_2 = value2;
//printbuffer();
}

//------------------------------------------------------------------------------------------------------------------
// Printer::print is used to process states with no num value into buffer of Kinds with a variable number
//		of columns
//------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, unsigned int lid, char state ) {

	unsigned int index = 0;
	switch( kind ) {						// Matches up with index in buffer
		case Kind::Student:
			index = 6 + (int) lid;
			break;
		case Kind::Vending:
			index = 6 + numStudents + (int) lid;
			break;
		case Kind::Courier:
			index = 6 + numStudents + numVendingMachines + (int) lid;
			break;
		default:
			exit(EXIT_FAILURE);
	}

	if ( buffer[index].valid == true ) {				// If buffer is full
		printbuffer();
		resetbuffer();
	}
	if ( index > last_one ) {						// If this is the end item in current buffer
        last_one = index;
    }

	buffer[index].valid = true;					// Sets values
	buffer[index].state = state;
	buffer[index].numValues = 0;
	if ( state == 'F' ) {						// If state is "Finished"
		numDone++;
		if ( numDone == totalRows ) {				// Check if all rows are done
			printbuffer();
			cout << "***********************" << endl;
		}
	}
//printbuffer();
}

//------------------------------------------------------------------------------------------------------------------
// Printer::print is used to process states with 1 num value into buffer of Kinds with a variable number
//		of columns
//------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) {

	unsigned int index = 0;
	switch( kind ) {						// Matches up with index in buffer
		case Kind::Student:
			index = 6 + (int) lid;
			break;
		case Kind::Vending:
			index = 6 + numStudents + (int) lid;
			break;
		case Kind::Courier:
			index = 6 + numStudents + numVendingMachines + (int) lid;
			break;
		default:
			exit(EXIT_FAILURE);
	}

	if ( buffer[index].valid == true ) {				// If buffer is full
		printbuffer();
		resetbuffer();
	}
	if ( index > last_one ) {						// If this is the end item in current buffer
        last_one = index;
    }

	buffer[index].valid = true;					// Sets values
	buffer[index].state = state;
	buffer[index].numValues = 1;
	buffer[index].value_1 = value1;
//printbuffer();
}

//------------------------------------------------------------------------------------------------------------------
// Printer::print is used to process states with 2 num values into buffer of Kinds with a variable number
//		of columns
//------------------------------------------------------------------------------------------------------------------
void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) {

	unsigned int index = 0;
	switch( kind ) {						// Matches up with index in buffer
		case Kind::Student:
			index = 6 + (int) lid;
			break;
		case Kind::Vending:
			index = 6 + numStudents + (int) lid;
			break;
		case Kind::Courier:
			index = 6 + numStudents + numVendingMachines + (int) lid;
			break;
		default:
			exit(EXIT_FAILURE);
	}

	if ( buffer[index].valid == true ) {				// If buffer is full
		printbuffer();
		resetbuffer();
	}
	if ( index > last_one ) {						// If this is the end item in current buffer
        last_one = index;
    }

	buffer[index].valid = true;					// Sets values
	buffer[index].state = state;
	buffer[index].numValues = 2;
	buffer[index].value_1 = value1;
	buffer[index].value_2 = value2;
//printbuffer();
}
