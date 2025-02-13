#include "SlaveNodeDPublisher.hpp"

SlaveNodeDPubListener::SlaveNodeDPubListener()
:m_matched(0)
{
}

SlaveNodeDPubListener::~SlaveNodeDPubListener()
{
  
}

void SlaveNodeDPubListener::on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info)
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

SlaveNodeDPublisher::SlaveNodeDPublisher()
:m_participant(nullptr),
m_publisher(nullptr)
{

}
SlaveNodeDPublisher::~SlaveNodeDPublisher()
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
bool SlaveNodeDPublisher::initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener)
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
bool SlaveNodeDPublisher::init()
{
  DomainParticipantQos paritcipantQos;
  paritcipantQos.name("slavenodeb_publisher");
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
  initPubType("HeartBeatTopic","HeartBeat",new  HeartBeatPubSubType,&m_heartBeatListener);
}


bool SlaveNodeDPublisher::heartBeatInfoMatched()
{
  return m_heartBeatListener.m_matched > 0;
}

bool SlaveNodeDPublisher::publishHeartBeatInfo(HeartBeat &heartBeat)
{
  return !m_writers.empty() && m_writers[0].second->write(&heartBeat);
}