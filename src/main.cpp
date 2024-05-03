//
// Created by mi on 30.09.23.
//
#include <SFML/Network.hpp>
#include <ThreadPool.h>
#include <iostream>
#include <vector>
#include <thread>
#include <unordered_map>
#include "shared_net.h"
#include "Gra.hpp"
#include "Klient.hpp"
#define char unsigned char



int main()
{
    sf::TcpListener listener;
    if (listener.listen(21376) != sf::Socket::Done)
    {
        std::cerr << "can't listen";
    }
    sf::SocketSelector selector;
    selector.add(listener);
    std::vector<Klient *> klienci;
    std::unordered_map<std::size_t, Gra *> Gry;
    while (true)
    {
        selector.wait();
        if (selector.isReady(listener))
        {
            Klient *client = new Klient;
            if (listener.accept(client->socket) == sf::Socket::Done)
            {
                klienci.push_back(client);
                client->socket.setBlocking(0);
                selector.add(client->socket);
                std::cout << client->socket.getRemoteAddress() << ':' << client->socket.getRemotePort() << '\n';
            }
            else
            {
                delete client;
            }
        }
        for (int i = 0; i < klienci.size(); i++)
        {
            sf::TcpSocket &sock = klienci[i]->socket;
            Klient *client = klienci[i];
            if (selector.isReady(sock))
            {
                packeddata p;
                std::size_t recieved;
                sf::Socket::Status status = sock.receive(p.data, 2, recieved);
                if (status == sf::Socket::Status::Disconnected)
                {
                    delete Gry[client->game_num];
                    Gry.erase(client->game_num);
                    klienci.erase(klienci.begin() + i);
                    delete client;
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
                        }
                        Gry[d.GameNum]->add_client(client);
                        client->first = 0;
                    }else{
                        Gry[d.GameNum]->handle_packet(d, client->numer_gracza);
                    }
                }
            }
        }
    }
}
