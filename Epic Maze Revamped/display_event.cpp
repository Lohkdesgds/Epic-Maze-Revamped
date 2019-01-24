#include "display_event.h"

namespace LSW {

	namespace EpicMazeR {

		displayer_data displayer::data;
		event_mng_data event_mng::data;

		const bool is_debug = false;

		const int displayer::think()
		{
			fixLoad();
			event_mng evmng_e;
			while (data.now != LSW_S_EXIT)
			{
				data.lastC = GetTickCount64();
				double multiply = 1.0;

				switch (data.now)
				{
				case LSW_S_INITIALIZING:
				{
					/* Imagens||fontes a serem usadas: */
					lsw_texture log;
					lsw_font font;

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

						clearTo(color(0, 0, 0));
						drawIt(log, 0.0, -0.4, 0);

						float a, b;
						a = data.usedx*(830 + 1.2*posoffset) / base_res[0];
						b = data.usedy*650.0 / base_res[1];
						drawText(font, color(1, 1, 1), a, b, 0, "Loading... (%02.1f%c)", (99.9f*ref_loading_files / LSW_BMP_MAX), '%');
						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f - %02.3f%c", nowFps, (99.9f*ref_loading_files / LSW_BMP_MAX), '%');

						flip();

						//restFor(0.016);
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

						clearTo(color(0, 0, 0));
						drawIt(log, 0.0, -0.4, 0);

						float a, b;
						a = data.usedx*(830 + 1.2*posoffset) / base_res[0];
						b = data.usedy*(650.0 + to_add * 0.4) / base_res[1];
						drawText(font, color(1.0 - to_add / 90.0, 1.0 - to_add / 90.0, 1.0 - to_add / 90.0), a, b, 0, "Loading... (100%c)",'%');
						if (to_add > 45.0)drawText(font, color((to_add - 45.0) / 45.0, (to_add - 45.0) / 45.0, (to_add - 45.0) / 45.0), a, b, 0, "   DONE   ");
						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f - %02.3f%c", nowFps, 100.0, '%');

						flip();
					}

					data.now = LSW_S_MENU;
				}
				break;
				case LSW_S_MENU:
				{
					lsw_texture log, vig, opt_01, opt_02, opt_03, opt_04;
					lsw_font font;
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

						clearTo(color(0, 0, 0));
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

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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
						clearTo(color(0, 0, 0));
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

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", nowFps, nowMult);
						drawIt(vig, 0.0, 0.0, 0);
						flip();
						multiply = multiplier();
					}

					for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						clearTo(color(0, 0, 0));
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

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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
					lsw_texture log, vig, instr;
					lsw_font font;
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
						clearTo(color(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos + 0.02)*0.8, -0.5, 0);

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						drawIt(instr, pos + 0.02, 0.0, 0);

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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

						clearTo(color(0, 0, 0));
						bganim(multiply);
						drawIt(log, 0.0, -0.5, 0);

						drawIt(instr, 0.0, 0.0, 0);

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", nowFps, nowMult);
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

						clearTo(color(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos - 0.02)*0.8, -0.5, 0);

						drawIt(instr, pos - 0.02, 0.0, 0);

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
						drawIt(vig, 0.0, 0.0, 0);
						flip();

						multiply = multiplier();
					}

					if (moree)
					{
						choosing = true;
						int option_on_screen = 0;
						bool new_isfull = isFullscreen;
						bool selected = false;
						double y_off_motion = 0.0;

						int vars[2] = { data.usedx, data.usedy };
						float multipl_mult = 1;
						int multipl = 10;
						lsw_mode mn = data.modes.modes[data.modes.using_rn];
						int lmn = data.modes.using_rn;
						// enabled_alternative_mode
						// infinite_map
							
						while (choosing)
						{
							int key = evmng_e.getLastKeyIfAvailable();
							int keyleft = evmng_e.getLastKeyIfAvailable(LSW_KEYLEFT);

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
									if (option_on_screen == 0 || option_on_screen == 1) vars[option_on_screen] += multipl * multipl_mult;
									if (option_on_screen == -1) multipl += 10;
									if (option_on_screen ==  2) data.modes.using_rn += multipl * multipl_mult * 0.1 * ((multipl_mult < 1.0 && multipl < 100) ? 10.0 : 1.0);
									if (option_on_screen ==  3) data.fixed_fps += multipl * multipl_mult;
								}
								break;
							case ALLEGRO_KEY_DOWN:
								if (!selected) option_on_screen++;
								else {
									if (option_on_screen == 0 || option_on_screen == 1) vars[option_on_screen] -= multipl* multipl_mult;
									if (option_on_screen == -1) multipl -= 10;
									if (option_on_screen == 2) data.modes.using_rn -= multipl * multipl_mult * 0.1 * ((multipl_mult < 1.0 && multipl < 100) ? 10.0 : 1.0);
									if (option_on_screen == 3) data.fixed_fps -= multipl * multipl_mult;
								}
								break;
							case ALLEGRO_KEY_ENTER:
								selected = !selected;
								break;
							case ALLEGRO_KEY_ESCAPE:
								choosing = false;
								continue;
							case ALLEGRO_KEY_LSHIFT:
								multipl_mult = 0.1;
								break;
							case ALLEGRO_KEY_LCTRL:
								multipl_mult = 10.0;
								break;
							}
							switch (keyleft)
							{
							case ALLEGRO_KEY_LSHIFT:
							case ALLEGRO_KEY_LCTRL:
								multipl_mult = 1.0;
								break;
							}

							if (selected)
							{
								switch (option_on_screen)
								{
								case 4:
									enabled_alternative_mode = !enabled_alternative_mode;
									selected = false;
									break;
								case 5:
									infinite_map = !infinite_map;
									selected = false;
									break;
								case 6:
									if (++data.display_mode_draw > 2) data.display_mode_draw = 0;
									selected = false;
									break;
								case 7:
									selected = false;
									new_isfull = !new_isfull;
									break;
								case 8:
									selected = false;
									if ((new_isfull != isFullscreen) || (lmn != data.modes.using_rn))
									{
										if (lmn != data.modes.using_rn)
										{
											data.usedx = mn.x;
											data.usedy = mn.y;											
										}
										else {
											data.usedx = vars[0];
											data.usedy = vars[1];
										}
										fixProportion(data.usedx, data.usedy);
										isFullscreen = new_isfull;
										data.now = LSW_S_INITIALIZING;
										return 1;
									}
									resizeBufTo(vars[0], vars[1]);
									font = data.data_control.get(LSW_FONT_DEJAVUSANS);
									break;
								case 9:
									choosing = false;
									break;
								}
							}


							if ((data.fixed_fps < 10 && data.fixed_fps >= 0) || data.fixed_fps < -1) data.fixed_fps = 10;
							if (data.fixed_fps >= 250) data.fixed_fps = -1;
							if (multipl < 10) multipl = 10;
							if (option_on_screen < -1) option_on_screen = 9;
							if (option_on_screen > 9) option_on_screen = -1;
							if (vars[0] < 853) vars[0] = 853;
							if (vars[1] < 480) vars[1] = 480;
							if (option_on_screen == 0 && selected) vars[1] = vars[0] * 9.0 / 16.0;
							if (option_on_screen == 1 && selected) vars[0] = vars[1] * 16.0 / 9.0;
							if (data.modes.using_rn >= (int)data.modes.modes.size()) data.modes.using_rn = 0;
							if (data.modes.using_rn < 0)
								data.modes.using_rn = ((int)data.modes.modes.size() - 1);

							mn = data.modes.modes[data.modes.using_rn];
							y_off_motion -= multiply * 0.2 * (y_off_motion - option_on_screen*0.05);

							if (option_on_screen == 2 && selected)
							{
								vars[0] = mn.x;
								vars[1] = mn.y;
							}

							clearTo(color(0, 0, 0));

							double y_help = (0.46 - y_off_motion)*data.usedy;
							double y_eq_001 = (0.01)*data.usedy;
							int opt_being_tested = -1;

							// ----------------------------- DRAWTEXT START ----------------------------- //

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c MULTIPL_VAL: %d*%.1f (SHIFT/CTRL) %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), multipl, multipl_mult, ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 8.0;

							drawText(font, color(0.78, 0.78, 0.78),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "- RESOLUTION BASE -");

							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Width: %d %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), vars[0], ((option_on_screen == opt_being_tested) ? '<' : '-'));
							
							opt_being_tested++;
							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Height: %d %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), vars[1], ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c DISPLAY RES: %dx%d@%d[#%d/%u] %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), mn.x, mn.y, mn.hz,data.modes.using_rn, data.modes.modes.size(), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c FPS LIMIT: %s %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), ((data.fixed_fps == -1 || data.fixed_fps >= 250) ? "UNLIMITED" : std::to_string(data.fixed_fps).c_str()), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 8.0;

							drawText(font, color(0.78, 0.78, 0.78),                                                                                            
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "- MISCELLANEOUS -");

							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Alternative game mode? %s %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), (enabled_alternative_mode ? "YES" : "NO"), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Infinite map? (EXPERIMENTAL) %s %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), (infinite_map ? "YES" : "NO"), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 4.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Background mode: #%d %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), data.display_mode_draw, ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 6.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Fullscreen? %s %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), (new_isfull ? "YES" : "NO"), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 6.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Apply? %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							opt_being_tested++;
							y_help += y_eq_001 * 6.0;

							drawText(font, ((option_on_screen == opt_being_tested) ? (selected ? color(1, 0, 0) : color(1, 1, 0)) : color(0.5, 0.5, 0.5)),
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "%c Exit? %c", ((option_on_screen == opt_being_tested) ? '>' : '-'), ((option_on_screen == opt_being_tested) ? '<' : '-'));

							y_help += y_eq_001 * 4.0;

							drawText(font, color(0.78, 0.78, 0.78),                                                                                            
								0.5*data.usedx, y_help, ALLEGRO_ALIGN_CENTER, "Version: %s", VERSION);
							
							// ----------------------------- END ----------------------------- //

							drawCircle(0.0, 0.25, 340.0 + sin(getTime()*0.3)*30.0);

							drawIt(log, 0.0, -0.5, 0);
							if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", nowFps, nowMult);
							drawIt(vig, 0.0, 0.0, 0);
							flip();

							multiply = multiplier();
						}
						data.modes.using_rn = lmn;
					}

					data.now = LSW_S_MENU;
				}
				break;
				case LSW_S_RECORDS:
				{
					lsw_texture log, vig, rec_back;
					lsw_font font;
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
						clearTo(color(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos + 0.02)*0.8, -0.5, 0);

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						drawIt(rec_back, pos + 0.02, 0.1, 0);
						
						drawText(font, color(1, 1, 1), ((pos + 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- EASY -->");

						for (int u = 0; u < 10; u++)
						{
							std::string to_print_rn = "=-=-=-=-=-=-=-=-=-=-=-=";
							if (u < (int)records[level_choice].size()) to_print_rn = records[level_choice][u].name + " = " + std::to_string(records[level_choice][u].score);

							drawText(font, color(1, 1, 1), ((pos + 0.02) + 1.0)*0.5*data.usedx, (0.46 + u * 0.038)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", to_print_rn.c_str());
						}

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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

						if (offset > (int)records[level_choice].size() - 10) offset = records[level_choice].size() - 10;
						if (offset < 0) offset = 0;
						if (level_choice > 2) level_choice = 0;
						if (level_choice < 0) level_choice = 2;

						if (clock() - now > CLOCKS_PER_SEC / 4) {
							now += CLOCKS_PER_SEC / 4;
							nowFps = lastFPS();
							nowMult = multiply;
						}

						clearTo(color(0, 0, 0));
						bganim(multiply);
						drawIt(log, 0.0, -0.5, 0);

						drawIt(rec_back, 0.0, 0.1, 0);

						switch (level_choice) {
						case 0:
							drawText(font, color(1, 1, 1), 0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- EASY -->");
							break;
						case 1:
							drawText(font, color(1, 1, 1), 0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- NORMAL -->");
							break;
						case 2:
							drawText(font, color(1, 1, 1), 0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- UNBELIEVABLE -->");
							break;
						}

						for (int u = offset; u < 10 + offset; u++)
						{
							std::string to_print_rn = "=-=-=-=-=-=-=-=-=-=-=-=";
							if (u < (int)records[level_choice].size()) to_print_rn = records[level_choice][u].name + " = " + std::to_string(records[level_choice][u].score);

							drawText(font, color(1, 1, 1), 0.5*data.usedx, (0.46 + (u - offset) * 0.038)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", to_print_rn.c_str());
						}

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", nowFps, nowMult);
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

						clearTo(color(0, 0, 0));
						bganim(multiply);
						drawIt(log, (pos - 0.02)*0.8, -0.5, 0);

						drawIt(rec_back, pos - 0.02, 0.1, 0);

						switch (level_choice) {
						case 0:
							drawText(font, color(1, 1, 1), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- EASY -->");
							break;
						case 1:
							drawText(font, color(1, 1, 1), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- NORMAL -->");
							break;
						case 2:
							drawText(font, color(1, 1, 1), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.422)*data.usedy, ALLEGRO_ALIGN_CENTER, "<-- UNBELIEVABLE -->");
							break;
						}

						for (int u = offset; u < 10 + offset; u++)
						{
							std::string to_print_rn = "=-=-=-=-=-=-=-=-=-=-=-=";
							if (u < (int)records[level_choice].size()) to_print_rn = records[level_choice][u].name + " = " + std::to_string(records[level_choice][u].score);

							drawText(font, color(1, 1, 1), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.46 + (u - offset) * 0.038)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", to_print_rn.c_str());
						}

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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

					lsw_texture log, vig, opt_01, opt_02, opt_03;
					lsw_font font;
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

						clearTo(color(0, 0, 0));
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

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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
						clearTo(color(0, 0, 0));
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

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", nowFps, nowMult);
						drawIt(vig, 0.0, 0.0, 0);
						flip();
						multiply = multiplier();
					}

					for (double pos = 0.02; pos < 1.55; pos += multiply * (0.2*fabsf(pos / 2.0)))
					{
						clearTo(color(0, 0, 0));
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

						if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
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
					return 0;
				case LSW_S_GAMING:
				{
					mapthing map;
					infinity_map map2;

					gameplay_needs rn;
					gameplay_needs &gr = rn;// testing
					
					lsw_texture log, vig, plr[3], blk, enb, sav, mbl;
					lsw_font font;

					rn.now = clock() - CLOCKS_PER_SEC / 4;
					rn.nowMult = multiply;
					rn.map = &map;
					rn.map2 = &map2;

					clearTo(color(0, 0, 0));

					/*rn.being_made = true;
					rn.needed_reset = 0;
					rn.debug = 0;

					rn.nowFps = 0.0;
					rn.playin = true;
					rn.paused = false;
					rn.save_score = true;
					rn.asked_for_help = false;

					rn.way = -1; // NSWE
					rn.alternative_way[4] = { false };
					rn.way_cam = -1;
					rn.speed = 0.0;
					rn.speed_y = 0.0;
					rn.distance_taken = 0.0;
					rn.posrel[2] = { -0.9, -0.9 };
					rn.plrrot = 0.0;

					rn.playersiz_rel[2] = { 0.0, 0.0 };
					rn.blocksize_rel[2] = { 0.0, 0.0 };
					rn.colided = false;
					rn.cases_times_mult = 0.0;

					rn.time_final[2] = { 0.0 };
					rn.final_score = 0.0;

					rn.min_dist[9][2];
					rn.min_dist_used[9] = { false };
					rn.fixed_distance = 1.0;*/					

					std::thread thr(_thr_temp_generatemap,&map, level, &rn.needed_reset, &rn.being_made, &rn.playin);
					data.if_playin = &rn;
									
					if (data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST) == ALLEGRO_KEY_F3) rn.debug = -1;


					log = data.data_control.get(LSW_BMP_LOGO);
					vig = data.data_control.get(LSW_BMP_VIGNETTE);
					blk = data.data_control.get(LSW_BMP_BLOCK);
					enb = data.data_control.get(LSW_BMP_BLOCK_END);
					mbl = data.data_control.get(LSW_BMP_MENU_BLOCK);
					sav = data.data_control.get(LSW_BMP_SAVING_SCORE);
					for (int p = 0; p < 3; p++) plr[p] = data.data_control.get((images_available)(p + LSW_BMP_PERSON));

					font = data.data_control.get(LSW_FONT_DEJAVUSANS);

					//y_offset = (56.0 / getBitmapWidth(blk)) / base_res[1];
					rn.playersiz_rel[0] = (getBitmapWidth(plr[0]) * 1.0 / base_res[0]) * 0.9;
					rn.playersiz_rel[1] = (getBitmapHeight(plr[0]) * 1.0 / base_res[1]) * 0.9;
					rn.blocksize_rel[0] = getBitmapWidth(blk) * 1.0 / base_res[0];
					rn.blocksize_rel[1] = getBitmapHeight(blk) * 1.0 / base_res[1];
					multiplier(); // reset for animation
					multiply = 0.0;

					rn.collision_controller = new std::thread(_thr_collisionwork_ext, &rn, this);

					if (infinite_map) map2.init();

					rn.time_final[0] = getTime();

					while (rn.playin)
					{
						rn.change_oneanother.lock();
						rn.beingusedby = 0;

						//gr = rn; // copies pos and values to draw;
						
						/* * * * * * * PRE CASES * * * * * * */
						{
							multiply = multiplier();

							if (gr.needed_reset > 0)
							{
								gr.needed_reset = 0;
								gr.posrel[0] = gr.posrel[1] = -0.9;
							}
							if (clock() - gr.now > CLOCKS_PER_SEC / 4) {
								gr.now += CLOCKS_PER_SEC / 4;
								gr.nowFps = lastFPS();
								gr.nowMult = multiply;
							}
							if (gr.paused)
							{
								clearTo(color(0, 0, 0));
								double before_pause = getTime();
								int got = pauseScreenGame();

								clearTo(color(0, 0, 0));
								gr.time_final[0] += getTime() - before_pause;

								multiplier();
								if (got == 1) {
									gr.playin = false;
									gr.save_score = false;
									gr.paused = false;

									//rn = gr;
									rn.beingusedby = -1;
									rn.change_oneanother.unlock();
									rn.collision_controller->join();
									delete rn.collision_controller;
									rn.collision_controller = nullptr;

									data.now = LSW_S_MENU;
									continue;
								}
								else if (got == 2)
								{
									gr.playin = false;
									gr.save_score = true;
									gr.paused = false;
									gr.distance_taken = -1.0;

									//rn = gr;
									rn.beingusedby = -1;
									rn.change_oneanother.unlock();
									rn.collision_controller->join();
									delete rn.collision_controller;
									rn.collision_controller = nullptr;
									continue;
								}
								else {
									gr.paused = false;
								}
							}
						}

						
						//rn = gr;
						if (data.if_playin->beingusedby == 0) {
							data.if_playin->change_oneanother.try_lock();
							data.if_playin->change_oneanother.unlock();
						}

						/* * * * * * * DRAWNING * * * * * * */
						{
							if (data.display_mode_draw == 0) clearTo(color(0.5*sin(getTime()*0.33) + 0.5, 0.5*cos(getTime()*0.54) + 0.5, -0.5*sin(getTime()*0.215) + 0.5));
							else if (data.display_mode_draw == 1) clearTo(color(0, 0, 0));

							for (int py = (gr.campos[1] * 4.21875) - 1; py < 9 + (gr.campos[1] * 4.21875); py++)
							{
								for (int px = (gr.campos[0] * 7.5) - 1; px < 15 + (gr.campos[0] * 7.5); px++)
								{
									double xx, yy;
									xx = (px * (gr.blocksize_rel[0]) - 0.5) * 2.0 - gr.campos[0];
									yy = (py * (gr.blocksize_rel[1]) - 0.5) * 2.0 - gr.campos[1];

									int mapread = 0;
									if (!infinite_map) mapread = map.readpos(px, py);
									else mapread = map2.readpos(px, py);

									if (mapread > 0 && data.display_mode_draw == 2) {
										drawIt(mbl, xx, yy, 0.0, 2.0, 2.0, -1.0, 0.0, 0.0,color(data.color_blend.r*0.2, data.color_blend.g*0.2, data.color_blend.b*0.2, data.color_blend.a*0.2),true);
									}
									if (mapread <= 0) {

										if (level >= 2 && !gr.asked_for_help)
										{
											if (fabs((gr.posrel[0] - gr.campos[0]) - (xx + gr.blocksize_rel[0])) <= gr.fixed_distance * 3.5 && (fabs((gr.posrel[1] - gr.campos[1]) - (yy + gr.blocksize_rel[1])) <= gr.fixed_distance * 3.5))
												drawIt(blk, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
										}
										else drawIt(blk, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
									}
									else if (!infinite_map && px == map.getSiz(LSW_SIZ_X) - 1)	drawIt(enb, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);
									else if (gr.asked_for_help && mapread == LSW_VISITADO)			drawIt(mbl, xx, yy, 0.0, 2.0, 2.0, -1.0, 0.0, 0.0);

									if (gr.debug > 0) drawText(font, color(0, 0, 0), (xx*0.5 + 0.5)*data.usedx, (yy*0.5 + 0.5)*data.usedy, ALLEGRO_ALIGN_CENTER, "%d;%d", px, py);
								}
							}

							drawIt(plr[((gr.way >= 0) ? (1 + (int)(2.0*getTime()) % 2) : 0)], gr.posrel[0] - gr.campos[0], gr.posrel[1] - gr.campos[1], gr.plrrot, 1.0, 1.0, ((gr.debug > 0) ? 2.0 : -1.0), -1, -1, (gr.colided ? color(1, 0, 0) : color(0, 1, 0)));

							if (level >= 2 && !gr.asked_for_help) drawCircle(gr.posrel[0] - gr.campos[0], gr.posrel[1] - gr.campos[1], (1.5 + sin(getTime())*0.5 - gr.speed * 7.0)*100.0);

							if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f TPS: %.3f P: %.3fx%.3f / %.3fx%.3f (R); S: %.2fE-3, Sy: %.4fE-3; R: %.2f | CP [%.2f;%.2f] | K: %d | T: %04.1f", gr.nowFps, gr.collision_tps, gr.posrel[0], gr.posrel[1], gr.cammult[0], gr.cammult[1], gr.speed*1000.0, gr.speed_y*1000.0, gr.plrrot, gr.campos[0], gr.campos[1], data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST), gr.distance_taken);
							
							if (data.display_mode_draw == 2) drawIt(vig, 0.0, 0.0, 0, 1.0, 1.0, -1.0, -1.0, -1.0, data.color_blend, true);
							else drawIt(vig, 0.0, 0.0, 0);
							flip();
						}
					}

					// MUST END THREAD COLLISION HERE
					if (rn.collision_controller) {
						rn.collision_controller->join();
						delete rn.collision_controller;
						rn.collision_controller = nullptr;
					}
					//gr = rn;

					gr.time_final[1] = getTime();
					gr.final_score = gr.distance_taken;

					while (!rn.being_made)
					{
						multiply = multiplier();
						bganim(multiply);

						drawIt(plr[((gr.way >= 0) ? (1 + (int)(2.0*getTime()) % 2) : 0)], gr.posrel[0] - gr.campos[0], gr.posrel[1] - gr.campos[1], gr.plrrot, 1.0, 1.0, ((gr.debug > 0) ? 2.0 : -1.0), -1, -1, (gr.colided ? color(1, 0, 0) : color(0, 1, 0)));

						if (data.display_mode_draw == 2) drawIt(vig, 0.0, 0.0, 0, 1.0, 1.0, -1.0, -1.0, -1.0, data.color_blend, true);
						else drawIt(vig, 0.0, 0.0, 0);
						flip();
					}

					if (gr.save_score) // if infinite_map it will never go here
					{
						for (clock_t now = clock(); clock() - now < CLOCKS_PER_SEC * 4.0;) {
							multiply = multiplier() * 0.3;

							clearTo(color(0.5*sin(getTime()*0.33) + 0.5, 0.5*cos(getTime()*0.54) + 0.5, -0.5*sin(getTime()*0.215) + 0.5));

							for (int py = (gr.campos[1] * 4.21875) - 1; py < 9 + (gr.campos[1] * 4.21875); py++)
							{
								for (int px = (gr.campos[0] * 7.5) - 1; px < 15 + (gr.campos[0] * 7.5); px++)
								{
									double xx, yy;
									xx = (px * (gr.blocksize_rel[0]) - 0.5) * 2.0 - gr.campos[0];
									yy = (py * (gr.blocksize_rel[1]) - 0.5) * 2.0 - gr.campos[1];

									if (map.readpos(px, py) <= 0) {

										drawIt(blk, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);

									}
									else if (px == map.getSiz(LSW_SIZ_X) - 1) drawIt(enb, xx, yy, 0.0, 1.0, 1.0, -1.0, 0.0, 0.0);

									if (gr.debug > 0) drawText(font, color(0, 0, 0), (xx*0.5 + 0.5)*data.usedx, (yy*0.5 + 0.5)*data.usedy, ALLEGRO_ALIGN_CENTER, "%d;%d", px, py);
								}
							}
							

							gr.speed -= (gr.speed * 0.14)*multiply;
							//if (speed > 0.1) speed = 0.1;

							while (gr.plrrot > 360.0)
								gr.plrrot -= 360.0;
							while (gr.plrrot < 0.0)
								gr.plrrot += 360.0;

							double pi_r = ALLEGRO_PI * gr.plrrot / 180.0; // 0 means down
							gr.posrel[0] += multiply * gr.speed * (sin(pi_r));
							gr.posrel[1] += multiply * gr.speed * (-cos(pi_r));

							if (gr.posrel[0] - gr.campos[0] > 1.0) gr.posrel[0] = 1.0 + gr.campos[0];
							if (gr.posrel[0] - gr.campos[0] < -1.0) gr.posrel[0] = -1.0 + gr.campos[0];
							if (gr.posrel[1] - gr.campos[1] > 1.0) gr.posrel[1] = 1.0 + gr.campos[1];
							if (gr.posrel[1] - gr.campos[1] < -1.0) gr.posrel[1] = -1.0 + gr.campos[1];

							drawIt(plr[((gr.way >= 0) ? (1 + (int)(2.0*getTime()) % 2) : 0)], gr.posrel[0] - gr.campos[0], gr.posrel[1] - gr.campos[1], gr.plrrot, 1.0, 1.0, ((gr.debug > 0) ? 2.0 : -1.0), -1, -1, (gr.colided ? color(1, 0, 0) : color(0, 1, 0)));

							if (data.display_mode_draw == 2) drawIt(vig, 0.0, 0.0, 0, 1.0, 1.0,-1.0, -1.0, -1.0, data.color_blend, true);
							else drawIt(vig, 0.0, 0.0, 0);
							
							flip();
						}

						lsw_texture rec_back;
						FILE* fp = nullptr;
						clock_t now = clock() - CLOCKS_PER_SEC / 4;
						double nowFps = 0.0, nowMult = multiply;
						bool choosing = true;

						double real_final_score = sqrt(gr.final_score) * 0.01 * (gr.time_final[1] - gr.time_final[0]);

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
							clearTo(color(0, 0, 0));
							bganim(multiply);
							drawIt(log, (pos + 0.02)*0.8, -0.5, 0);

							if (clock() - now > CLOCKS_PER_SEC / 4) {
								now += CLOCKS_PER_SEC / 4;
								nowFps = lastFPS();
								nowMult = multiply;
							}

							drawIt(rec_back, pos + 0.02, 0.1, 0);

							if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
							if (data.display_mode_draw == 2) drawIt(vig, 0.0, 0.0, 0, 1.0, 1.0, -1.0, -1.0, -1.0, data.color_blend, true);
							else drawIt(vig, 0.0, 0.0, 0);
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

							clearTo(color(0, 0, 0));
							bganim(multiply);
							drawIt(log, 0.0, -0.5, 0);

							drawIt(rec_back, 0.0, 0.1, 0);

							drawText(font, color(1, 1, 0), 0.5*data.usedx, (0.59)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", ((hisname.length() >= 50) ? hisname.c_str() : ((int)(2.0*getTime())%2 ? hisname.c_str() : (hisname + '_').c_str())));
							drawText(font, color(1, 1, 0), 0.5*data.usedx, (0.78)*data.usedy, ALLEGRO_ALIGN_CENTER, "%.6f points (%.2f s, %.1f m)", real_final_score, gr.time_final[1] - gr.time_final[0], gr.distance_taken);

							if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f", nowFps, nowMult);
							if (data.display_mode_draw == 2) drawIt(vig, 0.0, 0.0, 0, 1.0, 1.0, -1.0, -1.0, -1.0, data.color_blend, true);
							else drawIt(vig, 0.0, 0.0, 0);
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

							clearTo(color(0, 0, 0));
							bganim(multiply);
							drawIt(log, (pos - 0.02)*0.8, -0.5, 0);

							drawIt(rec_back, pos - 0.02, 0.1, 0);

							drawText(font, color(1, 1, 0), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.59)*data.usedy, ALLEGRO_ALIGN_CENTER, "%s", hisname.c_str());
							drawText(font, color(1, 1, 0), ((pos - 0.02) + 1.0)*0.5*data.usedx, (0.78)*data.usedy, ALLEGRO_ALIGN_CENTER, "%.6f points (%.2f s, %.1f m)", real_final_score, gr.time_final[1] - gr.time_final[0], gr.distance_taken);

							if (is_debug) drawText(font, color(1, 1, 0), 1, 1, 0, "FPS: %.2f | TIMEMULTIPLY: %.3f | POSRN: %.4f", nowFps, nowMult, pos);
							if (data.display_mode_draw == 2) drawIt(vig, 0.0, 0.0, 0, 1.0, 1.0, -1.0, -1.0, -1.0, data.color_blend, true);
							else drawIt(vig, 0.0, 0.0, 0);
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
			return 0;
		}

		void displayer::drawIt(lsw_texture chosen, const double pos_related_x, const double pos_related_y, const double rotation, const double scale_x, const double scale_y, const double hasboxthing, double pos_center_bitmap_x, double pos_center_bitmap_y, const lsw_color color, const bool blend, const int used_x_p, const int used_y_p)
		{
			if (!chosen) return;
			float _scale_x, _scale_y;
			_scale_x = (1.0f*data.usedx / base_res[0]) * scale_x;
			_scale_y = (1.0f*data.usedy / base_res[1]) * scale_y;
			if (_scale_x == 0) _scale_x = 1.0;
			if (_scale_y == 0) _scale_y = 1.0;
			int sx_b = getBitmapWidth(chosen);
			int sy_b = getBitmapHeight(chosen);
			if (pos_center_bitmap_x < 0.0 || pos_center_bitmap_y < 0.0)
			{
				pos_center_bitmap_x = (1.0 * sx_b / 2.0);
				pos_center_bitmap_y = (1.0 * sy_b / 2.0);
			}
			float var1, var2; // posx, posy
			if (used_x_p > 0 && used_y_p > 0)
			{
				var1 = 1.0 * used_x_p * ((pos_related_x + 1.0) / 2.0);
				var2 = 1.0 * used_y_p * ((pos_related_y + 1.0) / 2.0);
			}
			else {
				var1 = 1.0 * data.usedx * ((pos_related_x + 1.0) / 2.0);
				var2 = 1.0 * data.usedy * ((pos_related_y + 1.0) / 2.0);
			}

			if (!blend) {
				drawBitmap(chosen,
					pos_center_bitmap_x,
					pos_center_bitmap_y,
					var1,
					var2,
					_scale_x,
					_scale_y,
					(rotation / 180.0)*ALLEGRO_PI,
					0);
			}
			if (hasboxthing > 0.0)
			{
				double box_x1 = var1 - pos_center_bitmap_x * _scale_x;
				double box_y1 = var2 - pos_center_bitmap_y * _scale_y;
				double box_x2 = var1 + pos_center_bitmap_x * _scale_x;
				double box_y2 = var2 + pos_center_bitmap_y * _scale_y;
				al_draw_rectangle(box_x1, box_y1, box_x2, box_y2, color, hasboxthing*sqrt(_scale_x*_scale_y));
			}
			else if (blend) {
				drawBitmap(chosen, color,
					pos_center_bitmap_x,
					pos_center_bitmap_y,
					var1,
					var2,
					_scale_x,
					_scale_y,
					(rotation / 180.0)*ALLEGRO_PI,
					0);
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

			//al_draw_ellipse(realposx, realposy, _scale_x, _scale_y, color(0,0,0), 5.0);

			defineOut(data.transparency);

			al_draw_filled_rectangle(0, 0, getBitmapWidth(data.transparency), getBitmapHeight(data.transparency), color(0, 0, 0));

			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

			for (double u = 1.0; u >= 0.5; u -= 0.02)
			{
				al_draw_filled_ellipse(realposx, realposy, _scale_x * u, _scale_y * u, color(0.0, 0.0, 0.0, 2.0*(u - 0.5)));
			}

			al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

			fixLoad();

			drawIt(data.transparency, 0, 0, 0, 0.0, 0.0);// , -1, -1, -1, -1, -1, color(1, 0, 0), false, getDisplayWidth(data.display), getDisplayHeight(data.display));
			//al_draw_bitmap(data.transparency, 0, 0, 0);
		}
		void displayer::bganim(const double mult)
		{
			double calc = (1.0 * data.usedx / base_res[0]);
			lsw_texture blk;
			blk = data.data_control.get(LSW_BMP_MENU_BLOCK);
			int blk_siz = calc * getBitmapWidth(blk);

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
			lsw_texture pause_anim[30] = { nullptr };
			lsw_texture vig;
			lsw_texture options[2];

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
				
				int key = 0;
				/*if (!data.if_playin) */key = data.evm.getLastKeyIfAvailable();
				//else key = data.if_playin->key;

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

				clearTo(color(0, 0, (times_shift_hack * 10.0)/255.0));

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

		void displayer::_thr_collision_work(gameplay_needs& gr)
		{
			gr.change_oneanother.lock();
			gr.beingusedby = 1;

			double multiply = (1.0 / gr.collision_tps) * 60.0;
			
			{
				gr.colided = false;
				gr.fixed_distance = sqrt(gr.blocksize_rel[0] * gr.blocksize_rel[0] + gr.blocksize_rel[1] * gr.blocksize_rel[1])*1.44;
				for (int t = 0; t < 9; t++) { gr.min_dist[t][0] = gr.fixed_distance; gr.min_dist[t][1] = gr.fixed_distance; }

				gr.key = data.evm.getLastKeyIfAvailable(LSW_KEYPRESSED);
				gr.keykeep = data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST);
				gr.keylost = data.evm.getLastKeyIfAvailable(LSW_KEYLEFT);


				/* * * * * * * KEYBOARD * * * * * * */
				{
					if (gr.debug == -1) {
						if (data.evm.getLastKeyIfAvailable(LSW_KEYKEEP_LAST) != ALLEGRO_KEY_F3) gr.debug = 0;
						else gr.debug = 1;
					}

					switch (gr.keykeep)
					{
					case ALLEGRO_KEY_ESCAPE:
						gr.paused = true;
						break;
					case ALLEGRO_KEY_F1:
						gr.asked_for_help = true;
						break;
					case ALLEGRO_KEY_UP: case ALLEGRO_KEY_W:
						gr.way = 0;
						break;
					case ALLEGRO_KEY_LEFT: case ALLEGRO_KEY_A:
						gr.way = 2;
						break;
					case ALLEGRO_KEY_DOWN: case ALLEGRO_KEY_S:
						gr.way = 1;
						break;
					case ALLEGRO_KEY_RIGHT: case ALLEGRO_KEY_D:
						gr.way = 3;
						break;
					case -1:
						gr.way = -1;
					}

					if (enabled_alternative_mode)
					{
						switch (gr.keykeep)
						{
						case ALLEGRO_KEY_UP: case ALLEGRO_KEY_W:
							gr.alternative_way[0] = true;
							break;
						case ALLEGRO_KEY_LEFT: case ALLEGRO_KEY_A:
							gr.alternative_way[2] = true;
							break;
						case ALLEGRO_KEY_DOWN: case ALLEGRO_KEY_S:
							gr.alternative_way[1] = true;
							break;
						case ALLEGRO_KEY_RIGHT: case ALLEGRO_KEY_D:
							gr.alternative_way[3] = true;
							break;
						}
						switch (gr.keylost)
						{
						case ALLEGRO_KEY_UP: case ALLEGRO_KEY_W:
							gr.alternative_way[0] = false;
							break;
						case ALLEGRO_KEY_LEFT: case ALLEGRO_KEY_A:
							gr.alternative_way[2] = false;
							break;
						case ALLEGRO_KEY_DOWN: case ALLEGRO_KEY_S:
							gr.alternative_way[1] = false;
							break;
						case ALLEGRO_KEY_RIGHT: case ALLEGRO_KEY_D:
							gr.alternative_way[3] = false;
							break;
						}
					}
				}

				/* * * * * * * MOVEMENT * * * * * * */ // TRANSFORM INTO A THREAD!
				gr.cammult[0] = (gr.posrel[0] - gr.campos[0]);
				gr.cammult[1] = (gr.posrel[1] - gr.campos[1]);
				if (!gr.asked_for_help) { // set limits if not helping
					if (gr.cammult[0] > 0.5)
					{
						gr.campos[0] += (gr.cammult[0] - 0.5) * 0.07 * multiply;
					}
					if (gr.cammult[0] < -0.5)
					{
						gr.campos[0] += (gr.cammult[0] + 0.5) * 0.07 * multiply;
					}
					if (gr.cammult[1] > 0.5)
					{
						gr.campos[1] += (gr.cammult[1] - 0.5) * 0.07 * multiply;
					}
					if (gr.cammult[1] < -0.5)
					{
						gr.campos[1] += (gr.cammult[1] + 0.5) * 0.07 * multiply;
					}
				}

				if (enabled_alternative_mode) gr.speed_y += fabs(0.0001 + 0.05*gr.speed_y)*multiply;


				/* * * * * * * COLLISION & POS UPDATE * * * * * * */
				for (int py = (gr.campos[1] * 4.21875) - 1; py < 9 + (gr.campos[1] * 4.21875); py++)
				{
					for (int px = (gr.campos[0] * 7.5) - 1; px < 15 + (gr.campos[0] * 7.5); px++)
					{
						double xx, yy;
						xx = (px * (gr.blocksize_rel[0]) - 0.5) * 2.0 - gr.campos[0];
						yy = (py * (gr.blocksize_rel[1]) - 0.5) * 2.0 - gr.campos[1];

						int mapread = 0;
						if (!infinite_map) mapread = gr.map->readpos(px, py);
						else mapread = gr.map2->readpos(px, py);

						if (mapread <= 0 && !gr.asked_for_help) {
							for (int t = 0; t < 9; t++) {
								if (fabs((gr.posrel[0] - gr.campos[0]) - (xx + gr.blocksize_rel[0])) <= gr.min_dist[t][0] &&
									(fabs((gr.posrel[1] - gr.campos[1]) - (yy + gr.blocksize_rel[1])) <= gr.min_dist[t][1]))
								{
									gr.min_dist_used[t] = true;
									gr.min_dist[t][0] = (gr.posrel[0] - gr.campos[0]) - (xx + gr.blocksize_rel[0]);
									gr.min_dist[t][1] = (gr.posrel[1] - gr.campos[1]) - (yy + gr.blocksize_rel[1]);
									if (gr.debug > 0)
									{
										int t2 = t;
										float cx, cy, r;
										ALLEGRO_COLOR c;
										cx = ((gr.posrel[0] - gr.campos[0] - gr.min_dist[t2][0])*0.5 + 0.5) * data.usedx;
										cy = ((gr.posrel[1] - gr.campos[1] - gr.min_dist[t2][1])*0.5 + 0.5) * data.usedy;
										r = 50.0;
										c = color(1, 0, 1);
										al_draw_filled_circle(cx, cy, r, c);
									}
									t = 9;

								}
							}
						}
					}
				}
				for (int t = 0; t < 9 && !gr.asked_for_help; t++) {
					if (gr.min_dist_used[t]) {

						if (enabled_alternative_mode) {
							if (fabs(gr.min_dist[t][0]) < gr.blocksize_rel[0] + gr.playersiz_rel[0] * 0.9 &&
								fabs(gr.min_dist[t][1]) < gr.blocksize_rel[1] + gr.playersiz_rel[1] * 0.9)
							{
								gr.speed_y = 0.0;
							}
						}
						if (fabs(gr.min_dist[t][0]) < gr.blocksize_rel[0] + gr.playersiz_rel[0] * 0.6 &&
							fabs(gr.min_dist[t][1]) < gr.blocksize_rel[1] + gr.playersiz_rel[1] * 0.6) // collision
						{
							gr.colided = true;
							if (gr.debug > 0) al_draw_filled_circle(((gr.posrel[0] - gr.campos[0] - gr.min_dist[t][0])*0.5 + 0.5) * data.usedx, ((gr.posrel[1] - gr.campos[1] - gr.min_dist[t][1])*0.5 + 0.5) * data.usedy, 27.0, color(1, 0, 0));

							double dx = gr.min_dist[t][0]; // player pos - block pos
							double dy = gr.min_dist[t][1]; // player pos - block pos
							double to_rot = 0.0;

							dx /= 1.0 * (gr.blocksize_rel[0] + gr.playersiz_rel[0] * 0.6); // 0 to 1
							dy /= 1.0 * (gr.blocksize_rel[1] + gr.playersiz_rel[1] * 0.6); // 0 to 1

							double draw_ref[2];
							draw_ref[0] = ((gr.posrel[0] - gr.campos[0] - gr.min_dist[t][0])*0.5 + 0.5) * data.usedx;
							draw_ref[1] = ((gr.posrel[1] - gr.campos[1] - gr.min_dist[t][1])*0.5 + 0.5) * data.usedy;

							assistance_nsew where_to_tp_plr = _whereToTp(dx, dy);

							switch (where_to_tp_plr)
							{
							case LSW_P_NORTH:
								to_rot = 180.0;
								/*if (gr.debug > 0)
								{
									al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0], draw_ref[1] - 0.1 * data.usedy, al_map_rgb(175, 175, 175), 4.0);
									drawText(font, color(1, 1, 0), draw_ref[0], draw_ref[1] - 0.13 * data.usedy, ALLEGRO_ALIGN_CENTER, "NORTH");
									drawText(font, color(1, 1, 0), draw_ref[0], draw_ref[1] - 0.1 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
								}*/
								break;
							case LSW_P_SOUTH:
								to_rot = 0.0;
								/*if (gr.debug > 0)
								{
									al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0], draw_ref[1] + 0.1 * data.usedy, al_map_rgb(175, 175, 175), 4.0);
									drawText(font, color(1, 1, 0), draw_ref[0], draw_ref[1] + 0.13 * data.usedy, ALLEGRO_ALIGN_CENTER, "SOUTH");
									drawText(font, color(1, 1, 0), draw_ref[0], draw_ref[1] + 0.1 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
								}*/
								break;
							case LSW_P_WEST:
								to_rot = 90.0;
								/*if (gr.debug > 0)
								{
									al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0] - 0.1 * data.usedx, draw_ref[1], al_map_rgb(175, 175, 175), 4.0);
									drawText(font, color(1, 1, 0), draw_ref[0] - 0.1 * data.usedx, draw_ref[1], ALLEGRO_ALIGN_CENTER, "WEST");
									drawText(font, color(1, 1, 0), draw_ref[0] - 0.1 * data.usedx, draw_ref[1] + 0.03 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
								}*/
								break;
							case LSW_P_EAST:
								to_rot = 270.0;
								/*if (gr.debug > 0)
								{
									al_draw_line(draw_ref[0], draw_ref[1], draw_ref[0] + 0.1 * data.usedx, draw_ref[1], al_map_rgb(175, 175, 175), 4.0);
									drawText(font, color(1, 1, 0), draw_ref[0] + 0.1 * data.usedx, draw_ref[1], ALLEGRO_ALIGN_CENTER, "EAST");
									drawText(font, color(1, 1, 0), draw_ref[0] + 0.1 * data.usedx, draw_ref[1] + 0.03 * data.usedy, ALLEGRO_ALIGN_CENTER, "%.3f;%.3f", dx, dy);
								}*/
								break;
							}

							if (gr.speed < 0.004) gr.speed = 0.004;

							if (fabs(gr.min_dist[t][0]) < gr.blocksize_rel[0] + gr.playersiz_rel[0] * 0.4 &&
								fabs(gr.min_dist[t][1]) < gr.blocksize_rel[1] + gr.playersiz_rel[1] * 0.4)
							{
								gr.plrrot = to_rot;
							}
							gr.speed = -fabs(gr.speed * 0.3);
						}
					}
				}
				gr.speed -= (gr.speed * 0.03) * multiply;
				if (gr.speed > 0.07) gr.speed = 0.07;
				if (gr.speed < -0.02) gr.speed = -0.02;

				if (gr.speed_y > 0.03) gr.speed_y = 0.03;

				while (gr.plrrot > 360.0)
					gr.plrrot -= 360.0;
				while (gr.plrrot < 0.0)
					gr.plrrot += 360.0;

				if (!gr.asked_for_help) { // if playing, so correction of ang w movement

					if (enabled_alternative_mode) {

						if (gr.alternative_way[0]) { // north
							double coss = cos(ALLEGRO_PI * gr.plrrot / 180.0);
							gr.speed += fabs(0.00012 + 0.04*gr.speed)*multiply;
							if (coss > 0.0) gr.speed_y *= 0.95 * coss;
							gr.way = 5;
						}
						if (gr.alternative_way[1]) { // south
							gr.speed -= (gr.speed * 0.03) * multiply;
							gr.way = 5;
						}
						if (gr.alternative_way[2]) { // east
							gr.plrrot -= multiply * 0.01 / (fabs(gr.speed) + 0.001);
							gr.way = 5;
						}
						if (gr.alternative_way[3]) { // west
							gr.plrrot += multiply * 0.01 / (fabs(gr.speed) + 0.001);
							gr.way = 5;
						}

						if (gr.speed_y > 0.0 && gr.way != 5)
						{
							double usedhere;

							if (gr.speed < 0.0) usedhere = gr.speed_y;
							else usedhere = gr.speed_y - gr.speed;

							if (gr.plrrot < 180.0) gr.plrrot += usedhere * ((180.0 - gr.plrrot) / 2.0)*2.0*multiply;
							else gr.plrrot -= usedhere * 2.0*((gr.plrrot - 180.0) / 6.0)*multiply;
						}
					}
					else {
						if (gr.way >= 0)
							gr.speed += fabs(0.00012 + 0.08*gr.speed)*multiply;

						switch (gr.way)
						{
						case 0: // north
							if (gr.plrrot < 180.0) gr.plrrot -= ((gr.plrrot) / 2.0)*0.3*multiply;
							else gr.plrrot += ((360.0 - gr.plrrot) / 6.0)*multiply;
							break;
						case 1: // south
							if (gr.plrrot < 180.0) gr.plrrot += ((180.0 - gr.plrrot) / 2.0)*0.3*multiply;
							else gr.plrrot -= ((gr.plrrot - 180.0) / 6.0)*multiply;
							break;
						case 2: // east
							if (gr.plrrot < 90.0) gr.plrrot -= ((270.0 - gr.plrrot) / 6.0)*0.3*multiply;
							else gr.plrrot += ((270.0 - gr.plrrot) / 6.0)*multiply;
							break;
						case 3: // west
							if (gr.plrrot > 270.0) gr.plrrot -= ((90.0 - gr.plrrot) / 6.0)*0.3*multiply;
							else gr.plrrot += ((90.0 - gr.plrrot) / 6.0)*multiply;
							break;
						}
					}

					double pi_r = ALLEGRO_PI * gr.plrrot / 180.0; // 0 means down
					gr.posrel[0] += multiply * gr.speed * (sin(pi_r));
					gr.posrel[1] += multiply * gr.speed * (-cos(pi_r));
					if (enabled_alternative_mode && !gr.asked_for_help) gr.posrel[1] += gr.speed_y * multiply;

					if (gr.posrel[0] - gr.campos[0] > 1.0) gr.posrel[0] = 1.0 + gr.campos[0];
					if (gr.posrel[0] - gr.campos[0] < -1.0) gr.posrel[0] = -1.0 + gr.campos[0];
					if (gr.posrel[1] - gr.campos[1] > 1.0) gr.posrel[1] = 1.0 + gr.campos[1];
					if (gr.posrel[1] - gr.campos[1] < -1.0) gr.posrel[1] = -1.0 + gr.campos[1];

					gr.distance_taken += (fabs(gr.speed) + fabs(gr.speed_y)*cos(pi_r + ALLEGRO_PI)) * 0.05 / multiply;
				}
				else {
					if (gr.way >= 0) {
						gr.way_cam = gr.way;
						gr.speed += fabs(0.00015 + 0.08*gr.speed)*multiply;
					}
					switch (gr.way_cam)
					{
					case 0:
						gr.campos[1] -= multiply * gr.speed * 0.5;
						break;
					case 1:
						gr.campos[1] += multiply * gr.speed * 0.5;
						break;
					case 2:
						gr.campos[0] -= multiply * gr.speed * 0.5;
						break;
					case 3:
						gr.campos[0] += multiply * gr.speed * 0.5;
						break;
					}
				}
				int plrx = 1 + (15.0 * (1.0 * gr.posrel[0] - gr.blocksize_rel[0] * 2.0 + 1.0) / 2.0);
				//int plry = 1 + (8.4375 * (1.0 *  posrel[1] - blocksize_rel[1] * 2.0 + 1.0) / 2.0);

				if (!infinite_map && plrx == gr.map->getSiz(LSW_SIZ_X) - 1)
				{
					gr.playin = false;
					gr.save_score = true;
				}
			}

			gr.beingusedby = -1;
			gr.change_oneanother.unlock();
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
		void displayer::fixFPS(const double antes, const double agora, const double fps_max)
		{
			if (agora - antes < 1.0 / fps_max && ((1.0 / fps_max) - (agora - antes)) > 0.0)
			{
				restFor((1.0 / fps_max) - (agora - antes));
			}
		}
		const bool displayer::loadModes(const int modes)
		{
			data.modes.modes.clear();

			int nva = al_get_num_video_adapters();
			if (nva < 1) return false;

			al_set_new_display_flags(modes);
			int num_modes = al_get_num_display_modes();
			for (int j = 0; j < num_modes; ++j) {
				ALLEGRO_DISPLAY_MODE admode;
				if (al_get_display_mode(j, &admode) == &admode) {
					lsw_mode mod;
					mod.x = admode.width;
					mod.y = admode.height;
					mod.hz = admode.refresh_rate;
					bool push = true;
					for (auto& i : data.modes.modes) {
						if (mod.x == i.x && mod.y == i.y && mod.hz == i.hz) {
							push = false;
							break;
						}
					}
					if (push) data.modes.modes.push_back(mod);

				}
			}
			return true;
		}
		const bool displayer::init()
		{
			if (data.loaded) return true;
			data.muu.lock();

			int flags = (isFullscreen ? ALLEGRO_FULLSCREEN : (ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE)) | ALLEGRO_OPENGL;

			int assistance = 0;
			lsw_mode mode_selected;
			//data.modes.using_rn = 0;

			if (data.modes.modes.size() == 0)
			{
				if (!loadModes(flags)) return false;
				if (data.modes.modes.size() == 0) return false;


				for (auto& i : data.modes.modes)
				{
					if ((i.x > mode_selected.x || i.y > mode_selected.y) || (i.x == mode_selected.x && i.y == mode_selected.y && i.hz > mode_selected.hz))
					{
						mode_selected = i;
						data.modes.using_rn = assistance;
					}
					assistance++;
				}
			}
			else {
				mode_selected = data.modes.modes[data.modes.using_rn];
			}
			data.full_a[0] = mode_selected.x;
			data.full_a[1] = mode_selected.y;

			al_set_new_display_option(ALLEGRO_AUTO_CONVERT_BITMAPS, 1, ALLEGRO_DONTCARE);
			al_set_new_display_flags(flags);
			al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_SUGGEST);
			al_set_new_display_refresh_rate(mode_selected.hz);

			if (data.usedx < 16 || data.usedy < 9) {
				data.usedx = 1280;
				data.usedy = 720;
			}
			if (!isFullscreen)
			{
				data.full_a[0] = data.usedx;
				data.full_a[1] = data.usedy;
			}

			data.display = createDisplay(data.full_a[0], data.full_a[1]);
			if (!data.display) {
				data.muu.unlock();
				throw "FAILED CREATING DISPLAY!";
				return false;
			}
			al_hide_mouse_cursor(data.display);

			al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP);
			al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR);
			al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR);

			data.usedx = data.full_a[0];
			data.usedy = data.full_a[1];

			fixProportion(data.usedx, data.usedy);

			data.buffer = createTexture(data.usedx, data.usedy);
			if (!data.buffer) {
				freeUp(data.display);
				freeUp(data.buffer);
				data.muu.unlock();
				throw "FAILED CREATING DISPLAY!";
				return false;
			}
			data.transparency = createTexture(data.usedx, data.usedy);
			if (!data.transparency) {
				freeUp(data.display);
				data.muu.unlock();
				throw "FAILED CREATING DISPLAY!";
				return false;
			}

			if (data.data_control.load(LSW_BMP_ICON)) al_set_display_icon(data.display, data.data_control.get(LSW_BMP_ICON));

			data.prop[0] = 1.0 * getDisplayWidth(data.display) / base_res[0];
			data.prop[1] = 1.0 * getDisplayHeight(data.display) / base_res[1];

			float temp_siz_font = 1.0*sqrt(data.usedx*data.usedy)*28.8 / sqrt(base_res[0] * base_res[1]);
			if (!data.data_control.load(LSW_FONT_DEJAVUSANS, temp_siz_font))
			{
				freeUp(data.display);
				freeUp(data.buffer);
				freeUp(data.transparency);
				data.data_control.unloadAll();
				data.data_control.clearAll();
				data.muu.unlock();
				throw "FAILED LOADING FONT!";
				return false;
			}

			data.ev_qu = al_create_event_queue();
			if (!data.ev_qu) {
				freeUp(data.display);
				freeUp(data.buffer);
				freeUp(data.transparency);
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
				freeUp(data.ev_qu);
				freeUp(data.buffer);
				freeUp(data.transparency);
				freeUp(data.display);
				data.data_control.clearAll();
				data.muu.unlock();
				throw "FAILED CREATING KEYBOARD THREAD!";
				return false;
			}
			data.lastC = GetTickCount64();

			defineOut(data.buffer);
			data.loaded = true;
			data.muu.unlock();
			return true;
		}
		void displayer::clearTo(const lsw_color c)
		{
			al_clear_to_color(c);
		}
		const double displayer::multiplier()
		{
			double saved = getTime();
			double val = saved - data.lastC_fMult_al;
			data.lastC_fMult_al = saved;
			return val * 60.0; // 1.0 multiplier for 60 fps

		}
		void displayer::flip()
		{
			if (data.lastdraw != 0.0) {
				if (data.fixed_fps > 0 && data.fixed_fps < 250) fixFPS(data.lastdraw, getTime(), data.fixed_fps);
				double noww = getTime();

				data.fps = 0.01 + (data.fps * 2 + (1.0 / (1.0*noww - data.lastdraw))) / 3.0;
				data.lastdraw = noww;

				double var_b = 10.0 / data.fps;
				if (var_b > 0.99) var_b = 0.99;
			}
			else data.lastdraw = getTime();

			double var_b = 10.0 / data.fps;
			if (var_b > 0.99) var_b = 0.99;

			double s[2];
			s[0] = 1.0 * getDisplaySize(data.display, 0) / getBitmapSize(data.buffer, 0);
			s[1] = 1.0 * getDisplaySize(data.display, 1) / getBitmapSize(data.buffer, 1);

			data.color_blend = color(var_b, var_b, var_b, var_b);

			if (!isFullscreen) {
				al_acknowledge_resize(data.display);
				data.prop[0] = 1.0 * data.usedx / base_res[0];
				data.prop[1] = 1.0 * data.usedy / base_res[1];
			}
			defineOut(data.display);
			if (data.display_mode_draw == 2) {
				
				defineOut(data.transparency);
				al_draw_filled_rectangle(0, 0, data.usedx, data.usedy, color(0.75,0.75,0.75));

				defineOut(data.display);
				double d[3][4];

				d[0][0] = 0.003*sin(getTime()*4.1);
				d[0][1] = 0.003*cos(getTime()*5.9);
				d[0][2] = 0.003*sin(getTime()*4.7);
				d[0][3] = 0.003*cos(getTime()*6.4);

				d[1][0] = 0.003*cos(getTime()*2.7);
				d[1][1] = 0.003*cos(getTime()*3.3);
				d[1][2] = 0.003*sin(getTime()*4.1);
				d[1][3] = 0.003*sin(getTime()*5.2);

				d[2][0] = 0.003*cos(getTime()*6.2);
				d[2][1] = 0.003*sin(getTime()*1.9);
				d[2][2] = 0.003*sin(getTime()*5.7);
				d[2][3] = 0.003*cos(getTime()*3.9);

				drawIt(data.buffer, 0, 0, 0, s[0] / data.prop[0], s[1] / data.prop[1], -1, -1, -1, color(var_b*0.75, var_b*0.75, var_b*0.75, var_b*0.75), true, getDisplayWidth(data.display), getDisplayHeight(data.display));
				drawIt(data.buffer, d[0][0], d[0][1], 0, (s[0] / data.prop[0]) + d[0][2], (s[1] / data.prop[1]) + d[0][3], -1, -1, -1, color(var_b*0.70, var_b*0.99, var_b*0.99, var_b*0.99), true, getDisplayWidth(data.display), getDisplayHeight(data.display));
				drawIt(data.buffer, d[1][0], d[1][1], 0, (s[0] / data.prop[0]) + d[1][2], (s[1] / data.prop[1]) + d[1][3], -1, -1, -1, color(var_b*0.99, var_b*0.70, var_b*0.99, var_b*0.99), true, getDisplayWidth(data.display), getDisplayHeight(data.display));
				drawIt(data.buffer, d[2][0], d[2][1], 0, (s[0] / data.prop[0]) + d[2][2], (s[1] / data.prop[1]) + d[2][3], -1, -1, -1, color(var_b*0.99, var_b*0.99, var_b*0.70, var_b*0.99), true, getDisplayWidth(data.display), getDisplayHeight(data.display));
				drawIt(data.buffer, 0, 0, 0, s[0] / data.prop[0], s[1] / data.prop[1], -1, -1, -1, color(var_b*0.95, var_b*0.95, var_b*0.99, var_b*0.95), true, getDisplayWidth(data.display), getDisplayHeight(data.display));

				/*al_draw_tinted_scaled_bitmap(data.buffer,
					color(var_b*0.75, var_b*0.75, var_b*0.75, var_b*0.75),
					0,
					0,
					data.usedx,
					data.usedy,
					0,
					0,
					getDisplayWidth(data.display),
					getDisplayHeight(data.display),
					0);

				//al_draw_bitmap(data.transparency, 0, 0, 0);
				al_draw_tinted_scaled_bitmap(data.buffer,
					color(var_b*0.70, var_b*0.99, var_b*0.99, var_b*0.99),
					data.usedx*0.002*sin(getTime()*4.1), 
					data.usedy*0.002*cos(getTime()*5.9), 
					data.usedx + data.usedx*0.002*sin(getTime()*4.7), 
					data.usedy + data.usedy*0.002*cos(getTime()*6.4), 
					0.002*getDisplayWidth(data.display)*sin(getTime()*2.5), 
					0.002*getDisplayHeight(data.display)*cos(getTime()*2.2),
					getDisplayWidth(data.display) + 0.002*getDisplayWidth(data.display)*cos(getTime()*1.9), 
					getDisplayHeight(data.display) + 0.002*getDisplayHeight(data.display)*sin(getTime()*2.7), 
					0);
				al_draw_tinted_scaled_bitmap(data.buffer, 
					color(var_b*0.99, var_b*0.70, var_b*0.99, var_b*0.99), 
					data.usedx*0.002*cos(getTime()*6.7),
					data.usedy*0.002*cos(getTime()*4.6), 
					data.usedx + data.usedx*0.002*cos(getTime()*5.5), 
					data.usedy + data.usedy*0.002*cos(getTime()*4.7),
					0.002*getDisplayWidth(data.display)*cos(getTime()*1.6), 
					0.002*getDisplayHeight(data.display)*sin(getTime()*1.9),
					getDisplayWidth(data.display) + 0.002*getDisplayWidth(data.display)*cos(getTime()*1.7),
					getDisplayHeight(data.display) + 0.002*getDisplayHeight(data.display)*cos(getTime()*2.2),
					0);
				al_draw_tinted_scaled_bitmap(data.buffer,
					color(var_b*0.99, var_b*0.99, var_b*0.70, var_b*0.99),
					data.usedx*0.002*sin(getTime()*3.4), 
					data.usedy*0.002*sin(getTime()*6.6), 
					data.usedx + data.usedx*0.002*sin(getTime()*4.6),
					data.usedy + data.usedy*0.002*sin(getTime()*3.2),
					0.002*getDisplayWidth(data.display)*sin(getTime()*1.9),
					0.002*getDisplayHeight(data.display)*cos(getTime()*2.7),
					getDisplayWidth(data.display) + 0.002*getDisplayWidth(data.display)*sin(getTime()*1.2),
					getDisplayHeight(data.display) + 0.002*getDisplayHeight(data.display)*sin(getTime()*2.5),
					0);
				al_draw_tinted_scaled_bitmap(data.buffer,
					color(var_b*0.99, var_b*0.99, var_b*0.99, var_b*0.99),
					0,
					0,
					data.usedx,
					data.usedy,
					0,
					0,
					getDisplayWidth(data.display),
					getDisplayHeight(data.display),
					0);*/
			}
			else drawIt(data.buffer, 0, 0, 0, s[0] / data.prop[0], s[1] / data.prop[1], -1, -1, -1, color(0,0,0), false, getDisplayWidth(data.display), getDisplayHeight(data.display));// al_draw_scaled_bitmap(data.buffer, 0, 0, data.usedx, data.usedy, 0, 0, getDisplayWidth(data.display), getDisplayHeight(data.display), 0);
			flipD(data.buffer);
			//al_set_target_bitmap(data.buffer);
			//data.tickCount = GetTickCount64() - data.lastC;

			defineOut(data.buffer);
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
			defineOut(data.buffer);
		}
		void displayer::resizeBufTo(const int x, const int y)
		{
			if (data.buffer)
			{
				freeUp(data.buffer);
				freeUp(data.transparency);
				while (!(data.buffer = createTexture(x, y)));
				while (!(data.transparency = createTexture(x, y)));
				defineOut(data.buffer);
				data.usedx = x;
				data.usedy = y;
				data.data_control.unload(LSW_FONT_DEJAVUSANS);
				data.prop[0] = 1.0 * data.usedx / base_res[0];
				data.prop[1] = 1.0 * data.usedy / base_res[1];

				float temp_siz_font = 1.0*sqrt(data.usedx*data.usedy)*28.8 / sqrt(base_res[0] * base_res[1]);
				while (!data.data_control.load(LSW_FONT_DEJAVUSANS, temp_siz_font, true));
			}
		}
		void displayer::deinitAll()
		{
			if (!data.loaded) return;
			data.muu.lock();


			if (data.if_playin)
			{
				if (data.if_playin->beingusedby == 0) {
					data.if_playin->change_oneanother.try_lock();
					data.if_playin->change_oneanother.unlock();
				}
				gameplay_needs& rn = *data.if_playin;
				rn.playin = false;
				rn.collision_controller->join();
				delete rn.collision_controller;
				rn.collision_controller = nullptr;
				data.if_playin = nullptr;
			}

			data.evm.deinit();
			data.data_control.unloadAll();
			data.data_control.unload(LSW_FONT_DEJAVUSANS);
			freeUp(data.ev_qu);
			freeUp(data.buffer);
			freeUp(data.transparency);
			data.data_control.clearAll();
			freeUp(data.display);

			data.loaded = false;
			data.muu.unlock();
		}


		const bool event_mng::init(lsw_event_qu gimme)
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



		void _thr_collisionwork_ext(gameplay_needs* gr, displayer* d)
		{
			if (!gr || !d) {
				throw "FAILED THR COLLISION GAME_PLAY";
				exit(0);
			}
			gr->collision_tps = 90.0;

			lsw_event_qu ev_qu = al_create_event_queue();
			lsw_timer timar = al_create_timer(1.0 / gr->collision_tps);
			if (ev_qu && timar) {
				al_register_event_source(ev_qu, al_get_timer_event_source(timar));
				al_start_timer(timar);
			}

			while (gr->playin)
			{
				if ((gr->nowFps - gr->collision_tps > gr->collision_tps*0.10) || (gr->collision_tps - gr->nowFps > gr->collision_tps*0.40 && gr->nowFps > 90.0))
				{
					gr->collision_tps = gr->nowFps+30;
					al_unregister_event_source(ev_qu, al_get_timer_event_source(timar));
					al_stop_timer(timar);
					freeUp(timar);
					timar = al_create_timer(1.0 / gr->collision_tps);
					al_register_event_source(ev_qu, al_get_timer_event_source(timar));
					al_start_timer(timar);
				}

				if (ev_qu && timar)
				{
					lsw_event tr;
					//al_wait_for_event_timed(ev_qu, &tr, 1.0 / gr->nowFps);
					if (al_get_next_event(ev_qu, &tr)) {
						if (tr.type == ALLEGRO_EVENT_TIMER) {
							d->_thr_collision_work(*gr);
						}
					}
				}
				else {
					restFor(1.0 / 90.0);
					d->_thr_collision_work(*gr);
				}
				
			}

			if (timar) {
				al_stop_timer(timar);
				freeUp(timar);
			}
			if (ev_qu) freeUp(ev_qu);
		}

		void _thr_temp_loadallresources(int* which, bool* hasdone)
		{
			if (!hasdone || !which) return;

			controller ctrl;
			//displayer disp;

			*hasdone = false;

			//disp.fixLoad();
			for (*which = 0; *which < LSW_BMP_MAX; (*which)++) ctrl.load((images_available)(*which), false);

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

		void fixProportion(int& u, int& v, const float d) {
			float temp_f = 1.0* v / u;
			if (temp_f > d) {
				u = v * 16.0 / 9;
			}
			else {
				v = u * 9.0 / 16;
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