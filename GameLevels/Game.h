#ifndef LEAGUEOFGEMS_GAME_H
#define LEAGUEOFGEMS_GAME_H

#include "../DataStructures/LinkedList.cpp"
#include "../Characters/Player.h"
#include "../Characters/Enemy.h"
#include "../GreedyAlgorithms/Dijkstra.h"
#include "../Characters/Explosion.h"

class Game {
private:
    LinkedList<Player *> *playersList;
    LinkedList<Enemy *> *enemyList;
    LinkedList<Explosion *> *explosionList;
    ALLEGRO_BITMAP *tiles;
    Player *player;
    int map[21][27];
    Dijkstra dij = Dijkstra();//Agregue esta variable
    int level;
    int animationTimer;

    void createPlayers();
    void drawMap();
    void createMap();

public:
    Game();//Hice un cambio en este metodo
    void update(int, int);//Y en este metodo tambien XD
    void updateCenter(int x, int y);//Añadi este metodo para definir el centro d calculo para pathfinding
    Enemy * searchEnemy(int x, int y);
    void draw();
    ~Game();
};


#endif //LEAGUEOFGEMS_GAME_H
