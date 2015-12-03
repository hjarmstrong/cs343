#ifndef NAMESERVER_H
#define NAMESERVER_H

_Task NameServer;

#include "vendingmachine.h"
#include "printer.h"

_Task NameServer {
    void main();

    Printer print;
    unsigned int numVendingMachines;
    unsigned int numRegisteredMachines = 0;
    unsigned int numStudents;
    VendingMachine **machineList;
  public:
    NameServer(Printer &prt, unsigned int numVendingMachines, unsigned int numStudents);
    void VMregister(VendingMachine *vendingmachine);
    VendingMachine *getMachine(unsigned int id);
    VendingMachine **getMachineList();
};

#endif
