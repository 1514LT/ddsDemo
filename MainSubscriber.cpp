#include "MainSubscriber.hpp"

MainSubListener::MainSubListener()
:m_samples(0)
{
}

MainSubListener::~MainSubListener()
{
}

void MainSubListener::on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info)
{
  if(info.current_count_change == 1)
  {
      std::cout << "Subscriber matched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
      std::cout << "Last matched publisher handle:" << info.last_publication_handle << std::endl;
  }
  else if(info.current_count_change == -1)
  {
      std::cout << "Subscriber unmatched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
      std::cout << "Last unmatched publisher handle:" << info.last_publication_handle << std::endl;
  }
  else 
  {
      std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
  }
}

void MainSubListener::on_data_available(DataReader * reader)
{
  SampleInfo info;

  if (reader->get_topicdescription()->get_name() == "ReplyInfoTopic")
  {
    ReplyInfo msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if(info.valid_data)
      {
        std::cout << "is_recved:" << (int)msg.is_recved() << std::endl;
      }
    }
  }
  else if (reader->get_topicdescription()->get_name() == "RestartInfoTopic")
  {
    RestartInfo msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if(info.valid_data)
      {
        if(msg.participant() != 0)
          return;
        main_transport_type = (int)msg.transportType();
        is_main_reboot = 1;
      }
    }
  }
}

MainSubscriber::MainSubscriber()
:m_participant(nullptr),
m_subscriber(nullptr),
m_topic(nullptr)
{
}

MainSubscriber::~MainSubscriber()
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

bool MainSubscriber::init(int transportType)
{
  DomainParticipantQos participantQos;
  switch (transportType)
  {
  case SHMTRANSPORT:
    m_transport.initShmQos();
    participantQos = m_transport.getShmQos();
    break;
  case UDPTRANSPORT:
    m_transport.initUdpQos();
    participantQos = m_transport.getUdpQos();
  break;
  case TCPTRANSPORT:
    m_transport.initTcpQos(TCPSERVER,8080);
    participantQos = m_transport.getTcpQos();
  break;
  default:
    break;
  }

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
  initSubType("ReplyInfoTopic","ReplyInfo",new ReplyInfoPubSubType,&m_listener) &&
  initSubType("RestartInfoTopic","RestartInfo",new RestartInfoPubSubType,&m_listener);
}

bool MainSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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
