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
        std::cout << "Usage: ./soda [ config-file [ random-seed (> 0) ] ]" << std::endl;

    }
}

void uMain::main()
{
    ConfigParms params;
    int seed;

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
            {
                processConfigFile(argv[1], params); 
            } 
            break;
        case 1:
            {
                processConfigFile("soda.config", params);
            }
            break;
        default:
            {
                usage();
                return;
            }
    }


    {
        Printer output(params.numStudents, params.numVendingMachines, params.numCouriers);
        Bank bank(params.numStudents);
        Parent parent(output, bank, params.numStudents, params.parentalDelay);
        WATCardOffice office(output, bank, params.numCouriers);
        Groupoff groupoff(output, params.numStudents, params.sodaCost, params.groupoffDelay);
        NameServer nameserver(output, params.numVendingMachines, params.numStudents);

        VendingMachine *machines[params.numVendingMachines];
        for(unsigned int i = 0; i < params.numVendingMachines; i++)
        {
            machines[i] = new VendingMachine(output, nameserver, i, params.sodaCost, params.maxStockPerFlavour);
        }

        BottlingPlant *plant = new BottlingPlant(output, nameserver, params.numVendingMachines, params.maxShippedPerFlavour, params.maxStockPerFlavour, params.timeBetweenShipments);

        Student *students[params.numStudents];
        for(unsigned int i = 0; i < params.numStudents; i++)
        {
            students[i] = new Student(output, nameserver, office, groupoff, i, params.maxPurchases);
        }


        for(unsigned int i = 0; i < params.numStudents; i++)
        {
            delete students[i];
        }

        delete plant;

        for(unsigned int i = 0; i < params.numVendingMachines; i++)
        {
            delete machines[i];
        }
    }
    std::cout << "***********************" << std::endl;
}    
