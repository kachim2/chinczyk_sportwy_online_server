#include <cpath.h>
#include "Gra.hpp"
const short bpos[4][2]{{1, 1}, {10, 1}, {10, 10}, {1, 10}

};
const short spos[4][2][2]{
    {{1, 5}, {1, 6}}, {{7, 1}, {6, 1}}, {{11, 7}, {11, 6}}, {{5, 11}, 6, 11}

};
void movepawnone(pawn *p)
{
    const int posiblemoves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < 4; i++)
    {
        const int nx = posiblemoves[i][0] + p->x;
        const int ny = posiblemoves[i][1] + p->y;
        if (p->place < 39)
        {
            if (cpath[ny][nx] == 1)
            {
                if (nx != p->px || ny != p->py)
                {
                    p->px = p->x;
                    p->py = p->y;
                    p->x = nx;
                    p->y = ny;
                    p->place++;
                    return;
                }
            }
        }
        else
        {
            if (cpath[ny][nx] > 1)
            {
                if (nx != p->px || ny != p->py)
                {
                    p->px = p->x;
                    p->py = p->y;
                    p->x = nx;
                    p->y = ny;
                    p->place++;
                    return;
                }
            }
        }
    }
    return;
}
void movepawn(pawn *p, int k, unsigned char a)
{
    if (p->inplay == 0 && k != 0)
    {
        p->x = spos[a][0][0];
        p->y = spos[a][0][1];
        p->px = spos[a][1][0];
        p->py = spos[a][1][1];
        p->inplay = 1;
        return;
    }
    for (int i = 0; i < k; i++)
    {
        movepawnone(p);
    }
}
void sendback(pawn pawns[4][4], int pr, int pa)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == pr && j == pa)
                continue;
            else if (pawns[i][j].x == pawns[pr][pa].x &&
                     pawns[i][j].y == pawns[pr][pa].y)
            {
                pawns[i][j].place = 0;
                pawns[i][j].inplay = 0;
                pawns[i][j].x = bpos[i][0] + (j) % 2;
                pawns[i][j].y = bpos[i][1] + (j) / 2;
            }
        }
    }
}

Gra::Gra() {}
void Gra::add_client(Klient *client)
{
    clients[players] = client;
    players++;
    client 
}
void Gra::handle_packet(clipack pack, short playernum){
    
}