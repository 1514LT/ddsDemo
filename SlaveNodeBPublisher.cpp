#include "SlaveNodeBPublisher.hpp"

SlaveNodeBPubListener::SlaveNodeBPubListener()
:m_matched(0)
{
}

SlaveNodeBPubListener::~SlaveNodeBPubListener()
{
}

void SlaveNodeBPubListener::on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info)
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



SlaveNodeBPublisher::SlaveNodeBPublisher()
:m_participant(nullptr),
m_publisher(nullptr)
{
}

SlaveNodeBPublisher::~SlaveNodeBPublisher()
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
  if(!m_guidanceInfoListener)
    delete m_guidanceInfoListener;
  if(!m_replyInfoListener)
    delete m_replyInfoListener;
  if(!m_heartBeatListener)
    delete m_heartBeatListener;
}


bool SlaveNodeBPublisher::initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener)
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
bool SlaveNodeBPublisher::init()
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

  m_typeVec.reserve(3);
  m_writers.reserve(3);
  m_replyInfoListener = new SlaveNodeBPubListener;
  m_guidanceInfoListener = new SlaveNodeBPubListener;
  m_heartBeatListener = new SlaveNodeBPubListener;
  bool flag = true;
  flag && initPubType("ReplyInfoTopic","ReplyInfo",new  ReplyInfoPubSubType,m_replyInfoListener) &&
  initPubType("GuidanceInfoTopic","GuidanceInfo",new GuidanceInfoPubSubType,m_guidanceInfoListener) &&
  initPubType("HeartBeatTopic","HeartBeat",new  HeartBeatPubSubType,m_heartBeatListener);
  start(&SlaveNodeBPublisher::handleHeartbeat,this);
  return flag;
}
bool SlaveNodeBPublisher::init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataWriterListener *> vt_listener,DomainId_t domain_id)
{
  if(!(vt_topicName.size() == vt_typeName.size() && vt_typeName.size() == vt_dataType.size() && vt_dataType.size() == vt_listener.size()))
  {
    return false;
  }
    DomainParticipantQos paritcipantQos;
    paritcipantQos.name("mainnode_publisher");
    m_participant = DomainParticipantFactory::get_instance()->create_participant(domain_id,paritcipantQos);

    if(!m_participant)
    {
        return false;
    }

    m_publisher = m_participant->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
    if(!m_publisher)
    {
        return false;
    }
    m_typeVec.reserve(vt_topicName.size());
    m_writers.reserve(vt_topicName.size());
    bool flag = true;
    for(int i = 0; i < vt_topicName.size();i++)
    {
      flag && initPubType(vt_topicName[i],vt_typeName[i],vt_dataType[i],vt_listener[i]);
    }
    return flag;  
}

void SlaveNodeBPublisher::handleHeartbeat()
{
  while (true)
  {
    if(heartBeatInfoMatched())
    {
      HeartBeat heartBeat;
      heartBeat.isOnline(0x01);
      publishHeartBeatInfo(heartBeat);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5000)); 
  }
}

bool SlaveNodeBPublisher::replayInfoMatched()
{
  if(!m_replyInfoListener)
    return false;
  return m_replyInfoListener->m_matched > 0;
}
bool SlaveNodeBPublisher::publishReplyInfo(ReplyInfo &replyInfo)
{
  return !m_writers.empty() && m_writers[0].second->write(&replyInfo);
}

bool SlaveNodeBPublisher::guidanceInfoMatched()
{
  if(!m_guidanceInfoListener)
    return false;
  return m_guidanceInfoListener->m_matched > 0;
}

bool SlaveNodeBPublisher::publishGuidanceInfo(GuidanceInfo &guidanceInfo)
{
  return m_writers.size() > 1 && m_writers[1].second->write(&guidanceInfo);
}

bool SlaveNodeBPublisher::heartBeatInfoMatched()
{
  return m_heartBeatListener->m_matched > 0;
}
bool SlaveNodeBPublisher::publishHeartBeatInfo(HeartBeat &heartBeat)
{
  return m_writers.size() > 1 && m_writers[2].second->write(&heartBeat);
}