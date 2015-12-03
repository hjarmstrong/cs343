#include "truck.h"
#include "MPRNG.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
        unsigned int numVendingMachines, unsigned int maxStockPerFlavour )
: print(prt), server(nameServer), plant(plant),
    numMachines(numVendingMachines), maxStock(maxStockPerFlavour) 
{
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
            }
        }
        catch(BottlingPlant::Shutdown)
        {
            // no more soda, we are done
            return;
        }

        int zeros = 0;
        for(unsigned int i = 1; i <= numMachines; i++)
        {
            lastMachine = (lastMachine + i) % numMachines;

            unsigned int *stock = machines[lastMachine]->inventory();

            for(int j = 0; j < VendingMachine::NUM_FLAVOURS; j++)
            {
                while((cargo[j] > 0) && (stock[j] < maxStock))
                {
                    cargo[j]--;
                    if(cargo[j] == 0)
                    {
                        zeros++;
                    }

                    stock[j]++;
                }
            }
            if(zeros == VendingMachine::NUM_FLAVOURS)
            {
                // We are out of ssoda, remeber our last location
                break;
            }
        }
    }
}
