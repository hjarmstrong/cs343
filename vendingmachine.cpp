#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, 
    unsigned int sodaCost, unsigned int maxStockPerFlavour) : printer(prt), 
    nameServer(nameServer), id(id), sodaCost(sodaCost), maxStockPerFlavour(maxStockPerFlavour)
{
    for (int i = 0; i < 4; i++) //Hardcoded number of flavours
    {
        currentStock[i] = 0;
    }
}

void VendingMachine::main()
{
    nameServer.VMregister(this); //Register with NameServer

    for(;;)
    {
        _Accept(~VendingMachine)
        {
            return;
        }
        or _Accept(VendingMachine::inventory)
        {
            _Accept(~VendingMachine)
            {
                return;
            }
            or _Accept(VendingMachine::restocked)
            {
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
        _Throw Stock;
    }
    else if(card.getBalance() < sodaCost)
    {
        _Throw Funds;
    }
    else
    {
        currentStock[int(flavour)] -= 1;
        card.withdraw(sodaCost);
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