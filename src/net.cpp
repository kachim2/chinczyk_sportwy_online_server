#include "net.hpp"
void send(std::pair<srvpack, sf::TcpSocket&> p){
auto [packet, sock] = p;
packeddata d = packsrv(packet);
sf::Socket::Status status = sock.send(d.data, 2);

}
void asend(srvpack packet, sf::TcpSocket& sock)
{
    //send(packet, sock);
    static ThreadPool pool(8);
    //pool.
    pool.enqueue(send, std::pair<srvpack, sf::TcpSocket&>(packet, sock));
}