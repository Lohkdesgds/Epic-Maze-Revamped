#include "compat.h"

#ifdef USING_ALLEGRO

const bool load()
{
	bool main = al_init(); // has to be first, safer.
	return (main &&
		al_install_keyboard() &&
		al_init_image_addon() &&
		al_init_font_addon() &&
		al_init_ttf_addon() &&
		al_init_primitives_addon()
		);
}

const lsw_color color(const float r, const float g, const float b, const float a)
{
	return al_map_rgba_f(r, g, b, a);
}
void drawText(lsw_font f, const lsw_color c, const int x, const int y, const int p, const char* s, ...)
{
	va_list args;
	char temporary[512];
	va_start(args, s);
	vsnprintf_s(temporary, 512, s, args);
	al_draw_text(f, c, x, y, p, temporary);
}
const int getBitmapWidth(const lsw_texture u)
{
	return getBitmapSize(u, 0);
}
const int getBitmapHeight(const lsw_texture u)
{
	return getBitmapSize(u, 1);
}
const int getBitmapSize(const lsw_texture u, const int axes)
{
	if (axes == 0) return al_get_bitmap_width(u);
	else al_get_bitmap_height(u);
}
const int getDisplayWidth(const lsw_display u)
{
	return getDisplaySize(u, 0);
}
const int getDisplayHeight(const lsw_display u)
{
	return getDisplaySize(u, 1);
}
const int getDisplaySize(const lsw_display u, const int axes)
{
	if (axes == 0) return al_get_display_width(u);
	else al_get_display_height(u);
}
lsw_texture createTexture(const int x, const int y)
{
	return al_create_bitmap(x, y);
}
lsw_display createDisplay(const int x, const int y)
{
	return al_create_display(x, y);
}
void freeUp(lsw_texture& e)
{
	if (e) al_destroy_bitmap(e);
	e = nullptr;
}
void freeUp(lsw_font& e)
{
	if (e) al_destroy_font(e);
	e = nullptr;
}
void freeUp(lsw_display& e)
{
	if (e) al_destroy_display(e);
	e = nullptr;
}
void freeUp(lsw_timer& e)
{
	if (e) al_destroy_timer(e);
	e = nullptr;
}
void freeUp(lsw_event_qu& e)
{
	if (e) al_destroy_event_queue(e);
	e = nullptr;
}
void drawBitmap(lsw_texture t, const float cx, const float cy, const float dx, const float dy, const float sx, const float sy, const float theta, const int f)
{
	al_draw_scaled_rotated_bitmap(t, cx, cy, dx, dy, sx, sy, theta, f);
}
void drawBitmap(lsw_texture t, const lsw_color c, const float cx, const float cy, const float dx, const float dy, const float sx, const float sy, const float theta, const int f)
{
	al_draw_tinted_scaled_rotated_bitmap(t, c, cx, cy, dx, dy, sx, sy, theta, f);
}
template <> void flipD(lsw_display d)
{
	al_flip_display();
	defineOut(d);
}
template <> void flipD(lsw_texture d)
{
	al_flip_display();
	defineOut(d);
}
template<typename N> void flipD(N d)
{
	al_flip_display();
}
void defineOut(lsw_display d)
{
	al_set_target_backbuffer(d);
}
void defineOut(lsw_texture d)
{
	al_set_target_bitmap(d);
}

#else

const bool load()
{
	return true; // doesn't work that way
}
const sf::Color color(const float r, const float g, const float b, const float a)
{
	return sf::Color(255 * r, 255 * g, 255 * b, 255 * a);
}

#endif




const double getTime()
{
	/*static LARGE_INTEGER v;
	LARGE_INTEGER rn, freq;
	if (v.QuadPart == 0) QueryPerformanceCounter(&v);
	QueryPerformanceCounter(&rn);
	QueryPerformanceFrequency(&freq);
	double diff = fabs((rn.QuadPart - v.QuadPart) * 1000.0 /freq.QuadPart);
	return diff;*/

	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::time_point_cast<std::chrono::microseconds>(now);

	auto value = now_ms.time_since_epoch();

	return 0.000001 * value.count();
}
void restFor(const double t)
{
	double now = getTime();
	while (getTime() - now < t);
}