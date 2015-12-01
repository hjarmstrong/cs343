#include "groupoff.h"
#include "watcard.h"

_Task Groupoff {
  private:
    Printer &print;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDela;

    std::vector<WATCard::FWATCard> cards;
    void main();
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


void Groupoff::main()
{
    for(unsigned int i = 0; i < numStudents; i++)
    {
        _Accept(Groupoff::giftCard) //Accept a call from each student
    }
    for(unsigned int i = 0; i < numStudents; i++)
    {
        _Accept(~Groupoff)
        {
            return;
        }
        _Else
        {
            yield(groupoffDelay);
            WATCard card = new WATCard();
            card.deposit(sodaCost);
            cards[safeRandom(0, numStudents-1)] = card;
        }
    }
    _Accept(~Groupoff)
    {
        return;
    }
}

Groupoff::Groupoff(Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay) : 
print(prt), numStudents(numStudents), sodaCost(sodaCost), groupoffDelay(groupoffDelay) 
{
}

WATCard::FWATCard Groupoff::giftCard()
{
    unsigned int temp = index;
    index += 1; 
    index %= numStudents; //Increment index for the next caller
    return cards[temp]; //Return cards[index]
}