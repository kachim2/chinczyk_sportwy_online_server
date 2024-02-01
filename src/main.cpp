//
// Created by mi on 30.09.23.
//
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <unordered_map>
#include "shared_net.h"
#define char unsigned char
typedef struct Kilent{
    uint8_t numer_gracza;
    std::size_t game_num;
    sf::TcpSocket socket;

}Klient;
struct Gra{
    Gra(){
        for(int i = 0; i < 4; i++){
            pozycje[i] = i*10;
        }
        turn = 0;
    }
    uint8_t turn;
    uint8_t pozycje[4];
    uint8_t players;

};
int main(){
    sf::TcpListener listener;
    if (listener.listen(21376) != sf::Socket::Done)
    {
        std::cerr << "can't listen";
    }
    listener.setBlocking(0);
    sf::SocketSelector selector;
    selector.add(listener);
    std::vector<Klient*> klienci;
    std::unordered_map<std::size_t , Gra*> Gry;
    while (true){
        selector.wait();
        if(selector.isReady(listener)){
            Klient* client = new Klient;
            if(listener.accept(client->socket) == sf::Socket::Done){
                klienci.push_back(client);
                client->socket.setBlocking(0);
                selector.add(client->socket);
                std::cout << client->socket.getRemoteAddress() << ':'<< client->socket.getRemotePort() << '\n';
            } else{
                delete client;
            }
        }
        for(int i = 0; i<klienci.size(); i++){
            sf::TcpSocket &sock = klienci[i]->socket;
            Klient *client = klienci[i];
            if(selector.isReady( sock)){
                packeddata p;
                std::size_t recieved;
                sf::Socket::Status status=  sock.receive(p.data, 2, recieved);
                if(status == sf::Socket::Status::Disconnected){
                    delete Gry[client->game_num];
                    Gry.erase( client->game_num);
                    klienci.erase(klienci.begin()+i);
                    delete client;
                }else if(status == sf::Socket::Status::Done){


                    clipack d = unpackcli(p);
                    if(d.PlayerNum == 3){
                        client->game_num=d.GameNum;
                        if(Gry.count(d.GameNum) == 0){
                            Gry[d.GameNum] = new Gra;
                        }
                        client->numer_gracza = Gry[d.GameNum]->players;
                        Gry[d.GameNum]->players++;
                        
                    }
                }
            }
        }
    }

}