#include <iostream>
#include <thread>
#include "MainNodeAPublisher.hpp"
#include "MainNodeASubscriber.hpp"
#include "SlaveNodeBPublisher.hpp"
#include "SlaveNodeBSubscriber.hpp"
#include "SlaveNodeCPublisher.hpp"
#include "SlaveNodeCSubscriber.hpp"
#include <stdlib.h>
#include <unistd.h>

static void printHelp()
{
    std::cout << "Usage: SatelliteOperationDemo <node> [options]"                                   << std::endl;
    std::cout << ""                                                                                 << std::endl;
    std::cout << "Nodes:"                                                                           << std::endl;
    std::cout << "  main                            Run a mainnode application"                     << std::endl;
    std::cout << "  slave                           Run a slavenode application"                    << std::endl;
    std::cout << ""                                                                                 << std::endl;
    std::cout << "Options:"                                                                         << std::endl;
    std::cout << "  -h, --help                      Print this help message"                        << std::endl;
    std::cout << "  -t <num>, --time <num>          Time interval of application to send data"      << std::endl;
    std::cout << "                                  unit: ms"                                       << std::endl;
    std::cout << "                                  (Default: 0 [as soon as system event has been processed])"
                                                                                                    << std::endl;
}
int main(int argc, char const *argv[])
{
  int timeinterval = 1000;
    bool mainNode = true;
    if(argc < 2)
    {
        std::cerr << "error: missing node argument" << std::endl;
        printHelp();
    }

    std::string arg1 = argv[1];
    if(arg1 == "main")
    {
        mainNode = true;
    }
    else if(arg1 == "slave")
    {
        mainNode = false;
    }
    else if(arg1 == "-h" || arg1 == "--help") 
    {
        printHelp();
    }
    else
    {
        std::cerr << "error: unsupported node " + arg1 << std::endl;
        printHelp();
    }

    for(int i = 2; i < argc; ++i)
    {
        std::string argi = argv[i];
        if(argi == "-h" || argi == "--help")
        {
            printHelp();
        }
        else if(argi == "-t" || argi == "--time")
        {
            timeinterval = std::stoi(argv[++i]);
        }
        else
        {
            std::cerr << "error: unknow option " + argi << std::endl;
            printHelp();
        }

    }
    if(mainNode)
    {
    }
    else
    {
      
    }
  return 0;
}
