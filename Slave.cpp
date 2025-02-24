#include "Slave.hpp"

Slave::Slave()
{
  m_publisher = new SlavePublisher;
  m_subscriber = new SlaveSubscriber;
}

Slave::~Slave()
{
}

void Slave::init()
{
  start([this](){
    this->StartSubscriber();
  });
  start([this](){
    this->HandleReboot();
  });
  while (true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(timeinterval));
  }
}
void Slave::StartPublisher()
{
  m_publisher->init(slave_transport_type);
}

void Slave::StartSubscriber()
{
  m_subscriber->init(slave_transport_type);
}

void Slave::HandleReboot()
{
  while (true)
  {
    if(is_slave_reboot)
    {
      std::cout << "-------->slave reboot" << std::endl;
      is_slave_reboot = 0;
      delete m_subscriber;
      m_subscriber = new SlaveSubscriber;
      m_subscriber->init(slave_transport_type);
      std::this_thread::sleep_for(std::chrono::microseconds(timeinterval));
    }
    std::this_thread::sleep_for(std::chrono::microseconds(timeinterval));
  }
}