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
#include <conio.h>

namespace LSW {

	namespace EpicMazeR {

		const std::string images_paths[] = {
			"./data/icon.png\0",
			"./data/vignette.png\0",
			"./data/intro.png\0",
			"./data/menu_opt_01.png\0",
			"./data/menu_opt_02.png\0",
			"./data/menu_opt_03.png\0",
			"./data/menu_opt_04.png\0",
			"./data/menu_block.png\0",
			"./data/instr.png\0",
			"./data/rec_back.png\0",
			"./data/menu_opt_01_s.png\0",
			"./data/menu_opt_02_s.png\0",
			"./data/menu_opt_03_s.png\0",
			"./data/block.png\0",
			"./data/person.png\0",
			"./data/person_f01.png\0",
			"./data/person_f02.png\0",
			"./data/pause_00.png\0",
			"./data/pause_01.png\0",
			"./data/pause_02.png\0",
			"./data/pause_03.png\0",
			"./data/pause_04.png\0",
			"./data/pause_05.png\0",
			"./data/pause_06.png\0",
			"./data/pause_07.png\0",
			"./data/pause_08.png\0",
			"./data/pause_09.png\0",
			"./data/pause_10.png\0",
			"./data/pause_11.png\0",
			"./data/pause_12.png\0",
			"./data/pause_13.png\0",
			"./data/pause_14.png\0",
			"./data/pause_15.png\0",
			"./data/pause_16.png\0",
			"./data/pause_17.png\0",
			"./data/pause_18.png\0",
			"./data/pause_19.png\0",
			"./data/pause_20.png\0",
			"./data/pause_21.png\0",
			"./data/pause_22.png\0",
			"./data/pause_23.png\0",
			"./data/pause_24.png\0",
			"./data/pause_25.png\0",
			"./data/pause_26.png\0",
			"./data/pause_27.png\0",
			"./data/pause_28.png\0",
			"./data/pause_29.png\0",
			"./data/pause_continue.png\0",
			"./data/pause_exit.png\0",
			"./data/saving_score.png\0",
			"./data/block_end.png\0"
		};
		const std::string fonts_paths[] = {
			"./data/DejaVuSans.ttf\0"
		};

		enum images_available {
			LSW_BMP_ICON,
			LSW_BMP_VIGNETTE,
			LSW_BMP_INTRO,
			LSW_BMP_LOGO = LSW_BMP_INTRO,
			LSW_BMP_MENU_OPT_01,
			LSW_BMP_MENU_OPT_02,
			LSW_BMP_MENU_OPT_03,
			LSW_BMP_MENU_OPT_04,
			LSW_BMP_MENU_BLOCK,
			LSW_BMP_INSTR,
			LSW_BMP_REC_BACK,
			LSW_BMP_MENU_OPT_01_S,
			LSW_BMP_MENU_OPT_02_S,
			LSW_BMP_MENU_OPT_03_S,
			LSW_BMP_BLOCK,
			LSW_BMP_PERSON,
			LSW_BMP_PERSON_F01,
			LSW_BMP_PERSON_F02,
			LSW_BMP_PAUSE_00,
			LSW_BMP_PAUSE_01,
			LSW_BMP_PAUSE_02,
			LSW_BMP_PAUSE_03,
			LSW_BMP_PAUSE_04,
			LSW_BMP_PAUSE_05,
			LSW_BMP_PAUSE_06,
			LSW_BMP_PAUSE_07,
			LSW_BMP_PAUSE_08,
			LSW_BMP_PAUSE_09,
			LSW_BMP_PAUSE_10,
			LSW_BMP_PAUSE_11,
			LSW_BMP_PAUSE_12,
			LSW_BMP_PAUSE_13,
			LSW_BMP_PAUSE_14,
			LSW_BMP_PAUSE_15,
			LSW_BMP_PAUSE_16,
			LSW_BMP_PAUSE_17,
			LSW_BMP_PAUSE_18,
			LSW_BMP_PAUSE_19,
			LSW_BMP_PAUSE_20,
			LSW_BMP_PAUSE_21,
			LSW_BMP_PAUSE_22,
			LSW_BMP_PAUSE_23,
			LSW_BMP_PAUSE_24,
			LSW_BMP_PAUSE_25,
			LSW_BMP_PAUSE_26,
			LSW_BMP_PAUSE_27,
			LSW_BMP_PAUSE_28,
			LSW_BMP_PAUSE_29,
			LSW_BMP_PAUSE_CONTINUE,
			LSW_BMP_PAUSE_EXIT,
			LSW_BMP_SAVING_SCORE,
			LSW_BMP_BLOCK_END,
			LSW_BMP_MAX = LSW_BMP_BLOCK_END
		};
		enum fonts_available {
			LSW_FONT_DEJAVUSANS,
			LSW_FONT_MAX = LSW_FONT_DEJAVUSANS
		};
		enum load_modes {
			LSW_AS_BMP,
			LSW_AS_FONT
		};
		enum image_groups {
			LSW_BASICS_DEFAULT_LOAD,
			LSW_MENU_DEFAULT_LOAD,
			LSW_MENU_INSTRUCTIONS_LOAD,
			LSW_MENU_RECORDS_LOAD,
			LSW_MENU_CONFIG_OCULT,
			LSW_MENU_START_LOAD,
			LSW_GAME_LOAD,
			LSW_PAUSE_MENU_LOAD,
		};

		class bitmap {
			void* file = nullptr;
			// ULONGLONG lastcall = 0; // will be used later
			int lastopt = -1;
			float lastfontsiz = 0.0;
			load_modes occured = LSW_AS_BMP;
		public:
			const bool load(const images_available);
			const bool load(const fonts_available, const float = -1.0f);
			void* get();
			//const bool process(); // true if processed (lowered resolution of image) // LATER
			void freeup();
			void reload();

			const bool amI(const int, const load_modes);
		};

		struct controller_params {
			std::vector<bitmap*> bmps;
			std::mutex access;
		};

		class controller {
			static controller_params data;
			const bool hasIt(const int /*who*/, const load_modes, bitmap** /*can be nullptr*/ = nullptr, const bool /*force to be load?*/ = true);
		public:
			const bool load(const images_available);
			const bool load(const image_groups);
			const bool load(const fonts_available, const float);
			const bool loadAll();
			
			void unload(const images_available);
			void unload(const image_groups);
			void unload(const fonts_available);
			void unloadAll();

			void clearAll();

			ALLEGRO_BITMAP* get(const images_available);
			ALLEGRO_FONT* get(const fonts_available);
		};

		struct posicao {
			int x = 0;
			int y = 0;
		};
		struct posicao_precisa {
			double rx = 0;
			double ry = 0;
		};

		enum map_coding {
			LSW_BLOCO,
			LSW_LIVRE,
			LSW_VISITADO,
			LSW_SEM_SAIDA
		};

		enum map_sizes {
			LSW_SIZ_X,
			LSW_SIZ_Y
		};

		struct chunk {
			int blocks[16][16] = { LSW_BLOCO };
			int idx = 0;
			int idy = 0;
		};


		class mapthing {
			int *matriz = nullptr;
			int tamx = 0, tamy = 0;

			const bool solve();
			const bool moved(const posicao, int d_x, int d_y);
			const float percof(const int);
		public:
			~mapthing();
			const bool generate(bool*, const int = 0, const int = 8 /* y */);
			const bool generate_custom(const int, const int, float = 0.5, bool* = nullptr, const bool = true);
			void cleanUp();
			const int readpos(const int, const int);
			const int getSiz(const map_sizes);
		};

		class infinity_map {
			std::vector<chunk> chunks;
			std::vector<posicao> asked_notfound;
			int area_guaranteed = 0;
			bool keepin_on = true;
			std::mutex changes_happenin[2]; // chunks, asked
			std::thread* thr = nullptr;

			chunk gimmerandchunk();
			const bool doesItHave(const int, const int);
		public:
			~infinity_map();
			void init();

			int readpos(const int, const int);
			void setAreaPreLoadAsRequested(const int = 0);
			void _solve_unloaded_chunks();
		};

		void _thr_loadmap_infinity(infinity_map*, bool*);
	}
}