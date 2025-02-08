#ifndef MAINNODEASUBSCRIBER_HPP
#define MAINNODEASUBSCRIBER_HPP

#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

using namespace eprosima::fastdds::dds;

class MainNodeASubListener :public DataReaderListener
{
private:
  std::atomic_int m_samples;

public:
  MainNodeASubListener();
  ~MainNodeASubListener();
  void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

  void on_data_available(DataReader * reader) override;
};


class MainNodeASubscriber
{
private:
  DomainParticipant * m_participant;
  Subscriber * m_subscriber;
  std::vector<std::pair<Topic*,DataReader*> > m_readers;
  Topic * m_topic;
  std::vector<TypeSupport> m_type;
  MainNodeASubListener m_replyInfoListener;
public:
  MainNodeASubscriber();
  ~MainNodeASubscriber();
  bool init();
  bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id = 0);

  bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);
};




#endif