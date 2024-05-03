#ifndef KLIENT_H
#define KLIENT_H
#include<stdint.h>
#include<SFML/Network.hpp>
struct Klient
{
    uint8_t numer_gracza;
    std::size_t game_num;
    sf::TcpSocket socket;
    bool first = 1;
};
#endif