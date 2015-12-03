#include "student.h"
#include "MPRNG.h"
#include "watcard.h"
#include "nameServer.h"
#include "watcardoffice.h"
#include "groupoff.h"
#include "vendingmachine.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
        unsigned int id, unsigned int maxPurchases )
: print(prt), server(nameServer), office(cardOffice), group(groupoff), id(id), maxBuy(maxPurchases) 
{
}

void Student::main()
{
    int toBuy = safeRandom(1, maxBuy);
    int fav = safeRandom(0, 3);

    VendingMachine *machine = server.getMachine(id);

    WATCARD::FWATCard card = office.create(id, 5);
    WATCARD::FWATCard gift = group.giftCard();

    yield(safeRandom(1, 10));

    for(int i = 0; i <maxBuy; i++)
    {
        try
        { 
            _Enable
            {
                _Select(card)
                {
                   machine->buy(fav, card);
                }
                or
                _Select(gift)
                {
                    machine->buy(fav, gift);
                    gift.reset();
                }

                yield(safeRandom(1, 10));
            }
        }
        catch(WATCardOffice::Lost)
        {
            card = office.create(id, 5);
            i--;
        }
        catch(VendingMachine::Funds)
        {
            office.transfer(id, machine->cost() + 5, card);
            i--;
        }
        catch(VendingMachine::Stock)
        {
            machine = server.getMachine(id);
            i--;
        }
    }
}
