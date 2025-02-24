#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>
#include <fastdds/rtps/transport/shared_mem/SharedMemTransportDescriptor.h>
#include <fastrtps/utils/IPLocator.h>


using IPLocator = eprosima::fastrtps::rtps::IPLocator;
using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;
#define TCPSERVER 0
#define TCPCLIENT 1

class Transport
{
private:
 DomainParticipantQos m_udp_domain_qos;
 DomainParticipantQos m_tcp_domain_qos;
 DomainParticipantQos m_shm_domain_qos;
public:
  Transport();
  ~Transport();
public:
  void initUdpQos();
  void initTcpQos(int tcpType,int port);
  void initShmQos();

  DomainParticipantQos& getUdpQos();
  DomainParticipantQos& getTcpQos();
  DomainParticipantQos& getShmQos();
};




#endif