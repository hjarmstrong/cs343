#ifndef PARENT_H
#define PARENT_H

#include "printer.h"
#include "bank.h"

Task Parent 
{
  private:
    void main();
    Printer &print;
    Bank bank;
    unsinged int numStudents;
    unsinged int parentalDelay;
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif
