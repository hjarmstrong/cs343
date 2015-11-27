#ifndef PRINTER_H
#define PRINTER_H

#include <iostream>
#include "q3tallyVotes.h"
#include "q3voter.h"


struct bufferElement
{
    bool inUse;
    Voter::States state;
    TallyVotes::Tour vote;
    unsigned int numBlocked;
    bufferElement() : inUse(false)
    {
    }
};

_Monitor Printer 
{

    bufferElement *buffer;
    unsigned int voters;

    void flush();

    public:
    Printer( unsigned int voters );

    ~Printer();

    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
};

#endif
