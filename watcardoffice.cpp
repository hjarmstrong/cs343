#include "watcardoffice.h"
#include "watcard.h"

WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) : 
    print(prt), bank(bank), numCouriers(numCouriers)
{
}

void WATCardOffice::main()
{
    Courier couriers[numCouriers];

    for(;;)
    {
        _Accept(create);
    }
}

WATCard::FWATCard create(unsigned int sid, unsigned int amount)
{
    FWATCard newCard;
    work.push(new Job(sid, amount, newCard));
    return newCard;
}

WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, WATCard *card)
{
}

Job *requestWork()
{
    if(work.empty())
    {
        _Accept(~WATCardOfiice)
        {
            return;
        }
        or
            _Accept(create)
    }

    Job *ret = work.front();
    work.pop();
    return ret;
}


    Courier::Courier(WATCardOffice off, Bank bnk)
: office(off), bank(bnk)
{
}

void Courier::main()
{
    for(;;)
    {
        Job *current = office.requestWork();
        bank.widthdraw(current->id, current->reqVal);
        if(safeRandom(0,5) == 0)
        {
            current->card.exception(new Lost());
        }
        else
        {
            WATCard *card =  new WATCard();
            card->deposit(current->reqVal);
            current->card = card;
        }
        delete job;
    }
}
