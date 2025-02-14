#ifndef MAINNODEASUBSCRIBER_HPP
#define MAINNODEASUBSCRIBER_HPP

#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"
#include "Gloable.hpp"
#include "MainNodeAPublisher.hpp"
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

using namespace eprosima::fastdds::dds;


long long getCurrentTimeMillis()
{
  auto now = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
  return duration.count();
}

class MainNodeASubListener :public DataReaderListener
{
private:
  std::atomic_int m_samples;
public:
  MainNodeASubListener();
  ~MainNodeASubListener();
  void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

  void on_data_available(DataReader * reader) override;
  std::string showResult(std::array<uint8_t, 2> arry);
};


class MainNodeASubscriber
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
  MainNodeASubListener m_replyInfoListener;
  MainNodeASubListener m_heartBeatListener;

  MainNodeAPublisher* m_nodeA_publisher;
  int m_timeinterval;
  long long currentTime;
  bool stopNodeA = false;
public:
  MainNodeASubscriber();
  ~MainNodeASubscriber();
  bool init();
  bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id = 0);

  bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);
  void initNodeA();
  void HandleTimeOut(MainNodeAPublisher* nodeA_publisher);
  void HandleHeartBeat();
  void Run(MainNodeAPublisher* nodeA_publisher);
  void Stop();
};




#endif