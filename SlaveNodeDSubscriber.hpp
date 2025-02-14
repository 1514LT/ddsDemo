#ifndef SLAVENODEDSUBSCRIBER_HPP
#define SLAVENODEDSUBSCRIBER_HPP



#include "SlaveNodeBSubscriber.hpp"
#include "SlaveNodeDPublisher.hpp"
#include "Gloable.hpp"


class SlaveNodeDSubListener :public DataReaderListener
{
private:
  std::atomic_int m_samples;
public:
  SlaveNodeDSubListener();
  ~SlaveNodeDSubListener();
public:
  void on_subscription_matched(DataReader * reader, const SubscriptionMatchedStatus & info) override;

  void on_data_available(DataReader * reader) override;
};



class SlaveNodeDSubscriber
{
  template <typename Function, typename... Args>
  void start(Function&& f, Args&&... args)
  {
      std::thread(std::forward<Function>(f), std::forward<Args>(args)...).detach();
  }
private:

  SlaveNodeBSubscriber m_nodeb_subscriber;
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
public:
  void HandleNodeB();
};




#endif