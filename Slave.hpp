#ifndef SLAVE_HPP
#define SLAVE_HPP
#include "SlavePublisher.hpp"
#include "SlaveSubscriber.hpp"
#include <thread>

class Slave
{
  template <typename Function, typename... Args>
  void start(Function&& f, Args&&... args)
  {
    std::thread(std::forward<Function>(f), std::forward<Args>(args)...).detach();
  }
private:
  SlavePublisher* m_publisher;
  SlaveSubscriber* m_subscriber;
public:
  Slave();
  ~Slave();
public:
  void init();
  void StartPublisher();
  void StartSubscriber();
  void HandleReboot();
};




#endif