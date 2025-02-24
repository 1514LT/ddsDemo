#include "Main.hpp"
Main::Main()
{
  m_publisher = new MainPublisher;
  m_subscriber = new MainSubscriber;
}

Main::~Main()
{
  if(!m_publisher)
   delete m_publisher;
  if(!m_subscriber)
   delete m_subscriber;
}
void Main::init()
{
  start([this](){
    this->StartPublisher();
  });
  start([this](){
    this->StartSubscriber();
  });
  start([this](){
    this->HandleReboot();
  });
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::microseconds(timeinterval));
  }
}

void Main::StartPublisher()
{
  m_publisher->init(main_transport_type);
  int num = 0;
  while (true)
  {
    if(m_publisher && m_publisher->TargetMatched())
    {
      Target target;
      target.index(num);
      target.message("target message");
      m_publisher->PublishTargetInfo(target);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval));
    num ++;
  }
}
void Main::StartSubscriber()
{
  m_subscriber->init(main_transport_type);
}

void Main::HandleReboot()
{
  while (true)
  {
    if(is_main_reboot)
    {
      std::cout << "------>main reboot" << std::endl;
      is_main_reboot = 0;
      delete m_publisher;
      delete m_subscriber;
      m_publisher = new MainPublisher;
      m_subscriber = new MainSubscriber;
      start([this](){
        this->StartPublisher();
      });
      start([this](){
        this->StartSubscriber();
      });
      // m_publisher->init(main_transport_type);
      // m_subscriber->init(main_transport_type);
    }
    std::this_thread::sleep_for(std::chrono::microseconds(timeinterval));
  }
}