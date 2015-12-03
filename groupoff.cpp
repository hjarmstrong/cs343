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
            print.print(Printer::Groupoff, 'F');
            return;
        }
        _Else
        {
            yield(groupoffDelay);
            WATCard *card = new WATCard();
            card->deposit(sodaCost);
            
            int index = safeRandom(0, cards.size());
            
            cards.at(index).delivery(card);
            print.print(Printer::Groupoff, 'D', sodaCost);

            cards.erase(cards.begin() + index);
        }
    }
}

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay) : 
print(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) 
{
    print.print(Printer::Groupoff, 'S');
}

WATCard::FWATCard Groupoff::giftCard()
{
    unsigned int temp = index;
    index += 1; 
    index %= numStudents; //Increment index for the next caller
    return cards[temp]; //Return cards[index]
}
