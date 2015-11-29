#include "watcard.h"

WATCard::WATCard() : balance(0)
{
}

void WATCard::deposit( unsigned int amount )
{
    balance += amount;
}

void WATCard::withdraw( unsigned int amount )
{
    balance -= amount; // do what if there is no space?
}

unsigned int WATCard::getBalance()
{
    return balance;
}

