#ifndef NET_HPP
#define NET_HPP
#include <shared_net.h>
#include <SFML/Network.hpp>
#include <ThreadPool.h>
#include<utility>
void asend(srvpack packet, std::shared_ptr<sf::TcpSocket> sock);

#endif