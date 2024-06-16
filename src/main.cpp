//
// Created by mi on 30.09.23.
//
#include <SFML/Network.hpp>
#include <ThreadPool.h>
#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <unordered_map>
#include "shared_net.h"
#include "Gra.hpp"
#include "Klient.hpp"
#define char unsigned char



int main()
{
    srand(time(0));
    sf::TcpListener listener;
    if (listener.listen(21376) != sf::Socket::Done)
    {
        std::cerr << "can't listen";
    }
    sf::SocketSelector selector;
    selector.add(listener);
    std::vector<std::shared_ptr<Klient>> klienci;
    std::unordered_map<std::size_t, Gra *> Gry;
    while (true)
    {
        selector.wait();
        if (selector.isReady(listener))
        {
            Klient *client = new Klient;
            if (listener.accept(*client->socket) == sf::Socket::Done)
            {
                klienci.push_back(std::shared_ptr<Klient>(client));

                selector.add(*client->socket);
                std::cout << client->socket->getRemoteAddress() << ':' << client->socket->getRemotePort() << std::endl;
            }
            else
            {
                delete client;
            }
        }
        for (int i = 0; i < klienci.size(); i++)
        {
            sf::TcpSocket &sock = *klienci[i]->socket;
            std::shared_ptr<Klient> client = klienci[i];
            if (selector.isReady(sock))
            {
                packeddata p;
                std::size_t recieved;
                sf::Socket::Status status = sock.receive(p.data, 2, recieved);
                if (status == sf::Socket::Status::Disconnected)
                {
                    std::cerr << sock.getRemoteAddress() << ':' << sock.getRemotePort() << " disconnected from game: " << client->game_num<< std::endl;
                    int gamenum = client->game_num;
                    for(auto i: Gry[gamenum]->clients){
                        selector.remove(*i->socket);
                    }
                    Gry.erase(gamenum);
                    for(auto i : Gry){
                        std::cerr << i.first << ' ';
                    }
                    std::cerr << std::endl;
                }
                else if (status == sf::Socket::Status::Done)
                {

                    clipack d = unpackcli(p);
                    if (client->first)
                    {
                        client->game_num = d.GameNum;
                        if (Gry.count(d.GameNum) == 0)
                        {
                            Gry[d.GameNum] = new Gra();
                            std::cerr << "New Game " << d.GameNum << std::endl;
                        }
                        if(Gry.count(d.GameNum))
                        Gry[d.GameNum]->add_client(client);
                        client->first = 0;
                        if(Gry[d.GameNum]->players == 4){
                            if(Gry.count(d.GameNum))
                            Gry[d.GameNum]->next(d, client->numer_gracza);
                        }
                    }else{
                        if(Gry.count(d.GameNum))
                        Gry[d.GameNum]->handle_packet(d, client->numer_gracza);
                    }
                }
            }
        }
    }
}
