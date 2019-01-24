#include <iostream>
#include <string>
#include <vector>

#include "compat.h"
#include "resource.h"
#include "display_event.h"
#include <allegro5/allegro_native_dialog.h>

void freezeup();

int main()
{
	try {
		getTime(); // set first value
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

		} while (maindisp.think() != 0);
	}
	catch (const std::string& s)
	{
		al_show_native_message_box(nullptr, "ERROR", "Error: ",
			s.c_str(),
			NULL,
			ALLEGRO_MESSAGEBOX_ERROR
		);
	}
	catch (const char* s)
	{
		al_show_native_message_box(nullptr, "ERROR", "Error: ",
			s,
			NULL,
			ALLEGRO_MESSAGEBOX_ERROR
		);
	}
	catch (const int i)
	{
		al_show_native_message_box(nullptr, "ERROR", "Error: ",
			("Returned: " + std::to_string(i)).c_str(),
			NULL,
			ALLEGRO_MESSAGEBOX_ERROR
		);
	}
	catch (...)
	{
		al_show_native_message_box(nullptr, "ERROR", "Error: ",
			"UNKNOWN?",
			NULL,
			ALLEGRO_MESSAGEBOX_ERROR
		);
	}
	
	return 0;
}

void freezeup()
{
	int a;
	std::cin >> a;
}