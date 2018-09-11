#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <ctype.h>

#include "filenames.h"

#define INDEV           true
#define LOHKPLAYING     false
#define KEY_RET         false
#define LIVRE           1
#define VISITADO        2
#define SEM_SAIDA       3
#define EASY            80
#define MEDIUM          170
#define HARD            350
#define SHOW_FPS        true
#define CONTROLARFRAMES false

/// Do solucionador
typedef struct
{
	int x;
	int y;
}posicao;

/// STRUCT do Records
typedef struct{
    int score;
    char nick[30];
}defaultrecords;

/// ENUM das escolhas do painel
typedef enum{
EXITE=3,
MENU=10,
START=0,
INSTRUCTIONS=1,
RECORDS=2,
CONFIG_OCULT=4,
GAME_EASY=7,
GAME_MEDIUM,
GAME_INSANE,
BASIC=-1
}painel;

/// ENUM do clear_files
typedef enum{
ONER_BITMAPR,     // kill bitmap
CHAR_POINTER,     // kill chars
FILE_POINTER,     // kill arq
APOIO_THINGS=100, // kill apoioes
ANIMATION_KO,     // kill animation
KILL_ALL_GOD      // kill everythin!
}data_type;

/// ENUM do LOAD de imagens
typedef enum{
WAITING,
BASICS_DEFAULT_LOAD,
MENU_DEFAULT_LOAD,
MENU_INSTRUCTIONS_LOAD,
MENU_RECORDS_LOAD,
MENU_CONFIG_OCULT,
MENU_START_LOAD,
GAME_LOAD,
PAUSE_MENU_LOAD,
}image_type_to_load;

/// ENUM teclas de jogo
typedef enum{
NOTHING=0,
BACKSPACE_KEY=-1,
ENTER_KEY=-2,
ESC_KEY=-10,
UP_KEY=-50,
DOWN_KEY=-51,
LEFT_KEY=-52,
RIGHT_KEY=-53,
F3_KEY=-128,
F1_KEY=-11
}key_game_worker;

/// BITMAPS! (Máx de RAM c/ todos carregados: 970MB)
typedef struct{
    ALLEGRO_BITMAP *buffer;   ///cte
    ALLEGRO_BITMAP *logo;     ///cte
    ALLEGRO_BITMAP *vignette; ///cte
    ALLEGRO_BITMAP *apoio_01;
    ALLEGRO_BITMAP *apoio_02;
    ALLEGRO_BITMAP *apoio_03;
    ALLEGRO_BITMAP *apoio_04;
    ALLEGRO_BITMAP *apoio_05;
    ALLEGRO_BITMAP *apoio_06;
    ALLEGRO_BITMAP *apoio_07;
    ALLEGRO_BITMAP *apoio_08;
    ALLEGRO_BITMAP *apoio_09;
    ALLEGRO_BITMAP *apoio_10;
    ALLEGRO_BITMAP *apoio_11;
    ALLEGRO_BITMAP *apoio_12;
    ALLEGRO_BITMAP *apoio_13;
    ALLEGRO_BITMAP *anim_00;
    ALLEGRO_BITMAP *anim_01;
    ALLEGRO_BITMAP *anim_02;
    ALLEGRO_BITMAP *anim_03;
    ALLEGRO_BITMAP *anim_04;
    ALLEGRO_BITMAP *anim_05;
    ALLEGRO_BITMAP *anim_06;
    ALLEGRO_BITMAP *anim_07;
    ALLEGRO_BITMAP *anim_08;
    ALLEGRO_BITMAP *anim_09;
    ALLEGRO_BITMAP *anim_10;
    ALLEGRO_BITMAP *anim_11;
    ALLEGRO_BITMAP *anim_12;
    ALLEGRO_BITMAP *anim_13;
    ALLEGRO_BITMAP *anim_14;
    ALLEGRO_BITMAP *anim_15;
    ALLEGRO_BITMAP *anim_16;
    ALLEGRO_BITMAP *anim_17;
    ALLEGRO_BITMAP *anim_18;
    ALLEGRO_BITMAP *anim_19;
    ALLEGRO_BITMAP *anim_20;
    ALLEGRO_BITMAP *anim_21;
    ALLEGRO_BITMAP *anim_22;
    ALLEGRO_BITMAP *anim_23;
    ALLEGRO_BITMAP *anim_24;
    ALLEGRO_BITMAP *anim_25;
    ALLEGRO_BITMAP *anim_26;
    ALLEGRO_BITMAP *anim_27;
    ALLEGRO_BITMAP *anim_28;
    ALLEGRO_BITMAP *anim_29;
}pauses_anim;

typedef struct{
    pauses_anim *images;
    double timer;
    int what_to_load, what_to_unload;
    int render_x, render_y;
    int key_get_game;
    int chosen, option;
    int posxy;
    float fps_real;
    char key_get_write;
    bool key_get_write_push;
    bool is_loading, is_unloading, quitting;
    ALLEGRO_THREAD *keyer, *imager/*, *crash_handler*/;
    ALLEGRO_FONT *font;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_DISPLAY *display;
}complete_things;

///|--------------------------------------------------> Menus.c <--------------------------------------------------|///

/// Função principal
void seeker(ALLEGRO_DISPLAY *, ALLEGRO_DISPLAY_MODE, ALLEGRO_EVENT_QUEUE *, int, const char *, int, int); /// colocar este para controlar caminhos entre eles

/// Primeiro Menu
int menu(complete_things *);

/// Coisas do Menu
int menu_start(complete_things *);
int menu_instructions(complete_things *);
int menu_records(complete_things *);
int configurer(complete_things *);

/// Jogo
int game_play(complete_things *);
int game_gerarmapa(complete_things *);
int solucionar(int *, int , int );

/// Coisas de qualquer função
void exit_app(ALLEGRO_DISPLAY *, const char *);

///|----------------------------------------------> Dynamic_things.c <---------------------------------------------|///

/// Multitask de abertura de bitmaps!
void *dynamic_loader (ALLEGRO_THREAD *, void *);
/// Another  way
void dynamic_loaderU(complete_things *);
void not_dynamic_loader(complete_things *);

/// Keygetter multitasker LOL!
void *dynamic_keytest(ALLEGRO_THREAD *, void *);

//void *crash_handler(ALLEGRO_THREAD *, void *);

///|------------------------------------------------> Functions.c <------------------------------------------------|///

/// Funções principais de KEY
int func_key_get(ALLEGRO_EVENT_QUEUE *, ALLEGRO_DISPLAY *);
char raw_key_get(ALLEGRO_EVENT_QUEUE *, ALLEGRO_DISPLAY *);

/// Imprime na tela e no log um texto
int printer(const char *);

/// Carrega arquivos (início, e já sabe os arquivos)
int prepare_txts(bool *, int *, int *, int *, int *);

/// Para fins de controle de FrameRate
void controla_frame (double, double, int);

/// Para timer, transforma segundos em minutos + segundos;
void min_e_seg(double *, double *);

/// Animação de draw custom
void draw_effect(bool , complete_things *);

/// Pra ter certeza que tudo será liberado (memória)
void clear_memory(data_type , void *);

/// Pra facilitar o load de várias imagens (GIF montado)
void load_gif_bitmaps (int , pauses_anim *, const char *);

/// Ajuda o solucionador
bool moved(int *, posicao , int , int , int , int );

/// PAAAUSE!
int pauser_time(complete_things *);

/// Forma fácil de controlar frames
void frame_maker (complete_things *);

/// Drawn de efeito background dos "menus"
void background_menu_animation (complete_things *);

/// NULLER
void all_null(complete_things *);

/// Drawer mais fácil e compacto
void draw_bitmap_to_buff (ALLEGRO_BITMAP *, ALLEGRO_BITMAP *, float , float , double, double, double);

/// Call de LOAD em background!
bool load_correct (complete_things *);
