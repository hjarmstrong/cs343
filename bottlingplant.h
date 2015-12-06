#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

#include "printer.h"
#include "nameserver.h"

_Task BottlingPlant 
{
    void main();

    Printer &print;
    NameServer &server;
    unsigned int machines;
    unsigned int maxShipped;
    unsigned int maxStock;
    unsigned int time;
    bool shutdown;
    unsigned int generate[VendingMachine::NUM_FLAVOURS];
    public:
    _Event Shutdown {};                    // shutdown plant
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
            unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
            unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
};

#endif
