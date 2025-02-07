#include <iostream>
#include <thread>
#include "MainnodePublisher.hpp"
#include "MainnodeSubscriber.hpp"
#include "SlavenodePublisher.hpp"
#include "SlavenodeSubscriber.hpp"
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
void mainNodeSub()
{
    MainnodeSubscriber subscriber;
    std::cout << subscriber.init();
    while (1)
    {
      sleep(1);
    }
    
}
void slaveNodeSub()
{
    SlavenodeSubscriber subscriber;
    std::cout << subscriber.init();
    while (1)
    {
      sleep(1);
    }
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
      std::thread(mainNodeSub).detach();
      // MainnodeSubscriber subscriber;
      // std::cout << subscriber.init();
      while (true)
      {  
        if(publisher.timeBroadcastMatched())
        {
          // to do fill TimeBroadcast Data;
          TimeBroadcast timeBroadcast;
          timeBroadcast.number(0x30);
          timeBroadcast.seconds(1111);
          timeBroadcast.milliseconds(1111);
          // publisher.publishTimeBroadcast(timeBroadcast);
        }
        if(publisher.trackBroadcastMatched())
        {
            // to do fill TrackBroadcast Data;
            TrackBroadcast trackBroadcast;
            trackBroadcast.trackType(0x11);
            trackBroadcast.seconds(2222);
            trackBroadcast.microseconds(2222);
            trackBroadcast.axisX(2.222);
            trackBroadcast.axisY(2.222);
            trackBroadcast.axisZ(2.222);
            trackBroadcast.speedX(2.222);
            trackBroadcast.speedY(2.222);
            trackBroadcast.speedZ(2.222);
            
            // publisher.publishTrackBroadcast(trackBroadcast);
        }
        if(publisher.attitudeBroadcastMatched())
        {
            // to do fill AttitudeBroadcast Data;
            AttitudeBroadcast attitudeBroadcast;
            attitudeBroadcast.gap(0x1A);
            attitudeBroadcast.seconds(3);
            attitudeBroadcast.microseconds(3);
            attitudeBroadcast.roll(3.333);
            attitudeBroadcast.pitch(3.333);
            attitudeBroadcast.yaw(3.333);
            attitudeBroadcast.Vroll(3.333);
            attitudeBroadcast.Vpitch(3.333);
            attitudeBroadcast.Vyaw(3.333);

            // publisher.publishAttitudeBroadcast(attitudeBroadcast);
        }
        if(publisher.trackPredictMatched())
        {
            // to do fill TrackPredict Data;
            TrackPredict trackPredict;
            trackPredict.number(0x40);
            trackPredict.timestamp(4);
            trackPredict.locX(4);
            trackPredict.locY(4);
            trackPredict.locZ(4);
            trackPredict.speedX(4);
            trackPredict.speedY(4);
            trackPredict.speedZ(4);

            // publisher.publishTrackPredict(trackPredict);
        }
        if(publisher.telemetryRequestMatched())
        {
            // to do fill TelemetryRequest Data;
            TelemetryRequest telemetryRequest;
            telemetryRequest.number(0x01);
            const std::array<uint8_t, 6> command = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
            telemetryRequest.command(command);
            publisher.publishTelemetryRequest(telemetryRequest);
            //recv reply
            // std::vector<std::string> vt_topicName;
            // std::vector<std::string> vt_typeName;
            // std::vector<TopicDataType *> vt_dataType;
            // std::vector<DataReaderListener *> vt_listener;
            // MainnodeSubListener telemetryReplyListener;
            // vt_topicName.push_back("TelemetryReplyTopic");
            // vt_typeName.push_back("TelemetryReply");
            // vt_dataType.push_back(new TelemetryReplyPubSubType);
            // vt_listener.push_back(&telemetryReplyListener);
            // MainnodeSubscriber TelemetryReplySubscriber;
            // TelemetryReplySubscriber.init(vt_topicName,vt_typeName,vt_dataType,vt_listener);

            
        }
        if(publisher.paramPackageMatched())
        {
            // to do fill ParamPackage Data;
            ParamPackage paramPackage;
            paramPackage.packSize(6);
            paramPackage.contentCtrl(6);
            paramPackage.taskNumber(6);
            std::array<uint8_t, 60> block = {0x60};
            paramPackage.block1(block);
            paramPackage.block2(block);
            paramPackage.block3(block);
            paramPackage.block4(block);
            paramPackage.matrixSelect(0x60);
            paramPackage.gap(0x60);
            // publisher.publishParamPackage(paramPackage);
        }
      std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
    }
    else
    {

      SlavenodePublisher publisher;
      publisher.init();
      std::thread(slaveNodeSub).detach();
      // SlavenodeSubscriber subscriber;
      // subscriber.init();
      while (true)
      {
        if(publisher.telemetryReplyMatched())
        {
          printf("=====>telemetryReplyMatched\n");
          TelemetryReply telemetryReply;
          telemetryReply.loctime4(0x11);
          telemetryReply.loctime3(0x11);
          telemetryReply.loctime2(0x11);
          telemetryReply.loctime1(0x11);
          telemetryReply.sysState(0x11);
          telemetryReply.commandCnt(0x11);
          telemetryReply.busSignature(0x11);
          telemetryReply.subsysState(0x11);
          telemetryReply.imgMode(0x11);
          telemetryReply.startTimeHigh(0x11);
          telemetryReply.startTimeLow(0x11);
          telemetryReply.subbandCont(0x11);
          telemetryReply.argTelemetry1(0x11);
          telemetryReply.taskNumber(0x11);
          telemetryReply.cmdQueueLength(0x11);
          telemetryReply.digitalTelemetry1(0x11);
          telemetryReply.digitalTelemetry2(0x11);
          telemetryReply.power100M(0x11);
          telemetryReply.RFFM(0x11);
          telemetryReply.RFamplify(0x11);
          telemetryReply.RFoscillate(0x11);
          telemetryReply.RFmainOsc5v(0x11);
          telemetryReply.RFbackOsc5v(0x11);
          telemetryReply.RFmain8p5v(0x11);
          telemetryReply.RFback8p5v(0x11);
          telemetryReply.RFmain5v(0x11);
          telemetryReply.RFback5v(0x11);
          telemetryReply.captureMain5v(0x11);

          telemetryReply.captureBack5v(0x11);
          telemetryReply.controlMain5v(0x11);
          telemetryReply.controlBack5v(0x11);
          telemetryReply.realMod1(0x11);
          telemetryReply.realMod2(0x11);
          telemetryReply.realMod3(0x11);

          telemetryReply.argTelemetry2(0x11);
          telemetryReply.argTelemetry3(0x11);
          telemetryReply.argTelemetry4(0x11);
          telemetryReply.argTelemetry5(0x11);
          telemetryReply.argTelemetry6(0x11);
          publisher.publishTelemetryReply(telemetryReply);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval)); 
      }
      
    }

    return 0;
}