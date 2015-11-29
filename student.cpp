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

    WATCARD::FWATCard card = office.create(id, 5);
    WATCARD::FWATCard gift = griup.giftCard();

    for(;;)
    {
        VendingMachine *machine = server.getMachine(id);
        yield(safeRandom(1, 10))
       
        while(!card.available() && !gift.available())
        {
                yield();
        }

    }
}
