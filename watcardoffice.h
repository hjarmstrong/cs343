#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

#include <queue>
#include "printer.h"
#include "bank.h"
#include "watcard.h"

_Task WATCardOffice 
{
    struct Job 
    {                           
        unsigned int id;
        unsigned int reqVal;

        WATCard::FWATCard result;        
        Job(unsigned int id, unsigned int reqVal, WATCard::FWATCard card) 
            : id(id), reqVal(reqVal), result(card)
        {
        }
    };

    _Task Courier 
    {
        Bank &bank;
        WATCardOffice &office;
        void main();

        public:
        Courier(WATCardOffice &, Bank &);
    };

    void main();

    std::queue<Job *> work;

    Printer &print;
    Bank &bank;
    unsigned int numCouriers;
    public:
    _Event Lost {};                        // lost WATCard
    WATCardOffice(Printer &prt, Bank &bank, unsigned int numCouriers);
    WATCard::FWATCard create(unsigned int sid, unsigned int amount);
    WATCard::FWATCard transfer(unsigned int sid, unsigned int amount, WATCard *card);
    Job *requestWork();
};

#endif
