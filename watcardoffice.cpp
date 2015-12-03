#include "MPRNG.h"
#include <vector>
#include "watcardoffice.h"
#include "watcard.h"

    WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers )
: print(prt), bank(bank), numCouriers(numCouriers)
{
    print.print(Printer::WATCardOffice, 'S');
}

WATCard::FWATCard WATCardOffice::create(unsigned int sid, unsigned int amount)
{
    WATCard::FWATCard newCard;
    work.push(new Job(sid, amount, newCard, NULL));
    
    print.print(Printer::WATCardOffice, 'C', sid, amount);
    return newCard;
}

void WATCardOffice::main()
{
    std::vector<Courier *> couriers;
    couriers.reserve(numCouriers);

    for(unsigned int i = 0; i < numCouriers; i++)
    {
        couriers.push_back(new Courier(*this, bank));
    }

    for(;;)
    {
        _Accept(~WATCardOffice)
        {
            for(unsigned int i = 0; i < couriers.size(); i++)
            {
                delete couriers.at(i);
            }

            print.print(Printer::WATCardOffice, 'F');
            return;
        }
        or _Accept(create);
    }
}

WATCard::FWATCard WATCardOffice::transfer(unsigned int sid, unsigned int amount, WATCard *card)
{
    WATCard::FWATCard newCard;
    work.push(new Job(sid, amount, newCard, card));
    
    print.print(Printer::WATCardOffice, 'T', sid, amount);
    return newCard;
}

WATCardOffice::Job *WATCardOffice::requestWork()
{
    if(work.empty())
    {
        _Accept(~WATCardOffice)
        {
            return NULL;
        }
        or _Accept(create);
    }

    Job *ret = work.front();
    work.pop();

    print.print(Printer::WATCardOffice, 'W');
    return ret;
}


    WATCardOffice::Courier::Courier(WATCardOffice &off, Bank &bnk)
: office(off), bank(bnk)
{
}

void WATCardOffice::Courier::main()
{
    for(;;)
    {
        Job *current = office.requestWork();
        
        if(!current)
        {
            return;
        }

        bank.withdraw(current->id, current->reqVal);
        if(safeRandom(0,5) == 0)
        {
            current->result.exception(new Lost());
        }
        else
        {
            WATCard *card;

            if(current->oldcard == NULL)
            {
                card =  new WATCard();
            }
            else
            {
                card = current->oldcard;
            }

            card->deposit(current->reqVal);
            current->result.delivery(card);
        }
        delete current;
    }
}
