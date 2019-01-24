#pragma once

#include "compat.h"

#include <vector>
#include <mutex>
#include <string>
#include <Windows.h>

#include "resource.h"

#define VERSION "V2.3B UNIVp-1"


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
			lsw_event_qu ev_qu = nullptr;
			lsw_event ev;

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
			const bool init(lsw_event_qu);
			void deinit();

			const bool keepdisplayOn();
			const int getLastKeyIfAvailable(const key_type = LSW_KEYPRESSED);
		};

		// ********************************** //

		struct lsw_mode {
			int x = 0;
			int y = 0;
			int hz = 0;
		};
		struct lsw_modes_all {
			std::vector<lsw_mode> modes;
			int using_rn = 0;
		};

		struct gameplay_needs {
			bool being_made = true;
			int needed_reset = 0;
			int debug = 0;

			mapthing* map = nullptr;
			infinity_map* map2 = nullptr;

			std::thread* collision_controller = nullptr;
			/*int istestingcollision = -1;
			int main_asks_for_pause = 0;*/
			int beingusedby = -1;
			std::mutex change_oneanother;
			double collision_tps = 0.0;

			clock_t now = 0;
			double nowFps = 0.0, nowMult = 0.0;
			bool playin = true;
			bool paused = false;
			bool save_score = true;
			bool asked_for_help = false;

			int way = -1; // NSWE
			bool alternative_way[4] = { false };
			int way_cam = -1;
			double speed = 0.0;
			double speed_y = 0.0;
			double distance_taken = 0.0;
			double posrel[2] = { -0.9, -0.9 };
			double plrrot = 0.0;

			double playersiz_rel[2] = { 0.0, 0.0 };
			double blocksize_rel[2] = { 0.0, 0.0 };
			//double y_offset = 0.0;
			bool colided = false;
			double cases_times_mult = 0.0;

			double time_final[2] = { 0.0 };
			double final_score = 0.0;

			double min_dist[9][2];
			bool min_dist_used[9] = { false };
			double fixed_distance = 1.0;

			double campos[2] = { 0.0, 0.0 };
			double cammult[2];
			
			int key = -1, keykeep = -1, keylost = -1;
		};

		struct displayer_data {
			lsw_modes_all modes;
			lsw_display display = nullptr;
			lsw_texture buffer = nullptr;
			lsw_color color_blend = color(1.0, 1.0, 1.0, 1.0);
			lsw_texture transparency = nullptr;
			int full_a[2] = { 0,0 };
			lsw_event_qu ev_qu = nullptr;
			controller data_control;
			gameplay_needs *if_playin = nullptr;
			int usedx = 0, usedy = 0;
			float prop[2] = { 0.0,0.0 };

			bool loaded = false;
			std::mutex muu;

			event_mng evm;

			double fps = 0.0;
			//ULONGLONG tickCount = 0;
			stats now = LSW_S_INITIALIZING;

			ULONGLONG lastC = 0; // don't use normally
			double lastC_fMult_al = 0.0; // don't use normally

			double anim_posxy_keep = 0.0; // internal
			double lastdraw = 0.0; // internal

			double fixed_fps = -1;
			int display_mode_draw = false;

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

			int level = 0;
			bool enabled_alternative_mode = false;
			bool infinite_map = false;
			bool isFullscreen = false;

			// bmp, x, y, rot (º), scalex, scaley, boxsiz, cx, cy, blending? (only if no border), bitmap related x, bitmap related y
			void drawIt(lsw_texture, const double, const double, const double, const double = 1.0, const double = 1.0, const double = -1, double = -1, double = -1, const lsw_color = color(1, 0, 0), const bool = false, const int = -1, const int = -1);
			void bganim(const double); // you have to call multiplier to work (or its val)! (multiplier == sets right speed!)
			const int pauseScreenGame();

			// x, y, scale, blur
			void drawCircle(const double, const double, const double);

			// dx & dy. (plr pos - block pos)
			const assistance_nsew _whereToTp(const double, const double);
			// degrees
			const double _ang_dif(const double, const double);
			void fixFPS(const double, const double, const double);

			const bool loadModes(const int);
		public:
			void _thr_collision_work(gameplay_needs&);
			const bool init();

			void clearTo(const lsw_color);
			const double multiplier();
			void flip();
			const double lastFPS();
			void fixLoad();

			void resizeBufTo(const int, const int);

			const int think();

			void deinitAll();
		};

		void _thr_collisionwork_ext(gameplay_needs*, displayer*);
		void _thr_temp_generatemap(mapthing*, int, int*, bool*, bool*);
		void _thr_temp_loadallresources(int*, bool*);
		void _thr_keyboard(event_mng_data*);

		const char translate_al(const int);
		void fixProportion(int&, int&, const float = 16.0 / 9);
	}
}