#include "menus.h"

    /// MODELO:
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|                                         |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

const int version=1000;

///Esse cara controla todas as funções com seus retornos.
void seeker(ALLEGRO_DISPLAY *display, ALLEGRO_DISPLAY_MODE disp_data, ALLEGRO_EVENT_QUEUE *event_queue, int times, const char *chars, int render_x2, int render_y2)
{
    printer("[Seeker entrou]");
    al_set_new_bitmap_flags(ALLEGRO_KEEP_BITMAP_FORMAT);

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|         Variáveis da função             |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Seeker] Carregando variáveis para minhas funções...");

    char my_int;
    ALLEGRO_FONT *font;
    ALLEGRO_THREAD *representation_01, *representation_02/*, *representation_03*/;
    int other_int, mykeya=0, go=0, side=0;
    complete_things *_things;
    _things=(complete_things*)malloc(sizeof(complete_things));
    (_things->images)=(pauses_anim*)malloc(sizeof(pauses_anim));
    if (_things==NULL || _things->images==NULL)
        exit_app(display,"[Seeker-E00] Falha ao criar base de tudo (malloc)");
    all_null(_things);

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|       Load de "coisas do Allegro"       |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    //printer("[Seeker] Carregando fontes e imagens...");

    printer("[Seeker] Iniciando tasks em background");

    _things->font              = al_load_ttf_font(datapath_DejaVuSans,sqrt(render_x2*render_y2)/28.8,0);
    _things->fps_real          = 60;
    _things->posxy             = -63;
    _things->timer             = al_get_time();
    _things->what_to_load      = WAITING;
    _things->what_to_unload    = WAITING;
    _things->key_get_game      = 0;
    _things->fps_real          = 0;
    _things->key_get_write     = 0;
    _things->is_loading        = false;
    _things->quitting          = false;
    _things->event_queue       = event_queue;
    _things->display           = display;
    _things->render_x          = render_x2;
    _things->render_y          = render_y2;

    printf("Recognized resolution: %d x %d",_things->render_x, _things->render_y);

    representation_01 = _things->keyer;
    representation_02 = _things->imager;
    //representation_03 = _things->crash_handler;
    representation_01 = al_create_thread(dynamic_keytest,(void *)_things);
    //representation_02 = al_create_thread(dynamic_loader, (void *)_things);
    //representation_03 = al_create_thread(crash_handler,  (void *)_things);

    //al_start_thread(representation_03);
    al_start_thread(representation_01);
    //al_start_thread(representation_02);

	//std::thread representation_02_thr(dynamic_loaderU, _things);

    al_rest(0.5);

    _things->chosen = -1; // way to tell what to load (another way ;-;)
	while (!load_correct(_things));
    _things->chosen = 10;
	while (!load_correct(_things));

    ///| Toda função terá ponteiros auxiliares para apontar pros grandes |///
    ALLEGRO_BITMAP *log, *buf, *vig;

    log = _things->images->logo; // LOGO MEANS INTRO
    buf = _things->images->buffer;
    vig = _things->images->vignette;
    font= _things->font;


    //printer("[Seeker] Carregados.");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|   Verificação dos arquivos carregados   |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    //printer("[Seeker] Verificando arquivos recém abertos...");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///| Desenhando fundo preto de início padrão |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Seeker] Carregando \"background\" padrão de início (preto)...");

    al_set_target_bitmap(buf);
    al_clear_to_color(al_map_rgb(0,0,0));
    frame_maker(_things);

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|  Animação de StartUp com Skip (teclas)  |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Seeker] Iniciando animações e retornando com mensagens no final delas...");

    for (other_int=0;other_int<372;other_int++)
    {
        if (go==0)
        {
            if (side<1 && side>-1) side++;
            if (side<2 && side>-2) side++;
            if (side<6 && side>-6) side++;
            if (side<24 && side>-24) side++;
            if (side>=40) go=1;
            side++;
        }
        else if (go==1)
        {
            if (side<1 && side>-1) side--;
            if (side<2 && side>-2) side--;
            if (side<6 && side>-6) side--;
            if (side<24 && side>-24) side--;
            if (side<=-40) go=0;
            side--;
        }
        al_set_target_bitmap(buf);
        al_clear_to_color(al_map_rgb(0,0,0));
        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        al_set_target_bitmap(buf);
        al_draw_textf(font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*(850+((2.0*side)/3))/1920,al_get_bitmap_height(buf)*534.0/1080,0,"Loading...");

        if (INDEV == true) al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"Build %ds",version);

        frame_maker(_things);

        if (other_int>128 && side<=2 && side>=-2 || _things->key_get_write!=0)
            break;
    }


    for (other_int=127;other_int>0;other_int-=2)
    {
        if (mykeya!=0)
            break;
        my_int=2*other_int;
        al_set_target_bitmap(buf);
        al_clear_to_color(al_map_rgb(0,0,0));
        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        al_draw_textf(font,al_map_rgb(my_int,my_int,my_int),al_get_bitmap_width(buf)*850.0/1920,al_get_bitmap_height(buf)*(550-(other_int/8.0))/1080,0,"Loading...");

        if (INDEV == true) al_draw_textf(font,al_map_rgb(255,255,255),0,0,0,"Build %ds",version);
        if (_things->key_get_write!=0)
            other_int+=(128-other_int);

        frame_maker(_things);
    }

    log=NULL;
    buf=NULL;

    printer("[Seeker] Fim das animações de entrada do jogo, entrando no \"Controle de Função\"...");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///| O então controlador de funções V1.0.2B  |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Seeker] De agora em diante serei apenas um condutor de funções.\n");

    while (true)
    {
		while (!load_correct(_things));
        switch (_things->chosen){
        case EXITE:
            printer("[Seeker] Chosen: EXIT");
            exit_app(_things->display,"[Seeker-E02] Saí pelo modo usual.");
            break;
        case MENU:
            printer("[Seeker] Chosen: MENU");
            menu(_things);
            break;
        case START:
            printer("[Seeker] Chosen: START_MENU");
            menu_start(_things);
            break;
        case INSTRUCTIONS:
            printer("[Seeker] Chosen: INSTRUCTIONS");
            menu_instructions(_things);
            break;
        case RECORDS:
            printer("[Seeker] Chosen: RECORDS_SCREEN");
            menu_records(_things);
            break;
        case CONFIG_OCULT:
            printer("[Seeker] Chosen: CONFIG_OCULT");
            configurer(_things);
            break;
        case GAME_EASY: case GAME_MEDIUM: case GAME_INSANE:
            printer("[Seeker] Chosen: GAMEPLAY");
            game_play(_things);
            break;
        default:
            exit_app(_things->display,"[Seeker-E03] Saí por última opção (buracos?)");
        }
        /// clear_memory(APAUSESANIM_INSIDE,_things->images);
        printer("[Seeker] Computando...");
    }
	//representation_02_thr.join();
}

/// //////////////////////////////////////////////////////////////////////////////////////// ///
///|****************************************************************************************|///
///|*--------------------------------------------------------------------------------------*|///
///|****************************************************************************************|///
/// //////////////////////////////////////////////////////////////////////////////////////// ///

int menu(complete_things *__things)
{
    printer("[Menu entrou]");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|          Variáveis da função            |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Menu] Carregando variáveis...");

    bool exite=false;
    ALLEGRO_BITMAP *log, *vig, *buf, *opt_01, *opt_02, *opt_03, *opt_04;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|    Ligações e carregamento de imagem    |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    log    = __things->images->logo;
    vig    = __things->images->vignette;
    buf    = __things->images->buffer;
    opt_01 = __things->images->apoio_01;
    opt_02 = __things->images->apoio_02;
    opt_03 = __things->images->apoio_03;
    opt_04 = __things->images->apoio_04;
    __things->option = 1;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|   Início do funcionamento da função     |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Menu] Entrando na animação de entrada...");

    draw_effect(true,__things);

    printer("[Menu] Entrada do usuário ativada, esperando comandos.");

    while (!exite){

        if (__things->option > 3)
            __things->option = 0;
        if (__things->option < 0)
            __things->option = 3;

        background_menu_animation(__things);

        ///418 133
        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        if      (__things->option==0) draw_bitmap_to_buff (opt_01,buf,0,0,0,0,0);
        else if (__things->option==1) draw_bitmap_to_buff (opt_02,buf,0,0,0,0,0);
        else if (__things->option==2) draw_bitmap_to_buff (opt_03,buf,0,0,0,0,0);
        else if (__things->option==3) draw_bitmap_to_buff (opt_04,buf,0,0,0,0,0);
        draw_bitmap_to_buff (vig,buf,0,0,0,0,0);

        frame_maker(__things);

        switch (__things->key_get_write){
        case UP_KEY:
            __things->option++;
            break;
        case DOWN_KEY:
            __things->option--;
            break;
        case ENTER_KEY:
            __things->option+=10;
            exite=true;
            break;
        case '1':
            __things->option=0;
            exite=true;
            break;
        case '2':
            __things->option=1;
            exite=true;
            break;
        case '3':
            __things->option=2;
            exite=true;
            break;
        case ESC_KEY: case '4':
            return EXITE;
        }
    }

    __things->chosen = __things->option;

    printer("[Menu] Escolhido, processando, animando e saindo...");

    end_of_func(__things,APOIO_THINGS);

    printer("[Menu saiu]");
    return 0;
}

/// //////////////////////////////////////////////////////////////////////////////////////// ///
///|****************************************************************************************|///
///|*--------------------------------------------------------------------------------------*|///
///|****************************************************************************************|///
/// //////////////////////////////////////////////////////////////////////////////////////// ///

int menu_start(complete_things *__things)
{
    printer("[Start entrou]");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|          Variáveis da função            |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    bool exite=false;
    ALLEGRO_BITMAP *log, *vig, *buf, *opt_01, *opt_02, *opt_03;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|    Ligações e carregamento de imagem    |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    log              = __things->images->logo;
    vig              = __things->images->vignette;
    buf              = __things->images->buffer;
    opt_01           = __things->images->apoio_01;
    opt_02           = __things->images->apoio_02;
    opt_03           = __things->images->apoio_03;
    __things->option = 1;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|   Início do funcionamento da função     |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Start] Entrando na animação de entrada...");

    draw_effect(true,__things);

    printer("[Start] Entrada do usuário ativada, esperando comandos.");

    while (!exite){

        if (__things->option>2)
            __things->option=0;
        if (__things->option<0)
            __things->option=2;

        background_menu_animation(__things);

        ///418 133
        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        if      (__things->option==0) draw_bitmap_to_buff (opt_01,buf,0,0,0,0,0);
        else if (__things->option==1) draw_bitmap_to_buff (opt_02,buf,0,0,0,0,0);
        else if (__things->option==2) draw_bitmap_to_buff (opt_03,buf,0,0,0,0,0);
        draw_bitmap_to_buff (vig,buf,0,0,0,0,0);

        frame_maker(__things);

        switch (__things->key_get_write){
        case UP_KEY:
            __things->option++;
            break;
        case DOWN_KEY:
            __things->option--;
            break;
        case ENTER_KEY:
            __things->option+=10;
            exite=true;
            break;
        case '1':
            __things->option=0;
            exite=true;
            break;
        case '2':
            __things->option=1;
            exite=true;
            break;
        case '3':
            __things->option=2;
            exite=true;
            break;
        case ESC_KEY:
            exite=true;
            break;
        }
    }

    if (__things->option>=10)
        __things->option=10;
    else __things->option+=7;

    __things->chosen = __things->option;

    printer("[Start] Escolhido, processando, animando e saindo...");

    end_of_func(__things,APOIO_THINGS);

    printer("[Start saiu]");
    return 0;
}

///Carrega instruções, monta tela, mostra tela e destrói tudo (1)
int menu_instructions(complete_things *__things)
{
    printer("[Instructions entrou]");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|          Variáveis da função            |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    bool exite=false, config=false;
    ALLEGRO_BITMAP *log, *vig, *buf, *ins;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|    Ligações e carregamento de imagem    |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    log = __things->images->logo;
    vig = __things->images->vignette;
    buf = __things->images->buffer;
    ins = __things->images->apoio_01;
    __things->option = 1;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|   Início do funcionamento da função     |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Instructions] Entrando na animação de entrada...");

    draw_effect(true,__things);

    printer("[Instructions] Entrada do usuário ativada, esperando comandos.");

    while (!exite){
        background_menu_animation(__things);

        ///418 133
        draw_bitmap_to_buff(log,buf,0,0,418,133,0);

        draw_bitmap_to_buff (ins,buf,0,0,0,0,0);
        draw_bitmap_to_buff (vig,buf,0,0,0,0,0);

        frame_maker(__things);

        switch (__things->key_get_write){
        case 'C':
            config = true;
            __things->chosen = CONFIG_OCULT;
            exite=true;
            break;
        default:
            if (__things->key_get_write != 0) exite=true;
        }
    }

    printer("[Instructions] Escolhido, processando, animando e saindo...");

    if (config==false) __things->chosen = 10;
    else __things->chosen = 4;

    end_of_func((complete_things*)__things,APOIO_THINGS);

    printer("[Instructions saiu]");
    return 0;
}

///Carrega arquivo, monta tela, mostra tela e destrói tudo (2)
int menu_records(complete_things *__things)
{
    printer("[Records entrou]");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|          Variáveis da função            |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    bool exite=false;
    defaultrecords manobonito[10];
    ALLEGRO_BITMAP *log, *vig, *buf, *rec;
    ALLEGRO_FONT *font;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|    Ligações e carregamento de imagem    |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    log  = __things->images->logo;
    vig  = __things->images->vignette;
    buf  = __things->images->buffer;
    rec  = __things->images->apoio_01;
    font = __things->font;
    __things->option = 1;

    rec_reader("records.txt",manobonito);

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|   Início do funcionamento da função     |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Records] Entrando na animação de entrada...");

    draw_effect(true,__things);

    printer("[Records] Entrada do usuário ativada, esperando comandos.");

    while (!exite){
        background_menu_animation(__things);

        ///418 133
        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        draw_bitmap_to_buff(rec,buf,0,0,0,0,0);

        al_set_target_bitmap(buf);

        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*400.0/1080,0,"%s > %d",manobonito[0].nick,manobonito[0].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*450.0/1080,0,"%s > %d",manobonito[1].nick,manobonito[1].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*500.0/1080,0,"%s > %d",manobonito[2].nick,manobonito[2].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*550.0/1080,0,"%s > %d",manobonito[3].nick,manobonito[3].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*600.0/1080,0,"%s > %d",manobonito[4].nick,manobonito[4].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*650.0/1080,0,"%s > %d",manobonito[5].nick,manobonito[5].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*700.0/1080,0,"%s > %d",manobonito[6].nick,manobonito[6].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*750.0/1080,0,"%s > %d",manobonito[7].nick,manobonito[7].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*800.0/1080,0,"%s > %d",manobonito[8].nick,manobonito[8].score);
        al_draw_textf (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*850.0/1080,0,"%s > %d",manobonito[9].nick,manobonito[9].score);

        draw_bitmap_to_buff (vig,buf,0,0,0,0,0);

        frame_maker(__things);

        if (__things->key_get_write != 0)
            exite=true;
    }
    printer("[Records] Escolhido, processando, animando e saindo...");

    __things->chosen = 10;
    end_of_func(__things,APOIO_THINGS);

    printer("[Records saiu]");
    return 0;
}

/// CONFIG

int configurer(complete_things *__things)
{
    printer("\n[Config Joined]");

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|          Variáveis da função            |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    int  tamxbitmap, tamybitmap;
    bool exite=false, entrada=false, savesettings=false, is_fullscreen=false;
    ALLEGRO_DISPLAY_MODE disp_data;
    FILE *config;
    ALLEGRO_BITMAP *log, *vig, *buf;
    ALLEGRO_FONT *font;

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|    Ligações e carregamento de imagem    |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
    prepare_txts(&is_fullscreen,&(disp_data.width),&(disp_data.height),&tamxbitmap,&tamybitmap);
    log  = __things->images->logo;
    vig  = __things->images->vignette;
    buf  = __things->images->buffer;
    font = __things->font;
    tamxbitmap = al_get_bitmap_width(buf);
    tamybitmap = al_get_bitmap_height(buf);
    __things->option = 0;

    draw_effect(true,__things);

    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///
    ///|   Início do funcionamento da função     |///
    ///|*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*|///

    printer("[Config] Entrando no WHILE.");

	clock_t lastkey = clock();

    while (!exite){
        /*if (tamxbitmap>1920)
            tamxbitmap=1920;*/
        if (tamxbitmap<32)
            tamxbitmap=32;
        /*if (tamybitmap>1080)
            tamybitmap=1080;*/
        if (tamybitmap<24)
            tamybitmap=24;

        if (__things->option>2)
            __things->option=0;
        if (__things->option<0)
            __things->option=2;

        background_menu_animation(__things);

        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        al_set_target_bitmap(buf);

        ///| Impossível Draw Insano de Config |///

        al_draw_textf                                            (font,al_map_rgb(  0,  0,  0),al_get_bitmap_width(buf)*((452.0)/1920),al_get_bitmap_height(buf)*402.0/1080,0,"Screen Base Resolution: (Press C to Change)");
        al_draw_textf                                            (font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*400.0/1080,0,"Screen Base Resolution: (Press C to Change)");
        ///                                         |            |
        al_draw_textf                                            (font,al_map_rgb(  0,  0,  0),al_get_bitmap_width(buf)*((453.0)/1920),al_get_bitmap_height(buf)*473.0/1080,0,"Width: %d",tamxbitmap);
        if (__things->option==0 && !entrada)        al_draw_textf(font,al_map_rgb(255,255,125),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*470.0/1080,0,"Width: %d",tamxbitmap);
        else if (__things->option==0 && entrada)    al_draw_textf(font,al_map_rgb(255, 25, 25),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*470.0/1080,0,"Width: %d",tamxbitmap);
        else                                        al_draw_textf(font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*470.0/1080,0,"Width: %d",tamxbitmap);
        ///                                         |            |
        al_draw_textf                                            (font,al_map_rgb(  0,  0,  0),al_get_bitmap_width(buf)*((453.0)/1920),al_get_bitmap_height(buf)*543.0/1080,0,"Height: %d",tamybitmap);
        if (__things->option==1 && !entrada)        al_draw_textf(font,al_map_rgb(255,255,125),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*540.0/1080,0,"Height: %d",tamybitmap);
        else if (__things->option==1 && entrada)    al_draw_textf(font,al_map_rgb(255, 25, 25),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*540.0/1080,0,"Height: %d",tamybitmap);
        else                                        al_draw_textf(font,al_map_rgb(255,255,255),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*540.0/1080,0,"Height: %d",tamybitmap);
        ///                                         |            |
        if(is_fullscreen)                           al_draw_textf(font,al_map_rgb(  0,  0,  0),al_get_bitmap_width(buf)*((453.0)/1920),al_get_bitmap_height(buf)*613.0/1080,0,"Fullscreen: TRUE");
        if(!is_fullscreen)                          al_draw_textf(font,al_map_rgb(  0,  0,  0),al_get_bitmap_width(buf)*((453.0)/1920),al_get_bitmap_height(buf)*613.0/1080,0,"Fullscreen: FALSE");
        if (__things->option==2){
            if( is_fullscreen && !entrada)          al_draw_textf(font,al_map_rgb(255,255,125),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*610.0/1080,0,"Fullscreen: TRUE");
            if(!is_fullscreen && !entrada)          al_draw_textf(font,al_map_rgb(255,255,125),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*610.0/1080,0,"Fullscreen: FALSE");
            if( is_fullscreen && entrada)           al_draw_textf(font,al_map_rgb(255, 25, 25),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*610.0/1080,0,"Fullscreen: TRUE");
            if(!is_fullscreen && entrada)           al_draw_textf(font,al_map_rgb(255, 25, 25),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*610.0/1080,0,"Fullscreen: FALSE");}
        ///                                         |            |
        else if (is_fullscreen)                     al_draw_textf(font,al_map_rgb(255,255,225),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*610.0/1080,0,"Fullscreen: TRUE");
        else if (!is_fullscreen)                    al_draw_textf(font,al_map_rgb(255,255,225),al_get_bitmap_width(buf)*((450.0)/1920),al_get_bitmap_height(buf)*610.0/1080,0,"Fullscreen: FALSE");

        ///| Fim do Impossível Draw Insano de Config |///

        draw_bitmap_to_buff(vig,buf,0,0,418,133,0);

        frame_maker(__things);

        if (!entrada)
        {
			if (clock() - lastkey > CLOCKS_PER_SEC / 6) {
				switch (__things->key_get_write) {
				case DOWN_KEY:
					__things->option++;
					break;
				case UP_KEY:
					__things->option--;
					break;
				case ENTER_KEY:
					exite = true;
					savesettings = true;
					break;
				case ESC_KEY:
					exite = true;
					break;
				case 'C':
					entrada = true;
				}
				lastkey = clock();
			}
        }
        else if (__things->option==0)
        {
            switch (__things->key_get_write){
            case UP_KEY:
                tamxbitmap++;
                break;
            case DOWN_KEY:
                tamxbitmap--;
                break;
            case ENTER_KEY: case ESC_KEY: case 'C':
                entrada=false;
            }
        }
        else if (__things->option==1)
        {
            switch (__things->key_get_write){
            case UP_KEY:
                tamybitmap++;
                break;
            case DOWN_KEY:
                tamybitmap--;
                break;
            case ENTER_KEY: case ESC_KEY: case 'C':
                entrada=false;
            }
        }
        else if (__things->option==2)
        {
            switch (__things->key_get_write){
            case UP_KEY: case DOWN_KEY:
                if (is_fullscreen)
                    is_fullscreen=false;
                else is_fullscreen=true;
                break;
            case ENTER_KEY: case ESC_KEY: case 'C':
                entrada=false;
            }
        }
    }

    if (savesettings)
    {
        printer("[Config] Salvando arquivo de configuração...");
		fopen_s(&config, "config.txt", "w");
		if (!config) exit(0);

        __things->option=0;
        if (is_fullscreen)
            __things->option=1;

        if (config!=NULL)
        {
            if (__things->option==1) fprintf(config, "#Configuration_file\nfullscreen= true\nscreensize= %dx%d\n",tamxbitmap,tamybitmap);
            else                     fprintf(config,"#Configuration_file\nfullscreen= false\nscreensize= %dx%d\n",tamxbitmap,tamybitmap);
        }

        printer("[Config] Preparando-se para atualizar tela...");

        fclose(config);

        __things->what_to_unload = APOIO_THINGS;

        al_destroy_display(__things->display);

        printer("[Config] Espere um momento...");

        disp_data.width  = 0;
        disp_data.height = 0;

        printer("[Config] ...");

        al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
        prepare_txts(&is_fullscreen,&(disp_data.width),&(disp_data.height),&tamxbitmap,&tamybitmap);

        printer("[Config] ...");

        if (is_fullscreen) al_set_new_display_flags(ALLEGRO_FULLSCREEN);
        else al_set_new_display_flags(ALLEGRO_WINDOWED);
        __things->display = al_create_display(disp_data.width,disp_data.height);

        printer("[Config] ...");
    }
    __things->option = 0;
    __things->chosen = 10;

    end_of_func(__things,APOIO_THINGS);

    printer("[Config Exit]");
    return 0;
}

///Inicia o jogo

int game_play(complete_things *__things)
{
    int retorno, moves=0, tempos=0, relation, i, mykeya=0, mykeyac=0, tamx, tamy, mapa_x, mapa_y, scoreplayersuccess; ///mapax 0 a 14 e mapay 0 a 7
    double timer_s, timer_now, time_paused, mins=0, segs, poscharx=0, poschary=0, poscharr=0, antes = 0, relacao_x, relacao_y, basex, basey, referenciax=0.0, referenciax_low, pause=0.0;
    bool exite=false, savescore=false, pause_b=false, show_result = false, result_go=false;
    char ch, nomeplayersuccess[24];
    FILE *temp;
    retorno=__things->chosen%10; tamy=8;

    ALLEGRO_BITMAP *buf, *pse, *drk, *prs, *bkg, *blk, *bl2, *vig, *log, *p_ef;
    ALLEGRO_FONT *font;

    if      (__things->chosen%10==7)
        tamx=EASY;
    else if (__things->chosen%10==8)
        tamx=MEDIUM;
    else if (__things->chosen%10==9)
        tamx=HARD;

    log = __things->images->logo;
    vig = __things->images->vignette;
    buf = __things->images->buffer;
    bkg = __things->images->apoio_01;
    blk = __things->images->apoio_02;
    bl2 = __things->images->apoio_03;
    prs = __things->images->apoio_04;
    pse = __things->images->apoio_10;
    font= __things->font;
    __things->option = 0;

    printer("[Game-Play entrou]");

    if (game_gerarmapa(__things) == MENU)
        return MENU;

	fopen_s(&temp, "map.txt", "r");
    if (temp==NULL)
        exit_app(__things->display,"[Game-Play> Impossível carregar um mapa (arquivo bloqueado de ser lido)");


    relacao_x=(al_get_bitmap_width(buf)*1.0/1920.0);
    relacao_y=(al_get_bitmap_height(buf)*1.0/1080.0);

    timer_s=al_get_time();
    while (!exite)
    {
        relation=0;
        referenciax_low=referenciax;
        if (referenciax_low>=(128.0*relacao_x))
        {
            while (referenciax_low>=(128.0*relacao_x))
            {
                referenciax_low=referenciax_low*1.0-(128.0*relacao_x);
                relation++;
            }
            if (relation>=(tamx-14))
            {
                referenciax_low=0.0;
                if (poscharx>(1810.0*relacao_x) && !show_result)
                    savescore=true;
            }
        }
        if (poscharx>(al_get_bitmap_width(buf)*0.7) && relation<(tamx-14) && !show_result)
        {
            poscharx-=(2.0*relacao_x);
            referenciax+=(2.0*relacao_x);
        }
        if (poscharx>(al_get_bitmap_width(buf)*0.8) && relation<(tamx-14) && !show_result)
        {
            poscharx-=(4.0*relacao_x);
            referenciax+=(4.0*relacao_x);
        }
        if (poscharx>(al_get_bitmap_width(buf)*0.9) && relation<(tamx-14) && !show_result)
        {
            poscharx-=(12.0*relacao_x);
            referenciax+=(12.0*relacao_x);
        }

        if (moves<0)
            moves=0;
        if (tempos>0) tempos--;

        if (__things->key_get_write == F1_KEY)
            show_result = true;

        if (__things->key_get_write == ESC_KEY)
        {
            if (pauser_time(__things) == 10)
                return 10;
        }
        else if (__things->key_get_write != 0 && !show_result)
        {
            tempos+=2;
            moves++;
        }

        if (tempos>20) tempos=20;

        draw_bitmap_to_buff(bkg,buf,0,0,0,0,0);
        al_set_target_bitmap(buf);

        mapa_y=-1;
        basey=(56.0+128.0*(mapa_y))*relacao_y;
        for (mapa_x=-1;mapa_x<17;mapa_x++)
        {
            basex=(mapa_x*128.0)*relacao_x;
            al_draw_scaled_bitmap(blk,0,0,128,128,basex,basey,128.0*relacao_x,128.0*relacao_y,0);
        }

        fseek(temp,0,SEEK_SET);

        mapa_x=0; mapa_y=0;
        basex=(mapa_x*128.0)*relacao_x;
        basey=(56.0+128.0*(mapa_y))*relacao_y;

        if (tempos==0) prs = __things->images->apoio_04;

        while (!feof(temp))
        {
            fseek(temp,relation,SEEK_CUR);
            for (i=0;i<17;i++)
            {
                ch=fgetc(temp);

                if (ch=='0')
                {
                    al_draw_scaled_bitmap(blk,0,0,128,128,basex-referenciax_low,basey,128.0*relacao_x,128.0*relacao_y,0);

                    if ((basex-(24.0*relacao_x)-referenciax_low)<poscharx && (basex+(132.0*relacao_x)-referenciax_low)>poscharx && (basey-(24.0*relacao_y))<poschary && (basey+(132.0*relacao_y))>poschary && !show_result)
                    {
                        poscharx+=7.0*relacao_x;
                        if ((basex-(24.0*relacao_x)-referenciax_low)<poscharx && (basex+(132.0*relacao_x)-referenciax_low)>poscharx && (basey-(24.0*relacao_y))<poschary && (basey+(132.0*relacao_y))>poschary)
                        {
                            poscharx-=14.0*relacao_x;
                            if ((basex-(24.0*relacao_x)-referenciax_low)<poscharx && (basex+(132.0*relacao_x)-referenciax_low)>poscharx && (basey-(24.0*relacao_y))<poschary && (basey+(132.0*relacao_y))>poschary)
                            {
                                poscharx+=7.0*relacao_x;
                                poschary+=7.0*relacao_y;
                                if ((basex-(24.0*relacao_x)-referenciax_low)<poscharx && (basex+(132.0*relacao_x)-referenciax_low)>poscharx && (basey-(24.0*relacao_y))<poschary && (basey+(132.0*relacao_y))>poschary)
                                {
                                    poschary-=14.0*relacao_y;
                                    if ((basex-(24.0*relacao_x)-referenciax_low)<poscharx && (basex+(132.0*relacao_x)-referenciax_low)>poscharx && (basey-(24.0*relacao_y))<poschary && (basey+(132.0*relacao_y))>poschary)
                                    {
                                        poschary+=7.0*relacao_y;
                                        poscharx+=cos(((poscharr+90.0)/180)*ALLEGRO_PI)*((tempos+0.5)*relacao_x);
                                        poschary+=sin(((poscharr+90.0)/180)*ALLEGRO_PI)*((tempos+0.5)*relacao_y);
                                    }
                                }
                            }
                        }
                    }
                    if ((basex-referenciax_low)<poscharx && (basex+(128.0*relacao_x)-referenciax_low)>poscharx && basey<poschary && basey+(128.0*relacao_y)>poschary && !show_result)
                    {
                        savescore=true;
                        moves=moves*1000;
                        mins=segs*10;
                    }
                }
                if (ch=='2' && show_result==true)
                {
                    al_draw_scaled_bitmap(bl2,0,0,64,64,basex-referenciax_low,basey,128.0*relacao_x,128.0*relacao_y,0);
                }
                if (ch=='\n')
                {
                    blk = __things->images->apoio_13;
                    al_draw_scaled_bitmap(blk,0,0,128,128,basex-referenciax_low,basey,128.0*relacao_x,128.0*relacao_y,0);
                    blk = __things->images->apoio_02;
                    i=18;
                }
                mapa_x++;
                basex=(mapa_x*128.0)*relacao_x;
            }
            al_draw_scaled_bitmap(blk,0,0,128,128,basex-referenciax_low,basey,128.0*relacao_x,128.0*relacao_y,0);
            mapa_y++; mapa_x=0;
            basex=(mapa_x*128.0)*relacao_x;
            basey=(56.0+128.0*(mapa_y))*relacao_y;
            while (ch!='\n' && ch!=EOF)
                ch=fgetc(temp);
        }

        if (retorno==9 && !show_result){
            if (sin(1*segs*ALLEGRO_PI)<=-0.5){
                drk = __things->images->apoio_07;
                al_draw_scaled_bitmap(drk,0,0,al_get_bitmap_width(drk),al_get_bitmap_height(drk),poscharx-(1920.0*relacao_x),poschary-(1080.0*relacao_y),(3840.0*relacao_x),(2160.0*relacao_y),0);
            }
            else if (sin(1*segs*ALLEGRO_PI)<=0.5){
                drk = __things->images->apoio_08;
                al_draw_scaled_bitmap(drk,0,0,al_get_bitmap_width(drk),al_get_bitmap_height(drk),poscharx-(1920.0*relacao_x),poschary-(1080.0*relacao_y),(3840.0*relacao_x),(2160.0*relacao_y),0);
            }
            else{
                drk = __things->images->apoio_09;
                al_draw_scaled_bitmap(drk,0,0,al_get_bitmap_width(drk),al_get_bitmap_height(drk),poscharx-(1920.0*relacao_x),poschary-(1080.0*relacao_y),(3840.0*relacao_x),(2160.0*relacao_y),0);
            }
        }

        timer_now=al_get_time();
        if (!show_result) segs=1.0*timer_now-timer_s-pause;

        if (retorno>=7 && segs>30 && relation<(tamx-14) && !show_result)
        {
            referenciax+=relacao_x;
            poscharx-=relacao_x;
        }
        if (retorno>=8 && segs>60 && relation<(tamx-14) && !show_result)
        {
            referenciax+=relacao_x;
            poscharx-=relacao_x;
        }
        if (retorno==9 && segs>45 && relation<(tamx-14) && !show_result)
        {
            referenciax+=relacao_x;
            poscharx-=relacao_x;
        }
        if (retorno==9 && segs>75 && relation<(tamx-14) && !show_result)
        {
            referenciax+=2.0*relacao_x;
            poscharx-=2.0*relacao_x;
        }
        if (show_result && !result_go)
        {
            moves=0;
            if (referenciax>=64*relacao_x)
            {
                referenciax-=(1.0/50.0)*relacao_x*referenciax;
                poscharx+=(1.0/50.0)*relacao_x*referenciax;
            }
            else
            {
                result_go=true;
            }
        }
        if (show_result && result_go && relation<(tamx-14))
        {
            referenciax+=10.0*relacao_x;
            poscharx-=10.0*relacao_x;
            time_paused=al_get_time();
        }
        if (show_result && result_go && relation>=(tamx-14))
        {
            if (antes-time_paused>4)
                break;
        }

        mins=0;
        min_e_seg(&mins,&segs);

        ///| Bloqueio de saída de personagem |///
        if (poscharx<(24.0*relacao_x) && !show_result)
        {
            poscharx=(24.0*relacao_x);
        }
        else if (poscharx>(1920.0-24.0)*relacao_x && !show_result)
        {
            poscharx=(1920.0-24.0)*relacao_x;
        }
        if (poschary<(56.0+24.0)*relacao_y && !show_result)
        {
            poschary=(56.0+24.0)*relacao_y;
        }
        else if (poschary>(1080.0-24.0)*relacao_y && !show_result)
        {
            poschary=(1080.0-24.0)*relacao_y;
        }

        al_draw_scaled_rotated_bitmap(prs,24,24,poscharx,poschary,relacao_x,relacao_y,(poscharr/180)*ALLEGRO_PI,0);

        ///| Draws de textos |///
                               al_draw_textf(font,al_map_rgb(  0,  0,  0),1102.0*relacao_x ,0 , 0,"Meters: %d",moves);
                               al_draw_textf(font,al_map_rgb(  0,  0,  0),1502.0*relacao_x ,0 , 0,"Time: ");
        if (mins<10)           al_draw_textf(font,al_map_rgb(  0,  0,  0),1702.0*relacao_x ,0 , 0,"%.0f:%.3f",mins,segs);
        else if (mins<100)     al_draw_textf(font,al_map_rgb( 50,  0,  0),1682.0*relacao_x ,0 , 0,"%.0f:%.2f",mins,segs);
        else if (mins<500)     al_draw_textf(font,al_map_rgb(150,  0,  0),1662.0*relacao_x ,0 , 0,"%.0f:%.1f",mins,segs);
        else if ((mins/60)<48) al_draw_textf(font,al_map_rgb(200,  0,  0),1652.0*relacao_x ,0 , 0,"%.0f h",mins/60);
        else                   al_draw_textf(font,al_map_rgb(255,  0,  0),1672.0*relacao_x ,0 , 0,"%.0f days",(mins/60)/24);
                               al_draw_textf(font,al_map_rgb(255,255,255),1100.0*relacao_x ,0 , 0,"Meters: %d",moves);
                               al_draw_textf(font,al_map_rgb(255,255,255),1500.0*relacao_x ,0 , 0,"Time:");
        if (mins<10)           al_draw_textf(font,al_map_rgb(255,255,255),1700.0*relacao_x ,0 , 0,"%.0f:%.3f",mins,segs);
        else if (mins<100)     al_draw_textf(font,al_map_rgb(255,255,255),1680.0*relacao_x ,0 , 0,"%.0f:%.2f",mins,segs);
        else if (mins<500)     al_draw_textf(font,al_map_rgb(255,255,255),1660.0*relacao_x ,0 , 0,"%.0f:%.1f",mins,segs);
        else if ((mins/60)<48) al_draw_textf(font,al_map_rgb(255,255,255),1650.0*relacao_x ,0 , 0,"%.0f h",mins/60);
        else                   al_draw_textf(font,al_map_rgb(255,255,255),1670.0*relacao_x ,0 , 0,"%.0f days",(mins/60)/24);
        ///| Draws de textos |///

        ///| Draws do personagem |///
        //down up left right
        if (poscharr>350)
            poscharr=-10;
        else if (poscharr<-10)
            poscharr=350;

        ///| Entradas |///
        if (mykeya%2>=1 && !show_result) /// OK
        {
            //poschary+=tempos;
            if (poscharr<180) poscharr+=(180-poscharr)/6;
            else poscharr-=(poscharr-180)/6;
        }
        if (mykeya%4>=2 && !show_result) /// OK
        {
            //poschary-=tempos;
            if (poscharr<180) poscharr-=(poscharr)/6;
            else poscharr+=(360-poscharr)/6;
        }
        if (mykeya%8>=4 && !show_result) /// OK
        {
            //poscharx-=tempos;
            if (poscharr<90) poscharr-=(270-poscharr)/6;
            else poscharr+=(270-poscharr)/6;
        }
        if (mykeya%16>=8 && !show_result) /// OK
        {
            //poscharx+=tempos;
            if (poscharr>270) poscharr-=(90-poscharr)/6;
            else poscharr+=(90-poscharr)/6;
        }
        if (mykeya<32 && mykeya!=0 && !show_result || tempos>0 && !show_result)
        {
            if (sin(4*segs*ALLEGRO_PI)>=0) prs = __things->images->apoio_05;
            else prs = __things->images->apoio_06;
            poscharx-=(cos(((poscharr+90)/180)*ALLEGRO_PI)*tempos*relacao_x);
            poschary-=(sin(((poscharr+90)/180)*ALLEGRO_PI)*tempos*relacao_y);
        }

        ///| Draws do personagem |///

        draw_bitmap_to_buff(vig,buf,0,0,0,0,0);

        frame_maker(__things);

        if (savescore==true)
            break;
    }
    fclose(temp);

    nomeplayersuccess[0]='_';
    nomeplayersuccess[1]='\0';

    scoreplayersuccess=((3.0/2)*__things->chosen-6.0)*(10000000.0/((mins+1.0)*(moves+1.0)));
    if (scoreplayersuccess<0)
        scoreplayersuccess=0;

    if (LOHKPLAYING)
        scoreplayersuccess=9999999;

    i=0;

    p_ef= __things->images->apoio_12;

    __things->option = 12;

    if (savescore==true) draw_effect(true,__things);

    while (savescore==true)
    {
        if (i>23)
            i=23;
        else if (i<0)
            i=0;

        if (__things->key_get_write>0)
        {
            nomeplayersuccess[i]=__things->key_get_write;
            i++;
            nomeplayersuccess[i]='\0';
        }
        if (__things->key_get_write<0)
        {
            switch (__things->key_get_write)
            {
            case BACKSPACE_KEY:
                i--;
                nomeplayersuccess[i]='\0';
                break;
            case ENTER_KEY:
				fopen_s(&temp, "records.txt", "a+");
                if (!isalnum(nomeplayersuccess[i-2]) && i>=2) nomeplayersuccess[i-2]='\0';
                if (i>=1) nomeplayersuccess[i-1]='\0';
                if (i==0 || i==1)
                {
                    strcpy_s(nomeplayersuccess,"NO_NAME_OH");
                }
                fprintf(temp,"%s %d\n",nomeplayersuccess,scoreplayersuccess);
                fclose(temp);
                __things->chosen=2;
                savescore=false;
                break;
            case ESC_KEY:
                savescore=false;
                break;
            default:
                break;
            }
        }
        background_menu_animation(__things);

        draw_bitmap_to_buff(log,buf,0,0,418,133,0);
        draw_bitmap_to_buff(p_ef,buf,0,0,0,0,0);

        al_set_target_bitmap(buf);

        al_draw_textf        (font,al_map_rgb(  0,  0,  0),360.0*relacao_x ,550.0*relacao_y , 0,"Type your name: %s",nomeplayersuccess);
        al_draw_textf        (font,al_map_rgb(  0,  0,  0),615.0*relacao_x ,760.0*relacao_y , 0,"Your score: %d",scoreplayersuccess);

        al_draw_textf        (font,al_map_rgb(255,255,255),362.0*relacao_x ,552.0*relacao_y , 0,"Type your name: %s",nomeplayersuccess);
        al_draw_textf        (font,al_map_rgb(255,255,255),617.0*relacao_x ,762.0*relacao_y , 0,"Your score: %d",scoreplayersuccess);

        draw_bitmap_to_buff(vig,buf,0,0,0,0,0);

        frame_maker(__things);
    }

    end_of_func(__things,APOIO_THINGS);

    printer("[Game-Play] Saindo...");

    return 0;
}

///Gerar o mapa /// ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *buffer, ALLEGRO_FONT *font, int *posxy, ALLEGRO_BITMAP *m_block, ALLEGRO_BITMAP *vignette, ALLEGRO_DISPLAY_MODE disp_data, int fps, int chosen
int game_gerarmapa(complete_things *__things)
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *vig, *buf, *log;
    printer("[Gerador] Gerando mapa!");
    int tempo = 0, norte, sul, leste, oeste, noroeste, nordeste, sudeste, sudoeste, tamx, tamy, *matriz, x=0, y=0, random, counter, times=0, times2=0;
    double start, end;
    bool iscompleted=false;
    time_t t;

    ///| Verificador de dificuldade e assim criador de mapas |///

    log  = __things->images->logo;
    vig  = __things->images->vignette;
    buf  = __things->images->buffer;
    font = __things->font;
    tamy=8;

    if      (__things->chosen%10==7)
        tamx=EASY;
    else if (__things->chosen%10==8)
        tamx=MEDIUM;
    else if (__things->chosen%10==9)
        tamx=HARD;

    srand((unsigned) time(&t));

    matriz=(int*)calloc(tamx*tamy,sizeof(int));

    printer("[Gerador] Criando labirinto!...");

    start=al_get_time();

    while (!iscompleted)
    {
        tempo++;

        if (tempo%10000==0){
            background_menu_animation(__things);

            al_set_target_bitmap(buf);

            al_draw_textf(font,al_map_rgb(0,0,0),(al_get_bitmap_width(buf))*(852.0/1920),(al_get_bitmap_height(buf))*(536.0/1080),0,"Loading...");
            al_draw_textf(font,al_map_rgb(0,0,0),(al_get_bitmap_width(buf))*(854.0/1920),(al_get_bitmap_height(buf))*(538.0/1080),0,"Loading...");
            al_draw_textf(font,al_map_rgb(0,0,0),(al_get_bitmap_width(buf))*(856.0/1920),(al_get_bitmap_height(buf))*(540.0/1080),0,"Loading...");

            al_draw_textf(font,al_map_rgb(tempo,tempo+85,tempo+170),(al_get_bitmap_width(buf))*(850.0/1920),(al_get_bitmap_height(buf))*(534.0/1080),0,"Loading...");

            draw_bitmap_to_buff(vig,buf,0,0,0,0,0);

            frame_maker(__things);
        }

        end=al_get_time();
        if (end-start*1.0>(sqrt(tamx*1.0*tamy)/10.0))
            iscompleted=true;

        if (__things->key_get_write == ESC_KEY)
            return MENU;

        ///| MATRIZ JOGO MAKER MATRIZ JOGO MAKER MATRIZ JOGO MAKER MATRIZ JOGO MAKER MATRIZ JOGO MAKER MATRIZ JOGO MAKER |///

        *(matriz + x + y*tamx) = 1;

        counter=0;

        /// Verifica saídas possíveis
        

        if (x<tamx-1 && *(matriz + (x+1) + y*tamx)==1) /// LESTE
        {
            counter++;
            leste=1;
        }
        if (x>0      && *(matriz + (x-1) + y*tamx)==1) /// OESTE
        {
            counter++;
            oeste=1;
        }
        if (y<tamy-1 && *(matriz + x + (y+1)*tamx)==1) /// NORTE
        {
            counter++;
            norte=1;
        }
        if (y>0      && *(matriz + x + (y-1)*tamx)==1) /// SUL
        {
            counter++;
            sul=1;
        }
        if (x==0 || x==tamx-1)
            counter++;
        if (y==0 || y==tamy-1)
            counter++;

        if (x<tamx-1 && y>0 && *(matriz + (x+1) + (y-1)*tamx)) /// NORDESTE
            nordeste++;
        if (x>0 && y>0 && *(matriz + (x-1) + (y-1)*tamx)) /// NOROESTE
            noroeste++;
        if (x<tamx-1 && y<tamy-1 && *(matriz + (x+1) + (y+1)*tamx)) /// SUDESTE
            sudeste++;
        if (x>0 && y<tamy-1 && *(matriz + (x-1) + (y+1)*tamx)) /// SUDOESTE
            sudoeste++;


        /// Aleatoriza para caso ==2 talvez possa ser 3
        random=rand();
        if (random%3==0)
            counter++;

        if (counter>3)
            times++;
        else times=0;

        if (times>19)
        {
            times2++;
            x=0;
            y=times2;
        }
        if (times2>tamy-2 && times>9)
            iscompleted=true;

        random=rand();
        random=random%4; ///0 N 1 S 2 L 3 O
        switch (random){
        case 0:
            if (y>0 && counter<3 && nordeste==0 && noroeste==0) ///VAI PRO NORTE
            {
                y--;
            }
            else
            {
                random=rand();
                random=random%4;
                if (random==0 && x<tamx-1 && *(matriz + (x+1) + y*tamx)==1)
                    x++;
                if (random==1 && y<tamy-1 && *(matriz + x + (y+1)*tamx)==1)
                    y++;
                if (random==2 && x>0      && *(matriz + (x-1) + y*tamx)==1)
                    x--;
                if (random==3 && y>0      && *(matriz + x + (y-1)*tamx)==1)
                    y--;
            }
            break;
        case 1:
            if (y<tamy-1 && counter<3 && sudoeste==0 && sudeste==0) /// VAI PRO SUL
            {
                y++;
            }
            else
            {
                random=rand();
                random=random%4;
                if (random==0 && x<tamx-1 && *(matriz + (x+1) + y*tamx)==1)
                    x++;
                if (random==1 && y<tamy-1 && *(matriz + x + (y+1)*tamx)==1)
                    y++;
                if (random==2 && x>0      && *(matriz + (x-1) + y*tamx)==1)
                    x--;
                if (random==3 && y>0      && *(matriz + x + (y-1)*tamx)==1)
                    y--;
            }
            break;
        case 2:
            if (x<tamx-1 && counter<3 && nordeste==0 && sudeste==0) /// VAI PRO LESTE
            {
                x++;
            }
            else
            {
                random=rand();
                random=random%4;
                if (random==0 && x<tamx-1 && *(matriz + (x+1) + y*tamx)==1)
                    x++;
                if (random==1 && y<tamy-1 && *(matriz + x + (y+1)*tamx)==1)
                    y++;
                if (random==2 && x>0      && *(matriz + (x-1) + y*tamx)==1)
                    x--;
                if (random==3 && y>0      && *(matriz + x + (y-1)*tamx)==1)
                    y--;
            }
            break;
        case 3:
            if (x>0 && counter<3 && noroeste==0 && sudoeste==0) /// VAI PRO OESTE
            {
                x--;
            }
            else
            {
                random=rand();
                random=random%4;
                if (random==0 && x<tamx-1 && *(matriz + (x+1) + y*tamx)==1)
                    x++;
                if (random==1 && y<tamy-1 && *(matriz + x + (y+1)*tamx)==1)
                    y++;
                if (random==2 && x>0      && *(matriz + (x-1) + y*tamx)==1)
                    x--;
                if (random==3 && y>0      && *(matriz + x + (y-1)*tamx)==1)
                    y--;
            }
            break;
        }
    }

    if (solucionar(matriz,tamx,tamy)!=0)
    {
        printer("[Gerador-E00] Falha ao verificar arquivos, tentando novamente...");
        return __things->chosen;
    }

	FILE *map = NULL;
	fopen_s(&map, "map.txt", "w+");

    printer("[Gerador] Verificando arquivo...");
    if (map==NULL)
    {
        printer("[Gerador] Falha ao abrir arquivo para salvar o mapa.");
        return MENU;
    }

    printer("[Gerador> Escrevendo no arquivo...");
    for (times=0;times<(tamx*tamy);times++)
    {
        if (times%tamx==0 && times>1)
            fprintf(map,"\n");
        fprintf(map,"%d",*(matriz+times));
    }
    fprintf(map,"\n");
    fflush(map);
    free(matriz);
    fclose(map);
    printer("[Gerador> Arquivo salvo, saindo!");

    return 0;
}

///Solucionador do mapa
int solucionar(int *labirinto, int tamx, int tamy)
{
	int maximo_tentativas, ultimo;
	posicao *visitados;
	visitados = (posicao*)malloc(tamx*tamy*sizeof(posicao));
	posicao atual;

	atual.x = 0;
	atual.y = 0;
	*(labirinto + 0 + 0*tamx) = VISITADO;
	ultimo = 0;
	maximo_tentativas = 1000;
	while (atual.x != tamx - 1)
	{
		visitados[ultimo] = atual;
		if (moved(labirinto, atual, 1, 0, tamx, tamy))
		{
			atual.x++;
			ultimo++;
			continue;
		}
		if (moved(labirinto, atual, 0,-1, tamx, tamy))
		{
			atual.y--;
			ultimo++;
			continue;
		}
		if (moved(labirinto, atual, 0, 1, tamx, tamy))
		{
			atual.y++;
			ultimo++;
			continue;
		}
		if (moved(labirinto, atual,-1, 0, tamx, tamy))
		{
			atual.x--;
			ultimo++;
			continue;
		}
		*(labirinto + atual.x + atual.y*tamx) = SEM_SAIDA;
		atual = visitados[--ultimo];

		if (--maximo_tentativas == 0)
			return -1;
	}
	return 0;
}

///Sair do app
void exit_app(ALLEGRO_DISPLAY *display, const char *texto_de_erro_a_salvar)
{
    printf("[exit_app> Alguém me chamou por causa do erro: %s\n",texto_de_erro_a_salvar);
	FILE *log = NULL;
	fopen_s(&log, "log.txt", "a+");
    if (log!=NULL){
        fprintf(log,"[exit_app> Alguém me chamou por causa do erro: %s\n",texto_de_erro_a_salvar);
    }
    if (display!=NULL) al_destroy_display(display);
    al_rest(2);
    exit(0);
    return;
}
