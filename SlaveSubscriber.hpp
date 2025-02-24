#ifndef SLAVESUBSCRIBER_HPP
#define SLAVESUBSCRIBER_HPP

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

#include "SlavePublisher.hpp"
#include "Transport.hpp"

using namespace eprosima::fastdds::dds;

class SlaveSubListener :public DataReaderListener
{
private:
  std::atomic_int m_matched;
  SlavePublisher m_publisher;
public:
  SlaveSubListener();
  ~SlaveSubListener() override;
public:
  void on_data_available(DataReader* reader) override;
  void on_subscription_matched(DataReader* reader,const SubscriptionMatchedStatus& info)override;
};




class SlaveSubscriber
{
private:
  DomainParticipant * m_participant;
  Subscriber * m_subscriber;
  std::vector<std::pair<Topic*,DataReader*> > m_readers;
  Topic * m_topic;
  std::vector<TypeSupport> m_type;

  SlaveSubListener m_listener;
  Transport m_transport;
public:
  SlaveSubscriber();
  ~SlaveSubscriber();
public:
  bool init(int transportType);
  bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);
};




#endif