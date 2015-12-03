#include "student.h"
#include "MPRNG.h"
#include "watcard.h"
#include "nameserver.h"
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
    unsigned int toBuy = safeRandom(1, maxBuy);
    VendingMachine::Flavours fav = static_cast<VendingMachine::Flavours>(safeRandom(0, 3));

    VendingMachine *machine = server.getMachine(id);

    WATCard::FWATCard card = office.create(id, 5);
    WATCard::FWATCard gift = group.giftCard();

    yield(safeRandom(1, 10));

    for(unsigned int i = 0; i < toBuy; i++)
    {
        try
        { 
            _Enable
            {
                _Select(card)
                {
                   machine->buy(fav, *card);
                }
                or
                _Select(gift)
                {
                    machine->buy(fav, *gift);
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
