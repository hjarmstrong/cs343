#include "bank.h"

Bank::Bank(unsinged int numStudents) : numStudents(numStudents) 
{
    for(unsigned int i = 0; i < numStudents; i++)
    {
        accounts[i] = 0;
    }
}

void Bank::deposit(unsigned int id, unsigned int amount)
{
    accounts[i] += amount;
}

void Bank::withdraw(unsigned int id, unsigned int amount)
{
    while(accounts[i] < amount) //busy wait? 
    {
        _Accept(~Bank)
        {
            return;
        }
        or _Accept(deposit);
    }
    accounts[i] -= amount;
}