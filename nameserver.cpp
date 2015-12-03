#include <assert.h>
#include "nameserver.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
print(prt), numVendingMachines(numVendingMachines), numStudents(numStudents)
{
}

void NameServer::main()
{
    for(unsigned int i = 0; i < numVendingMachines; i++)
    {
        _Accept(~NameServer)
        {
            return;
        }
        _Accept(NameServer::VMregister)
        {
        }
    }

    for(;;)
    {
        _Accept(~NameServer)
        {
            return;
        }
    }
}

void NameServer::VMregister(VendingMachine *vendingmachine)
{
   unsigned int temp = numRegisteredMachines;
   numRegisteredMachines += 1; 
   machineList[temp] = vendingmachine;
}

VendingMachine *NameServer::getMachine(unsigned int id)
{
    assert(id < numRegisteredMachines);
    return machineList[id];
}

VendingMachine **NameServer::getMachineList()
{
    return machineList;
}
