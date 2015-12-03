#ifndef WATCARDOFFICE_H
#define WATCARDOFFICE_H

_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;          // return future
        Job(Args args) : args( args ) {}
    };
    _Task Courier { ... };                 // communicates with bank

    void main();

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