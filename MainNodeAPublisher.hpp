#ifndef MAINNODEAPUBLISHER_HPP
#define MAINNODEAPUBLISHER_HPP

#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"
#include "Gloable.hpp"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>

using namespace eprosima::fastdds::dds;

class MainNodeAPubListenner : public DataWriterListener
{
private:
  
public:
  MainNodeAPubListenner();
  ~MainNodeAPubListenner() override;

  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;

  std::atomic_int m_matched;
};




class MainNodeAPublisher
{
private:
  DomainParticipant* m_participant;
  Publisher* m_publisher;
  std::vector<TypeSupport> m_typeVec;
  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
  MainNodeAPubListenner m_guidanceInfoListener;
  MainNodeAPubListenner m_guidanceNodeDStartInfoListener;
  
public:
  MainNodeAPublisher();
  ~MainNodeAPublisher();
public:
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
  bool init();
  bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataWriterListener *> vt_listener,DomainId_t domain_id = 0);
public:
  bool GuidanceInfoMatched();
  bool PublishGuidanceInfo(GuidanceInfo &guidanceInfo);

  bool GuidanceNodeDStartInfoMatched();
  bool PublishGuidanceNodeDStartInfo(GuidanceNodeDStartInfo &guidanceNodeDStartInfo);

};




#endif