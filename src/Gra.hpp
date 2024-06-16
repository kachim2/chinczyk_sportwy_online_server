#ifndef GRA_HPP
#define GRA_HPP
#include <stdint.h>
#include <shared_net.h>
#include <SFML/Network.hpp>
#include<memory>
#include "Klient.hpp"
struct pawn
{

  int x = 0, y = 0;
  int px = 0, py = 0;
  int place = 0;
  bool inplay = 0;
};
class Gra
{
    public:

        Gra();
        void handle_packet(clipack pack, short playernum);
        void add_client(std::shared_ptr<Klient> client);


        uint8_t players = 0;
        uint8_t turn = 3;
        uint8_t pturn = -1;
        pawn pawns[4][4];
        std::shared_ptr<Klient> clients[4];
        int pthrow = 0;
        bool is_pawn_in_game(pawn p);
        void retry(clipack pack, short playernum);
        void next(clipack pack, short playernum);
};

#endif