#include "SlaveSubscriber.hpp"

SlaveSubListener::SlaveSubListener()
:m_matched(0)
{
  m_publisher.init(slave_transport_type);
}

SlaveSubListener::~SlaveSubListener()
{
}

void SlaveSubListener::on_data_available(DataReader* reader)
{
  SampleInfo info;
  if (reader->get_topicdescription()->get_name() == "TargetTopic")
  {
    Target msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      std::cout << "index: " << msg.index() << std::endl;
      std::cout << "msg: " << msg.message() << std::endl;
      // replay
      ReplyInfo replyInfo;
      replyInfo.is_recved(0x01);
      if(m_publisher.replayInfoMatched())
      {
        m_publisher.publishReplyInfo(replyInfo);
      }
    }
  }
  if (reader->get_topicdescription()->get_name() == "RestartInfoTopic")
  {
    RestartInfo msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if((int)msg.participant() != 1)
        return;
      slave_transport_type = (int)msg.transportType();
      is_slave_reboot = 1;
    }
    
  }
}
void SlaveSubListener::on_subscription_matched(DataReader* reader,const SubscriptionMatchedStatus& info)
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

SlaveSubscriber::SlaveSubscriber()
:m_participant(nullptr),
m_subscriber(nullptr),
m_topic(nullptr)
{
}

SlaveSubscriber::~SlaveSubscriber()
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

bool SlaveSubscriber::init(int transportType)
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
  default:
  case TCPTRANSPORT:
    m_transport.initTcpQos(TCPSERVER,8000);
    participantQos = m_transport.getTcpQos();
    break;
  }
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
  initSubType("TargetTopic","Target",new TargetPubSubType,&m_listener) &&
  initSubType("RestartInfoTopic","RestartInfo",new RestartInfoPubSubType,&m_listener);
}

bool SlaveSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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

