#include <iostream>
#include <sstream>
#include <ctime>
#include "MPRNG.h"
#include "bank.h"
#include "bottlingplant.h"
#include "config.h"
#include "groupoff.h"
#include "nameserver.h"
#include "parent.h"
#include "printer.h"
#include "student.h"
#include "truck.h"
#include "vendingmachine.h"
#include "watcard.h"
#include "watcardoffice.h"


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
    ConfigParms params;
    unsigned int seed;

    switch(argc)
    {
        case 3:  
        {
            std::stringstream conv(argv[2]);
            conv >> seed;
            if(conv.fail() || seed <= 0) 
            {
                usage();
                return;
            }
            safeRandom.seed(seed);
        } /* FALL THROUGH! */
        case 2:
            processConfigFile(argv[1], params); 
         break

         default:
             
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
