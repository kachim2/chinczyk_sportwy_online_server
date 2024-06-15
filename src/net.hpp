#ifndef NET_HPP
#define NET_HPP
#include <shared_net.h>
#include <SFML/Network.hpp>
#include <ThreadPool.h>
#include<utility>
void asend(srvpack packet, sf::TcpSocket& sock);

#endif