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

void BottlingPlant::main()
{
    Truck truck(print, server, *this, machines, maxStock);

    for(;;)
    {
        _Accept(~BottlingPlant)
        {
            print.print(Printer::BottlingPlant, 'F');
            break;
        }
        _Else
        {
            generate = safeRandom(0, maxShipped);

            yield(time);
            print.print(Printer::BottlingPlant, 'G', generate);

            // Wait for truck to puck up production run
            _Accept(getShipment);
        }
    }

    shutdown = true;
}

void BottlingPlant::getShipment(unsigned int cargo[])
{
    if(shutdown)
    {
        _Throw Shutdown();
    }

    for(int i = 0; i < VendingMachine::NUM_FLAVOURS; i++)
    {
        cargo[i] = generate;
    }
    print.print(Printer::BottlingPlant, 'P');
}
