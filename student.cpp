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

    for(;;)
    {
        try
        { 
            _Enable
            {

                yield(safeRandom(1, 10))

                    _Select(card)
                    {
                        machine.buy(fav, card);
                    }
                or _Select(gift)
                {
                    machine.buy(fav, gift);
                    gift.reset();
                    gift = group.giftCard();
                }
            }
        }
        catch(WATCardOffice::Lost)
        {
            card = office.create(id, 5);
        }
        catch(VendingMachine::Funds)
        {
        }
        catch(VendingMachine::Stock)
        {
            machine = server.getMachine(id);
        }
    }
}
