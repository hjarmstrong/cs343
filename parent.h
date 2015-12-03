#ifndef PARENT_H
#define PARENT_H

#include "printer.h"
#include "bank.h"

_Task Parent 
{
  private:
    void main();
    Printer &print;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
