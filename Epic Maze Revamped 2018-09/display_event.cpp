#include "display_event.h"

namespace LSW {

	namespace EpicMazeR {

		displayer_data displayer::data;
		event_mng_data event_mng::data;



		const bool displayer::think()
		{
			fixLoad();
			event_mng evmng_e;
			int level = 0;
			bool enabled_alternative_mode = false;
			bool infinite_map = false;
			while (data.now != LSW_S_EXIT)
			{
				data.lastC = GetTickCount64();
				double multiply = 1.0;

				switch (data.now)
				{
				case LSW_S_INITIALIZING:
				{
					/* Imagens||fontes a serem usadas: */
					ALLEGRO_BITMAP *log;
					ALLEGRO_FONT *font;

					log = data.data_control.get(LSW_BMP_LOGO);
					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					multiplier(); // reset last call
					clock_t now = clock() - CLOCKS_PER_SEC / 4;
					//clock_t lastload = clock() - CLOCKS_PER_SEC / 10;
					double nowFps = 0.0;
					float posoffset = 1.0f;
					bool addin = true;
					bool loaded_all = false;
					int ref_loading_files = 0;

					std::thread thr_local(_thr_temp_loadallresources, &ref_loading_files, &loaded_all);

					while (!loaded_all)
					{
						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
						}
						if (addin) posoffset += multiply * 0.03 * posoffset + ((posoffset > 0) ? 0.01 : -0.01);
						else posoffset -= multiply * 0.03 * posoffset - ((posoffset < 0) ? 0.01 : -0.01);
						if (fabsf(posoffset) > 40.0) {
							if (posoffset < 0.0) posoffset = -40.0;
							else posoffset = 40.0;
							addin = !addin;
						}
						if (!addin && fabsf(posoffset) < 0.12) {
							posoffset = -posoffset;
							addin = !addin;
						}

						clearTo(al_map_rgb(0, 0, 0));
						drawIt(log, 0.0, -0.4, 0);

						float a, b;
						a = data.usedx*(830 + 1.2*posoffset) / base_res[0];
						b = data.usedy*650.0 / base_res[1];
						al_draw_textf(font, al_map_rgb(255, 255, 255), a, b, 0, "Loading... (%02.1f%c)", (99.9f*ref_loading_files / LSW_BMP_MAX), '%');
						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f - %02.3f%c", (float)nowFps, (99.9f*ref_loading_files / LSW_BMP_MAX), '%');

						flip();

						//al_rest(0.016);
						multiply = multiplier();

						/*if (clock() - lastload > CLOCKS_PER_SEC / 10) {
						lastload += CLOCKS_PER_SEC / 10;
						if (++ref_loading_files < LSW_BMP_MAX)
						{
						data.data_control.load((images_available)ref_loading_files);
						}
						else {
						loaded_all = true;
						ref_loading_files = LSW_BMP_MAX;
						}
						}*/
					}

					thr_local.join();

					//data.data_control.loadAll();
					//multiplier();

					for (double to_add = 0.0; to_add < 90.0; to_add += multiplier()) {
						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
						}

						clearTo(al_map_rgb(0, 0, 0));
						drawIt(log, 0.0, -0.4, 0);

						float a, b;
						a = data.usedx*(830 + 1.2*posoffset) / base_res[0];
						b = data.usedy*(650.0 + to_add * 0.4) / base_res[1];
						al_draw_textf(font, al_map_rgb(255 * (1.0 - to_add / 90.0), 255 * (1.0 - to_add / 90.0), 255 * (1.0 - to_add / 90.0)), a, b, 0, "Loading... (100%c)",'%');
						if (to_add > 45.0)al_draw_textf(font, al_map_rgb(255 * ((to_add - 45.0) / 45.0), 255 * ((to_add - 45.0) / 45.0), 255 * ((to_add - 45.0) / 45.0)), a, b, 0, "   DONE   ");
						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f - %02.3f%c", (float)nowFps, 100.0, '%');

						flip();
					}

					data.now = LSW_S_MENU;
				}
				break;
				case LSW_S_MENU:
				{
					ALLEGRO_BITMAP *log, *vig, *opt_01, *opt_02, *opt_03, *opt_04;
					ALLEGRO_FONT *font;
					clock_t now = clock() - CLOCKS_PER_SEC / 4;
					double nowFps = 0.0, nowMult = multiply;
					int opt = 0;
					bool choosing = true;

					log = data.data_control.get(LSW_BMP_LOGO);
					vig = data.data_control.get(LSW_BMP_VIGNETTE);
					opt_01 = data.data_control.get(LSW_BMP_MENU_OPT_01);
					opt_02 = data.data_control.get(LSW_BMP_MENU_OPT_02);
					opt_03 = data.data_control.get(LSW_BMP_MENU_OPT_03);
					opt_04 = data.data_control.get(LSW_BMP_MENU_OPT_04);
					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					multiplier(); // reset for animation
					multiply = 0.0;

					// pre-animation full of features because I CAN :3
					for (double pos = -1.55; pos < -0.02; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						int key = evmng_e.getLastKeyIfAvailable();

						switch (key)
						{
						case ALLEGRO_KEY_UP:
							if (--opt < 0) opt = 3;
							break;
						case ALLEGRO_KEY_DOWN:
							if (++opt > 3) opt = 0;
							break;
						}

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, -(pos + 0.02), -0.5, 0);

						switch (opt)
						{
						case 0:
							drawIt(opt_01, pos + 0.02, 0.0, 0);
							break;
						case 1:
							drawIt(opt_02, pos + 0.02, 0.0, 0);
							break;
						case 2:
							drawIt(opt_03, pos + 0.02, 0.0, 0);
							break;
						case 3:
							drawIt(opt_04, pos + 0.02, 0.0, 0);
							break;
						default:
							opt = 0;
							break;
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					while (choosing)
					{
						int key = evmng_e.getLastKeyIfAvailable();

						switch (key)
						{
						case ALLEGRO_KEY_UP:
							if (--opt < 0) opt = 3;
							break;
						case ALLEGRO_KEY_DOWN:
							if (++opt > 3) opt = 0;
							break;
						case ALLEGRO_KEY_ESCAPE:
							opt = 3;
							choosing = false;
							break;
						case ALLEGRO_KEY_ENTER:
							choosing = false;
							break;
						case ALLEGRO_KEY_1:
							opt = 0;
							choosing = false;
							break;
						case ALLEGRO_KEY_2:
							opt = 1;
							choosing = false;
							break;
						case ALLEGRO_KEY_3:
							opt = 2;
							choosing = false;
							break;
						case ALLEGRO_KEY_4:
							opt = 3;
							choosing = false;
							break;
						}

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}
						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, 0.0, -0.5, 0);

						switch (opt)
						{
						case 0:
							drawIt(opt_01, 0.0, 0.0, 0);
							break;
						case 1:
							drawIt(opt_02, 0.0, 0.0, 0);
							break;
						case 2:
							drawIt(opt_03, 0.0, 0.0, 0);
							break;
						case 3:
							drawIt(opt_04, 0.0, 0.0, 0);
							break;
						default:
							opt = 0;
							break;
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", (float)nowFps, (float)nowMult);
						drawIt(vig, 0.0, 0.0, 0);
						flip();
						multiply = multiplier();
					}

					for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, -(pos - 0.02), -0.5, 0);

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						switch (opt)
						{
						case 0:
							drawIt(opt_01, pos - 0.02, 0.0, 0);
							break;
						case 1:
							drawIt(opt_02, pos - 0.02, 0.0, 0);
							break;
						case 2:
							drawIt(opt_03, pos - 0.02, 0.0, 0);
							break;
						case 3:
							drawIt(opt_04, pos - 0.02, 0.0, 0);
							break;
						default:
							opt = 0;
							break;
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					switch (opt) {
					case 0:
						data.now = LSW_S_PLAY;
						break;
					case 1:
						data.now = LSW_S_INSTR;
						break;
					case 2:
						data.now = LSW_S_RECORDS;
						break;
					case 3:
						data.now = LSW_S_EXIT;
						break;
					}
				}
				break;
				case LSW_S_INSTR:
				{
					ALLEGRO_BITMAP *log, *vig, *instr;
					ALLEGRO_FONT *font;
					clock_t now = clock() - CLOCKS_PER_SEC / 4;
					double nowFps = 0.0, nowMult = multiply;
					bool choosing = true;
					bool moree = false;

					log = data.data_control.get(LSW_BMP_LOGO);
					vig = data.data_control.get(LSW_BMP_VIGNETTE);
					instr = data.data_control.get(LSW_BMP_INSTR);
					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					multiplier(); // reset for animation
					multiply = 0.0;

					// pre-animation full of features because I CAN :3
					for (double pos = -1.55; pos < -0.02; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos + 0.02)*0.8, -0.5, 0);

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						drawIt(instr, pos + 0.02, 0.0, 0);

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					while (choosing)
					{
						int key = evmng_e.getLastKeyIfAvailable();

						switch (key)
						{
						case ALLEGRO_KEY_C:
							moree = true;
						default:
							if (key >= 0) choosing = false;
						}

						if (key >= 0) choosing = false;

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, 0.0, -0.5, 0);

						drawIt(instr, 0.0, 0.0, 0);

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", (float)nowFps, (float)nowMult);
						drawIt(vig, 0.0, 0.0, 0);
						flip();
						multiply = multiplier();
					}

					for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos - 0.02)*0.8, -0.5, 0);

						drawIt(instr, pos - 0.02, 0.0, 0);

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					if (moree)
					{
						choosing = true;
						int option_on_screen = 0;
						bool selected = false;
						double y_off_motion = 0.0;

						int vars[2] = { data.usedx, data.usedy };
						int multipl = 10;
						// enabled_alternative_mode
						// infinite_map
							
						while (choosing)
						{
							int key = evmng_e.getLastKeyIfAvailable();

							if (clock() - now > CLOCKS_PER_SEC / 4) {
								now += CLOCKS_PER_SEC / 4;
								nowFps = lastFPS();
								nowMult = multiply;
							}

							switch (key)
							{
							case ALLEGRO_KEY_UP:
								if (!selected) option_on_screen--;
								else {
									if (option_on_screen < 2 && option_on_screen >= 0) {
										vars[option_on_screen] += multipl;
										if (option_on_screen == 0) { // x
											vars[1] = vars[0] * 9.0 / 16.0;
										}
										else { // y
											vars[0] = vars[1] * 16.0 / 9.0;
										}
									}
									else if (option_on_screen == 2) enabled_alternative_mode = !enabled_alternative_mode;
									else if (option_on_screen == 3) infinite_map = !infinite_map;
									else if (option_on_screen == -1) multipl += 10;
								}
								break;
							case ALLEGRO_KEY_DOWN:
								if (!selected) option_on_screen++;
								else {
									if (option_on_screen < 2 && option_on_screen >= 0) {
										vars[option_on_screen] -= multipl;
										if (option_on_screen == 0) { // x
											vars[1] = vars[0] * 9.0 / 16.0;
										}
										else { // y
											vars[0] = vars[1] * 16.0 / 9.0;
										}
									}
									else if (option_on_screen == 2) enabled_alternative_mode = !enabled_alternative_mode;
									else if (option_on_screen == 3) infinite_map = !infinite_map;
									else if (option_on_screen == -1) multipl -= 10;
								}
								break;
							case ALLEGRO_KEY_ENTER:
								selected = !selected;
								break;
							case ALLEGRO_KEY_ESCAPE:
								choosing = false;
								continue;
							}
							if (multipl < 10) multipl = 10;
							if (option_on_screen < -1) option_on_screen = 5;
							if (option_on_screen > 5) option_on_screen = -1;
							if (vars[0] < 640) vars[0] += 10;
							if (vars[1] < 480) vars[1] += 10;

							y_off_motion -= multiply * 0.2 * (y_off_motion - option_on_screen*0.05);


							clearTo(al_map_rgb(0, 0, 0));
							//bganim(multiply);

							al_draw_textf(font, ((option_on_screen == -1) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.46 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c MULTIPL_VAL: %d %c", ((option_on_screen == -1) ? '>' : '-'), multipl, ((option_on_screen == -1) ? '<' : '-'));

							al_draw_textf(font, al_map_rgb(200, 200, 200),                                                                                            0.5*data.usedx, (0.54 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "- RESOLUTION BASE -");
							al_draw_textf(font, ((option_on_screen == 0) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.58 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c Width: %d %c", ((option_on_screen == 0) ? '>' : '-'), vars[0], ((option_on_screen == 0) ? '<' : '-'));
							al_draw_textf(font, ((option_on_screen == 1) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.62 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c Height: %d %c", ((option_on_screen == 1) ? '>' : '-'), vars[1], ((option_on_screen == 1) ? '<' : '-'));

							al_draw_textf(font, al_map_rgb(200, 200, 200),                                                                                            0.5*data.usedx, (0.70 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "- MISCELLANEOUS -");
							al_draw_textf(font, ((option_on_screen == 2) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.74 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c Alternative game mode? %s %c", ((option_on_screen == 2) ? '>' : '-'), (enabled_alternative_mode ? "YES" : "NO"), ((option_on_screen == 2) ? '<' : '-'));
							al_draw_textf(font, ((option_on_screen == 3) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.78 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c Infinite map? (EXPERIMENTAL) %s %c", ((option_on_screen == 3) ? '>' : '-'), (infinite_map ? "YES" : "NO"), ((option_on_screen == 3) ? '<' : '-'));

							al_draw_textf(font, ((option_on_screen == 4) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.84 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c Apply [Resolution]? %c", ((option_on_screen == 4) ? '>' : '-'), ((option_on_screen == 4) ? '<' : '-'));
							al_draw_textf(font, ((option_on_screen == 5) ? (selected ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 0)) : al_map_rgb(125, 125, 125)), 0.5*data.usedx, (0.90 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "%c Exit? %c", ((option_on_screen == 5) ? '>' : '-'), ((option_on_screen == 5) ? '<' : '-'));

							al_draw_textf(font, al_map_rgb(200, 200, 200),                                                                                            0.5*data.usedx, (0.93 - y_off_motion)*data.usedy, ALLEGRO_ALIGN_CENTER, "Version: %s", VERSION);
							
							drawCircle(0.0, 0.25, 340.0 + sin(al_get_time()*0.3)*30.0);

							drawIt(log, 0.0, -0.5, 0);
							al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", (float)nowFps, (float)nowMult);
							drawIt(vig, 0.0, 0.0, 0);
							flip();

							multiply = multiplier();

							if (option_on_screen == 4 && selected)
							{
								selected = false;
								resizeBufTo(vars[0], vars[1]);
								font = data.data_control.get(LSW_FONT_DEJAVUSANS);
							}
							if (option_on_screen == 5 && selected)
							{
								choosing = false;
							}
						}
					}



					data.now = LSW_S_MENU;
				}
				break;
				case LSW_S_RECORDS:
				{
					ALLEGRO_BITMAP *log, *vig, *rec_back;
					ALLEGRO_FONT *font;
					FILE* fp[3] = { nullptr };
					clock_t now = clock() - CLOCKS_PER_SEC / 4;
					double nowFps = 0.0, nowMult = multiply;
					bool choosing = true;

					int offset = 0; // >= 0; <= records.size() - 10
					int level_choice = 0;

					std::vector<scores> records[3];
					/*
					std::string records[10] = {
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-=",
						"=-=-=-=-=-=-=-=-=-=-=-="
					};*/

					log = data.data_control.get(LSW_BMP_LOGO);
					vig = data.data_control.get(LSW_BMP_VIGNETTE);
					rec_back = data.data_control.get(LSW_BMP_REC_BACK);
					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					for (int k = 0; k < 3; k++)
					{
						char records_name[32];
						sprintf_s(records_name, "records_%d.txt", k);

						if (fopen_s(&fp[k], records_name, "r") == 0)
						{
							while (!feof(fp[k]))
							{
								char line[128];
								double db = 0.0;
								scores sc;
								fscanf_s(fp[k], "%s %lf\n", line, 128, &db);
								sc.name = line;
								sc.score = db;
								for (auto& i : sc.name)
								{
									if (i == '_') i = ' ';
								}
								records[k].push_back(sc);


								/*std::string rn;
								fgets(line, 128, fp);
								rn = line;
								if (rn.find('\n') != std::string::npos) rn.pop_back();
								records.push_back(rn);*/
							}

							fclose(fp[k]);

							clock_t now = clock();

							for (size_t u = 0; u < records[k].size(); u++)
							{
								for (size_t v = u + 1; v < records[k].size(); v++)
								{
									scores& a = records[k][u];
									scores& b = records[k][v];

									if (a.score > b.score)
									{
										scores sc = a;
										a = b;
										b = sc;
									}
								}
								if (clock() - now > CLOCKS_PER_SEC) {
									bganim(multiply);
									drawIt(vig, 0.0, 0.0, 0);
									flip();
									multiplier();
								}
							}
						}
					}

					multiplier(); // reset for animation
					multiply = 0.0;

					// pre-animation full of features because I CAN :3
					for (double pos = -1.55; pos < -0.02; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos + 0.02)*0.8, -0.5, 0);

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						drawIt(rec_back, pos + 0.02, 0.1, 0);
						
						al_draw_textf(font, al_map_rgb(255, 255, 255), ((pos + 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- EASY -->");

						for (int u = 0; u < 10; u++)
						{
							std::string to_print_rn = "=-=-=-=-=-=-=-=-=-=-=-=";
							if (u < records[level_choice].size()) to_print_rn = records[level_choice][u].name + " = " + std::to_string(records[level_choice][u].score);

							al_draw_textf(font, al_map_rgb(255, 255, 255), ((pos + 0.02) + 1.0)*0.5*data.usedx, (0.46 + u * 0.038)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", to_print_rn.c_str());
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					while (choosing)
					{
						int key = evmng_e.getLastKeyIfAvailable();

						switch (key)
						{
						case ALLEGRO_KEY_DOWN:
							offset++;
							break;
						case ALLEGRO_KEY_UP:
							offset--;
							break;
						case ALLEGRO_KEY_RIGHT:
							level_choice++;
							break;
						case ALLEGRO_KEY_LEFT:
							level_choice--;
							break;
						case ALLEGRO_KEY_ESCAPE: case ALLEGRO_KEY_ENTER:
							choosing = false;
							continue;
						}

						if (offset < 0) offset = 0;
						if (offset > records[level_choice].size() - 10) offset = records[level_choice].size() - 10;
						if (level_choice < 0) level_choice = 2;
						if (level_choice > 2) level_choice = 0;

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, 0.0, -0.5, 0);

						drawIt(rec_back, 0.0, 0.1, 0);

						switch (level_choice) {
						case 0:
							al_draw_textf(font, al_map_rgb(255, 255, 255), 0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- EASY -->");
							break;
						case 1:
							al_draw_textf(font, al_map_rgb(255, 255, 255), 0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- NORMAL -->");
							break;
						case 2:
							al_draw_textf(font, al_map_rgb(255, 255, 255), 0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- UNBELIEVABLE -->");
							break;
						}

						for (int u = offset; u < 10 + offset; u++)
						{
							std::string to_print_rn = "=-=-=-=-=-=-=-=-=-=-=-=";
							if (u < records[level_choice].size()) to_print_rn = records[level_choice][u].name + " = " + std::to_string(records[level_choice][u].score);

							al_draw_textf(font, al_map_rgb(255, 255, 255), 0.5*data.usedx, (0.46 + (u - offset) * 0.038)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", to_print_rn.c_str());
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", (float)nowFps, (float)nowMult);
						drawIt(vig, 0.0, 0.0, 0);
						flip();
						multiply = multiplier();
					}

					for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos - 0.02)*0.8, -0.5, 0);

						drawIt(rec_back, pos - 0.02, 0.1, 0);

						switch (level_choice) {
						case 0:
							al_draw_textf(font, al_map_rgb(255, 255, 255), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- EASY -->");
							break;
						case 1:
							al_draw_textf(font, al_map_rgb(255, 255, 255), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- NORMAL -->");
							break;
						case 2:
							al_draw_textf(font, al_map_rgb(255, 255, 255), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- UNBELIEVABLE -->");
							break;
						}

						for (int u = offset; u < 10 + offset; u++)
						{
							std::string to_print_rn = "=-=-=-=-=-=-=-=-=-=-=-=";
							if (u < records[level_choice].size()) to_print_rn = records[level_choice][u].name + " = " + std::to_string(records[level_choice][u].score);

							al_draw_textf(font, al_map_rgb(255, 255, 255), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.46 + (u - offset) * 0.038)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", to_print_rn.c_str());
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}
					data.now = LSW_S_MENU;
				}
				break;
				case LSW_S_PLAY:

				{
					if (infinite_map) {
						level = 0;
						data.now = LSW_S_GAMING;
						continue;
					}

					ALLEGRO_BITMAP *log, *vig, *opt_01, *opt_02, *opt_03;
					ALLEGRO_FONT *font;
					clock_t now = clock() - CLOCKS_PER_SEC / 4;
					double nowFps = 0.0, nowMult = multiply;
					int opt = 0;
					bool choosing = true;
					level = 0;

					log = data.data_control.get(LSW_BMP_LOGO);
					vig = data.data_control.get(LSW_BMP_VIGNETTE);
					opt_01 = data.data_control.get(LSW_BMP_MENU_OPT_01_S);
					opt_02 = data.data_control.get(LSW_BMP_MENU_OPT_02_S);
					opt_03 = data.data_control.get(LSW_BMP_MENU_OPT_03_S);
					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					multiplier(); // reset for animation
					multiply = 0.0;

					// pre-animation full of features because I CAN :3
					for (double pos = -1.55; pos < -0.02; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						int key = evmng_e.getLastKeyIfAvailable();

						switch (key)
						{
						case ALLEGRO_KEY_UP:
							if (--opt < 0) opt = 2;
							break;
						case ALLEGRO_KEY_DOWN:
							if (++opt > 2) opt = 0;
							break;
						}

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, -(pos + 0.02), -0.5, 0);

						switch (opt)
						{
						case 0:
							drawIt(opt_01, pos + 0.02, 0.0, 0);
							break;
						case 1:
							drawIt(opt_02, pos + 0.02, 0.0, 0);
							break;
						case 2:
							drawIt(opt_03, pos + 0.02, 0.0, 0);
							break;
						default:
							opt = 0;
							break;
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					while (choosing)
					{
						int key = evmng_e.getLastKeyIfAvailable();

						switch (key)
						{
						case ALLEGRO_KEY_UP:
							if (--opt < 0) opt = 2;
							break;
						case ALLEGRO_KEY_DOWN:
							if (++opt > 2) opt = 0;
							break;
						case ALLEGRO_KEY_ENTER:
							choosing = false;
							break;
						case ALLEGRO_KEY_1:
							opt = 0;
							choosing = false;
							break;
						case ALLEGRO_KEY_2:
							opt = 1;
							choosing = false;
							break;
						case ALLEGRO_KEY_3:
							opt = 2;
							choosing = false;
							break;
						case ALLEGRO_KEY_ESCAPE:
							data.now = LSW_S_MENU;
							choosing = false;
							break;
						}

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}
						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, 0.0, -0.5, 0);

						switch (opt)
						{
						case 0:
							drawIt(opt_01, 0.0, 0.0, 0);
							break;
						case 1:
							drawIt(opt_02, 0.0, 0.0, 0);
							break;
						case 2:
							drawIt(opt_03, 0.0, 0.0, 0);
							break;
						default:
							opt = 0;
							break;
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", (float)nowFps, (float)nowMult);
						drawIt(vig, 0.0, 0.0, 0);
						flip();
						multiply = multiplier();
					}

					for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						clearTo(al_map_rgb(0, 0, 0));
						bganim(multiply);
						drawIt(log, -(pos - 0.02), -0.5, 0);

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						switch (opt)
						{
						case 0:
							drawIt(opt_01, pos - 0.02, 0.0, 0);
							break;
						case 1:
							drawIt(opt_02, pos - 0.02, 0.0, 0);
							break;
						case 2:
							drawIt(opt_03, pos - 0.02, 0.0, 0);
							break;
						default:
							opt = 0;
							break;
						}

						al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					if (data.now != LSW_S_MENU) {
						switch (opt) {
						case 0:
							level = 0;
							data.now = LSW_S_GAMING;
							break;
						case 1:
							level = 1;
							data.now = LSW_S_GAMING;
							break;
						case 2:
							level = 2;
							data.now = LSW_S_GAMING;
							break;
						}
					}
				}
				break;
				case LSW_S_EXIT:
					deinitAll();
					return true;
				case LSW_S_GAMING:
				{
					mapthing map;
					infinity_map map2;
					bool being_made = true;
					int needed_reset = 0;
					int debug = 0;
					
					ALLEGRO_BITMAP *log, *vig, *plr[3], *blk, *enb, *sav, *mbl;
					ALLEGRO_FONT *font;
					clock_t now = clock() - CLOCKS_PER_SEC / 4;
					double nowFps = 0.0, nowMult = multiply;
					bool playin = true;
					bool paused = false;
					bool save_score = true;
					bool asked_for_help = false;

					std::thread thr(_thr_temp_generatemap,&map, level, &needed_reset, &being_made, &playin);

					//double direct[2] = { 0.0 }; // +right/-left, +down/-up
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

					if (data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST) == ALLEGRO_KEY_F3) debug = -1;

					double campos[2] = { 0.0, 0.0 };

					log = data.data_control.get(LSW_BMP_LOGO);
					vig = data.data_control.get(LSW_BMP_VIGNETTE);
					blk = data.data_control.get(LSW_BMP_BLOCK);
					enb = data.data_control.get(LSW_BMP_BLOCK_END);
					mbl = data.data_control.get(LSW_BMP_MENU_BLOCK);
					sav = data.data_control.get(LSW_BMP_SAVING_SCORE);
					for (int p = 0; p < 3; p++) plr[p] = data.data_control.get((images_available)(p + LSW_BMP_PERSON));

					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					//y_offset = (56.0 / al_get_bitmap_width(blk)) / base_res[1];
					playersiz_rel[0] = (al_get_bitmap_width(plr[0]) * 1.0 / base_res[0]) * 0.9;
					playersiz_rel[1] = (al_get_bitmap_height(plr[0]) * 1.0 / base_res[1]) * 0.9;
					blocksize_rel[0] = al_get_bitmap_width(blk) * 1.0 / base_res[0];
					blocksize_rel[1] = al_get_bitmap_height(blk) * 1.0 / base_res[1];
					multiplier(); // reset for animation
					multiply = 0.0;

					if (infinite_map) map2.init();

					time_final[0] = al_get_time();

					while (playin)
					{
						/* * * * * * * VARIABLES * * * * * * */
						colided = false;
						double min_dist[9][2];
						bool min_dist_used[9] = { false };
						double fixed_distance = sqrt(blocksize_rel[0] * blocksize_rel[0] + blocksize_rel[1] * blocksize_rel[1])*1.44;
						for (int t = 0; t < 9; t++) { min_dist[t][0] = fixed_distance; min_dist[t][1] = fixed_distance; }

						/* * * * * * * PRE CASES * * * * * * */
						{
							multiply = multiplier();

							if (needed_reset > 0)
							{
								needed_reset = 0;
								posrel[0] = posrel[1] = -0.9;
							}
							if (clock() - now > CLOCKS_PER_SEC / 4) {
								now += CLOCKS_PER_SEC / 4;
								nowFps = lastFPS();
								nowMult = multiply;
							}
							if (paused)
							{
								double before_pause = al_get_time();
								int got = pauseScreenGame();
								time_final[0] += al_get_time() - before_pause;

								multiplier();
								if (got == 1) {
									playin = false;
									save_score = false;
									paused = false;
									data.now = LSW_S_MENU;
								}
								else if (got == 2)
								{
									playin = false;
									save_score = true;
									paused = false;
									distance_taken = -1.0;
								}
								else {
									paused = false;
								}
								continue;
							}
						}

						/* * * * * * * KEYBOARD * * * * * * */
						{
							int key = data.evm.getLastKeyIfAvailable(LSW_KEYPRESSED);
							int keykeep = data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST);
							int keylost = data.evm.getLastKeyIfAvailable(LSW_KEYLEFT);

							if (debug == -1) {
								if (data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST) != ALLEGRO_KEY_F3) debug = 0;
								else debug = 1;
							}

							switch (key)
							{
							case ALLEGRO_KEY_ESCAPE:
								paused = true;
								continue;
							case ALLEGRO_KEY_F1:
								asked_for_help = true;
								continue;
							}

							switch (keykeep)
							{
							case ALLEGRO_KEY_UP: case ALLEGRO_KEY_W:
								way = 0;
								break;
							case ALLEGRO_KEY_LEFT: case ALLEGRO_KEY_A:
								way = 2;
								break;
							case ALLEGRO_KEY_DOWN: case ALLEGRO_KEY_S:
								way = 1;
								break;
							case ALLEGRO_KEY_RIGHT: case ALLEGRO_KEY_D:
								way = 3;
								break;
							case -1:
								way = -1;
							}

							if (enabled_alternative_mode)
							{
								switch (keykeep)
								{
								case ALLEGRO_KEY_UP: case ALLEGRO_KEY_W:
									alternative_way[0] = true;
									break;
								case ALLEGRO_KEY_LEFT: case ALLEGRO_KEY_A:
									alternative_way[2] = true;
									break;
								case ALLEGRO_KEY_DOWN: case ALLEGRO_KEY_S:
									alternative_way[1] = true;
									break;
								case ALLEGRO_KEY_RIGHT: case ALLEGRO_KEY_D:
									alternative_way[3] = true;
									break;
								}
								switch (keylost)
								{
								case ALLEGRO_KEY_UP: case ALLEGRO_KEY_W:
									alternative_way[0] = false;
									break;
								case ALLEGRO_KEY_LEFT: case ALLEGRO_KEY_A:
									alternative_way[2] = false;
									break;
								case ALLEGRO_KEY_DOWN: case ALLEGRO_KEY_S:
									alternative_way[1] = false;
									break;
								case ALLEGRO_KEY_RIGHT: case ALLEGRO_KEY_D:
									alternative_way[3] = false;
									break;
								}
							}
						}

						/* * * * * * * MOVEMENT * * * * * * */ // TRANSFORM INTO A THREAD!
						double cammult[2] = { (posrel[0] - campos[0]) , (posrel[1] - campos[1]) };
						if (!asked_for_help) { // set limits if not helping
							if (cammult[0] > 0.5)
							{
								campos[0] += (cammult[0] - 0.5) * 0.07 * multiply;
							}
							if (cammult[0] < -0.5)
							{
								campos[0] += (cammult[0] + 0.5) * 0.07 * multiply;
							}
							if (cammult[1] > 0.5)
							{
								campos[1] += (cammult[1] - 0.5) * 0.07 * multiply;
							}
							if (cammult[1] < -0.5)
							{
								campos[1] += (cammult[1] + 0.5) * 0.07 * multiply;
							}
						}

						if (enabled_alternative_mode) speed_y += fabs(0.0001 + 0.05*speed_y)*multiply;


						/* * * * * * * COLLISION & POS UPDATE * * * * * * */
						{
							for (int py = (campos[1] * 4.21875) - 1; py < 9 + (campos[1] * 4.21875); py++)
							{
								for (int px = (campos[0] * 7.5) - 1; px < 15 + (campos[0] * 7.5); px++)
								{
									double xx, yy;
									xx = (px * (blocksize_rel[0]) - 0.5) * 2.0 - campos[0];
									yy = (py * (blocksize_rel[1]) - 0.5) * 2.0 - campos[1];

									int mapread = 0;
									if (!infinite_map) mapread = map.readpos(px, py);
									else mapread = map2.readpos(px, py);

									if (mapread <= 0 && !asked_for_help) {
										for (int t = 0; t < 9; t++) {
											if (fabs((posrel[0] - campos[0]) - (xx + blocksize_rel[0])) <= min_dist[t][0] &&
												(fabs((posrel[1] - campos[1]) - (yy + blocksize_rel[1])) <= min_dist[t][1]))
											{
												min_dist_used[t] = true;
												min_dist[t][0] = (posrel[0] - campos[0]) - (xx + blocksize_rel[0]);
												min_dist[t][1] = (posrel[1] - campos[1]) - (yy + blocksize_rel[1]);
												if (debug > 0) al_draw_filled_circle(((posrel[0] - campos[0] - min_dist[t][0])*0.5 + 0.5) * data.usedx, ((posrel[1] - campos[1] - min_dist[t][1])*0.5 + 0.5) * data.usedy, 50.0, al_map_rgb(255, 0, 255));
												t = 9;

											}
										}
									}
								}
							}
							for (int t = 0; t < 9 && !asked_for_help; t++) {
								if (min_dist_used[t]) {

									if (enabled_alternative_mode) {
										if (fabs(min_dist[t][0]) < blocksize_rel[0] + playersiz_rel[0] * 0.9 &&
											fabs(min_dist[t][1]) < blocksize_rel[1] + playersiz_rel[1] * 0.9)
										{
											speed_y = 0.0;
										}
									}
									if (fabs(min_dist[t][0]) < blocksize_rel[0] + playersiz_rel[0] * 0.6 &&
										fabs(min_dist[t][1]) < blocksize_rel[1] + playersiz_rel[1] * 0.6) // collision
									{
										colided = true;
										if (debug > 0) al_draw_filled_circle(((posrel[0] - campos[0] - min_dist[t][0])*0.5 + 0.5) * data.usedx, ((posrel[1] - campos[1] - min_dist[t][1])*0.5 + 0.5) * data.usedy, 27.0, al_map_rgb(255, 0, 0));

										double dx = min_dist[t][0]; // player pos - block pos
										double dy = min_dist[t][1]; // player pos - block pos
										double to_rot = 0.0;

										dx /= 1.0 * (blocksize_rel[0] + playersiz_rel[0] * 0.6); // 0 to 1
										dy /= 1.0 * (blocksize_rel[1] + playersiz_rel[1] * 0.6); // 0 to 1

										double draw_ref[2];
										draw_ref[0] = ((posrel[0] - campos[0] - min_dist[t][0])*0.5 + 0.5) * data.usedx;
										draw_ref[1] = ((posrel[1] - campos[1] - min_dist[t][1])*0.5 + 0.5) * data.usedy;

										assistance_nsew where_to_tp_plr = _whereToTp(dx, dy);

										switch (where_to_tp_plr)
										{
										case LSW_P_NORTH:
											to_rot = 180.0;
											if (debug > 0)
											{
												al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0], draw_ref[1] - 0.1 * data.usedy, al_map_rgb(175, 175, 175), 4.0);
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0], draw_ref[1] - 0.13 * data.usedy, ALLEGRO_ALIGN_CENTER, "NORTH");
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0], draw_ref[1] - 0.1 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
											}
											break;
										case LSW_P_SOUTH:
											to_rot = 0.0;
											if (debug > 0)
											{
												al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0], draw_ref[1] + 0.1 * data.usedy, al_map_rgb(175, 175, 175), 4.0);
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0], draw_ref[1] + 0.13 * data.usedy, ALLEGRO_ALIGN_CENTER, "SOUTH");
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0], draw_ref[1] + 0.1 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
											}
											break;
										case LSW_P_WEST:
											to_rot = 90.0;
											if (debug > 0)
											{
												al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0] - 0.1 * data.usedx, draw_ref[1], al_map_rgb(175, 175, 175), 4.0);
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0] - 0.1 * data.usedx, draw_ref[1], ALLEGRO_ALIGN_CENTER, "WEST");
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0] - 0.1 * data.usedx, draw_ref[1] + 0.03 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
											}
											break;
										case LSW_P_EAST:
											to_rot = 270.0;
											if (debug > 0)
											{
												al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0] + 0.1 * data.usedx, draw_ref[1], al_map_rgb(175, 175, 175), 4.0);
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0] + 0.1 * data.usedx, draw_ref[1], ALLEGRO_ALIGN_CENTER, "EAST");
												al_draw_textf(font, al_map_rgb(255, 255, 0), draw_ref[0] + 0.1 * data.usedx, draw_ref[1] + 0.03 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
											}
											break;
										}

										if (speed < 0.004) speed = 0.004;

										if (fabs(min_dist[t][0]) < blocksize_rel[0] + playersiz_rel[0] * 0.4 &&
											fabs(min_dist[t][1]) < blocksize_rel[1] + playersiz_rel[1] * 0.4)
										{
											plrrot = to_rot;
										}
										speed = -fabs(speed * 0.3);
									}
								}
							}
							speed -= (speed * 0.03) * multiply;
							if (speed > 0.07) speed = 0.07;
							if (speed < -0.02) speed = -0.02;

							if (speed_y > 0.03) speed_y = 0.03;

							while (plrrot > 360.0)
								plrrot -= 360.0;
							while (plrrot < 0.0)
								plrrot += 360.0;

							if (!asked_for_help) { // if playing, so correction of ang w movement

								if (enabled_alternative_mode) {

									if (alternative_way[0]) { // north
										double coss = cos(ALLEGRO_PI * plrrot / 180.0);
										speed += fabs(0.00012 + 0.04*speed)*multiply;
										if (coss > 0.0) speed_y *= 0.95 * coss;
										way = 5;
									}
									if (alternative_way[1]) { // south
										speed -= (speed * 0.03) * multiply;
										way = 5;
									}
									if (alternative_way[2]) { // east
										plrrot -= multiply * 0.01 / (fabs(speed) + 0.001);
										way = 5;
									}
									if (alternative_way[3]) { // west
										plrrot += multiply * 0.01 / (fabs(speed) + 0.001);
										way = 5;
									}

									if (speed_y > 0.0 && way != 5)
									{
										double usedhere;

										if (speed < 0.0) usedhere = speed_y;
										else usedhere = speed_y - speed;

										if (plrrot < 180.0) plrrot += usedhere * ((180.0 - plrrot) / 2.0)*2.0*multiply;
										else plrrot -= usedhere * 2.0*((plrrot - 180.0) / 6.0)*multiply;
									}
								}
								else {
									if (way >= 0)
										speed += fabs(0.00012 + 0.08*speed)*multiply;

									switch (way)
									{
									case 0: // north
										if (plrrot < 180.0) plrrot -= ((plrrot) / 2.0)*0.3*multiply;
										else plrrot += ((360.0 - plrrot) / 6.0)*multiply;
										break;
									case 1: // south
										if (plrrot < 180.0) plrrot += ((180.0 - plrrot) / 2.0)*0.3*multiply;
										else plrrot -= ((plrrot - 180.0) / 6.0)*multiply;
										break;
									case 2: // east
										if (plrrot < 90.0) plrrot -= ((270.0 - plrrot) / 6.0)*0.3*multiply;
										else plrrot += ((270.0 - plrrot) / 6.0)*multiply;
										break;
									case 3: // west
										if (plrrot > 270.0) plrrot -= ((90.0 - plrrot) / 6.0)*0.3*multiply;
										else plrrot += ((90.0 - plrrot) / 6.0)*multiply;
										break;
									}
								}

								double pi_r = ALLEGRO_PI * plrrot / 180.0; // 0 means down
								posrel[0] += multiply * speed * (sin(pi_r));
								posrel[1] += multiply * speed * (-cos(pi_r));
								if (enabled_alternative_mode && !asked_for_help) posrel[1] += speed_y * multiply;

								if (posrel[0] - campos[0] > 1.0) posrel[0] = 1.0 + campos[0];
								if (posrel[0] - campos[0] < -1.0) posrel[0] = -1.0 + campos[0];
								if (posrel[1] - campos[1] > 1.0) posrel[1] = 1.0 + campos[1];
								if (posrel[1] - campos[1] < -1.0) posrel[1] = -1.0 + campos[1];

								distance_taken += (fabs(speed) + fabs(speed_y)*cos(pi_r + ALLEGRO_PI)) * 0.05 / multiply;
							}
							else {
								if (way >= 0) {
									way_cam = way;
									speed += fabs(0.00015 + 0.08*speed)*multiply;
								}
								switch (way_cam)
								{
								case 0:
									campos[1] -= multiply * speed * 0.5;
									break;
								case 1:
									campos[1] += multiply * speed * 0.5;
									break;
								case 2:
									campos[0] -= multiply * speed * 0.5;
									break;
								case 3:
									campos[0] += multiply * speed * 0.5;
									break;
								}
							}
							int plrx = 1 + (15.0 * (1.0 * posrel[0] - blocksize_rel[0] * 2.0 + 1.0) / 2.0);
							//int plry = 1 + (8.4375 * (1.0 *  posrel[1] - blocksize_rel[1] * 2.0 + 1.0) / 2.0);

							if (!infinite_map && plrx == map.getSiz(LSW_SIZ_X) - 1)
							{
								playin = false;
								save_score = true;
							}
						}
						
						/* * * * * * * DRAWNING * * * * * * */
						{
							clearTo(al_map_rgb_f(0.5*sin(al_get_time()*0.33) + 0.5, 0.5*cos(al_get_time()*0.54) + 0.5, -0.5*sin(al_get_time()*0.215) + 0.5));

							for (int py = (campos[1] * 4.21875) - 1; py < 9 + (campos[1] * 4.21875); py++)
							{
								for (int px = (campos[0] * 7.5) - 1; px < 15 + (campos[0] * 7.5); px++)
								{
									double xx, yy;
									xx = (px * (blocksize_rel[0]) - 0.5) * 2.0 - campos[0];
									yy = (py * (blocksize_rel[1]) - 0.5) * 2.0 - campos[1];

									int mapread = 0;
									if (!infinite_map) mapread = map.readpos(px, py);
									else mapread = map2.readpos(px, py);

									if (mapread <= 0) {

										if (level >= 2 && !asked_for_help)
										{
											if (fabs((posrel[0] - campos[0]) - (xx + blocksize_rel[0])) <= fixed_distance * 3.5 && (fabs((posrel[1] - campos[1]) - (yy + blocksize_rel[1])) <= fixed_distance * 3.5))
												drawIt(blk, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
										}
										else drawIt(blk, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
									}
									else if (!infinite_map && px == map.getSiz(LSW_SIZ_X) - 1)	drawIt(enb, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
									else if (asked_for_help && mapread == LSW_VISITADO)			drawIt(mbl, xx, yy, 0.0, 2.0, 2.0, -1.0, 0.0, 0.0);

									if (debug > 0) al_draw_textf(font, al_map_rgb(0, 0, 0), (xx*0.5 + 0.5)*data.usedx, (yy*0.5 + 0.5)*data.usedy, ALLEGRO_ALIGN_CENTER, "%d;%d", px, py);
								}
							}

							drawIt(plr[((way >= 0) ? (1 + (int)(2.0*al_get_time()) % 2) : 0)], posrel[0] - campos[0], posrel[1] - campos[1], plrrot, 1.0, 1.0, ((debug > 0) ? 2.0 : -1.0), -1, -1, (colided ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 255, 0)));

							if (level >= 2 && !asked_for_help) drawCircle(posrel[0] - campos[0], posrel[1] - campos[1], (1.5 + sin(al_get_time())*0.5 - speed * 7.0)*100.0);

							al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f TMULT: %.3f P: %.3fx%.3f / %.3fx%.3f (R); S: %.2fE-3, Sy: %.4fE-3; R: %.2f | CP [%.2f;%.2f] | K: %d | T: %04.1f", (float)nowFps, (float)nowMult, posrel[0], posrel[1], cammult[0], cammult[1], speed*1000.0, speed_y*1000.0, plrrot, campos[0], campos[1], data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST), distance_taken);

							drawIt(vig, 0.0, 0.0, 0);
							flip();
						}
					}

					time_final[1] = al_get_time();
					final_score = distance_taken;

					while (!being_made)
					{
						multiply = multiplier();
						bganim(multiply);

						drawIt(plr[((way >= 0) ? (1 + (int)(2.0*al_get_time()) % 2) : 0)], posrel[0] - campos[0], posrel[1] - campos[1], plrrot, 1.0, 1.0, ((debug > 0) ? 2.0 : -1.0), -1, -1, (colided ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 255, 0)));

						drawIt(vig, 0.0, 0.0, 0);
						flip();
					}

					if (save_score) // if infinite_map it will never go here
					{
						for (clock_t now = clock(); clock() - now < CLOCKS_PER_SEC * 4.0;) {
							multiply = multiplier() * 0.3;

							clearTo(al_map_rgb_f(0.5*sin(al_get_time()*0.33) + 0.5, 0.5*cos(al_get_time()*0.54) + 0.5, -0.5*sin(al_get_time()*0.215) + 0.5));

							for (int py = (campos[1] * 4.21875) - 1; py < 9 + (campos[1] * 4.21875); py++)
							{
								for (int px = (campos[0] * 7.5) - 1; px < 15 + (campos[0] * 7.5); px++)
								{
									double xx, yy;
									xx = (px * (blocksize_rel[0]) - 0.5) * 2.0 - campos[0];
									yy = (py * (blocksize_rel[1]) - 0.5) * 2.0 /*+ y_offset*/ - campos[1];

									if (map.readpos(px, py) <= 0) {

										drawIt(blk, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);

									}
									else if (px == map.getSiz(LSW_SIZ_X) - 1) drawIt(enb, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);

									if (debug > 0) al_draw_textf(font, al_map_rgb(0, 0, 0), (xx*0.5 + 0.5)*data.usedx, (yy*0.5 + 0.5)*data.usedy, ALLEGRO_ALIGN_CENTER, "%d;%d", px, py);
								}
							}
							

							speed -= (speed * 0.14)*multiply;
							//if (speed > 0.1) speed = 0.1;

							while (plrrot > 360.0)
								plrrot -= 360.0;
							while (plrrot < 0.0)
								plrrot += 360.0;

							double pi_r = ALLEGRO_PI * plrrot / 180.0; // 0 means down
							posrel[0] += multiply * speed * (sin(pi_r));
							posrel[1] += multiply * speed * (-cos(pi_r));

							if (posrel[0] - campos[0] > 1.0) posrel[0] = 1.0 + campos[0];
							if (posrel[0] - campos[0] < -1.0) posrel[0] = -1.0 + campos[0];
							if (posrel[1] - campos[1] > 1.0) posrel[1] = 1.0 + campos[1];
							if (posrel[1] - campos[1] < -1.0) posrel[1] = -1.0 + campos[1];

							drawIt(plr[((way >= 0) ? (1 + (int)(2.0*al_get_time()) % 2) : 0)], posrel[0] - campos[0], posrel[1] - campos[1], plrrot, 1.0, 1.0, ((debug > 0) ? 2.0 : -1.0), -1, -1, (colided ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 255, 0)));

							drawIt(vig, 0.0, 0.0, 0);
							flip();
						}

						ALLEGRO_BITMAP *rec_back;
						FILE* fp = nullptr;
						clock_t now = clock() - CLOCKS_PER_SEC / 4;
						double nowFps = 0.0, nowMult = multiply;
						bool choosing = true;

						double real_final_score = sqrt(final_score) * 0.01 * (time_final[1] - time_final[0]);

						std::string hisname;

						char records_name[32];
						sprintf_s(records_name, "records_%d.txt", level);

						if (fopen_s(&fp, records_name, "a+") != 0)
						{
							if (fopen_s(&fp, records_name, "w+") != 0) {
								choosing = false;
								hisname = "FAILED LOADING SCORE! SORRY!";
							}
						}

						rec_back = data.data_control.get(LSW_BMP_SAVING_SCORE);

						multiplier(); // reset for animation
						multiply = 0.0;

						// pre-animation full of features because I CAN :3
						for (double pos = -1.55; pos < -0.02; pos += multiply * (0.2*fabsf(pos / 2.0)))
						{
							clearTo(al_map_rgb(0, 0, 0));
							bganim(multiply);
							drawIt(log, (pos + 0.02)*0.8, -0.5, 0);

							if (clock() - now > CLOCKS_PER_SEC / 4) {
								now += CLOCKS_PER_SEC / 4;
								nowFps = lastFPS();
								nowMult = multiply;
							}

							drawIt(rec_back, pos + 0.02, 0.1, 0);

							al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
							drawIt(vig, 0.0, 0.0, 0);
							flip();

							multiply = multiplier();
						}

						bool isShiftOn = false;

						while (choosing)
						{
							int keyn = evmng_e.getLastKeyIfAvailable(LSW_KEYPRESSED);
							int keyl = evmng_e.getLastKeyIfAvailable(LSW_KEYLEFT);
							char translated = translate_al(keyn);

							if (keyn == ALLEGRO_KEY_LSHIFT || keyn == ALLEGRO_KEY_RSHIFT) isShiftOn = true;
							if (keyl == ALLEGRO_KEY_LSHIFT || keyl == ALLEGRO_KEY_RSHIFT) isShiftOn = false;

							switch (translated)
							{
							case 0:
								break;
							case 3:
								hisname.clear();
							case 1:
								choosing = false;
								continue;
							case 2:
								if (hisname.length() > 0) hisname.pop_back();
								break;
							default:
								if (hisname.length() < 50) {
									if (translated >= 'A' && translated <= 'Z')
									{
										if (isShiftOn) hisname += translated;
										else hisname += translated - 'A' + 'a';
									}
									else hisname += translated;
								}
							}																

							if (clock() - now > CLOCKS_PER_SEC / 4) {
								now += CLOCKS_PER_SEC / 4;
								nowFps = lastFPS();
								nowMult = multiply;
							}

							clearTo(al_map_rgb(0, 0, 0));
							bganim(multiply);
							drawIt(log, 0.0, -0.5, 0);

							drawIt(rec_back, 0.0, 0.1, 0);

							al_draw_textf(font, al_map_rgb(255, 255, 0), 0.5*data.usedx, (0.59)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", ((hisname.length() >= 50) ? hisname.c_str() : ((int)(2.0*al_get_time())%2 ? hisname.c_str() : (hisname + '_').c_str())));
							al_draw_textf(font, al_map_rgb(255, 255, 0), 0.5*data.usedx, (0.78)*data.usedy, ALLEGRO_ALIGN_CENTER, "%.6f points (%.2f s, %.1f m)", real_final_score, time_final[1] - time_final[0], distance_taken);

							al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", (float)nowFps, (float)nowMult);
							drawIt(vig, 0.0, 0.0, 0);
							flip();
							multiply = multiplier();
						}

						for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
						{
							if (clock() - now > CLOCKS_PER_SEC / 4) {
								now += CLOCKS_PER_SEC / 4;
								nowFps = lastFPS();
								nowMult = multiply;
							}

							clearTo(al_map_rgb(0, 0, 0));
							bganim(multiply);
							drawIt(log, (pos - 0.02)*0.8, -0.5, 0);

							drawIt(rec_back, pos - 0.02, 0.1, 0);

							al_draw_textf(font, al_map_rgb(255, 255, 0), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.59)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", hisname.c_str());
							al_draw_textf(font, al_map_rgb(255, 255, 0), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.78)*data.usedy, ALLEGRO_ALIGN_CENTER, "%.6f points (%.2f s, %.1f m)", real_final_score, time_final[1] - time_final[0], distance_taken);

							al_draw_textf(font, al_map_rgb(255, 255, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", (float)nowFps, (float)nowMult, pos);
							drawIt(vig, 0.0, 0.0, 0);
							flip();

							multiply = multiplier();
						}

						if (fp) {
							if (hisname.length() > 0) {
								for (auto& i : hisname) {
									if (i == ' ') i = '_';
								}
								fprintf_s(fp, "%s %.6lf\n", hisname.c_str(), real_final_score);
							}
							fclose(fp);
						}
						data.now = LSW_S_MENU;
					}

					data.now = LSW_S_MENU;

					thr.join();
				}
				break;
				}
			}
			return true;
		}

		void displayer::drawIt(ALLEGRO_BITMAP *chosen, const double pos_related_x, const double pos_related_y, const double rotation, const double scale_x, const double scale_y, const double hasboxthing, double pos_center_bitmap_x, double pos_center_bitmap_y, const ALLEGRO_COLOR color)
		{
			if (!chosen) return;
			float _scale_x, _scale_y;
			_scale_x = (1.0f*data.usedx / base_res[0]) * scale_x;
			_scale_y = (1.0f*data.usedy / base_res[1]) * scale_y;
			int sx_b = al_get_bitmap_width(chosen);
			int sy_b = al_get_bitmap_height(chosen);
			if (pos_center_bitmap_x < 0.0 || pos_center_bitmap_y < 0.0)
			{
				pos_center_bitmap_x = (sx_b / 2.0);
				pos_center_bitmap_y = (sy_b / 2.0);
			}
			float var1, var2; // posx, posy
			var1 = data.usedx * ((pos_related_x + 1.0) / 2.0);
			var2 = data.usedy * ((pos_related_y + 1.0) / 2.0);

			al_draw_scaled_rotated_bitmap(chosen,
				pos_center_bitmap_x,
				pos_center_bitmap_y,
				var1,
				var2,
				_scale_x,
				_scale_y,
				(rotation / 180.0)*ALLEGRO_PI,
				0);
			if (hasboxthing > 0.0)
			{
				double box_x1 = var1 - pos_center_bitmap_x * _scale_x;
				double box_y1 = var2 - pos_center_bitmap_y * _scale_y;
				double box_x2 = var1 + pos_center_bitmap_x * _scale_x;
				double box_y2 = var2 + pos_center_bitmap_y * _scale_y;
				al_draw_rectangle(box_x1, box_y1, box_x2, box_y2, color, hasboxthing*sqrt(_scale_x*_scale_y));
			}
		}
		// x, y, scale, blur
		void displayer::drawCircle(const double pos_related_x, const double pos_related_y, const double scale)
		{
			double realposx = ((pos_related_x * 0.5 + 0.5) * data.usedx);
			double realposy = ((pos_related_y * 0.5 + 0.5) * data.usedy);
			float _scale_x, _scale_y;
			_scale_x = (1.0f*data.usedx / base_res[0]) * scale;
			_scale_y = (1.0f*data.usedy / base_res[1]) * scale;

			//al_draw_ellipse(realposx, realposy, _scale_x, _scale_y, al_map_rgb(0,0,0), 5.0);

			al_set_target_bitmap(data.transparency);

			al_draw_filled_rectangle(0, 0, data.usedx, data.usedy, al_map_rgb(0, 0, 0));

			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

			for (double u = 1.0; u >= 0.5; u -= 0.02)
			{
				al_draw_filled_ellipse(realposx, realposy, _scale_x * u, _scale_y * u, al_map_rgba_f(0.0, 0.0, 0.0, 2.0*(u - 0.5)));
			}

			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

			fixLoad();

			al_draw_bitmap(data.transparency, 0, 0, 0);
		}
		void displayer::bganim(const double mult)
		{
			double calc = (1.0 * data.usedx / base_res[0]);
			ALLEGRO_BITMAP *blk;
			blk = data.data_control.get(LSW_BMP_MENU_BLOCK);
			int blk_siz = calc * al_get_bitmap_width(blk);

			data.anim_posxy_keep += mult * 1.2;

			if (data.anim_posxy_keep >= blk_siz / 2) data.anim_posxy_keep -= 1.0*blk_siz;
			for (double basex = data.anim_posxy_keep; basex < data.usedx + blk_siz / 2; basex += blk_siz)
			{
				for (double basey = data.anim_posxy_keep; basey < data.usedy + blk_siz / 2; basey += blk_siz)
				{
					drawIt(blk, (2.0*basex / data.usedx) - 1.0, (2.0*basey / data.usedy) - 1.0, 0.0);
				}
			}
		}
		const int displayer::pauseScreenGame() // 0 == continue, 1 == exit
		{
			ALLEGRO_BITMAP *pause_anim[30] = { nullptr };
			ALLEGRO_BITMAP *vig;
			ALLEGRO_BITMAP *options[2];

			vig = data.data_control.get(LSW_BMP_VIGNETTE);
			for (int p = 0; p < 30; p++) pause_anim[p] = data.data_control.get((images_available)(p + LSW_BMP_PAUSE_00));
			for (int p = 0; p < 2; p++) options[p] = data.data_control.get((images_available)(p + LSW_BMP_PAUSE_CONTINUE));

			double val_precise = 0.0;
			bool choosing = true;
			int opt = 0;
			int times_shift_hack = 0;

			while (choosing)
			{
				val_precise += multiplier()*0.5;

				int key = data.evm.getLastKeyIfAvailable();

				switch (key)
				{
				case ALLEGRO_KEY_UP:
					if (++opt > 1) opt = 0;
					break;
				case ALLEGRO_KEY_DOWN:
					if (--opt < 0) opt = 1;
					break;
				case ALLEGRO_KEY_ENTER:
					choosing = false;
					continue;
				case ALLEGRO_KEY_ESCAPE:
					opt = 0;
					choosing = false;
					continue;
				case ALLEGRO_KEY_RSHIFT:
					times_shift_hack++;
					break;
				}

				clearTo(al_map_rgb(0, 0, times_shift_hack * 10));

				if ((int)val_precise >= 30) val_precise = 0.0;

				drawIt(pause_anim[(int)val_precise], 0.0, -0.5, 0);
				drawIt(options[(opt > 1) ? 1 : opt], 0.0, 0.0, 0);

				drawIt(vig, 0.0, 0.0, 0);
				flip();

				if (times_shift_hack > 10)
				{
					opt = 2;
					choosing = false;
					continue;
				}
			}
			return opt;
		}
		// dx & dy. (plr pos - block pos)
		const assistance_nsew displayer::_whereToTp(const double dx, const double dy)
		{
			if (dx > 0.0) // 1 or 4 (quarters) +
			{
				if (dy > 0.0) // 4
				{
					if (fabs(dy) > fabs(dx)) return LSW_P_SOUTH;
					else return LSW_P_EAST;
				}
				else // 1
				{
					if (fabs(dy) > fabs(dx)) return LSW_P_NORTH;
					else return LSW_P_EAST;
				}
			}
			else { // 2 or 3 (quarters) +
				if (dy > 0.0) // 3
				{
					if (fabs(dy) > fabs(dx)) return LSW_P_SOUTH;
					else return LSW_P_WEST;
				}
				else // 2
				{
					if (fabs(dy) > fabs(dx)) return LSW_P_NORTH;
					else return LSW_P_WEST;
				}
			}
		}

		// degrees
		const double displayer::_ang_dif(const double a, const double b)
		{
			double r = a - b;
			if (fabs(r) > 180.0)
			{
				r = 360 - r;
			}
			return r;
		}
		const bool displayer::init()
		{
			if (data.loaded) return true;
			data.muu.lock();

			al_get_display_mode(al_get_num_display_modes() - 1, &data.full);

			al_set_new_display_option(ALLEGRO_AUTO_CONVERT_BITMAPS, 1, ALLEGRO_DONTCARE);
			al_set_new_display_flags(ALLEGRO_FRAMELESS | ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0);
			al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST);

			data.display = al_create_display(data.full.width, data.full.height);
			if (!data.display) {
				data.muu.unlock();
				throw "FAILED CREATING DISPLAY!";
				return false;
			}

			al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);
			al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR);
			al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);

			data.usedx = data.full.width;
			data.usedy = data.full.height;
			float temp_f = 1.0*data.usedy / data.usedx;
			if (temp_f > (16.0 / 9)) {
				data.usedx = data.usedy * 16.0 / 9;
			}
			else {
				data.usedy = data.usedx * 9.0 / 16;
			}

			data.buffer = al_create_bitmap(data.usedx, data.usedy);
			if (!data.buffer) {
				al_destroy_display(data.display);
				al_destroy_bitmap(data.buffer);
				data.muu.unlock();
				throw "FAILED CREATING DISPLAY!";
				return false;
			}
			data.transparency = al_create_bitmap(data.usedx, data.usedy);
			if (!data.transparency) {
				al_destroy_display(data.display);
				data.muu.unlock();
				throw "FAILED CREATING DISPLAY!";
				return false;
			}

			if (data.data_control.load(LSW_BMP_ICON)) al_set_display_icon(data.display, data.data_control.get(LSW_BMP_ICON));

			data.prop = data.usedx / base_res[0];

			float temp_siz_font = 1.0*sqrt(data.usedx*data.usedy)*28.8 / sqrt(base_res[0] * base_res[1]);
			if (!data.data_control.load(LSW_FONT_DEJAVUSANS, temp_siz_font))
			{
				al_destroy_display(data.display);
				al_destroy_bitmap(data.buffer);
				al_destroy_bitmap(data.transparency);
				data.data_control.unloadAll();
				data.data_control.clearAll();
				data.muu.unlock();
				throw "FAILED LOADING FONT!";
				return false;
			}

			data.ev_qu = al_create_event_queue();
			if (!data.ev_qu) {
				al_destroy_display(data.display);
				al_destroy_bitmap(data.buffer);
				al_destroy_bitmap(data.transparency);
				data.data_control.unloadAll();
				data.data_control.unload(LSW_FONT_DEJAVUSANS);
				data.data_control.clearAll();
				data.muu.unlock();
				throw "FAILED CREATING QUEUE!";
				return false;
			}

			al_register_event_source(data.ev_qu, al_get_display_event_source(data.display));
			al_register_event_source(data.ev_qu, al_get_keyboard_event_source());

			al_set_window_title(data.display, "Maze Game by Erfra REVAMPED");
			al_set_exe_name("Maze_App.exe");

			if (!data.evm.init(data.ev_qu)) {
				data.data_control.unloadAll();
				data.data_control.unload(LSW_FONT_DEJAVUSANS);
				al_destroy_event_queue(data.ev_qu);
				al_destroy_bitmap(data.buffer);
				al_destroy_bitmap(data.transparency);
				data.data_control.clearAll();
				al_destroy_display(data.display);
				data.muu.unlock();
				throw "FAILED CREATING KEYBOARD THREAD!";
				return false;
			}
			data.lastC = GetTickCount64();

			al_set_target_bitmap(data.buffer);
			data.loaded = true;
			data.muu.unlock();
			return true;
		}
		void displayer::clearTo(const ALLEGRO_COLOR c)
		{
			al_clear_to_color(c);
		}
		const double displayer::multiplier()
		{
			double saved = al_get_time();
			double val = saved - data.lastC_fMult_al;
			data.lastC_fMult_al = saved;
			return val * 60.0; // 1.0 multiplier for 60 fps

		}
		void displayer::flip()
		{
			al_set_target_backbuffer(data.display);
			al_draw_scaled_bitmap(data.buffer, 0, 0, data.usedx, data.usedy, 0, 0, al_get_display_width(data.display), al_get_display_height(data.display), 0);
			al_flip_display();
			al_set_target_bitmap(data.buffer);
			data.tickCount = GetTickCount64() - data.lastC;

			if (data.lastdraw != 0.0) {
				double noww = al_get_time();
				data.fps = (data.fps * 2 + (1.0 / (noww - data.lastdraw))) / 3;
				data.lastdraw = noww;
			}
			else data.lastdraw = al_get_time();

			if (!data.evm.keepdisplayOn()) {
				deinitAll();
				exit(0);
			}
		}
		const double displayer::lastFPS()
		{
			return data.fps;
		}
		void displayer::fixLoad()
		{
			al_set_target_bitmap(data.buffer);
		}
		void displayer::resizeBufTo(const int x, const int y)
		{
			if (data.buffer)
			{
				al_destroy_bitmap(data.buffer);
				al_destroy_bitmap(data.transparency);
				while (!(data.buffer = al_create_bitmap(x, y)));
				while (!(data.transparency = al_create_bitmap(x, y)));
				data.usedx = x;
				data.usedy = y;
				data.data_control.unload(LSW_FONT_DEJAVUSANS);

				float temp_siz_font = 1.0*sqrt(data.usedx*data.usedy)*28.8 / sqrt(base_res[0] * base_res[1]);
				while (!data.data_control.load(LSW_FONT_DEJAVUSANS, temp_siz_font));
			}
		}
		void displayer::deinitAll()
		{
			if (!data.loaded) return;
			data.muu.lock();

			data.evm.deinit();
			data.data_control.unloadAll();
			data.data_control.unload(LSW_FONT_DEJAVUSANS);
			al_destroy_event_queue(data.ev_qu);
			al_destroy_bitmap(data.buffer);
			al_destroy_bitmap(data.transparency);
			data.data_control.clearAll();
			al_destroy_display(data.display);

			data.loaded = false;
			data.muu.unlock();
		}


		const bool event_mng::init(ALLEGRO_EVENT_QUEUE* gimme)
		{
			if (!gimme) return false;
			if (data.keeprunning) return false;

			data.ev_qu = gimme;
			data.thr = new std::thread(_thr_keyboard, &data);
			if (data.thr) for (int timing = 0; timing < 20 && (!data.keeprunning); timing++) Sleep(50);
			else return false;
			if (!data.keeprunning) return false;

			return true;
		}
		void event_mng::deinit()
		{
			if (!data.keeprunning) return;

			data.keeprunning = false;
			data.thr->join();
		}
		const bool event_mng::keepdisplayOn()
		{
			return !data.closewindow;
		}
		const int event_mng::getLastKeyIfAvailable(const key_type which)
		{
			if (which == LSW_KEYPRESSED) {
				if (data.hasnewstroke)
				{
					int v = data.laststroke;
					data.hasnewstroke = false;
					return v;
				}
				return -1;
			}
			else if (which == LSW_KEYLEFT) {
				if (data.hasnewstrokeleft)
				{
					int v = data.laststrokeleft;
					data.hasnewstrokeleft = false;
					return v;
				}
				return -1;
			}
			else if (which == LSW_KEYKEEP_LAST)
			{
				return data.lastkeykeep;
			}
			return -1;
		}

		void _thr_temp_loadallresources(int* which, bool* hasdone)
		{
			if (!hasdone || !which) return;

			controller ctrl;
			//displayer disp;

			*hasdone = false;

			//disp.fixLoad();
			for (*which = 0; *which < LSW_BMP_MAX; (*which)++) ctrl.load((images_available)(*which));

			*hasdone = true;
		}

		void _thr_temp_generatemap(mapthing* map, int level, int* needed_reset, bool* done, bool* playin)
		{
			if (!done || !map || !needed_reset || !playin) {
				throw "_THR GENERATEMAP FAILED!";
				exit(0); // cannot run
			}

			*done = false;
			while (!map->generate(playin, level, 8 + pow(level,2.0)*8) && *playin) *needed_reset = 1;
			*done = true;

			return;
		}

		void _thr_keyboard(event_mng_data* dat)
		{
			if (!dat) return;
			dat->keeprunning = true;

			while (dat->keeprunning)
			{
				al_wait_for_event(dat->ev_qu, &dat->ev);

				if (dat->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					dat->closewindow = true;
					dat->keeprunning = false;
					continue;
				}
				if (dat->ev.type == ALLEGRO_EVENT_KEY_DOWN)
				{
					for (unsigned tried = 0; (tried < 10) && dat->hasnewstroke; tried++) Sleep(10);
					dat->laststroke = dat->ev.keyboard.keycode;
					dat->lastkeykeep = dat->ev.keyboard.keycode;
					dat->hasnewstroke = true;
				}
				if (dat->ev.type == ALLEGRO_EVENT_KEY_UP)
				{
					for (unsigned tried = 0; (tried < 10) && dat->hasnewstrokeleft; tried++) Sleep(10);
					dat->laststrokeleft = dat->ev.keyboard.keycode;
					if (dat->laststrokeleft == dat->lastkeykeep) dat->lastkeykeep = -1;
					dat->hasnewstrokeleft = true;
				}
				if (dat->ev.type == ALLEGRO_EVENT_KEY_CHAR)
				{
					dat->lastkeykeep = dat->ev.keyboard.keycode;
				}
			}
		}

		const char translate_al(const int code)
		{
			char ch = 0;
			switch (code)
			{
			case ALLEGRO_KEY_A:
				ch = 'A';
				break;
			case ALLEGRO_KEY_B:
				ch = 'B';
				break;
			case ALLEGRO_KEY_C:
				ch = 'C';
				break;
			case ALLEGRO_KEY_D:
				ch = 'D';
				break;
			case ALLEGRO_KEY_E:
				ch = 'E';
				break;
			case ALLEGRO_KEY_F:
				ch = 'F';
				break;
			case ALLEGRO_KEY_G:
				ch = 'G';
				break;
			case ALLEGRO_KEY_H:
				ch = 'H';
				break;
			case ALLEGRO_KEY_I:
				ch = 'I';
				break;
			case ALLEGRO_KEY_J:
				ch = 'J';
				break;
			case ALLEGRO_KEY_K:
				ch = 'K';
				break;
			case ALLEGRO_KEY_L:
				ch = 'L';
				break;
			case ALLEGRO_KEY_M:
				ch = 'M';
				break;
			case ALLEGRO_KEY_N:
				ch = 'N';
				break;
			case ALLEGRO_KEY_O:
				ch = 'O';
				break;
			case ALLEGRO_KEY_P:
				ch = 'P';
				break;
			case ALLEGRO_KEY_Q:
				ch = 'Q';
				break;
			case ALLEGRO_KEY_R:
				ch = 'R';
				break;
			case ALLEGRO_KEY_S:
				ch = 'S';
				break;
			case ALLEGRO_KEY_T:
				ch = 'T';
				break;
			case ALLEGRO_KEY_U:
				ch = 'U';
				break;
			case ALLEGRO_KEY_V:
				ch = 'V';
				break;
			case ALLEGRO_KEY_W:
				ch = 'W';
				break;
			case ALLEGRO_KEY_X:
				ch = 'X';
				break;
			case ALLEGRO_KEY_Y:
				ch = 'Y';
				break;
			case ALLEGRO_KEY_Z:
				ch = 'Z';
				break;
			case ALLEGRO_KEY_0:
				ch = '0';
				break;
			case ALLEGRO_KEY_1:
				ch = '1';
				break;
			case ALLEGRO_KEY_2:
				ch = '2';
				break;
			case ALLEGRO_KEY_3:
				ch = '3';
				break;
			case ALLEGRO_KEY_4:
				ch = '4';
				break;
			case ALLEGRO_KEY_5:
				ch = '5';
				break;
			case ALLEGRO_KEY_6:
				ch = '6';
				break;
			case ALLEGRO_KEY_7:
				ch = '7';
				break;
			case ALLEGRO_KEY_8:
				ch = '8';
				break;
			case ALLEGRO_KEY_9:
				ch = '9';
				break;
			case ALLEGRO_KEY_ENTER:
			case ALLEGRO_KEY_PAD_ENTER:
				ch = 1;
				break;
			case ALLEGRO_KEY_FULLSTOP:
				ch = '.';
				break;
			case ALLEGRO_KEY_BACKSPACE:
				ch = 2;
				break;
			case ALLEGRO_KEY_ESCAPE:
				ch = 3;
				break;
			case ALLEGRO_KEY_SPACE:
				ch = ' ';
				break;
			}
			return ch;
		}
	}
}