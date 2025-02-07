#ifndef MAINNODEPUBLISHER_HPP
#define MAINNODEPUBLISHER_HPP

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

class MainnodePubListener : public DataWriterListener
{
public:
    MainnodePubListener();
    ~MainnodePubListener() override;

    void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;

    std::atomic_int m_matched;
};

class MainnodePublisher
{
public:
    MainnodePublisher();
    ~MainnodePublisher();

    bool init();
    bool init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataWriterListener *> vt_listener,DomainId_t domain_id = 0);

    bool timeBroadcastMatched();
    bool publishTimeBroadcast(TimeBroadcast & timeBroadcast);

    bool trackBroadcastMatched();
    bool publishTrackBroadcast(TrackBroadcast & trackBroadcast);

    bool attitudeBroadcastMatched();
    bool publishAttitudeBroadcast(AttitudeBroadcast & attitudeBraodcast);

    bool trackPredictMatched();
    bool publishTrackPredict(TrackPredict & trackPredict);

    bool telemetryRequestMatched();
    bool publishTelemetryRequest(TelemetryRequest & telemetryRequest);

    bool paramPackageMatched();
    bool publishParamPackage(ParamPackage & paramPackage);

private:
    bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);

private:
    MainnodePubListener m_timeBroadcastListener;
    MainnodePubListener m_trackBroadcastListener;
    MainnodePubListener m_AttitudeBroadcastListener;
    MainnodePubListener m_trackPredictListener;
    MainnodePubListener m_telemetryRequestListener;
    MainnodePubListener m_telemetryReplyListener;
    MainnodePubListener m_paramPackageListener;

    DomainParticipant* m_participant;
    Publisher* m_publisher;
 
    std::vector<TypeSupport> m_typeVec;

    std::vector<std::pair<Topic*,DataWriter*> > m_writers;
 
};

#endif