#include "all_my_things.h"

void not_dynamic_loader(complete_things *_things)
{
	int bitx, bity;

	bitx = _things->render_x;
	bity = _things->render_y;

	switch (_things->what_to_unload)
	{
	case APOIO_THINGS:
		_things->is_unloading = true;
		printer("{>DYNAMIC_LOADER}> Descarregando \"apoios\" no background dinamicamente.");

		clear_memory(APOIO_THINGS, _things->images);

		printer("{>DYNAMIC_LOADER}> \"Apoios\" descarregados.");
		_things->what_to_unload = WAITING;
		_things->is_unloading = false;
		break;
	case ANIMATION_KO:
		_things->is_unloading = true;
		printer("{>DYNAMIC_LOADER}> Descarregando \"animation\" no background dinamicamente.");

		clear_memory(ANIMATION_KO, _things->images);

		printer("{>DYNAMIC_LOADER}> \"Animation\" descarregados.");
		_things->what_to_unload = WAITING;
		_things->is_unloading = false;
		break;
	default:
		_things->is_unloading = false;
	}
	switch (_things->what_to_load)
	{
	case BASICS_DEFAULT_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando básicos.");

		_things->images->buffer = al_create_bitmap(bitx, bity);
		_things->images->vignette = al_load_bitmap(datapath_vignette);
		_things->images->logo = al_load_bitmap(datapath_intro);

		printer("{>DYNAMIC_LOADER}> Básicos carregados!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_DEFAULT_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando menu básico.");

		_things->images->apoio_01 = al_load_bitmap(datapath_menu_opt_01);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_opt_02);
		_things->images->apoio_03 = al_load_bitmap(datapath_menu_opt_03);
		_things->images->apoio_04 = al_load_bitmap(datapath_menu_opt_04);
		_things->images->apoio_05 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Menu básico carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_INSTRUCTIONS_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando instruções.");

		_things->images->apoio_01 = al_load_bitmap(datapath_instr);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Instruções carregadas!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_RECORDS_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando records.");

		_things->images->apoio_01 = al_load_bitmap(datapath_rec_back);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Records carregados!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_CONFIG_OCULT: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando ~*~ocult~*~.");

		_things->images->apoio_01 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> ~*~Ocult~*~ carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_START_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando início.");

		_things->images->apoio_01 = al_load_bitmap(datapath_menu_opt_01_s);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_opt_02_s);
		_things->images->apoio_03 = al_load_bitmap(datapath_menu_opt_03_s);
		_things->images->apoio_04 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Início de jogo carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case PAUSE_MENU_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando menu de pause.");

		load_gif_bitmaps(30, _things->images, "pause");

		printer("{>DYNAMIC_LOADER}> Pause Menu carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case GAME_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando menu de pause.");

		_things->images->apoio_01 = al_load_bitmap(datapath_background_01);
		_things->images->apoio_02 = al_load_bitmap(datapath_block);
		_things->images->apoio_03 = al_load_bitmap(datapath_menu_block);
		_things->images->apoio_04 = al_load_bitmap(datapath_person);
		_things->images->apoio_05 = al_load_bitmap(datapath_person_f01);
		_things->images->apoio_06 = al_load_bitmap(datapath_person_f02);
		_things->images->apoio_07 = al_load_bitmap(datapath_dark_01);
		_things->images->apoio_08 = al_load_bitmap(datapath_dark_02);
		_things->images->apoio_09 = al_load_bitmap(datapath_dark_03);
		_things->images->apoio_10 = al_load_bitmap(datapath_pause_continue);
		_things->images->apoio_11 = al_load_bitmap(datapath_pause_exit);
		_things->images->apoio_12 = al_load_bitmap(datapath_saving_score);
		_things->images->apoio_13 = al_load_bitmap(datapath_block_end);

		printer("{>DYNAMIC_LOADER}> Jogo carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	default:
		_things->is_loading = false;
	}
}
void dynamic_loaderU(complete_things *_things)
{
	dynamic_loader(nullptr, (void*)_things);
	return;
	/*int bitx, bity;

	bitx = _things->render_x;
	bity = _things->render_y;

	switch (_things->what_to_load)
	{
	case BASICS_DEFAULT_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando básicos.");

		_things->images->buffer = al_create_bitmap(bitx, bity);
		_things->images->vignette = al_load_bitmap(datapath_vignette);
		_things->images->logo = al_load_bitmap(datapath_intro);

		printer("{>DYNAMIC_LOADER}> Básicos carregados!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_DEFAULT_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando menu básico.");

		_things->images->apoio_01 = al_load_bitmap(datapath_menu_opt_01);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_opt_02);
		_things->images->apoio_03 = al_load_bitmap(datapath_menu_opt_03);
		_things->images->apoio_04 = al_load_bitmap(datapath_menu_opt_04);
		_things->images->apoio_05 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Menu básico carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_INSTRUCTIONS_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando instruções.");

		_things->images->apoio_01 = al_load_bitmap(datapath_instr);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Instruções carregadas!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_RECORDS_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando records.");

		_things->images->apoio_01 = al_load_bitmap(datapath_rec_back);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Records carregados!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_CONFIG_OCULT: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando ~*~ocult~*~.");

		_things->images->apoio_01 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> ~*~Ocult~*~ carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case MENU_START_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando início.");

		_things->images->apoio_01 = al_load_bitmap(datapath_menu_opt_01_s);
		_things->images->apoio_02 = al_load_bitmap(datapath_menu_opt_02_s);
		_things->images->apoio_03 = al_load_bitmap(datapath_menu_opt_03_s);
		_things->images->apoio_04 = al_load_bitmap(datapath_menu_block);

		printer("{>DYNAMIC_LOADER}> Início de jogo carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case PAUSE_MENU_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando menu de pause.");

		load_gif_bitmaps(30, _things->images, "pause");

		printer("{>DYNAMIC_LOADER}> Pause Menu carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	case GAME_LOAD: ///| OK |///
		_things->is_loading = true;
		printer("{>DYNAMIC_LOADER}> Carregando menu de pause.");

		_things->images->apoio_01 = al_load_bitmap(datapath_background_01);
		_things->images->apoio_02 = al_load_bitmap(datapath_block);
		_things->images->apoio_03 = al_load_bitmap(datapath_menu_block);
		_things->images->apoio_04 = al_load_bitmap(datapath_person);
		_things->images->apoio_05 = al_load_bitmap(datapath_person_f01);
		_things->images->apoio_06 = al_load_bitmap(datapath_person_f02);
		_things->images->apoio_07 = al_load_bitmap(datapath_dark_01);
		_things->images->apoio_08 = al_load_bitmap(datapath_dark_02);
		_things->images->apoio_09 = al_load_bitmap(datapath_dark_03);
		_things->images->apoio_10 = al_load_bitmap(datapath_pause_continue);
		_things->images->apoio_11 = al_load_bitmap(datapath_pause_exit);
		_things->images->apoio_12 = al_load_bitmap(datapath_saving_score);
		_things->images->apoio_13 = al_load_bitmap(datapath_block_end);

		printer("{>DYNAMIC_LOADER}> Jogo carregado!");
		_things->what_to_load = WAITING;
		_things->is_loading = false;
		break;
	default:
		_things->is_loading = false;
	}
	switch (_things->what_to_unload)
	{
	case APOIO_THINGS:
		_things->is_unloading = true;
		printer("{>DYNAMIC_LOADER}> Descarregando \"apoios\" no background dinamicamente.");

		clear_memory(APOIO_THINGS, _things->images);

		printer("{>DYNAMIC_LOADER}> \"Apoios\" descarregados.");
		_things->what_to_unload = WAITING;
		_things->is_unloading = false;
		break;
	case ANIMATION_KO:
		_things->is_unloading = true;
		printer("{>DYNAMIC_LOADER}> Descarregando \"animation\" no background dinamicamente.");

		clear_memory(ANIMATION_KO, _things->images);

		printer("{>DYNAMIC_LOADER}> \"Animation\" descarregados.");
		_things->what_to_unload = WAITING;
		_things->is_unloading = false;
		break;
	default:
		_things->is_unloading = false;
	}*/
}
void *dynamic_loader(ALLEGRO_THREAD *thr, void *data)
{
    printer("\n{>DYNAMIC_LOADER}> INICIADO! ~multitask\n");
    complete_things *_things;
    int bitx, bity;
    _things = (complete_things *)data;

    bitx = _things->render_x;
    bity = _things->render_y;

    while (!_things->quitting)
    {
        switch (_things->what_to_load)
        {
        case BASICS_DEFAULT_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando básicos em background dinamicamente.");

            _things->images->buffer     = al_create_bitmap(bitx,bity);
            _things->images->vignette   = al_load_bitmap(datapath_vignette);
            _things->images->logo       = al_load_bitmap(datapath_intro);

            printer("{>DYNAMIC_LOADER}> Básicos carregados!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case MENU_DEFAULT_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando menu básico em background dinamicamente.");

            _things->images->apoio_01 = al_load_bitmap(datapath_menu_opt_01);
            _things->images->apoio_02 = al_load_bitmap(datapath_menu_opt_02);
            _things->images->apoio_03 = al_load_bitmap(datapath_menu_opt_03);
            _things->images->apoio_04 = al_load_bitmap(datapath_menu_opt_04);
            _things->images->apoio_05 = al_load_bitmap(datapath_menu_block);

            printer("{>DYNAMIC_LOADER}> Menu básico carregado!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case MENU_INSTRUCTIONS_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando instruções em background dinamicamente.");

            _things->images->apoio_01 = al_load_bitmap(datapath_instr);
            _things->images->apoio_02 = al_load_bitmap(datapath_menu_block);

            printer("{>DYNAMIC_LOADER}> Instruções carregadas!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case MENU_RECORDS_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando records em background dinamicamente.");

            _things->images->apoio_01 = al_load_bitmap(datapath_rec_back);
            _things->images->apoio_02 = al_load_bitmap(datapath_menu_block);

            printer("{>DYNAMIC_LOADER}> Records carregados!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case MENU_CONFIG_OCULT: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando ~*~ocult~*~ em background dinamicamente.");

            _things->images->apoio_01 = al_load_bitmap(datapath_menu_block);

            printer("{>DYNAMIC_LOADER}> ~*~Ocult~*~ carregado!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case MENU_START_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando início em background dinamicamente.");

            _things->images->apoio_01 = al_load_bitmap(datapath_menu_opt_01_s);
            _things->images->apoio_02 = al_load_bitmap(datapath_menu_opt_02_s);
            _things->images->apoio_03 = al_load_bitmap(datapath_menu_opt_03_s);
            _things->images->apoio_04 = al_load_bitmap(datapath_menu_block);

            printer("{>DYNAMIC_LOADER}> Início de jogo carregado!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case PAUSE_MENU_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando menu de pause em background dinamicamente.");

            load_gif_bitmaps(30,_things->images, "pause");

            printer("{>DYNAMIC_LOADER}> Pause Menu carregado!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        case GAME_LOAD: ///| OK |///
            _things->is_loading   = true;
            printer("{>DYNAMIC_LOADER}> Carregando menu de pause em background dinamicamente.");

            _things->images->apoio_01 = al_load_bitmap(datapath_background_01);
            _things->images->apoio_02 = al_load_bitmap(datapath_block);
            _things->images->apoio_03 = al_load_bitmap(datapath_menu_block);
            _things->images->apoio_04 = al_load_bitmap(datapath_person);
            _things->images->apoio_05 = al_load_bitmap(datapath_person_f01);
            _things->images->apoio_06 = al_load_bitmap(datapath_person_f02);
            _things->images->apoio_07 = al_load_bitmap(datapath_dark_01);
            _things->images->apoio_08 = al_load_bitmap(datapath_dark_02);
            _things->images->apoio_09 = al_load_bitmap(datapath_dark_03);
            _things->images->apoio_10 = al_load_bitmap(datapath_pause_continue);
            _things->images->apoio_11 = al_load_bitmap(datapath_pause_exit);
            _things->images->apoio_12 = al_load_bitmap(datapath_saving_score);
            _things->images->apoio_13 = al_load_bitmap(datapath_block_end);

            printer("{>DYNAMIC_LOADER}> Jogo carregado!");
            _things->what_to_load = WAITING;
            _things->is_loading   = false;
            break;
        default:
            _things->is_loading   = false;
        }
        switch (_things->what_to_unload)
        {
        case APOIO_THINGS:
            _things->is_unloading = true;
            printer("{>DYNAMIC_LOADER}> Descarregando \"apoios\" no background dinamicamente.");

            clear_memory(APOIO_THINGS,_things->images);

            printer("{>DYNAMIC_LOADER}> \"Apoios\" descarregados.");
            _things->what_to_unload = WAITING;
            _things->is_unloading = false;
            break;
        case ANIMATION_KO:
            _things->is_unloading = true;
            printer("{>DYNAMIC_LOADER}> Descarregando \"animation\" no background dinamicamente.");

            clear_memory(ANIMATION_KO,_things->images);

            printer("{>DYNAMIC_LOADER}> \"Animation\" descarregados.");
            _things->what_to_unload = WAITING;
            _things->is_unloading = false;
            break;
        default:
            _things->is_unloading = false;
        }
    }
    printer("{>DYNAMIC_LOADER}> FUI DETONADO (Alguém pediu para eu parar, parei!)");
    return thr;
}

void *dynamic_keytest(ALLEGRO_THREAD *thr, void *data)
{
    printer("\n{>DYNAMIC_KEYTEST}> INICIADO! ~multitask\n");
    complete_things *__things;
    __things = (complete_things *)data;

    ALLEGRO_EVENT_QUEUE *event_queue;
    event_queue = __things->event_queue;
    ALLEGRO_DISPLAY *display;
    display = __things->display;
    char keyer=0, old_key;
    while (!__things->quitting)
    {
        old_key = keyer;
        keyer = raw_key_get(event_queue,display);
        __things->key_get_write = keyer;
        if (keyer<-49)
        {
            switch (keyer)
            {
            case UP_KEY:
                __things->key_get_game = 1;
                break;
            case DOWN_KEY:
                __things->key_get_game = 2;
                break;
            case LEFT_KEY:
                __things->key_get_game = 3;
                break;
            case RIGHT_KEY:
                __things->key_get_game = 4;
                break;
            }
        }
        else __things->key_get_game = 0;

        if (keyer == old_key && old_key !=0)
            __things->key_get_write_push  = true;
        else __things->key_get_write_push = false;
    }

    printer("{>DYNAMIC_KEYTEST}> FUI DETONADO (Alguém pediu para eu parar, parei!)");
    return NULL;
}
/*
void *crash_handler(ALLEGRO_THREAD *thr, void *data)
{
    printer("\n{>DYNAMIC_CRASH_HANDLER}> INICIADO! ~multitask\n");
    complete_things *__things;
    __things = (complete_things *)data;
    ALLEGRO_DISPLAY *display2;

}
*/