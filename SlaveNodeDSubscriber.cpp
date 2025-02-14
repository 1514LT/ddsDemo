#include "SlaveNodeDSubscriber.hpp"
SlaveNodeDSubListener::SlaveNodeDSubListener()
:m_samples(0)
{
}

SlaveNodeDSubListener::~SlaveNodeDSubListener()
{
}


void SlaveNodeDSubListener::on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info)
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

void SlaveNodeDSubListener::on_data_available(DataReader * reader)
{
  SampleInfo info;
  if (reader->get_topicdescription()->get_name() == "GuidanceNodeDStartInfoTopic")
  {
    // start nodeB
    printf("start nodeB\n");
    start_nodeB = 1;
  }
}

SlaveNodeDSubscriber::SlaveNodeDSubscriber()
:m_participant(nullptr),
m_subscriber(nullptr),
m_topic(nullptr)
{
  start([this](){
    this->HandleNodeB();
  });
}

SlaveNodeDSubscriber::~SlaveNodeDSubscriber()
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

void SlaveNodeDSubscriber::HandleNodeB()
{
  while (true)
  {
    if(start_nodeB == 1)
    {
      m_nodeb_subscriber.init();
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
  }
  
}
bool SlaveNodeDSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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
bool SlaveNodeDSubscriber::init()
{
  DomainParticipantQos participantQos;
  participantQos.name("slavenoded_subscriber");
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
  initSubType("GuidanceNodeDStartInfoTopic","GuidanceNodeDStartInfo",new  GuidanceNodeDStartInfoPubSubType,&m_listener);
}



