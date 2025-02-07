#include "MainnodeSubscriber.hpp"

MainnodeSubListener::MainnodeSubListener()
    :m_samples(0)
{

}

MainnodeSubListener::~MainnodeSubListener()
{
}

void MainnodeSubListener::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &info)
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

void MainnodeSubListener::on_data_available(DataReader *reader)
{
  SampleInfo info;

  if (reader->get_topicdescription()->get_name() == "TelemetryReplyTopic")
  {
    printf("mainNode recv TelemetryReplyTopic\n");
    TelemetryReply msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      
      if (info.valid_data)
      {
        std::cout
        << (int)msg.loctime1() << (int)msg.loctime2() << (int)msg.loctime3() << (int)msg.loctime4() << "\n"
        << msg.sysState() << msg.commandCnt() << msg.busSignature() << msg.subsysState() << "\n"
        << msg.imgMode() << msg.startTimeHigh() << msg.startTimeLow() << msg.subbandCont() << "\n"
        << msg.argTelemetry1() << msg.taskNumber() << msg.cmdQueueLength() << msg.digitalTelemetry1() << "\n"
        << msg.digitalTelemetry2() << msg.power100M() << msg.RFFM() << msg.RFamplify() << msg.RFoscillate() << "\n"
        << msg.RFmainOsc5v() << msg.RFbackOsc5v() << msg.RFmain8p5v() << msg.RFback8p5v() << msg.RFmain5v() << "\n"
        << msg.RFback5v() << msg.captureMain5v() << msg.captureBack5v() << msg.controlMain5v() << msg.controlBack5v() << "\n"
        << msg.realMod1() << msg.realMod2() << msg.realMod3() << msg.realMod4() << "\n"
        << msg.argTelemetry2() << msg.argTelemetry3() << msg.argTelemetry4() << msg.argTelemetry5() 
        << msg.argTelemetry6() << std::endl;
      }
    }
  }
}

MainnodeSubscriber::MainnodeSubscriber()
    :m_participant(nullptr),
    m_subscriber(nullptr),
    m_topic(nullptr)
{
}

MainnodeSubscriber::~MainnodeSubscriber()
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
bool MainnodeSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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

bool MainnodeSubscriber::init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id)
{
  if(!(vt_topicName.size() == vt_typeName.size() && vt_typeName.size() == vt_dataType.size() && vt_dataType.size() == vt_listener.size()))
  {
    return false;
  }
  DomainParticipantQos participantQos;
  participantQos.name("mainnode_subscriber");
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

bool MainnodeSubscriber::init()
{
    DomainParticipantQos participantQos;
    participantQos.name("mainnode_subscriber");
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
    initSubType("TelemetryReplyTopic","TelemetryReply",new TelemetryReplyPubSubType,&m_telemetryReplyListener);
}
