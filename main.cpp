#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <iostream>
#include "GameLevels/Game.h"
#include "GreedyAlgorithms/AstarDirectory/execAStar.h"
#include "GreedyAlgorithms/AstarDirectory/globalArray.h"
#include "GreedyAlgorithms/AstarDirectory/MapSearchNode.h"
#include "GreedyAlgorithms/AstarDirectory/coordinate.h"

//int main() {
//
//
//    ///Esta es la matriz se generó en la interfaz
//    int matrizInterfaz[21][27] =
//            {
//
//
//                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //00
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 01
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 02
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 03
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 04
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 05
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 06
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 07
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 08
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 09
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 10
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 11
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 12
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 13
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 14
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 15
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 16
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 17
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 18
//                    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},  // 19
//                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //20
//
//            };
//
//    ///Posicipn inicial
//    MapSearchNode nodeStart;
//    nodeStart.x = 0;
//    nodeStart.y = 0;
//
//    ///Se define la posicion del objetivo
//    MapSearchNode nodeEnd;
//    nodeEnd.x = 26;
//    nodeEnd.y = 20;
//    execAStar ejecutable;
//    vector<coordinate> rutaPathfinding = ejecutable.obtenerCoordenadas(matrizInterfaz, nodeStart, nodeEnd);
//
//    cout << "Largo: " << rutaPathfinding.size() << endl;
//    cout << rutaPathfinding[0].x << endl;
//    rutaPathfinding.erase(rutaPathfinding.begin());
//
//    cout << "Largo: " << rutaPathfinding.size() << endl;
//    cout << rutaPathfinding[0].x << endl;
//    rutaPathfinding.erase(rutaPathfinding.begin());
//
//    cout << "Largo: " << rutaPathfinding.size() << endl;
//    cout << rutaPathfinding[0].x << endl;
//    rutaPathfinding.erase(rutaPathfinding.begin());
//
//    cout << "Largo: " << rutaPathfinding.size() << endl;
//    cout << rutaPathfinding[0].x << endl;
//
//    for (coordinate i: rutaPathfinding) {
//        cout << i.x << "," << i.y << endl;
//    }
//
//
//    return 0;
//
//}


int main(int argc, char **argv){
    ALLEGRO_DISPLAY *display;
    bool running = false;

    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    //X: 1350   Y:1050
    display = al_create_display(1350, 1150);

    if(!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    al_set_window_position(display, 600, 300);

    al_init_image_addon();
    al_init_primitives_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_install_mouse();
    al_install_keyboard();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER *drawTimer = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(drawTimer));

    al_start_timer(timer);
    al_start_timer(drawTimer);

    Game *game = new Game;
    int x = 1150, y = 850;

    while (!running){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (events.keyboard.keycode) {
                case ALLEGRO_KEY_1:
                    game->setCurrentAttack(1);
                    break;
                case ALLEGRO_KEY_2:
                    game->setCurrentAttack(2);
                    break;
                case ALLEGRO_KEY_3:
                    game->setCurrentAttack(3);
                    break;
                default:
                    break;
            }
        }

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = true;
        }
        else if(events.type == ALLEGRO_EVENT_TIMER)
        {
            if (events.timer.source == timer)
            {
                // Update
                game->update();

                ALLEGRO_MOUSE_STATE state;
                al_get_mouse_state(&state);

                if (state.buttons & 1) {
                    x = state.x;
                    y = state.y;
                }
                else if (state.buttons & 2) {
                    // GreedyAlgorithms
                    x = state.x;
                    y = state.y;

                    cout << "Pathfindeo" << endl;

                    int posx = x / 50;
                    int posy = y / 50;

                    cout << "Mover hacia: " << "[" << posx << ", " << posy << "]" << endl;
                    if (y < 1050) {
                        game->updateCenter(posx,posy); //Aqui se recalcula el nodo al que tiene q llegar el personaje
                    }
                }

                if (events.type == ALLEGRO_EVENT_MOUSE_AXES) {
                    x = events.mouse.x;
                    y = events.mouse.y;
                }
            }

            else if (events.timer.source == drawTimer) {
                // Draw
                al_clear_to_color(al_map_rgb(62, 240, 98));
                al_draw_filled_rectangle(0, 1050, 1350, 1150, al_map_rgb(0, 0, 113));
                game->draw();
                al_flip_display();
            }
        }
    }

    delete game;
    al_destroy_display(display);
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_destroy_event_queue(event_queue);
    return 0;
}