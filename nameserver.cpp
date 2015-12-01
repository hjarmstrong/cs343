_Task NameServer {
    void main();

    Printer print;
    unsigned int numVendingMachines;
    unsigned int numStudents;
  public:
    NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents);
    void VMregister(VendingMachine *vendingmachine);
    VendingMachine *getMachine(unsigned int id);
    VendingMachine **getMachineList();
};

#include "namerserver.h"


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

VendingMachine *VendingMachine::getMachine(unsigned int id)
{
    return machineList[id % numRegisteredMachines]; //Correct? Need cycle?
}

VendingMachine **VendingMachine::getMachineList()
{
    return machineList;
}
