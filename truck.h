#ifndef TRUCK_H
#define TRUCK_H

#include "bottlingplaint.h"
#include "printer.h"
#include "nameserver.h"

_Task Truck 
{
    void main();

    Printer &print;
    NameServer &server;
    BottlingPlant &plant;
    unsigned int numMachines;
    unsigned int maxStock;
    public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
            unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif
