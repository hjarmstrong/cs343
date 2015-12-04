#include <iostream>
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

    print.print(Printer::Student, id, 'S', fav, toBuy);

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
               // std::cout << "Fuck";
                _Select(card)
                {
                   machine->buy(fav, *card);
                   print.print(Printer::Student, id, 'B', (*card).getBalance());
                }
                or
                _Select(gift)
                {
                    machine->buy(fav, *gift); 
                    print.print(Printer::Student, id, 'G', (*gift).getBalance());
                    
                    gift.reset();
                }

                yield(safeRandom(1, 10));
            }
        }
        catch(WATCardOffice::Lost)
        {
            print.print(Printer::Student, id, 'L');

            card = office.create(id, 5);
            i--;
        }
        catch(VendingMachine::Funds)
        {
            WATCard *japan = card;
            card.reset();
            card = office.transfer(id, machine->cost() + 5, japan);
            i--;
        }
        catch(VendingMachine::Stock)
        {
            machine = server.getMachine(id);
            i--;
        }
    }


   print.print(Printer::Student, id, 'F');
}
