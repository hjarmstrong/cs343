#include "q3printer.h"

void Printer::flush()
{
    for(unsigned int i = 0; i < voters; i++)
    {
        if(buffer[i].inUse == true)
        {
            switch(buffer[i].state)
            {
                case 'S':
                    std::cout << "S";
                    break;

                case 'V':
                    if(buffer[i].vote == TallyVotes::Statue)
                    {
                        std::cout << "V " << "s";
                    }
                    else
                    {
                        std::cout << "V " << "p";
                    }
                    break;

                case 'B':
                    std::cout << "B " << buffer[i].numBlocked;
                    break;

                case 'U':
                    std::cout << "U " << buffer[i].numBlocked;
                    break;

                case 'b':
                    std::cout << "b";
                    break;

                case 'C':
                    std::cout << "C";
                    break;
            }
            buffer[i].inUse = false;
        }
        std::cout << "\t";
    }
    std::cout << std::endl;
}

Printer::Printer( unsigned int voters ) : buffer(new bufferElement[voters]), voters(voters)
{
    for(unsigned int i = 0; i < voters; i++)
    {
        std::cout << "Voter" << i << "\t";
    }
    std::cout << std::endl;

    for(unsigned int i = 0; i < voters; i++)
    {
        std::cout << "=======" << "\t";
    }
    std::cout << std::endl;
}

Printer::~Printer()
{
    delete []buffer;
}

void Printer::print( unsigned int id, Voter::States state )
{
    if(buffer[id].inUse == true)
    {
        flush();
    } 
    buffer[id].inUse = true;
    buffer[id].state = state;
}

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour vote )
{
    if(state == 'F')
    {
        flush();
        for(unsigned int i = 0; i < voters; i++)
        {
            if(i == id)
            {
                if(vote == TallyVotes::Statue)
                {
                    std::cout << "F " << "s";
                }
                else
                {
                    std::cout << "F " << "p";
                }
            }
            else
            {
                std::cout << "...";
            }
            std::cout << "\t";
        }
        std::cout << std::endl;
    }
    else
    {
        if(buffer[id].inUse == true)
        {
            flush();
        }
        buffer[id].inUse = true; 
        buffer[id].state = state;
        buffer[id].vote = vote;
    }
}

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked )
{
    if(buffer[id].inUse == true)
    {
        flush();
    }
    buffer[id].inUse = true;
    buffer[id].state = state;
    buffer[id].numBlocked = numBlocked;
}

