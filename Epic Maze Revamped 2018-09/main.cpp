#include <iostream>
#include <string>
#include <vector>

#include "resource.h"
#include "display_event.h"

const bool loadAllegro();
void freezeup();

int main()
{
	LSW::EpicMazeR::displayer maindisp;

	std::cout << "#####[{> EpicMaze Revamped V2 <}]#####" << std::endl;
	std::cout << "[!] Running on:" << std::endl;
	system("cd");
	std::cout << "[!] Loading core..." << std::endl;

	if (!loadAllegro()) {
		std::cout << "[!] Failed loading core! (Allegro)" << std::endl;
		freezeup();
	}

	std::cout << "[!] Creating display..." << std::endl;
	maindisp.init();

	maindisp.clearTo(al_map_rgb(0, 0, 0));
	maindisp.flip();

	std::cout << "[!] Displayer now will think about the display." << std::endl;

	maindisp.think();

	return 0;
}

const bool loadAllegro()
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
void freezeup()
{
	int a;
	std::cin >> a;
}