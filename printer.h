#ifndef __PRINTER_H__
#define __PRINTER_H__

#include <uC++.h>

_Monitor Printer;

struct Action {
    bool valid;                            // true if Action is valid, false otherwise
    char state;								// state id
    int numValues;
    int value_1;
    int value_2;
}; // Action

_Monitor Printer { 
	Action * buffer;
    unsigned int numStudents;               // # of current voters
    unsigned int numVendingMachines;               // # of current voters
    unsigned int numCouriers;               // # of current voters
    unsigned int totalRows;               		// # of voters done process done
    unsigned int numDone;
    unsigned int last_one;                  // signifies the last valid value in the buffer
    void resetbuffer();                     // resets the buffer
    void printbuffer();                     // prints the content in the buffer
  public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif // __PRINTER_H__
