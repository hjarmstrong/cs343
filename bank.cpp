#include "bank.h"

Bank::Bank(unsigned int numStudents) : numStudents(numStudents), accounts(new unsigned int [numStudents])
{
    for(unsigned int i = 0; i < numStudents; i++)
    {
        accounts[i] = 0;
    }
}

Bank::~Bank()
{
    delete []accounts;
}

void Bank::deposit(unsigned int id, unsigned int amount)
{
    accounts[id] += amount;
}

void Bank::withdraw(unsigned int id, unsigned int amount)
{
    while(accounts[id] < amount) 
    {
        _Accept(~Bank)
        {
            return;
        }
        or _Accept(deposit);
    }
    accounts[id] -= amount;
}
