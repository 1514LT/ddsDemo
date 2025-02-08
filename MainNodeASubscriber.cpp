#include "MainNodeASubscriber.hpp"

MainNodeASubListener::MainNodeASubListener()
:m_samples(0)
{
}

MainNodeASubListener::~MainNodeASubListener()
{
}
void MainNodeASubListener::on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info)
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

void MainNodeASubListener::on_data_available(DataReader * reader)
{
  SampleInfo info;

  if (reader->get_topicdescription()->get_name() == "ReplyInfoTopic")
  {
    ReplyInfo msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if (info.valid_data)
      {
      }
    }
  }
}

MainNodeASubscriber::MainNodeASubscriber()
:m_participant(nullptr),
m_subscriber(nullptr),
m_topic(nullptr)
{
}

MainNodeASubscriber::~MainNodeASubscriber()
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

bool MainNodeASubscriber::init()
{
  DomainParticipantQos participantQos;
  participantQos.name("mainnodea_subscriber");
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
  initSubType("ReplyInfoTopic","ReplyInfo",new ReplyInfoPubSubType,&m_replyInfoListener);
}

bool MainNodeASubscriber::init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id)
{
  if(!(vt_topicName.size() == vt_typeName.size() && vt_typeName.size() == vt_dataType.size() && vt_dataType.size() == vt_listener.size()))
  {
    return false;
  }
  DomainParticipantQos participantQos;
  participantQos.name("mainnodea_subscriber");
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

bool MainNodeASubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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