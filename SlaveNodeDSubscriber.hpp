#ifndef SLAVENODEDSUBSCRIBER_HPP
#define SLAVENODEDSUBSCRIBER_HPP



#include "SlaveNodeBSubscriber.hpp"
#include "SlaveNodeDPublisher.hpp"


class SlaveNodeDSubListener :public DataReaderListener
{
private:
  std::atomic_int m_samples;
  std::shared_ptr<SlaveNodeBSubscriber> m_subscriber;
public:
  SlaveNodeDSubListener();
  ~SlaveNodeDSubListener();
public:
  void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

  void on_data_available(DataReader * reader) override;
};



class SlaveNodeDSubscriber
{
private:
  DomainParticipant * m_participant;
  Subscriber * m_subscriber;
  std::vector<std::pair<Topic*,DataReader*> > m_readers;
  Topic * m_topic;
  std::vector<TypeSupport> m_type;
  SlaveNodeDSubListener m_guidanceNodeDStartInfoListener;
public:
  SlaveNodeDSubscriber();
  ~SlaveNodeDSubscriber();
public:
  bool init();
  bool initSubType(const std::string &topicName, const std::string & typeName, TopicDataType *dataType, DataReaderListener * listener);
};




#endif