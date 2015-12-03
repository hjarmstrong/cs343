#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, 
    unsigned int sodaCost, unsigned int maxStockPerFlavour) : print(prt), 
    nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour),
    currentStock(new unsigned int[NUM_FLAVOURS])
{
    print.print(Printer::Vending, 'S', sodaCost);

    for (int i = 0; i < NUM_FLAVOURS; i++)
    {
        currentStock[i] = 0;
    }
}

VendingMachine::~VendingMachine()
{
    delete []currentStock;
}

void VendingMachine::main()
{
    nameServer.VMregister(this); //Register with NameServer

    for(;;)
    {
        _Accept(~VendingMachine)
        {
            print.print(Printer::Vending, 'F');
            return;
        }
        or _Accept(VendingMachine::inventory)
        {
            print.print(Printer::Vending, 'r');
            _Accept(~VendingMachine)
            {
                return;
            }
            or _Accept(VendingMachine::restocked)
            {
                print.print(Printer::Vending, 'R');
            }
        }
        or _Accept(VendingMachine::buy)
        {
        }
    }
}

void VendingMachine::buy(Flavours flavour, WATCard &card)
{
    if(currentStock[flavour] < 1)
    {
        _Throw Stock();
    }
    else if(card.getBalance() < sodaCost)
    {
        _Throw Funds();
    }
    else
    {
        
        currentStock[flavour] -= 1;
        card.withdraw(sodaCost);
        
        print.print(Printer::Vending, 'B', flavour, currentStock[flavour]);
    }
}

unsigned int *VendingMachine::inventory()
{
    return currentStock;
}

void restocked()
{
    //Allow sales to continue;
}

_Nomutex unsigned int VendingMachine::cost()
{
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
    return id;
}
