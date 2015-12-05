#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

_Task VendingMachine;

#include "printer.h"
#include "nameserver.h"
#include "watcard.h"

_Task VendingMachine 
{
  private:
    void main();

    uCondition buying;
    bool throwStock;
    bool throwFunds;

    Printer &print; 
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    unsigned int *currentStock;
    
  public:
    enum Flavours {blue, cream, root, lime, NUM_FLAVOURS};
    _Event Funds {};                       // insufficient funds
    _Event Stock {};                       // out of stock for particular flavour
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    void buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
    
    private:
      Flavours buyRequest;
      WATCard *cardRequest;
};

#endif
