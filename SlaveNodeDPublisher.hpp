#ifndef SLAVENODEDPUBLISHER_HPP
#define SLAVENODEDPUBLISHER_HPP


#include "SlaveNodeBPublisher.hpp"


class SlaveNodeDPubListener :public DataWriterListener
{
public:
  SlaveNodeDPubListener();
  ~SlaveNodeDPubListener()override;
public:
  std::atomic_int m_matched;
public:
  void on_publication_matched(DataWriter * dataWriter, const PublicationMatchedStatus & info) override;
};

class SlaveNodeDPublisher
{

private:
  SlaveNodeDPubListener m_heartBeatListener;
  DomainParticipant* m_participant;
  Publisher* m_publisher;

  std::vector<TypeSupport> m_typeVec;

  std::vector<std::pair<Topic*,DataWriter*> > m_writers;
public:
  SlaveNodeDPublisher();
  ~SlaveNodeDPublisher();
public:
  bool initPubType(const std::string & topicName, const std::string & typeName, TopicDataType * dataType, DataWriterListener * listener);
  bool init();

  bool heartBeatInfoMatched();
  bool publishHeartBeatInfo(HeartBeat &heartBeat);
};



#endif