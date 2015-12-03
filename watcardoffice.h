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
        WATCard *oldcard; 
        Job(unsigned int id, unsigned int reqVal, WATCard::FWATCard card, WATCard *oldcard) 
            : id(id), reqVal(reqVal), result(card), oldcard(oldcard)
        {
        }
    };

    _Task Courier 
    {
        Printer &print;
        WATCardOffice &office;
        Bank &bank;
        void main();

        public:
        Courier(Printer &, WATCardOffice &, Bank &);
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
