#include <iostream>
#include <sstream>
#include <ctime>
#include "MPRNG.h"

MPRNG safeRandom;

namespace 
{
    void usage()
    {
        std::cout << "Usage: ./vote Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)" << std::endl;

    }
}

void uMain::main()
{
    unsigned int voters = 6;
    unsigned int groupSize = 3;
    unsigned int seed = time(NULL);

    switch(argc)
    {
        case 4:
        {
            std::stringstream conv(argv[3]);
            conv >> seed;
            if(conv.fail() || seed < 0)
            {
                usage();
                return;
            }
        }

        case 3:
        {
            std::stringstream conv(argv[2]);
            conv >> groupSize;
            if(conv.fail() || groupSize < 0 || ((groupSize % 2) == 0))
            {
                usage();
                return;
            }
        }
        case 2:
        {
            std::stringstream conv(argv[1]);
            conv >> voters;
            if(conv.fail() || voters < 0 || ((voters % groupSize) != 0))
            {std::cout << "test";
                usage();
                return;
            }

            break;
        }

        case 1: 
        break;
        
        default:
        usage();
        return;
    }
    
    safeRandom.seed(seed);

    Printer output(voters);
    TallyVotes tally(groupSize, output);

    Voter **tasks = new Voter *[voters];

    for(unsigned int i = 0; i < voters; i++)
    {
        tasks[i] = new Voter(i, tally, output);
    }

    for(unsigned int i = 0; i < voters; i++)
    {
        delete tasks[i];
    }

    delete []tasks;

    std::cout << "=================" << std::endl;
    std::cout << "All tours started" << std::endl;
}
