#ifndef MAIN_HPP
#define MAIN_HPP
#include "MainPublisher.hpp"
#include "MainSubscriber.hpp"
class Main
{
  template <typename Function, typename... Args>
  void start(Function&& f, Args&&... args)
  {
    std::thread(std::forward<Function>(f), std::forward<Args>(args)...).detach();
  }
private:
  MainPublisher* m_publisher;
  MainSubscriber* m_subscriber;
public:
  Main();
  ~Main();
public:
  void init();
  void StartPublisher();
  void StartSubscriber();
  void HandleReboot();
};


#endif