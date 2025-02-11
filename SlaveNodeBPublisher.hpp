#ifndef SLAVENODEBPUBLISHER_HPP
#define SLAVENODEBPUBLISHER_HPP

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

class SlaveNodeBPubListener :public DataWriterListener
{
public:
  SlaveNodeBPubListener();
  ~SlaveNodeBPubListener() override;
public:
  std::atomic_int m_matched;
public:
  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;
};


class SlaveNodeBPublisher
{
private:
  SlaveNodeBPubListener m_replyInfoListener;
  SlaveNodeBPubListener m_guidanceInfoListener;

  DomainParticipant* m_participant;
  Publisher* m_publisher;

  std::vector<TypeSupport> m_typeVec;

  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
public:
  SlaveNodeBPublisher();
  ~SlaveNodeBPublisher();
public:
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
  bool init();
  bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataWriterListener *> vt_listener,DomainId_t domain_id = 0);

  bool replayInfoMatched();
  bool publishReplyInfo(ReplyInfo &replyInfo);

  bool guidanceInfoMatched();
  bool publishGuidanceInfo(GuidanceInfo &guidanceInfo);
};



#endif