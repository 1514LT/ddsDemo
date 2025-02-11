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
    int timeinterval = 1000 * 5;
    int mainNode = 0;
    if(argc < 2)
    {
        std::cerr << "error: missing node argument" << std::endl;
        printHelp();
    }

    std::string arg1 = argv[1];
    if(arg1 == "nodeA")
    {
        mainNode = 1;
    }
    else if(arg1 == "nodeB")
    {
        mainNode = 2;
    }
    else if(arg1 == "nodeC")
    {
      mainNode = 3;
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
    if(mainNode == 1)
    {
      // nodeA
      MainNodeAPublisher publisher;
      publisher.init();
      MainNodeASubscriber subscriber;
      subscriber.init();
      while (true)
      {
        if(publisher.GuidanceInfoMatched())
        {
          GuidanceInfo guidanceInfo;
          guidanceInfo.beatCount(11111);
          guidanceInfo.targetCount(5);
          guidanceInfo.startNode(0x00);
          guidanceInfo.targetNode(0x02);
          guidanceInfo.targetType(0x55);
          Target First,Second,Third,Fourth,Fifth;
          First.targetNumber(11111);
          std::array<u_int8_t,6> timeNumber = {0x00,0x5f,0x7a,0x0d,0x1b,0xfc};
          First.time(timeNumber);
          First.longitude(-9000000);
          First.latitude(-18000000);
          First.elevation(0);
          First.Priority(0);
          First.confidenceDegree(0);
          First.informationType(0x0001);
          First.positionAccuracy(20);
          First.imagingMode(0);
          First.desiredTrack(0);
          // try
          First.shipSpeed(0.1);
          std::array<u_int8_t,5> back;
          back.fill(0x00);
          First.back(back);

          guidanceInfo.First(First);
          guidanceInfo.Second(First);
          guidanceInfo.Third(First);
          guidanceInfo.Fourth(First);
          guidanceInfo.Fifth(First);
          publisher.PublishGuidanceInfo(guidanceInfo);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
      
    }
    else if (mainNode == 2)
    {
      // node B
      SlaveNodeBSubscriber subscriber;
      subscriber.init();
      while (true)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
      
    }
    else if(mainNode == 3)
    {
      // node C
      SlaveNodeCSubscriber subscriber;
      subscriber.init();
      while (true)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
    }
  return 0;
}
