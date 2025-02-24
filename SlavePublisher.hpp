#ifndef SLAVEPUBLISHER_HPP
#define SLAVEPUBLISHER_HPP

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

class SlavePubListener : public DataWriterListener
{
public:
  SlavePubListener();
  ~SlavePubListener() override;
  public:
  std::atomic_int m_matched;
public:
  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;
};

class SlavePublisher
{
private:
  SlavePubListener m_listener;

  DomainParticipant* m_participant;
  Publisher* m_publisher;

  std::vector<TypeSupport> m_typeVec;

  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
  Transport m_transport;
public:
  SlavePublisher();
  ~SlavePublisher();
public:
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
  bool init(int transportType);
  bool replayInfoMatched();
  bool publishReplyInfo(ReplyInfo &replyInfo);
};





#endif