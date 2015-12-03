#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>

struct bufferElement
{
    bool inUse;
    char state;
    unsigned int lid;
    int value1;
    int value2;
    bufferElement() : inUse(false), lid(~0u)
    {
    }
};

_Monitor Printer 
{
    unsigned int elements;
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    
    bufferElement *buffer;

    void flush();

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
    
    private:
    int getIndex(Kind kind, unsigned int lid);
    void finalState(Kind kind, unsigned int id);
};

#endif
