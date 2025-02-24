#include "Transport.hpp"

Transport::Transport()
{
}

Transport::~Transport()
{
}

void Transport::initUdpQos()
{
  // Create a descriptor for the new transport.
  auto udp_transport = std::make_shared<UDPv4TransportDescriptor>();
  udp_transport->sendBufferSize = 65501;
  udp_transport->receiveBufferSize = 65501;
  udp_transport->non_blocking_send = true;
  
  m_udp_domain_qos.transport().user_transports.push_back(udp_transport);
  
  // Avoid using the default transport
  m_udp_domain_qos.transport().use_builtin_transports = false;

}
void Transport::initTcpQos(int tcpType,int port)
{
  if(tcpType == 0)//server
  {
    auto tcp_transport = std::make_shared<TCPv4TransportDescriptor>();
    tcp_transport->sendBufferSize = 65501;
    tcp_transport->receiveBufferSize = 65501;
    tcp_transport->add_listener_port(port);
    
    m_tcp_domain_qos.transport().user_transports.push_back(tcp_transport);
    
    m_tcp_domain_qos.transport().use_builtin_transports = false;
    
    Locator locator;
    locator.kind = LOCATOR_KIND_TCPv4;
    IPLocator::setIPv4(locator, "192.168.5.165");
    IPLocator::setPhysicalPort(locator, port);

    IPLocator::setLogicalPort(locator, port);
    
    m_tcp_domain_qos.wire_protocol().builtin.metatrafficUnicastLocatorList.push_back(locator);
    m_tcp_domain_qos.wire_protocol().default_unicast_locator_list.push_back(locator);
  }
  else // client
  {
    m_tcp_domain_qos.transport().use_builtin_transports = false;

    auto tcp_transport = std::make_shared<TCPv4TransportDescriptor>();
    m_tcp_domain_qos.transport().user_transports.push_back(tcp_transport);
    Locator initial_peer_locator;
    initial_peer_locator.kind = LOCATOR_KIND_TCPv4;
    IPLocator::setIPv4(initial_peer_locator, "192.168.5.165");
    IPLocator::setPhysicalPort(initial_peer_locator, port);
    IPLocator::setLogicalPort(initial_peer_locator, port);

    m_tcp_domain_qos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator);

    m_tcp_domain_qos.wire_protocol().builtin.initialPeersList.push_back(initial_peer_locator);
  }
}
void Transport::initShmQos()
{

  std::shared_ptr<SharedMemTransportDescriptor> shm_transport = std::make_shared<SharedMemTransportDescriptor>();

  m_shm_domain_qos.transport().user_transports.push_back(shm_transport);
}

DomainParticipantQos& Transport::getUdpQos()
{
  return m_udp_domain_qos;
}
DomainParticipantQos& Transport::getTcpQos()
{
  return m_tcp_domain_qos;
}
DomainParticipantQos& Transport::getShmQos()
{
  return m_shm_domain_qos;
}