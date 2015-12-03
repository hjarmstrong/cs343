#include "parent.h"
#include "MPRNG.h"

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) : 
    print(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}

void Parent::main()
{
    _Accept(~Parent)
    {
        return;
    }
    _Else
    {
        yield(parentalDelay);
        
        int student = safeRandom(1, numStudents);
        int amount = safeRandom(1, 3);

        bank.deposit(student, amount);
    }
}
