#include "vendingmachine.h"

VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, 
        unsigned int sodaCost, unsigned int maxStockPerFlavour) : throwStock(false),
    throwFunds(false), print(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
    maxStockPerFlavour(maxStockPerFlavour), currentStock(new unsigned int[NUM_FLAVOURS])
{
    print.print(Printer::Vending, id, 'S', sodaCost);

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
        try
        {
            _Enable
            {
                _Accept(~VendingMachine)
                {
                    print.print(Printer::Vending, id, 'F');
                    return;
                }
                or _Accept(VendingMachine::inventory)
                {
                    print.print(Printer::Vending, id, 'r');
                    _Accept(~VendingMachine)
                    {
                        return;
                    }
                    or _Accept(VendingMachine::restocked)
                    {
                        print.print(Printer::Vending, id, 'R');
                    }
                }
                or _Accept(VendingMachine::buy)
                {
                    if(currentStock[buyRequest] < 1)
                    {
                        throwStock = true;
                    }
                    else if(cardRequest->getBalance() < sodaCost)
                    {
                        throwFunds = true;
                    }
                    buying.signalBlock();
                }
            }
        }
        catch (uMutexFailure::RendezvousFailure)
        {
            // This is expected, move on
        }
    }
}

void VendingMachine::buy(Flavours flavour, WATCard &card)
{
    buyRequest = flavour;
    cardRequest = &card;
    buying.wait();
    if(throwStock)
    {
        throwStock = false;
        _Throw Stock();
    }
    else if(throwFunds)
    {
        throwFunds = false;
        _Throw Funds();
    }
    else
    {

        currentStock[flavour] -= 1;
        card.withdraw(sodaCost);

        print.print(Printer::Vending, id, 'B', flavour, currentStock[flavour]);
    }
}

unsigned int *VendingMachine::inventory()
{
    return currentStock;
}

void VendingMachine::restocked()
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
