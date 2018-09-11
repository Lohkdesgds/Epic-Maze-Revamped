#pragma once

#include "all_my_things.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

///funções principais

int func_key_get(ALLEGRO_EVENT_QUEUE *, ALLEGRO_DISPLAY *);
char raw_key_get(ALLEGRO_EVENT_QUEUE *, ALLEGRO_DISPLAY *);

///Imprime na tela e no log
int printer(char *); /// V2.1 OK

///Carrega arquivos (início, e já sabe os arquivos)
int prepare_txts(bool *, int *, int *, int *, int *); /// V2.1 OK

///Para fins de controle de FrameRate
void controla_frame (double, double, int);

///Para timer, transforma segundos em minutos + segundos;
void min_e_seg(double *, double *);

///Animação de draw custom
void draw_effect(bool, complete_things *);

///Carregamento ordenado dos Records
int rec_reader(const char *arquivo, defaultrecords [10]);

// ADDED LATER: DEF
void end_of_func(complete_things *, int);