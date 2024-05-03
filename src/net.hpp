#ifndef NET_HPP
#define NET_HPP
#include <shared_net.h>
#include <SFML/Network.hpp>
#include <ThreadPool.h>
inline void send(srvpack packet, sf::TcpSocket& sock){
packeddata d = packsrv(packet);
sf::Socket::Status status = sock.send(d.data, 2);

}
inline void asend(srvpack packet, sf::TcpSocket& sock)
{
    static ThreadPool pool(8);
    pool.enqueue(send, packet, sock);
}
#endif