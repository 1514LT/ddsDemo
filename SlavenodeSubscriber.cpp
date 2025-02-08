#include "SlavenodeSubscriber.hpp"

SlavenodeSubListener::SlavenodeSubListener():m_samples(0)
{
  m_publisher = std::make_shared<SlavenodePublisher>();
  m_publisher->init();
}

SlavenodeSubListener::~SlavenodeSubListener()
{

}
void SlavenodeSubListener::on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info)
{
    if(info.current_count_change == 1)
    {
        std::cout << "Subscriber matched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
    }
    else if(info.current_count_change == -1)
    {
        std::cout << "Subscriber unmatched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
    }
    else 
    {
        std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void SlavenodeSubListener::on_data_available(DataReader * reader)
{
    SampleInfo info;
    if (reader->get_topicdescription()->get_name() == "TimeBroadcastTopic")
    {
        TimeBroadcast msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              printf("number:%d,seconds:%u,milliseconds:%u\n",(int)msg.number(),msg.seconds(),msg.milliseconds());
            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "TrackBroadcastTopic")
    {
        TrackBroadcast msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              printf("trackType:%d,seconds:%u,microseconds:%u,axisX:%f,axisY:%f,axisZ:%f,speedX:%f,speedY:%f,speedZ:%f\n",(int)msg.trackType(),msg.seconds(),msg.microseconds(),msg.axisX(),msg.axisY(),msg.axisZ(),msg.speedX(),msg.speedY(),msg.speedZ());
            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "AttitudeBroadcastTopic")
    {
        AttitudeBroadcast msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              std::cout << "gap: " << static_cast<int>(msg.gap()) << std::endl;
              std::cout << "seconds: " << msg.seconds() << std::endl;
              std::cout << "microseconds: " << msg.microseconds() << std::endl;
          
              std::cout << "roll (rad): " << msg.roll() << std::endl;
              std::cout << "pitch (rad): " << msg.pitch() << std::endl;
              std::cout << "yaw (rad): " << msg.yaw() << std::endl;
          
              std::cout << "Vroll (rad/s): " << msg.Vroll() << std::endl;
              std::cout << "Vpitch (rad/s): " << msg.Vpitch() << std::endl;
              std::cout << "Vyaw (rad/s): " << msg.Vyaw() << std::endl;
            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "TrackPredictTopic")
    {
        TrackPredict msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              std::cout << "TrackPredict Data:\n";
              std::cout << "Number: " << static_cast<unsigned int>(msg.number()) << "\n";
              std::cout << "Timestamp: " << msg.timestamp() << "\n";
              std::cout << "Location (X, Y, Z): " << msg.locX() << ", " << msg.locY() << ", " << msg.locZ() << " m\n";
              std::cout << "Speed (X, Y, Z): " << msg.speedX() << ", " << msg.speedY() << ", " << msg.speedZ() << " cm/s\n";
            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "TelemetryRequestTopic")
    {
        TelemetryRequest msg;

        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              std::array<uint8_t, 6> commands = msg.command();
              int i = 0;
              for(auto command : commands)
              {
                printf("command[%d]:%d ",i,(int)command);
                i++;
              }
              printf("number:%d\n",(int)msg.number());

              if(m_publisher->telemetryReplyMatched())
              {
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
                m_publisher->publishTelemetryReply(telemetryReply);
              }

            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "ParamPackageTopic")
    {
        ParamPackage msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              std::cout << "ParamPackage Data:\n";
              std::cout << "Pack Size: " << msg.packSize() << "\n";
              std::cout << "Content Control: " << msg.contentCtrl() << "\n";
              std::cout << "Task Number: " << msg.taskNumber() << "\n";
              std::array<unsigned char,60> block1 = msg.block1();
              std::array<unsigned char,60> block2 = msg.block2();
              std::array<unsigned char,60> block3 = msg.block3();
              std::array<unsigned char,60> block4 = msg.block4();

              std::cout << "block1:";
              ShowArry(block1);

              std::cout << "block2:";
              ShowArry(block2);

              std::cout << "block3:";
              ShowArry(block3);

              std::cout << "block4:";
              ShowArry(block4);

              std::cout << "matrixSelect: " << (int)msg.matrixSelect()  << std::endl;
              std::cout << "gap: " << (int)msg.gap()  << std::endl;
            }
        }
    }
}

void SlavenodeSubListener::ShowArry(std::array<unsigned char,60> block)
{
  int i = 0;
  for(auto value :block)
  {
    printf("block[%d]:%d ",i,(int)value);
    i++;
  }
  printf("\n");
}
SlavenodeSubscriber::SlavenodeSubscriber()
  :m_participant(nullptr),
  m_subscriber(nullptr),
  m_topic(nullptr)
{
}

SlavenodeSubscriber::~SlavenodeSubscriber()
{
  for(auto readerPair : m_readers)
  {
    m_participant->delete_topic(readerPair.first);
    m_subscriber->delete_datareader(readerPair.second);
  }
  if(m_subscriber)
  {
    m_participant->delete_subscriber(m_subscriber);
  }
  DomainParticipantFactory::get_instance()->delete_participant(m_participant);
}

bool SlavenodeSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
{
  m_type.emplace_back(dataType);
  m_type.back().register_type(m_participant);

  Topic* topic = m_participant->create_topic(topicName,typeName,TOPIC_QOS_DEFAULT);

  if(!topic)
  {
      return false;
  }

  DataReader *reader = m_subscriber->create_datareader(topic,DATAREADER_QOS_DEFAULT,listener); 

  if(!reader)
  {
      return false;
  }

  m_readers.push_back({topic,reader});
  return true;
}
bool SlavenodeSubscriber::init()
{
  DomainParticipantQos participantQos;
  participantQos.name("slavenode_subscriber");
  m_participant = DomainParticipantFactory::get_instance()->create_participant(0,participantQos);
  if(!m_participant)
  {
      return false;
  }

  m_subscriber = m_participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,nullptr);
  if(!m_subscriber)
  {
      return false;
  }
  return
  initSubType("TimeBroadcastTopic","TimeBroadcast",new  TimeBroadcastPubSubType,&m_timeBroadcastListener) &&
  initSubType("TrackBroadcastTopic","TrackBroadcast",new TrackBroadcastPubSubType,&m_trackBroadcastListener) &&
  initSubType("AttitudeBroadcastTopic","AttitudeBroadcast",new AttitudeBroadcastPubSubType,&m_AttitudeBroadcastListener) &&
  initSubType("TrackPredictTopic","TrackPredict",new TrackPredictPubSubType,&m_trackPredictListener) &&
  initSubType("TelemetryRequestTopic","TelemetryRequest",new TelemetryRequestPubSubType,&m_telemetryRequestListener) &&
  initSubType("ParamPackageTopic","ParamPackage",new ParamPackagePubSubType,&m_paramPackageListener);
}
bool SlavenodeSubscriber::init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id)
{
if(!(vt_topicName.size() == vt_typeName.size() && vt_typeName.size() == vt_dataType.size() && vt_dataType.size() == vt_listener.size()))
  {
    return false;
  }
  DomainParticipantQos participantQos;
  participantQos.name("slavenode_subscriber");
  m_participant = DomainParticipantFactory::get_instance()->create_participant(domain_id,participantQos);
  if(!m_participant)
  {
      return false;
  }

  m_subscriber = m_participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,nullptr);
  if(!m_subscriber)
  {
      return false;
  }
  bool flag = true;
  for(int i = 0; i < vt_topicName.size();i++)
  {
    flag && initSubType(vt_topicName[i],vt_typeName[i],vt_dataType[i],vt_listener[i]);
  }
  return flag;
}

