#include <iostream>
#include "bottlingplant.h"
#include "vendingmachine.h"
#include "truck.h"
#include "MPRNG.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
        unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
        unsigned int timeBetweenShipments )
: print(prt), server(nameServer), machines(numVendingMachines), maxShipped(maxShippedPerFlavour),
    maxStock(maxStockPerFlavour), time(timeBetweenShipments), shutdown(false)
{
    print.print(Printer::BottlingPlant, 'S');
}

void BottlingPlant::getShipment(unsigned int cargo[])
{
    if(shutdown)
    {
        _Throw Shutdown();
    }

    for(int i = 0; i < VendingMachine::NUM_FLAVOURS; i++)
    {
        cargo[i] = generate[i];
    }
    print.print(Printer::BottlingPlant, 'P');
}

void BottlingPlant::main()
{
    Truck truck(print, server, *this, machines, maxStock);

    for(;;)
    {
        int totalSoda = 0;
        for(int i = 0; i < VendingMachine::NUM_FLAVOURS; i++)
        {

            generate[i] = safeRandom(0, maxShipped);
            totalSoda += generate[i];
        }

        yield(time);
        print.print(Printer::BottlingPlant, 'G', totalSoda);

        // Wait for truck to puck up production run
        _Accept(getShipment) {}
        or
            _Accept(~BottlingPlant) { break; }
    }

    print.print(Printer::BottlingPlant, 'F');
    shutdown = true;
    try
    {
        _Enable
        {
            _Accept(getShipment);
        }
    }
    catch (uMutexFailure::RendezvousFailure)
    {
        // This is expected, it should not complete if the plant is finished
    }
}

