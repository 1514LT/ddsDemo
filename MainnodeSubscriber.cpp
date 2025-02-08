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
    TelemetryReply msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      
      if (info.valid_data)
      {
        std::cout
        << (int)msg.loctime1() << (int)msg.loctime2() << (int)msg.loctime3() << (int)msg.loctime4() << "\n"
        << (int)msg.sysState() << (int)msg.commandCnt() << (int)msg.busSignature() << (int)msg.subsysState() << "\n"
        << (int)msg.imgMode() << (int)msg.startTimeHigh() << (int)msg.startTimeLow() << (int)msg.subbandCont() << "\n"
        << (int)msg.argTelemetry1() << (int)msg.taskNumber() << (int)msg.cmdQueueLength() << (int)msg.digitalTelemetry1() << "\n"
        << (int)msg.digitalTelemetry2() << (int)msg.power100M() << (int)msg.RFFM() << (int)msg.RFamplify() << "\n"
        << (int)msg.RFoscillate() << (int)msg.RFmainOsc5v() << (int)msg.RFbackOsc5v() << (int)msg.RFmain8p5v() << "\n"
        << (int)msg.RFback8p5v() << (int)msg.RFmain5v()  << (int)msg.RFback5v() << (int)msg.captureMain5v()  << "\n"
        << (int)msg.captureBack5v() << (int)msg.controlMain5v() << (int)msg.controlBack5v() << "\n"
        << (int)msg.realMod1() << (int)msg.realMod2() << (int)msg.realMod3() << (int)msg.realMod4() << "\n"
        << (int)msg.argTelemetry2() << (int)msg.argTelemetry3() << (int)msg.argTelemetry4() << (int)msg.argTelemetry5() 
        << (int)msg.argTelemetry6() << std::endl;
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
