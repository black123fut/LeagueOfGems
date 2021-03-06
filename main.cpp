#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>
#include "GameLevels/Game.h"
#include "GreedyAlgorithms/AstarDirectory/execAStar.h"
#include "GreedyAlgorithms/AstarDirectory/globalArray.h"
#include "GreedyAlgorithms/AstarDirectory/MapSearchNode.h"
#include "GreedyAlgorithms/AstarDirectory/coordinate.h"

//AGREGADO POR GABRIEL
#include "DataStructures/AlgoritmoGen.h"
//AGREGADO POR GABRIEL
using namespace std;

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

    al_init_font_addon();
    al_init_ttf_addon();

    al_init_image_addon();
    al_init_primitives_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_install_mouse();
    al_install_keyboard();

    ALLEGRO_KEYBOARD_STATE keyState;
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER *drawTimer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER *menuTimer = al_create_timer(1.0 / 60);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(drawTimer));
    al_register_event_source(event_queue, al_get_timer_event_source(menuTimer));

    al_reserve_samples(6);


    ALLEGRO_SAMPLE *EtimusSound = al_load_sample("../resources/Etimus.wav");
    ALLEGRO_SAMPLE *EspartaSound = al_load_sample("../resources/Esparta.wav");
    ALLEGRO_SAMPLE *AUSound = al_load_sample("../resources/AU.wav");
    ALLEGRO_SAMPLE *ChoiceSound = al_load_sample("../resources/Button.wav");
    ALLEGRO_SAMPLE *Intro = al_load_sample("../resources/Cancion.ogg");
    ALLEGRO_BITMAP *winImage = al_load_bitmap("../resources/win.png");
    ALLEGRO_BITMAP *loseImage = al_load_bitmap("../resources/gameover.png");
    ALLEGRO_BITMAP *titule = al_load_bitmap("../resources/titule.png");
    ALLEGRO_BITMAP *option = al_load_bitmap("../resources/options.png");

    ALLEGRO_SAMPLE_INSTANCE *IntroInstance = al_create_sample_instance(Intro);
    al_set_sample_instance_playmode(IntroInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(IntroInstance, al_get_default_mixer());

    al_play_sample_instance(IntroInstance);
    al_start_timer(timer);
    al_start_timer(drawTimer);
    al_start_timer(menuTimer);

    al_play_sample_instance(IntroInstance);

    bool on = false;
    int x = 1150, y = 850;
    int operation = 1;

    // Menu
    while(!on) {
        ALLEGRO_EVENT events2;
        al_wait_for_event(event_queue, &events2);

        if (events2.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (events2.keyboard.keycode) {
                case ALLEGRO_KEY_ENTER:
                    on = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    if (operation != 3)
                        operation++;
                    break;
                case ALLEGRO_KEY_UP:
                    if (operation != 1)
                        operation--;
                    break;
            }
        }
        if (events2.type == ALLEGRO_EVENT_TIMER) {
            if(events2.timer.source == menuTimer) {
                al_clear_to_color(al_map_rgb(62, 240, 98));
                al_draw_bitmap(titule, 0, 0, 0);
                al_draw_filled_rectangle(0, 300 + 100 * (operation - 1), 300, 300 + 100 * operation, al_map_rgb(255, 255, 255));
                al_draw_bitmap(option, 0, 0, 0);
                al_flip_display();
            }
        }
    }

    Game *game = new Game(operation);

    // Juego
    while (!running){
        al_play_sample_instance(IntroInstance);
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = true;
        }
        else if(events.type == ALLEGRO_EVENT_TIMER)
        {
            if (events.timer.source == timer) {
                //Still playing
                if (game->getState() == 0) {
                    // Update
                    game->update();

                    al_get_keyboard_state(&keyState);
                    if (al_key_down(&keyState, ALLEGRO_KEY_1)) {
                        game->setCurrentAttack(1);
                        al_play_sample(ChoiceSound,6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);


                    }
                    else if (al_key_down(&keyState, ALLEGRO_KEY_2)) {
                        al_play_sample(ChoiceSound,6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        game->setCurrentAttack(2);
                    }
                    else if (al_key_down(&keyState, ALLEGRO_KEY_3)) {
                        al_play_sample(ChoiceSound,6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        game->setCurrentAttack(3);
                    }

                    ALLEGRO_MOUSE_STATE state;
                    al_get_mouse_state(&state);

                    if (state.buttons & 2) {
                        // GreedyAlgorithms
                        al_play_sample(EtimusSound,6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);

                        x = state.x;
                        y = state.y;

                        int posx = x / 50;
                        int posy = y / 50;

                        cout << "Mover hacia: " << "[" << posx << ", " << posy << "]" << endl;
                        if (y < 1050) {
                            game->updateCenter(posx, posy); //Aqui se recalcula el nodo al que tiene q llegar el personaje
                            al_play_sample(EspartaSound, 6.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                        }
                    }
                }
            }

            else if (events.timer.source == drawTimer) {
                // Draw
                al_clear_to_color(al_map_rgb(62, 240, 98));
                al_draw_filled_rectangle(0, 1050, 1350, 1150, al_map_rgb(0, 0, 113));
                if (game->getState() == 0) {
                    game->draw();
                }
                if (game->getState() == 1) {
                    al_draw_bitmap(loseImage, 0, 0, 0);
                }
                    // won
                else if (game->getState() == 2) {
                    al_draw_bitmap(winImage, 0, 0, 0);
                }
                al_flip_display();
            }
        }
    }

    delete game;
    al_destroy_display(display);
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_destroy_sample(Intro);
    al_destroy_sample_instance(IntroInstance);
    al_destroy_event_queue(event_queue);

//AGREGADO POR GABRIEL
//    AlgoritmoGen *X;
//    X = new AlgoritmoGen();
//    X->CreaOleadas(1);

//AGREGADO POR GABRIEL

    return 0;
}