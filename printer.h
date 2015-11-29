#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include "q3tallyVotes.h"
#include "q3voter.h"


struct bufferElement
{
    bool inUse;
    char state;
    unsigned int lid;
    unsigned int numBlocked;
    bufferElement() : inUse(false)
    {
    }
};

_Monitor Printer 
{

    bufferElement *buffer;
    unsigned int voters;

    void flush();

    public:
    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
   
};

#endif
