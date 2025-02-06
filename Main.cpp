#include <iostream>
#include <thread>
#include "MainnodePublisher.hpp"
#include "MainnodeSubscriber.hpp"
#include "SlavenodePublisher.hpp"
#include "SlavenodeSubscriber.hpp"

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

int main(int argc, char * argv[])
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
      MainnodePublisher publisher;
      publisher.init();
      while (true)
      {  
        if(publisher.timeBroadcastMatched())
        {
          // to do fill TimeBroadcast Data;
          // printf("timeBroadcastMatched\n");
          TimeBroadcast timeBroadcast;
          timeBroadcast.number(10);
          timeBroadcast.seconds(12345);
          timeBroadcast.milliseconds(678);
          publisher.publishTimeBroadcast(timeBroadcast);
        }
        if(publisher.trackBroadcastMatched())
        {
            // to do fill TrackBroadcast Data;
            TrackBroadcast trackBroadcast;
            
            publisher.publishTrackBroadcast(trackBroadcast);
        }
        if(publisher.attitudeBroadcastMatched())
        {
            // to do fill AttitudeBroadcast Data;
            AttitudeBroadcast attitudeBroadcast;

            publisher.publishAttitudeBroadcast(attitudeBroadcast);
        }
        if(publisher.trackPredictMatched())
        {
            // to do fill TrackPredict Data;
            TrackPredict trackPredict;
            publisher.publishTrackPredict(trackPredict);
        }
        if(publisher.telemetryRequestMatched())
        {
            // to do fill TelemetryRequest Data;
            TelemetryRequest telemetryRequest;
            publisher.publishTelemetryRequest(telemetryRequest);
        }
        if(publisher.paramPackageMatched())
        {
            // to do fill ParamPackage Data;
            ParamPackage paramPackage;
            publisher.publishParamPackage(paramPackage);
        }
      std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
    }
    else
    {
      MainnodeSubscriber subscriber;
      subscriber.init();
      while (1)
      {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
      
    }

    return 0;
}