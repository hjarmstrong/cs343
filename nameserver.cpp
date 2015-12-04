#include <assert.h>
#include "nameserver.h"

NameServer::NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents) :
    print(prt), numVendingMachines(numVendingMachines), 
    numStudents(numStudents), machineList(new VendingMachine *[numVendingMachines])
{
    print.print(Printer::NameServer, 'S');

    for(unsigned int i = 0; i < numStudents; i++)
    {
        assignments[i] = i % numVendingMachines;
    }
}

NameServer::~NameServer()
{
    delete []machineList;
}

void NameServer::VMregister(VendingMachine *vendingmachine)
{
    unsigned int temp = numRegisteredMachines;
    machineList[temp] = vendingmachine;
    numRegisteredMachines++;

    print.print(Printer::NameServer, 'R', temp);
}

VendingMachine *NameServer::getMachine(unsigned int id)
{
    int index = assignments[id];
    assignments[id] = (assignments[id] + 1) % numVendingMachines;

    print.print(Printer::NameServer, 'N', id, index);
    print.print(Printer::Student, id, 'V', index);
    return machineList[index];
}

VendingMachine **NameServer::getMachineList()
{
    return machineList;
}

void NameServer::main()
{
    for(unsigned int i = 0; i < numVendingMachines; i++)
    {
        _Accept(~NameServer)
        {
            assert(false);
            return;
        }
        or
        _Accept(NameServer::VMregister)
        {
        }
    }

    for(;;)
    {
        _Accept(~NameServer)
        {
            print.print(Printer::NameServer, 'F');
            return;
        }
        or
            _Accept(getMachine) {}
        or
            _Accept(getMachineList);
    }
}
