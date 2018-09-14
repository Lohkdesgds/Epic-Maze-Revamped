#include "resource.h"

namespace LSW {

	namespace EpicMazeR {

		controller_params controller::data;

		const bool bitmap::load(const images_available o, const bool force_reload)
		{
			if (lastopt != -1 && !force_reload) return false;
			if (force_reload) {
				if (file) this->freeup();
			}
			lastopt = o;
			occured = LSW_AS_BMP;
			file = (void*)al_load_bitmap(images_paths[o].c_str());
			return true;
		}
		const bool bitmap::load(const fonts_available o, const float fontsiz, const bool force_reload)
		{
			if (lastopt != -1 && !force_reload) return false;
			if (force_reload) {
				if (file) this->freeup();
			}
			lastopt = o;
			occured = LSW_AS_FONT;
			file = (void*)al_load_ttf_font(fonts_paths[o].c_str(), fontsiz, 0);
			lastfontsiz = fontsiz;
			return true;
		}
		void* bitmap::get()
		{
			return file;
		}
		void bitmap::freeup()
		{
			if (file) {
				if (occured == LSW_AS_BMP) {
					lsw_texture tt = (lsw_texture)file;
					freeUp(tt);
					file = nullptr;
				}
				else {
					lsw_font tt = (lsw_font)file;
					freeUp(tt);
					file = nullptr;
				}
			}
		}
		void bitmap::reload()
		{
			if (!file) {
				if (occured == LSW_AS_BMP) {
					file = (void*)al_load_bitmap(images_paths[lastopt].c_str());
				}
				else {
					file = (void*)al_load_ttf_font(fonts_paths[lastopt].c_str(), lastfontsiz, 0);
				}
			}
		}
		const bool bitmap::amI(const int u, const load_modes m)
		{
			return (m == occured && u == lastopt);
		}


		const bool controller::hasIt(const int who, const load_modes mod, bitmap** sav, const bool force)
		{
			for (auto& i : data.bmps)
			{
				if (i->amI(who, mod)) {
					if (force) i->reload();
					if (sav) *sav = i;
					return true;
				}
			}
			if (force && sav)
			{
				bitmap* newdata = nullptr;
				newdata = new bitmap();
				data.bmps.push_back(newdata);
				if (mod == LSW_AS_BMP)
				{
					newdata->load((images_available)who);
				}
				*sav = newdata;
				return true;
			}
			return false;
		}
		const bool controller::load(const images_available o, const bool force_reload)
		{
			data.access.lock();
			bitmap* thus = nullptr;
			if (!hasIt(o, LSW_AS_BMP, &thus))
			{
				return false;
			}
			bool done = thus->load(o, force_reload);
			data.access.unlock();	
			return done;
		}
		const bool controller::load(const fonts_available o, const float s, const bool force_reload)
		{
			data.access.lock();
			bitmap* thus = nullptr;
			if (!hasIt(o, LSW_AS_FONT, &thus))
			{
				return false;
			}
			bool done = thus->load(o, s, force_reload);
			data.access.unlock();
			return done;
		}
		const bool controller::loadAll()
		{
			bool response = true;
			for (int u = LSW_BMP_ICON; u <= LSW_BMP_MAX; u++) {
				if (!load((const images_available)u)) response = false;
			}
			return response;
		}


		void controller::unload(const images_available o)
		{
			data.access.lock();
			bitmap* thus = nullptr;

			if (hasIt(o, LSW_AS_BMP, &thus, false)) {
				thus->freeup();
			}

			data.access.unlock();
		}
		void controller::unload(const fonts_available o)
		{
			data.access.lock();
			bitmap* thus = nullptr;

			if (hasIt(o, LSW_AS_FONT, &thus, false)) {
				thus->freeup();
			}

			data.access.unlock();

		}
		void controller::unloadAll()
		{
			for (int u = LSW_BMP_ICON; u <= LSW_BMP_MAX; u++) unload((images_available)u);
		}
		void controller::clearAll()
		{
			data.bmps.clear();
		}

		lsw_texture controller::get(const images_available o)
		{
			data.access.lock();
			bitmap* thus = nullptr;

			if (hasIt(o, LSW_AS_BMP, &thus, true)) {
				if (!thus->get()) thus->reload();
			}

			al_convert_memory_bitmaps();
			data.access.unlock();
			return (lsw_texture)thus->get();
		}
		lsw_font controller::get(const fonts_available o)
		{
			data.access.lock();
			bitmap* thus = nullptr;

			if (hasIt(o, LSW_AS_FONT, &thus, true)) {
				if (!thus->get()) thus->reload();
			}
			al_convert_memory_bitmaps();
			data.access.unlock();
			return (lsw_font)thus->get();
		}
		const float mapthing::percof(const int u)
		{
			if (!matriz) return -1;

			ULONG numof_u = 0;
			ULONG numof_others = 0;

			for (ULONG p = 0; p < tamx*tamy; p++)
			{
				if (matriz[p] == u) numof_u++;
				else numof_others++;
			}

			return 1.0f * numof_u / (tamx * tamy);
		}
		const bool mapthing::generate_custom(const int tx, const int ty, float needed, bool* keeprunning, const bool verify)
		{
			tamx = fabs(tx);
			tamy = fabs(ty);
			if (needed >= 1.0) needed = 0.99;
			if (needed <= 0.0) needed = 0.01;


			int times, times2;
			int processtimes = 0;
			int x, y;
			double now = getTime(); // not useful rn
			bool running = true;

			x = y = times = times2 = 0;

			srand((unsigned)clock());

			if (matriz != nullptr) {
				delete matriz;
				matriz = nullptr;
			}
			matriz = new int[tamx*tamy];
			for (size_t u = 0; u < (size_t)tamx*tamy; u++) matriz[u] = 0;
			processtimes = tamx * tamy;

			while (/*getTime() - now < sqrt(tamx*tamy)*0.1f*/processtimes > 0 && now != -1 && ((keeprunning) ? *keeprunning : true))
			{
				if (--processtimes == 0)
				{
					float reasonn = percof(LSW_LIVRE);
					if (reasonn < needed) processtimes = sqrt(tamx * tamy);
				}

				*(matriz + x + y * tamx) = 1;
				int counter = 0, leste = 0, oeste = 0, norte = 0, sul = 0, nordeste = 0, noroeste = 0, sudoeste = 0, sudeste = 0;

				if (x < tamx - 1 && *(matriz + (x + 1) + y * tamx) == 1) /// LESTE
				{
					counter++;
					leste = 1;
				}
				if (x > 0 && *(matriz + (x - 1) + y * tamx) == 1) /// OESTE
				{
					counter++;
					oeste = 1;
				}
				if (y < tamy - 1 && *(matriz + x + (y + 1)*tamx) == 1) /// NORTE
				{
					counter++;
					norte = 1;
				}
				if (y > 0 && *(matriz + x + (y - 1)*tamx) == 1) /// SUL
				{
					counter++;
					sul = 1;
				}
				if (x == 0 || x == tamx - 1)
					counter++;
				if (y == 0 || y == tamy - 1)
					counter++;

				if (x < tamx - 1 && y>0 && *(matriz + (x + 1) + (y - 1)*tamx)) /// NORDESTE
					nordeste++;
				if (x > 0 && y > 0 && *(matriz + (x - 1) + (y - 1)*tamx)) /// NOROESTE
					noroeste++;
				if (x < tamx - 1 && y < tamy - 1 && *(matriz + (x + 1) + (y + 1)*tamx)) /// SUDESTE
					sudeste++;
				if (x > 0 && y < tamy - 1 && *(matriz + (x - 1) + (y + 1)*tamx)) /// SUDOESTE
					sudoeste++;


				/// Aleatoriza para caso ==2 talvez possa ser 3
				int random = rand();
				if (random % 3 == 0)
					counter++;

				if (counter > 3)
					times++;
				else times = 0;

				if (times > 19)
				{
					times2++;
					x = 0;
					y = times2;
				}
				if (times2 > tamy - 2 && times > 9)
				{
					now = -1;
				}

				random = rand() % 4; ///0 N 1 S 2 L 3 O

				switch (random) {
				case 0:
					if (y > 0 && counter < 3 && nordeste == 0 && noroeste == 0) ///VAI PRO NORTE
					{
						y--;
					}
					else
					{
						random = rand();
						random = random % 4;
						if (random == 0 && x < tamx - 1 && *(matriz + (x + 1) + y * tamx) == 1)
							x++;
						if (random == 1 && y < tamy - 1 && *(matriz + x + (y + 1)*tamx) == 1)
							y++;
						if (random == 2 && x > 0 && *(matriz + (x - 1) + y * tamx) == 1)
							x--;
						if (random == 3 && y > 0 && *(matriz + x + (y - 1)*tamx) == 1)
							y--;
					}
					break;
				case 1:
					if (y < tamy - 1 && counter < 3 && sudoeste == 0 && sudeste == 0) /// VAI PRO SUL
					{
						y++;
					}
					else
					{
						random = rand();
						random = random % 4;
						if (random == 0 && x < tamx - 1 && *(matriz + (x + 1) + y * tamx) == 1)
							x++;
						if (random == 1 && y < tamy - 1 && *(matriz + x + (y + 1)*tamx) == 1)
							y++;
						if (random == 2 && x > 0 && *(matriz + (x - 1) + y * tamx) == 1)
							x--;
						if (random == 3 && y > 0 && *(matriz + x + (y - 1)*tamx) == 1)
							y--;
					}
					break;
				case 2:
					if (x < tamx - 1 && counter < 3 && nordeste == 0 && sudeste == 0) /// VAI PRO LESTE
					{
						x++;
					}
					else
					{
						random = rand();
						random = random % 4;
						if (random == 0 && x < tamx - 1 && *(matriz + (x + 1) + y * tamx) == 1)
							x++;
						if (random == 1 && y < tamy - 1 && *(matriz + x + (y + 1)*tamx) == 1)
							y++;
						if (random == 2 && x > 0 && *(matriz + (x - 1) + y * tamx) == 1)
							x--;
						if (random == 3 && y > 0 && *(matriz + x + (y - 1)*tamx) == 1)
							y--;
					}
					break;
				case 3:
					if (x > 0 && counter < 3 && noroeste == 0 && sudoeste == 0) /// VAI PRO OESTE
					{
						x--;
					}
					else
					{
						random = rand();
						random = random % 4;
						if (random == 0 && x < tamx - 1 && *(matriz + (x + 1) + y * tamx) == 1)
							x++;
						if (random == 1 && y < tamy - 1 && *(matriz + x + (y + 1)*tamx) == 1)
							y++;
						if (random == 2 && x > 0 && *(matriz + (x - 1) + y * tamx) == 1)
							x--;
						if (random == 3 && y > 0 && *(matriz + x + (y - 1)*tamx) == 1)
							y--;
					}
					break;
				}
			}

			if (verify) {
				if (!solve()) {
					delete matriz;
					matriz = nullptr;
					return false;
				}
			}
			return true;
		}
		const bool mapthing::generate(bool* keeprunning, const int level, const int tty)
		{
			if (!keeprunning) return false;

			tamx = 80 + level * 120;
			tamy = tty;

			return generate_custom(tamx, tamy, 0.56, keeprunning);
		}

		const bool mapthing::solve()
		{
			int maximo_tentativas, ultimo;
			posicao *visitados;
			visitados = new posicao[tamx*tamy];
			posicao atual;

			atual.x = 0;
			atual.y = 0;
			*(matriz + 0 + 0 * tamx) = LSW_VISITADO;
			ultimo = 0;
			maximo_tentativas = 1000;
			while (atual.x != tamx - 1)
			{
				visitados[ultimo] = atual;
				if (moved(atual, 1, 0))
				{
					atual.x++;
					ultimo++;
					continue;
				}
				if (moved(atual, 0, -1))
				{
					atual.y--;
					ultimo++;
					continue;
				}
				if (moved(atual, 0, 1))
				{
					atual.y++;
					ultimo++;
					continue;
				}
				if (moved(atual, -1, 0))
				{
					atual.x--;
					ultimo++;
					continue;
				}
				*(matriz + atual.x + atual.y*tamx) = LSW_SEM_SAIDA;
				if (--ultimo < 0) {
					delete visitados;
					return false;
				}
				atual = visitados[ultimo];


				if (--maximo_tentativas == 0)
				{
					delete visitados;
					return false;
				}
			}
			delete visitados;
			return true;
		}

		const bool mapthing::moved(const posicao atual, int d_x, int d_y)
		{
			if (atual.x + d_x < 0 || atual.y + d_y == tamy ||
				atual.y + d_y < 0 || atual.x + d_x == tamx)
			{
				return false;
			}
			if (*(matriz + (atual.x + d_x) + (atual.y + d_y)*tamx) == LSW_LIVRE)
			{
				*(matriz + (atual.x + d_x) + (atual.y + d_y)*tamx) = LSW_VISITADO;
				return true;
			}
			return false;
		}

		void mapthing::cleanUp()
		{
			if (matriz)
			{
				delete matriz;
				matriz = nullptr;
				tamx = tamy = -1;
			}
		}

		const int mapthing::readpos(const int x, const int y)
		{
			if (!matriz) return -1;
			if (x < 0 || y < 0) return -3;
			if (x >= tamx || y >= tamy) return -4;
			int u = x + y * tamx;
			if (u >= tamx * tamy || u < 0) return -2;
			return *(matriz + u);
		}

		const int mapthing::getSiz(const map_sizes u)
		{
			switch (u)
			{
			case LSW_SIZ_X:
				return tamx;
			case LSW_SIZ_Y:
				return tamy;
			}
			return 0;
		}

		mapthing::~mapthing()
		{
			cleanUp();
		}



		infinity_map::~infinity_map()
		{
			keepin_on = false;
			if (thr) {
				thr->join();
				delete thr;
			}
		}
		void infinity_map::init()
		{
			if (!thr)
			{
				thr = new std::thread(_thr_loadmap_infinity, this, &keepin_on);
			}
		}

		chunk infinity_map::gimmerandchunk()
		{
			chunk chk;
			mapthing map;
			map.generate_custom(16, 16, 0.5, nullptr, false);

			for (int u = 0; u < 16 * 16; u++)
			{
				chk.blocks[u % 16][u / 16] = map.readpos(u % 16, u / 16);
			}
			return chk;
		}
		void infinity_map::setAreaPreLoadAsRequested(const int r)
		{
			if (r < 0) return;
			area_guaranteed = r;
		}
		const bool infinity_map::doesItHave(const int c_x, const int c_y)
		{
			changes_happenin[0].lock();
			for (auto& i : chunks)
			{
				if (i.idx == c_x && i.idy == c_y) {
					changes_happenin[0].unlock();
					return true;
				}
			}
			changes_happenin[0].unlock();
			return false;
		}
		void infinity_map::_solve_unloaded_chunks()
		{
			if (asked_notfound.size() > 0)
			{
				changes_happenin[1].lock();
				for (auto& i : asked_notfound)
				{
					for (int sx = -area_guaranteed; sx <= area_guaranteed; sx++)
					{
						for (int sy = -area_guaranteed; sy <= area_guaranteed; sy++)
						{
							if (!doesItHave(i.x + sx, i.y + sy)) {
								chunk ck = gimmerandchunk();
								ck.idx = i.x + sx;
								ck.idy = i.y + sy;

								printf_s("[MAP_EXPERIMENTAL][THR] Created chunk %d x %d\n", i.x, i.y);
								changes_happenin[0].lock();
								chunks.push_back(ck);
								changes_happenin[0].unlock();
							}
						}
					}
				}
				changes_happenin[1].unlock();
			}
		}
		int infinity_map::readpos(const int x, const int y)
		{
			int c_x = x / 16;
			int c_y = y / 16;

			int i_x = x % 16;
			int i_y = y % 16;

			changes_happenin[0].lock();
			for (auto& i : chunks)
			{
				if (i.idx == c_x && i.idy == c_y)
				{
					changes_happenin[0].unlock();
					return i.blocks[i_x][i_y];
				}
			}
			changes_happenin[0].unlock();

			changes_happenin[1].lock();
			for (auto& i : asked_notfound)
			{
				if (i.x == c_x && i.y == c_y)
				{
					changes_happenin[1].unlock();
					return -1;
				}
			}

			posicao p;
			p.x = c_x;
			p.y = c_y;
			asked_notfound.push_back(p);
			changes_happenin[1].unlock();
			return -1;
		}

		void _thr_loadmap_infinity(infinity_map* u, bool* k)
		{
			if (!u || !k) return;

			while (*k)
			{
				u->_solve_unloaded_chunks();
				Sleep(50);
			}
		}
	}
}