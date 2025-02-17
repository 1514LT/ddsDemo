#ifndef SLAVENODEPUBLISHER_HPP
#define SLAVENODEPUBLISHER_HPP
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

using namespace eprosima::fastdds::dds;

class SlavenodePubListener : public DataWriterListener
{

public:
  SlavenodePubListener();
  ~SlavenodePubListener()override;

  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;

  std::atomic_int m_matched;

};

class SlavenodePublisher
{
private:
  
public:
  SlavenodePublisher();
  ~SlavenodePublisher();
public:
  bool init();
  bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataWriterListener *> vt_listener,DomainId_t domain_id = 0);
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
public:
  bool telemetryReplyMatched();
  bool publishTelemetryReply(TelemetryReply & telemetryReply);
private:
  SlavenodePubListener m_listener;
  DomainParticipant* m_participant;
  Publisher* m_publisher;
  std::vector<TypeSupport> m_typeVec;
  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
};




#endif