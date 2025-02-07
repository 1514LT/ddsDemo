#include "MainnodeSubscriber.hpp"

MainnodeSubListener::MainnodeSubListener()
    :m_samples(0)
{
}

MainnodeSubListener::~MainnodeSubListener()
{
}

void MainnodeSubListener::on_subscription_matched(DataReader *reader, const SubscriptionMatchedStatus &info)
{
    if(info.current_count_change == 1)
    {
        std::cout << "Subscriber matched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
    }
    else if(info.current_count_change == -1)
    {
        std::cout << "Subscriber unmatched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
    }
    else 
    {
        std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
}

void MainnodeSubListener::on_data_available(DataReader *reader)
{
    SampleInfo info;
    if (reader->get_topicdescription()->get_name() == "TimeBroadcastTopic")
    {
        TimeBroadcast msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {
              printf("number:%d\nseconds:%u\nmilliseconds:%u\n",(int)msg.number(),msg.seconds(),msg.milliseconds());
            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "TrackBroadcastTopic")
    {
        TrackBroadcast msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {

            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "AttitudeBroadcastTopic")
    {
        AttitudeBroadcast msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {

            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "TrackPredictTopic")
    {
        TrackPredict msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {

            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "TelemetryRequestTopic")
    {
        TelemetryRequest msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {

            }
        }
    }
    else if (reader->get_topicdescription()->get_name() == "ParamPackageTopic")
    {
        ParamPackage msg;
        while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
            if (info.valid_data)
            {

            }
        }
    }

}

MainnodeSubscriber::MainnodeSubscriber()
    :m_participant(nullptr),
    m_subscriber(nullptr),
    m_topic(nullptr)
{
}

MainnodeSubscriber::~MainnodeSubscriber()
{
  for(auto readerPair : m_readers)
  {
    m_participant->delete_topic(readerPair.first);
    m_subscriber->delete_datareader(readerPair.second);
  }
  if(m_subscriber)
  {
    m_participant->delete_subscriber(m_subscriber);
  }
  DomainParticipantFactory::get_instance()->delete_participant(m_participant);
}
bool MainnodeSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
{
  m_type.emplace_back(dataType);
  m_type.back().register_type(m_participant);

  Topic* topic = m_participant->create_topic(topicName,typeName,TOPIC_QOS_DEFAULT);

  if(!topic)
  {
      return false;
  }

  DataReader *reader = m_subscriber->create_datareader(topic,DATAREADER_QOS_DEFAULT,listener); 

  if(!reader)
  {
      return false;
  }

  m_readers.push_back({topic,reader});
  return true;
}
bool MainnodeSubscriber::init()
{
    DomainParticipantQos participantQos;
    participantQos.name("mainnode_subscriber");
    m_participant = DomainParticipantFactory::get_instance()->create_participant(0,participantQos);
    if(!m_participant)
    {
        return false;
    }

    m_subscriber = m_participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,nullptr);
    if(!m_subscriber)
    {
        return false;
    }
    return
    initSubType("TimeBroadcastTopic","TimeBroadcast",new  TimeBroadcastPubSubType,&m_timeBroadcastListener) &&
    initSubType("TrackBroadcastTopic","TrackBroadcast",new TrackBroadcastPubSubType,&m_trackBroadcastListener) &&
    initSubType("AttitudeBroadcastTopic","AttitudeBroadcast",new AttitudeBroadcastPubSubType,&m_AttitudeBroadcastListener) &&
    initSubType("TrackPredictTopic","TrackPredict",new TrackPredictPubSubType,&m_trackPredictListener) &&
    initSubType("TelemetryRequestTopic","TelemetryRequest",new TelemetryRequestPubSubType,&m_telemetryRequestListener) &&
    initSubType("ParamPackageTopic","ParamPackage",new ParamPackagePubSubType,&m_paramPackageListener);
}
