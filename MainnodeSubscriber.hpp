#ifndef MAINNODESUBSCRIBER_HPP
#define MAINNODESUBSCRIBER_HPP

#include "DataDefine.h"
#include "DataDefinePubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
// #include <fastdds/dds/core/condition/WaitSet.hpp>
// #include <fastdds/dds/core/condition/GuardCondition.hpp>

using namespace eprosima::fastdds::dds;

class MainnodeSubListener : public DataReaderListener
{
public:
    MainnodeSubListener();
    ~MainnodeSubListener();

    void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

    void on_data_available(DataReader * reader) override;

private:
    std::atomic_int m_samples;
};

class MainnodeSubscriber
{
public:
    MainnodeSubscriber();
    ~MainnodeSubscriber();

    bool init();
    bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);

private:
    DomainParticipant * m_participant;
    Subscriber * m_subscriber;
    std::vector<std::pair<Topic*,DataReader*> > m_readers;
    Topic * m_topic;
    std::vector<TypeSupport> m_type;
    MainnodeSubListener m_listener;

    MainnodeSubListener m_timeBroadcastListener;
    MainnodeSubListener m_trackBroadcastListener;
    MainnodeSubListener m_AttitudeBroadcastListener;
    MainnodeSubListener m_trackPredictListener;
    MainnodeSubListener m_telemetryRequestListener;
    MainnodeSubListener m_paramPackageListener;
};

#endif