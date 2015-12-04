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
        couriers.push_back(new Courier(print, *this, bank, i));
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
        or _Accept(create) {}
        or _Accept(requestWork) {}
        or _Accept(transfer);
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
        or _Accept(create) {}
        or _Accept(transfer);
    }

    Job *ret = work.front();
    work.pop();

    print.print(Printer::WATCardOffice, 'W');
    return ret;
}


    WATCardOffice::Courier::Courier(Printer &print, WATCardOffice &off, Bank &bnk, unsigned int id)
: print(print), office(off), bank(bnk), id(id)
{
    print.print(Printer::Courier, id, 'S');
}

void WATCardOffice::Courier::main()
{
    for(;;)
    {

        Job *current = office.requestWork();
        
        if(!current)
        {
            print.print(Printer::Courier, id, 'F');
            return;
        }

        print.print(Printer::Courier, id, 't', current->id, current->reqVal);
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
            print.print(Printer::Courier, id, 'T', current->id, current->reqVal);
        }
        delete current;
    }
}
