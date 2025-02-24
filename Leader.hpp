#ifndef LEADER_HPP
#define LEADER_HPP

#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include "Transport.hpp"
#include "Gloable.hpp"
using namespace eprosima::fastdds::dds;
class LeaderListener :public DataWriterListener
{
public:
  std::atomic_int m_matched;
public:
  LeaderListener();
  ~LeaderListener()override;
public:
  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;
};

class Leader
{
private:
  DomainParticipant* m_participant;
  Publisher* m_publisher;
  std::vector<TypeSupport> m_typeVec;
  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
  LeaderListener m_listener;
  Transport m_transport;
public:
  Leader();
  ~Leader();
public:
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
  bool init(int transportType);

  bool RestartInfoMatched();
  bool PublishRestartInfo(RestartInfo &restartInfo);
};




#endif