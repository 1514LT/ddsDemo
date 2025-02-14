#include "MainNodeASubscriber.hpp"

MainNodeASubListener::MainNodeASubListener()
:m_samples(0)
{
}

MainNodeASubListener::~MainNodeASubListener()
{
}
void MainNodeASubListener::on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info)
{
  if(info.current_count_change == 1)
  {
      std::cout << "Subscriber matched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
      std::cout << "Last matched publisher handle:" << info.last_publication_handle << std::endl;
  }
  else if(info.current_count_change == -1)
  {
      std::cout << "Subscriber unmatched, topic:" + reader->get_topicdescription()->get_name() + ", count:" + std::to_string(info.current_count) << std::endl;
      std::cout << "Last unmatched publisher handle:" << info.last_publication_handle << std::endl;
  }
  else 
  {
      std::cout << info.current_count_change << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
  }
}

std::string MainNodeASubListener::showResult(std::array<uint8_t, 2> arry)
{
  std::stringstream iss;
  for(auto value: arry)
  {
    iss << std::to_string((int)value) << "";
  }
  return iss.str();
}

void MainNodeASubListener::on_data_available(DataReader * reader)
{
  SampleInfo info;

  if (reader->get_topicdescription()->get_name() == "ReplyInfoTopic")
  {
    ReplyInfo msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if (info.valid_data)
      {
        if((int)msg.startNode() != 1)
          return;
        std::cout << "Start Node: " << (int)msg.startNode() << std::endl;
        std::cout << "Target Node " << (int)msg.targetNode() << std::endl;
        std::cout << "Target Number: " << msg.targetNumber() << std::endl;
        std::cout << "Handle Number: " << msg.handleNumber() << std::endl;
        std::cout << "Success Number: " << msg.sucessNumber() << std::endl;
        std::cout << "Execution Number: " << msg.executionNumber() << std::endl;
        std::cout << "Own Target Number: " << msg.ownTargetNumber() << std::endl;

        std::cout << "\nNumber 1: " << msg.number1() << ", Result Number 1: " << showResult(msg.resultNumer1()) << std::endl;
        std::cout << "Number 2: " << msg.number2() << ", Result Number 2: " << showResult(msg.resultNumer2()) << std::endl;
        std::cout << "Number 3: " << msg.number3() << ", Result Number 3: " << showResult(msg.resultNumer3()) << std::endl;
        std::cout << "Number 4: " << msg.number4() << ", Result Number 4: " << showResult(msg.resultNumer4()) << std::endl;
        std::cout << "Number 5: " << msg.number5() << ", Result Number 5: " << showResult(msg.resultNumer5()) << std::endl;
        std::cout << "Number 6: " << msg.number6() << ", Result Number 6: " << showResult(msg.resultNumer6()) << std::endl;
        std::cout << "Number 7: " << msg.number7() << ", Result Number 7: " << showResult(msg.resultNumer7()) << std::endl;
        std::cout << "Number 8: " << msg.number8() << ", Result Number 8: " << showResult(msg.resultNumer8()) << std::endl;
        std::cout << "Number 9: " << msg.number9() << ", Result Number 9: " << showResult(msg.resultNumer9()) << std::endl;
        std::cout << "Number 10: " << msg.number10() << ", Result Number 10: " << showResult(msg.resultNumer10()) << std::endl;
      }
    }
  }
  else if (reader->get_topicdescription()->get_name() == "HeartBeatTopic")
  {
    HeartBeat msg;
    while (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
    {
      if (info.valid_data)
      {
        is_nodeD_online = 1;
        lastHeartbeatTime = getCurrentTimeMillis();
      }
    }
  }
}

void MainNodeASubscriber::initNodeA()
{
  stopNodeA = false;
  m_nodeA_publisher = new MainNodeAPublisher;
  m_nodeA_publisher->init();
  start([this](){
    this->Run(m_nodeA_publisher);
  });
  start([this](){
    this->HandleTimeOut(m_nodeA_publisher);
  });
  while(true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timeinterval));
  }
}
void MainNodeASubscriber::HandleTimeOut(MainNodeAPublisher* nodeA_publisher)
{
  while (!stopNodeA)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timeinterval)); 
    if(is_nodeD_online == 0)
    {
      std::cout << "send GuidanceNodeDStartInfo" << std::endl;
      if(nodeA_publisher->GuidanceNodeDStartInfoMatched())
      {
        GuidanceNodeDStartInfo guidanceNodeDStartInfo;
        guidanceNodeDStartInfo.isStart(0x01);
        nodeA_publisher->PublishGuidanceNodeDStartInfo(guidanceNodeDStartInfo);
      }
      break;
    }
  }
}

void MainNodeASubscriber::HandleHeartBeat()
{
  lastHeartbeatTime = getCurrentTimeMillis();
  while (!stopNodeA)
  {
    currentTime = getCurrentTimeMillis();
    if(currentTime - lastHeartbeatTime > 10000)
    {
      printf("Time Out\n");
      is_nodeD_online = 0;
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timeinterval)); 
  }
  // creat new publisher
  Stop();
  std::this_thread::sleep_for(std::chrono::milliseconds(4*m_timeinterval));
  delete m_nodeA_publisher; 
  start([this](){
    this->initNodeA();
  });
}

void MainNodeASubscriber::Run(MainNodeAPublisher* nodeA_publisher)
{
  while (!stopNodeA)
  {
    if(nodeA_publisher->GuidanceInfoMatched())
    {
      GuidanceInfo guidanceInfo;
      guidanceInfo.beatCount(11111);
      guidanceInfo.targetCount(5);
      guidanceInfo.startNode(0x00);
      guidanceInfo.targetNode(0x02);
      guidanceInfo.targetType(0x55);
      Target First,Second,Third,Fourth,Fifth;
      First.targetNumber(11111);
      std::array<u_int8_t,6> timeNumber = {0x00,0x5f,0x7a,0x0d,0x1b,0xfc};
      First.time(timeNumber);
      First.longitude(-9000000);
      First.latitude(-18000000);
      First.elevation(0);
      First.Priority(0);
      First.confidenceDegree(0);
      First.informationType(0x0001);
      First.positionAccuracy(20);
      First.imagingMode(0);
      First.desiredTrack(0);
      // try
      First.shipSpeed(0.1);
      std::array<u_int8_t,5> back;
      back.fill(0x00);
      First.back(back);

      guidanceInfo.First(First);
      guidanceInfo.Second(First);
      guidanceInfo.Third(First);
      guidanceInfo.Fourth(First);
      guidanceInfo.Fifth(First);
      std::cout << "PublishGuidanceInfo" << std::endl;
      nodeA_publisher->PublishGuidanceInfo(guidanceInfo);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(m_timeinterval)); 
  }
}

void MainNodeASubscriber::Stop()
{
  stopNodeA = true;
}

MainNodeASubscriber::MainNodeASubscriber()
:m_participant(nullptr),
m_subscriber(nullptr),
m_topic(nullptr),
m_timeinterval(5000)
{
  start([this](){
    this->initNodeA();
  });
  start([this](){
    this->HandleHeartBeat();
  });
}

MainNodeASubscriber::~MainNodeASubscriber()
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

bool MainNodeASubscriber::init()
{
  DomainParticipantQos participantQos;
  participantQos.name("mainnodea_subscriber");
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
  initSubType("ReplyInfoTopic","ReplyInfo",new ReplyInfoPubSubType,&m_replyInfoListener)&&
  initSubType("HeartBeatTopic","HeartBeat",new HeartBeatPubSubType,&m_heartBeatListener);
}

bool MainNodeASubscriber::init(std::vector<std::string> vt_topicName,std::vector<std::string> vt_typeName,std::vector<TopicDataType *> vt_dataType,std::vector<DataReaderListener *> vt_listener,DomainId_t domain_id)
{
  if(!(vt_topicName.size() == vt_typeName.size() && vt_typeName.size() == vt_dataType.size() && vt_dataType.size() == vt_listener.size()))
  {
    return false;
  }
  DomainParticipantQos participantQos;
  participantQos.name("mainnodea_subscriber");
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

bool MainNodeASubscriber::initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener)
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