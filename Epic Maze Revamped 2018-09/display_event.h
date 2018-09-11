#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <mutex>
#include <string>
#include <Windows.h>

#include "resource.h"

#define VERSION "V2.1A snapshot-1"


// prop == 1 + 7/9

namespace LSW {

	namespace EpicMazeR {

		const int base_res[2] = { 1920,1080 };

		enum stats {
			LSW_S_INITIALIZING,
			LSW_S_MENU,
			LSW_S_INSTR,
			LSW_S_RECORDS,
			LSW_S_PLAY,
			LSW_S_EXIT,
			LSW_S_GAMING
		};

		enum key_type {
			LSW_KEYPRESSED,
			LSW_KEYLEFT,
			LSW_KEYKEEP_LAST
		};

		struct scores {
			std::string name;
			double score = -1.0;
		};

		struct event_mng_data {
			ALLEGRO_EVENT_QUEUE* ev_qu = nullptr;
			ALLEGRO_EVENT ev;

			std::thread* thr = nullptr;

			// LSW_KEYPRESSED
			int laststroke = 0;
			bool hasnewstroke = false;
			// LSW_KEYLEFT
			int laststrokeleft = 0;
			bool hasnewstrokeleft = false;

			int lastkeykeep = -1;


			bool closewindow = false;

			bool keeprunning = false;
			std::mutex m;
		};

		class event_mng {
			static event_mng_data data;
		public:
			const bool init(ALLEGRO_EVENT_QUEUE*);
			void deinit();

			const bool keepdisplayOn();
			const int getLastKeyIfAvailable(const key_type = LSW_KEYPRESSED);
		};

		// ********************************** //

		struct displayer_data {
			ALLEGRO_DISPLAY* display = nullptr;
			ALLEGRO_BITMAP* buffer = nullptr;
			ALLEGRO_BITMAP* transparency = nullptr;
			ALLEGRO_DISPLAY_MODE full;
			ALLEGRO_EVENT_QUEUE* ev_qu = nullptr;
			controller data_control;
			int usedx = 0, usedy = 0;
			float prop = 0.0;

			bool loaded = false;
			std::mutex muu;

			event_mng evm;

			double fps = 0.0;
			ULONGLONG tickCount = 0;
			stats now = LSW_S_INITIALIZING;

			ULONGLONG lastC = 0; // don't use normally
			double lastC_fMult_al = 0.0; // don't use normally

			double anim_posxy_keep = 0.0; // internal
			double lastdraw = 0.0; // internal

			bool infinite_mode = false;
		};

		enum assistance_nsew {
			LSW_P_NORTH,
			LSW_P_SOUTH,
			LSW_P_EAST,
			LSW_P_WEST
		};

		class displayer {
			static displayer_data data;
			// bmp, x, y, rot (º), scalex, scaley, boxsiz, cx, cy
			void drawIt(ALLEGRO_BITMAP*, const double, const double, const double, const double = 1.0, const double = 1.0, const double = -1, double = -1, double = -1, const ALLEGRO_COLOR = al_map_rgb(255, 0, 0));
			void bganim(const double); // you have to call multiplier to work (or its val)! (multiplier == sets right speed!)
			const int pauseScreenGame();

			// x, y, scale, blur
			void drawCircle(const double, const double, const double);

			// dx & dy. (plr pos - block pos)
			const assistance_nsew _whereToTp(const double, const double);
			// degrees
			const double _ang_dif(const double, const double);

			void _thr_collision_work();
		public:
			const bool init();

			void clearTo(const ALLEGRO_COLOR);
			const double multiplier();
			void flip();
			const double lastFPS();
			void fixLoad();

			void resizeBufTo(const int, const int);

			const bool think();

			void deinitAll();
		};

		void _thr_temp_generatemap(mapthing*, int, int*, bool*, bool*);
		void _thr_temp_loadallresources(int*, bool*);
		void _thr_keyboard(event_mng_data*);

		const char translate_al(const int);
	}
}