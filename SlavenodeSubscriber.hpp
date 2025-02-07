#ifndef SLAVENODESUBSCRIBER_HPP
#define SLAVENODESUBSCRIBER_HPP
#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"
#include "MainnodePublisher.hpp"
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

class SlavenodeSubListener : public DataReaderListener
{
public:
  SlavenodeSubListener();
  ~SlavenodeSubListener();
  void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

  void on_data_available(DataReader * reader) override;
private:
    std::atomic_int m_samples;
};


class SlavenodeSubscriber
{
private:
  /* data */
public:
  SlavenodeSubscriber(/* args */);
  ~SlavenodeSubscriber();
public:
  bool init();
  bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id = 0);

  bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);

private:
  DomainParticipant * m_participant;
  Subscriber * m_subscriber;
  std::vector<std::pair<Topic*,DataReader*> > m_readers;
  Topic * m_topic;
  std::vector<TypeSupport> m_type;
  SlavenodeSubListener m_listener;

  SlavenodeSubListener m_timeBroadcastListener;
  SlavenodeSubListener m_trackBroadcastListener;
  SlavenodeSubListener m_AttitudeBroadcastListener;
  SlavenodeSubListener m_trackPredictListener;
  SlavenodeSubListener m_telemetryRequestListener;

  SlavenodeSubListener m_paramPackageListener;
};



#endif
