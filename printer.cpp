#include <iostream>
#include <assert.h>
#include "printer.h"
#include "watcardoffice.h"

void Printer::flush()
{
    for(unsigned int i = 0; i < elements; i++)
    {
        if(buffer[i].inUse == true)
        {
            std::cout << buffer[i].state;
            switch(buffer[i].state)
            {
                case 'D':
                    std::cout << buffer[i].value1;

                    if(!(i == Groupoff))
                    {
                        std::cout << ',' <<  buffer[i].value2;
                    }
                    break;

                case 'C':     
                    std::cout << buffer[i].value1 << ',' <<  buffer[i].value2;
                    break;

                case 'T':
                    std::cout << buffer[i].value1 << ',' <<  buffer[i].value2;
                    break;

                case 'R':
                    std::cout << buffer[i].value1;
                    break;

                case 'N':
                    std::cout << buffer[i].value1 << ',' <<  buffer[i].value2;
                    break;

                case 'P':
                    std::cout << buffer[i].value1;
                    break;

                case 'd':
                    std::cout << buffer[i].value1 << ',' <<  buffer[i].value2;
                    break;

                case 'U':
                    std::cout << buffer[i].value1 << ',' <<  buffer[i].value2;
                    break;
            }
            buffer[i].inUse = false;
        }
        std::cout << "\t";
    }
    std::cout << std::endl;
}

void Printer::finalState(Kind kind, unsigned int id = ~0u)
{
    for(unsigned int i = 0; i < elements; i++)
    {
        if((i == kind && (id == ~0u)) || (buffer[i].lid == id))
        {
            std::cout << "F";
        }
        else
        {
            std::cout << "...";
        }
        std::cout << "\t";
    }
    std::cout << std::endl;
}

int Printer::getIndex(Kind kind, unsigned int lid)
{
    switch(kind)
    {
        case Student:
            return 6 + lid;

        case Vending:
            return 6 + numStudents + lid;

        case Courier:
            return 6 + numStudents + numVendingMachines + lid; 
    }
    assert(false);
}

    Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
: elements(numStudents + numVendingMachines + numCouriers + 6), 
    numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers),
    buffer(new bufferElement[elements])
{

    std::cout << "Parent" << "\t";
    std::cout << "Groupoff" << "\t";
    std::cout << "WATOff" << "\t";
    std::cout << "Names" << "\t";
    std::cout << "Truck" << "\t";
    std::cout << "Plant" << "\t";

    for(unsigned int i = 0; i < numStudents; i++)
    {
        std::cout << "Stud" << i << "\t";
    }

    for(unsigned int i = 0; i < numVendingMachines; i++)
    {
        std::cout << "Mach" << i << "\t";
    } 

    for(unsigned int i = 0; i < numCouriers; i++)
    {
        std::cout << "Cour" << i << "\t";
    } 

    std::cout << std::endl;

    for(unsigned int i = 0; i < elements; i++)
    {
        std::cout << "*******" << "\t";
    }
    std::cout << std::endl;
}

Printer::~Printer()
{
    delete []buffer;
}

void Printer::print( Kind kind, char state )
{
    if(state == 'F')
    {
        flush();
        finalState(kind);
    }
    else
    {
        if(buffer[kind].inUse == true)
        {
            flush();
        }
        buffer[kind].inUse = true; 
        buffer[kind].state = state;
    }
}

void Printer::print( Kind kind, char state, int value1 )
{
    if(buffer[kind].inUse == true)
    {
        flush();
    } 
    buffer[kind].inUse = true;
    buffer[kind].state = state;
    buffer[kind].value1 = value1;
}


void Printer::print( Kind kind, char state, int value1, int value2 )
{
    if(buffer[kind].inUse == true)
    {
        flush();
    } 
    buffer[kind].inUse = true;
    buffer[kind].state = state;
    buffer[kind].value1 = value1;
    buffer[kind].value2 = value2;
}

void Printer::print( Kind kind, unsigned int lid, char state )
{
    int index = getIndex(kind, lid);

    if(state == 'F')
    {
        flush();
        finalState(kind, lid);
    }
    else
    {
        if(buffer[index].inUse == true)
        {
            flush();
        }
        buffer[index].inUse = true; 
        buffer[index].state = state;
        buffer[index].lid = lid;
    }
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 )
{
    int index = getIndex(kind, lid);

    if(buffer[index].inUse == true)
    {
        flush();
    } 
    buffer[index].inUse = true;
    buffer[index].state = state;
    buffer[index].lid = lid;
    buffer[index].value1 = value1;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 )
{
    int index = getIndex(kind, lid);

    if(buffer[index].inUse == true)
    {
        flush();
    } 
    buffer[index].inUse = true;
    buffer[index].state = state;
    buffer[index].lid = lid;
    buffer[index].value1 = value1;
    buffer[index].value2 = value2;
}
