#include "MainPublisher.hpp"

MainPubListenner::MainPubListenner()
:m_matched(0)
{

}
MainPubListenner::~MainPubListenner()
{

}

void MainPubListenner::on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info)
{
  if(info.current_count_change == 1)
  {
      m_matched = info.current_count;
      std::cout << "Publisher matched, topic:" + dataWriter->get_topic()->get_name() +", count: " + std::to_string(info.current_count) << std::endl;
  }
  else if(info.current_count_change == -1)
  {
      m_matched = info.current_count;
      std::cout << "Publisher unmatched, topic:" + dataWriter->get_topic()->get_name() + ", count: " + std::to_string(info.current_count) << std::endl;
  }
  else
  {
      std::cout << info.current_count_change
                << " is not a valid value for PublicationMatchedStatus current count change" << std::endl;
  }
}

MainPublisher::MainPublisher()
:m_participant(nullptr),
m_publisher(nullptr)
{
}

MainPublisher::~MainPublisher()
{
  for(auto writerPair : m_writers)
  {
      m_participant->delete_topic(writerPair.first);
      m_publisher->delete_datawriter(writerPair.second);
  }
  if(m_publisher)
  {
      m_participant->delete_publisher(m_publisher);
  }
  DomainParticipantFactory::get_instance()->delete_participant(m_participant);
}

bool MainPublisher::initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener)
{
  m_typeVec.emplace_back(dataType);
  m_typeVec.back().register_type(m_participant);
  Topic *topic = m_participant->create_topic(topicName,typeName,TOPIC_QOS_DEFAULT);
  if(!topic)
  {
      return false;
  }
  DataWriter *writer = m_publisher->create_datawriter(topic,DATAWRITER_QOS_DEFAULT,listener); 
  if(!writer)
  {
      return false;
  }
  m_writers.push_back({topic,writer});
  return true;
}
bool MainPublisher::init(int transportType)
{
  DomainParticipantQos paritcipantQos;
  switch (transportType)
  {
  case SHMTRANSPORT:
    m_transport.initShmQos();
    paritcipantQos = m_transport.getShmQos();
    break;
  case UDPTRANSPORT:
    m_transport.initUdpQos();
    paritcipantQos = m_transport.getUdpQos();
    break;
  case TCPTRANSPORT:
    m_transport.initTcpQos(TCPCLIENT,8000);
    paritcipantQos = m_transport.getTcpQos();
    break;
  default:
    break;
  }

  paritcipantQos.name("mainnode_publisher");
  m_participant = DomainParticipantFactory::get_instance()->create_participant(0,paritcipantQos);

  if(!m_participant)
  {
      return false;
  }

  m_publisher = m_participant->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
  if(!m_publisher)
  {
      return false;
  }

  m_typeVec.reserve(1);
  m_writers.reserve(1);
  return 
  initPubType("TargetTopic","Target",new  TargetPubSubType,&m_listener);
}

bool MainPublisher::TargetMatched()
{
  return m_listener.m_matched > 0;
}
bool MainPublisher::PublishTargetInfo(Target &target)
{
  return m_writers.size() > 0 && m_writers[0].second->write(&target);
}