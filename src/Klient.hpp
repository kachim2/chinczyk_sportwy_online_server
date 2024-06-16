#ifndef KLIENT_H
#define KLIENT_H
#include<stdint.h>
#include<SFML/Network.hpp>
#include <memory>
struct Klient
{
    uint8_t numer_gracza;
    std::size_t game_num;
    std::shared_ptr<sf::TcpSocket> socket = std::make_shared<sf::TcpSocket>();
    bool first = 1;
};
#endif