#include "parent.h"
#include "MPRNG.h"

Parent::Parent(Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay) : 
    print(prt), bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) 
{
    print.print(Printer::Parent, 'S');
}

void Parent::main()
{
    for(int i = 0;i < 10; i++)
    {
        _Accept(~Parent)
        {
            print.print(Printer::Parent, 'F');
            return;
        }
        _Else
        {
            yield(parentalDelay);

            int student = safeRandom(0, numStudents - 1);
            int amount = safeRandom(1, 3);

            print.print(Printer::Parent, 'D', student, amount);
            bank.deposit(student, amount);
        }
    }
}
