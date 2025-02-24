#ifndef MAINPUBLISHER_HPP
#define MAINPUBLISHER_HPP

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

class MainPubListenner : public DataWriterListener
{
public:
  MainPubListenner();
  ~MainPubListenner() override;

  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;

  std::atomic_int m_matched;
};

class MainPublisher
{
private:
  DomainParticipant* m_participant;
  Publisher* m_publisher;
  std::vector<TypeSupport> m_typeVec;
  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
  MainPubListenner m_listener;
  Transport m_transport;
  
public:
  MainPublisher();
  ~MainPublisher();
public:
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
  bool init(int transportType);

  bool TargetMatched();
  bool PublishTargetInfo(Target &target);
};



#endif