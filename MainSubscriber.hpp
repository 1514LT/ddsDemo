#ifndef MAINSUBSCRIBER_HPP
#define MAINSUBSCRIBER_HPP
#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"
#include <thread>

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

#include "MainPublisher.hpp"
#include "Transport.hpp"
#include "Gloable.hpp"


using namespace eprosima::fastdds::dds;

class MainSubListener : public DataReaderListener
{
private:
  std::atomic_int m_samples;
public:
  MainSubListener();
  ~MainSubListener();
public:
  void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

  void on_data_available(DataReader * reader) override;
};

class MainSubscriber
{
  template <typename Function, typename... Args>
  void start(Function&& f, Args&&... args)
  {
    std::thread(std::forward<Function>(f), std::forward<Args>(args)...).detach();
  }
private:
  DomainParticipant * m_participant;
  Subscriber * m_subscriber;
  std::vector<std::pair<Topic*,DataReader*> > m_readers;
  Topic * m_topic;
  std::vector<TypeSupport> m_type;
  MainSubListener m_listener;

  Transport m_transport;
public:
  MainSubscriber();
  ~MainSubscriber();
public:
  bool init(int transportType);

  bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);

};




#endif