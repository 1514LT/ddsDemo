#include "SlaveNodeCSubscriber.hpp"

SlaveNodeCSubListener::SlaveNodeCSubListener()
:m_samples(0)
{
  m_publisher = std::make_shared<SlaveNodeCPublisher>();
  m_publisher->init();
}

SlaveNodeCSubListener::~SlaveNodeCSubListener()
{
  
}

void SlaveNodeCSubListener::on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info)
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

void SlaveNodeCSubListener::on_data_available(DataReader * reader)
{
  SampleInfo info;
  if (reader->get_topicdescription()->get_name() == "GuidanceInfoTopic")
  {
    GuidanceInfo msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if (info.valid_data)
      {
        if((int)msg.startNode() != 1)
          return;
        printf("recv GuidanceInfoTopic info\n");
        std::cout << "本节拍总目标数" << (short)msg.beatCount() << std::endl;
        std::cout << "本包目标数" << (int)msg.targetCount() << std::endl;
        std::cout << "起始节点" << (int)msg.startNode() << std::endl;
        std::cout << "目标节点" << (int)msg.targetNode() << std::endl;
        std::cout << "目标类型" << (int)msg.targetType() << std::endl;

        std::cout << "\nFirst Target:" << std::endl;
        printTarget(msg.First());
    
        std::cout << "\nSecond Target:" << std::endl;
        printTarget(msg.Second());
    
        std::cout << "\nThird Target:" << std::endl;
        printTarget(msg.Third());
    
        std::cout << "\nFourth Target:" << std::endl;
        printTarget(msg.Fourth());
    
        std::cout << "\nFifth Target:" << std::endl;
        printTarget(msg.Fifth());
        // send nodeA
        if(m_publisher->replayInfoMatched())
        {
          ReplyInfo replyInfo;
          replyInfo.startNode() = 0x02;
          replyInfo.targetNode() = 0x01;
          replyInfo.targetNumber() = 100;
          replyInfo.handleNumber() = 200;
          replyInfo.sucessNumber() = 150;
          replyInfo.executionNumber() = 300;
          replyInfo.ownTargetNumber() = 400;
      
          replyInfo.number1() = 10; replyInfo.resultNumer1({0xAA,0xBB});
          replyInfo.number2() = 20; replyInfo.resultNumer2({0xAA,0xBB});
          replyInfo.number3() = 30; replyInfo.resultNumer3({0xAA,0xBB});
          replyInfo.number4() = 40; replyInfo.resultNumer4({0xAA,0xBB});
          replyInfo.number5() = 50; replyInfo.resultNumer5({0xAA,0xBB});
          replyInfo.number6() = 60; replyInfo.resultNumer6({0xAA,0xBB});
          replyInfo.number7() = 70; replyInfo.resultNumer7({0xAA,0xBB});
          replyInfo.number8() = 80; replyInfo.resultNumer8({0xAA,0xBB});
          replyInfo.number9() = 90; replyInfo.resultNumer9({0xAA,0xBB});
          replyInfo.number10() = 100; replyInfo.resultNumer10({0xAA,0xBB});
          m_publisher->publishReplyInfo(replyInfo);
        }
      }
    }
  }
}

void SlaveNodeCSubListener::printTarget(const Target& target)
{
  std::cout << "Target Number: " << target.targetNumber() << std::endl;
  std::cout << "Time: ";
  for(auto time:target.time())
  {
    std::cout << (int)time << " ";
  }
  std::cout << std::endl;

  std::cout << "Longitude: " << target.longitude() << std::endl;
  std::cout << "Latitude: " << target.latitude() << std::endl;
  std::cout << "Elevation: " << target.elevation() << std::endl;
  std::cout << "Priority: " << (int)target.Priority() << std::endl;
  std::cout << "Confidence Degree: " << (int)target.confidenceDegree() << std::endl;
  std::cout << "Information Type: " << (int)target.informationType() << std::endl;
  std::cout << "Position Accuracy: " << (int)target.positionAccuracy() << std::endl;
  std::cout << "Imaging Mode: " << (int)target.imagingMode() << std::endl;
  std::cout << "Desired Track: " << target.desiredTrack() << std::endl;
  std::cout << "Ship Speed: " << target.shipSpeed() << std::endl;
  
  std::cout << "Back: ";
  for(auto back:target.back())
  {
    std::cout << (int)back << " ";
  }
  std::cout << std::endl;
}

SlaveNodeCSubscriber::SlaveNodeCSubscriber()
:m_participant(nullptr),
m_subscriber(nullptr),
m_topic(nullptr)
{
}

SlaveNodeCSubscriber::~SlaveNodeCSubscriber()
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

bool SlaveNodeCSubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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

bool SlaveNodeCSubscriber::init()
{
  DomainParticipantQos participantQos;
  participantQos.name("slavenodec_subscriber");
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
  initSubType("GuidanceInfoTopic","GuidanceInfo",new  GuidanceInfoPubSubType,&m_guidanceInfoListener);
}
bool SlaveNodeCSubscriber::init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id)
{
  if(!(vt_topicName.size() == vt_typeName.size() && vt_typeName.size() == vt_dataType.size() && vt_dataType.size() == vt_listener.size()))
  {
    return false;
  }
  DomainParticipantQos participantQos;
  participantQos.name("slavenode_subscriber");
  m_participant = DomainParticipantFactory::get_instance()->create_participant(domain_id,participantQos);
  if(!m_participant)
  {
      return false;
  }

  m_subscriber = m_participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT,nullptr);
  if(!m_subscriber)
  {
      return false;
  }
  bool flag = true;
  for(int i = 0; i < vt_topicName.size();i++)
  {
    flag && initSubType(vt_topicName[i],vt_typeName[i],vt_dataType[i],vt_listener[i]);
  }
  return flag;
}

