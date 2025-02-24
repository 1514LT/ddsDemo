#include <iostream>
#include <thread>
#include "Main.hpp"
#include "Slave.hpp"
#include "Leader.hpp"
#include <stdlib.h>
#include <unistd.h>
#define SHMTRANSPORT 0
#define UDPTRANSPORT 1
#define TCPTRANSPORT 2
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
  int timeinterval = 1000 * 5;
    int Node = 0;
    if(argc < 2)
    {
        std::cerr << "error: missing node argument" << std::endl;
        printHelp();
    }

    std::string arg1 = argv[1];
    if(arg1 == "main")
    {
      Node = 1;
    }
    else if(arg1 == "slave")
    {
      Node = 2;
    }
    else if(arg1 == "leader")
    {
      Node = 3;
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
    if(Node == 1)
    {
      // nodeA
      Main main;
      main.init();
    }
    else if (Node == 2)
    {
      // node B
      Slave slave;
      slave.init();
    }
    else if(Node == 3)
    {
      Leader leader;
      leader.init(SHMTRANSPORT);

      while (true)
      {
        if(leader.RestartInfoMatched())
        {
          RestartInfo msgMain;
          msgMain.participant(0x00);
          msgMain.transportType(0x02);
          leader.PublishRestartInfo(msgMain);
          sleep(10);
          // std::this_thread::sleep_for(std::chrono::microseconds(10000));
          RestartInfo msgSlave;
          msgSlave.participant(0x01);
          msgSlave.transportType(0x02);
          leader.PublishRestartInfo(msgSlave);
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1000));
      }
      

    }
  return 0;
}
