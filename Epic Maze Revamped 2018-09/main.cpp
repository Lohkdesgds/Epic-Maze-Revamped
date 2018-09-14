#include <iostream>
#include <string>
#include <vector>

#include "compat.h"
#include "resource.h"
#include "display_event.h"

void freezeup();

int main()
{
	//getTime(); // set first value
	LSW::EpicMazeR::displayer maindisp;

	std::cout << "#####[{> EpicMaze Revamped V2 <}]#####" << std::endl;
	std::cout << "[!] Loading core..." << std::endl;

	if (!load()) {
		std::cout << "[!] Failed loading core! (Allegro)" << std::endl;
		freezeup();
	}

	std::cout << "[!] Creating display..." << std::endl;

	std::cout << "[!] Displayer now will think about the display." << std::endl;

	do
	{
		maindisp.deinitAll();
		maindisp.init();

		maindisp.clearTo(color(0, 0, 0));
		maindisp.flip();

	}while (maindisp.think() != 0);

	return 0;
}

void freezeup()
{
	int a;
	std::cin >> a;
}