#include <iostream>
#include <assert.h>
#include "groupoff.h"
#include "watcard.h"
#include "MPRNG.h"

void Groupoff::main()
{
    for(unsigned int i = 0; i < numStudents; i++)
    {
        _Accept(giftCard) //Accept a call from each student
    }
    for(unsigned int i = 0; i < numStudents; i++)
    {
        _Accept(~Groupoff)
        {
            assert(false);
            return;
        }
        _Else
        {
            yield(groupoffDelay);
            WATCard *card = new WATCard();
            card->deposit(sodaCost);
                        
            int index = safeRandom(0, cards.size() - 1);
            cards.at(index).delivery(card);
            print.print(Printer::Groupoff, 'D', sodaCost);

            cards.erase(cards.begin() + index);
        }
    }
            print.print(Printer::Groupoff, 'F');
}

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay) : 
print(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) 
{
    print.print(Printer::Groupoff, 'S');
}

WATCard::FWATCard Groupoff::giftCard()
{
    WATCard::FWATCard card;
    cards.push_back(card);
    return card; //Return cards[index]
}
