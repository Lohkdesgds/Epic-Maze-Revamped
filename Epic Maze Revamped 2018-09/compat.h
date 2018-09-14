#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>  
#include <Windows.h>
#include <cmath>
#include <chrono>

// define or undef to use ALLEGRO or SFML
#define USING_ALLEGRO

#ifdef USING_ALLEGRO

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

typedef ALLEGRO_COLOR lsw_color;
typedef ALLEGRO_BITMAP* lsw_texture;
typedef ALLEGRO_FONT* lsw_font;
typedef ALLEGRO_DISPLAY* lsw_display;
typedef ALLEGRO_TIMER* lsw_timer;
typedef ALLEGRO_EVENT_QUEUE* lsw_event_qu;
typedef ALLEGRO_EVENT lsw_event;

const bool load();
const lsw_color color(const float, const float, const float, const float = 1.0);
void drawText(lsw_font, const lsw_color, const int, const int, const int, const char*, ...);
const int getBitmapWidth(const lsw_texture);
const int getBitmapHeight(const lsw_texture);
const int getBitmapSize(const lsw_texture, const int);
const int getDisplayWidth(const lsw_display);
const int getDisplayHeight(const lsw_display);
const int getDisplaySize(const lsw_display, const int);
lsw_texture createTexture(const int, const int);
lsw_display createDisplay(const int, const int);
void freeUp(lsw_texture&);
void freeUp(lsw_font&);
void freeUp(lsw_display&);
void freeUp(lsw_timer&);
void freeUp(lsw_event_qu&);
void drawBitmap(lsw_texture, const float, const float, const float, const float, const float, const float, const float, const int);
void drawBitmap(lsw_texture, const lsw_color, const float, const float, const float, const float, const float, const float, const float, const int);
template <typename N> void flipD(N);
void defineOut(lsw_display);
void defineOut(lsw_texture);

#else

#include <SFML/Graphics.hpp>

const bool load();
const sf::Color color(const float, const float, const float, const float = 1.0);


#endif

// doesn't depend on the library to work:
const double getTime();
void restFor(const double);