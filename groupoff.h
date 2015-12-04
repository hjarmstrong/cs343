#ifndef GROUPOFF_H
#define GROUPOFF_H

#include <vector>
#include "watcard.h"
#include "printer.h"

_Task Groupoff {
  private:
    void main();

    Printer &print;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;
    unsigned int index = 0;
    std::vector<WATCard::FWATCard *> cards;
  public:
    Groupoff( Printer &prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};

#endif
