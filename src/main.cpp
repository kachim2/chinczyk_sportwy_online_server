//
// Created by mi on 30.09.23.
//
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "shared_net.h"
typedef struct Kilent{
    int8_t numer_gracza;
    sf::Socket socket;
}Klient;
typedef struct Gra{


}Gra;
int main(){
    sf::TcpListener listener;
    if (listener.listen(21376) != sf::Socket::Done)
    {
        std::cerr << "can't listen";
    }

    sf::SocketSelector selector;
    selector.add(listener);
    std::vector<sf::Socket> klienci;
    while (true){
        selector.wait();
        if(selector.isReady(listener)){

        }
    }

}