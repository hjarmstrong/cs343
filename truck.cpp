#include <iostream>
#include "truck.h"
#include "MPRNG.h"

namespace
{
    int totalShipment(unsigned int *cargo)
    {
        int totalSodas = 0;
        for(int i = 0; i < VendingMachine::NUM_FLAVOURS; i++)
        {
            totalSodas += cargo[i];
        }
        return totalSodas;
    }
}

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
        unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
: print(prt), server(nameServer), plant(plant),
    numMachines(numVendingMachines), maxStock(maxStockPerFlavour) 
{
    print.print(Printer::Truck, 'S');
}

void Truck::main()
{
    VendingMachine **machines = server.getMachineList();
    int lastMachine = -1;
    unsigned int cargo[VendingMachine::NUM_FLAVOURS];

    for(;;)
    {
        yield(safeRandom(1,10));
        try
        {
            _Enable
            {
                plant.getShipment(cargo); 
                print.print(Printer::Truck, 'P', totalShipment(cargo));
            }
        }
        catch(BottlingPlant::Shutdown)
        {
            // no more soda, we are done
            print.print(Printer::Truck, 'F');
            return;
        }

        int zeros = 0; 
        for(unsigned int i = 0; i < numMachines; i++)
        {
            lastMachine = (lastMachine + 1) % numMachines;

            unsigned int *stock = machines[lastMachine]->inventory();
            print.print(Printer::Truck, 'd', lastMachine, totalShipment(cargo));

            for(int j = 0; j < VendingMachine::NUM_FLAVOURS; j++)
            {
                while((cargo[j] > 0) && (stock[j] < maxStock))
                {
                    cargo[j]--;
                    stock[j]++;

                    if(cargo[j] == 0)
                    {
                        print.print(Printer::Truck, 'U', lastMachine, maxStock - stock[j]);
                    }

                }

                if(cargo[j] == 0)
                {
                    zeros++;
                }
            }

            print.print(Printer::Truck, 'D', lastMachine, totalShipment(cargo));

            machines[lastMachine]->restocked();

            if(zeros == VendingMachine::NUM_FLAVOURS)
            {
                // We are out of ssoda, remeber our last location
                break;
            }
        }
    }
}
