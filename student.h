#ifndef STUDENT_H
#define STUDENT_H

#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "groupoff.h"

_Task Student {
    void main();

    Printer &print;
    NameServer &server
    WATCardOffice &office;
    Groupoff &group;
    unsigned int id;
    unsigned int maxBuy;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, Groupoff &groupoff,
             unsigned int id, unsigned int maxPurchases );
};

#endif
