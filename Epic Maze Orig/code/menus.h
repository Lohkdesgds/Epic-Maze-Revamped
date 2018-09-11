#pragma once

#include "functions.h"
#include "all_my_things.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <thread>

///NÃO ESQUECER DO CONTROLE DE FPS!

void seeker(ALLEGRO_DISPLAY *, ALLEGRO_DISPLAY_MODE, ALLEGRO_EVENT_QUEUE *, int, char *, int, int, int); /// colocar este para controlar caminhos entre eles

///primeiro menu
int menu(int *, ALLEGRO_DISPLAY *, ALLEGRO_EVENT_QUEUE *, pauses_anim *, ALLEGRO_FONT *, ALLEGRO_DISPLAY_MODE , int );

///coisas do menu
int menu_start(int *, ALLEGRO_DISPLAY *, ALLEGRO_EVENT_QUEUE *, int , char *, pauses_anim *, ALLEGRO_FONT *, ALLEGRO_DISPLAY_MODE disp_data, int);
int menu_instructions(int *, ALLEGRO_DISPLAY *, ALLEGRO_EVENT_QUEUE *, int , char *, pauses_anim *, ALLEGRO_FONT *, ALLEGRO_DISPLAY_MODE disp_data, int);
int menu_records(int *, ALLEGRO_DISPLAY *, ALLEGRO_EVENT_QUEUE *, int , char *, pauses_anim *, ALLEGRO_FONT *, ALLEGRO_DISPLAY_MODE disp_data, int);

///Jogo
int game_play(int *, ALLEGRO_DISPLAY *, ALLEGRO_EVENT_QUEUE *, int , char *, pauses_anim *, ALLEGRO_FONT *, ALLEGRO_DISPLAY_MODE , int , int );
int game_gerarmapa(ALLEGRO_EVENT_QUEUE *, ALLEGRO_DISPLAY *, ALLEGRO_BITMAP *, ALLEGRO_FONT *, int *, ALLEGRO_BITMAP *, ALLEGRO_BITMAP *, ALLEGRO_DISPLAY_MODE , int , int);

///coisas de qualquer função
void exit_app(ALLEGRO_DISPLAY *, char *);

