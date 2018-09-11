#include "all_my_things.h"

///Startup do allegro e funções necessárias Níquel e Alumínio em vez de Cobre e Zn

int main()
{
    ///| ======================================== |///
    ///| >  Definições e itens a usar no jogo   < |///
    ///| ======================================== |///

    setlocale(LC_ALL,"");
    bool is_fullscreen  =  false;
    const char *chars = "V0.0";
    int times, render_x, render_y;

    ALLEGRO_DISPLAY       *display = NULL;
    ALLEGRO_DISPLAY_MODE   disp_data;
    ALLEGRO_EVENT_QUEUE   *event_queue;
    ALLEGRO_BITMAP        *icon;

    ///| ============================================ |///
    ///| > Definições iniciais do jogo (para teste) < |///
    ///| ============================================ |///

    disp_data.width =0;
    disp_data.height=0;

    ///| Função para preparar os arquivos pro game |///

    printer("Carregando o jogo...");

    ///| ======================================== |///
    ///| > Carregamento do jogo (tela, funções) < |///
    ///| ======================================== |///

    printer("Iniciando...");
    if(!al_init()){
        printer("Falha ao carregar o jogo: Allegro indisponível.");
        exit(-1);
        return -1;
    }
    printer("Verificando dispositivos conectados...");
    if(!al_install_keyboard()){
        printer("Falha ao carregar o jogo: Keyboard falhou.");
        exit(-1);
        return -1;
    }
    printer("Carregando carregadores de carga...");
    if(!al_init_image_addon()){
        printer("Falha ao carregar o jogo: Carregamento de imagens ausente.");
        exit(-1);
        return -1;
    }
    printer("Girando rodas redondas e circulares...");
    if (!al_init_font_addon() || !al_init_ttf_addon()){
        printer("Falha ao carregar o jogo: Parte de texto falhou ao carregar.");
        exit(-1);
        return -1;
    }

    ///| Config DISPLAY |///
    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

    times=prepare_txts(&is_fullscreen,&(disp_data.width),&(disp_data.height),&render_x,&render_y);

    printer("Verificando o valor da vida...");
    if (is_fullscreen == true)
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);

    al_set_new_display_flags(ALLEGRO_FRAMELESS|ALLEGRO_OPENGL);
    al_set_new_display_option(ALLEGRO_VSYNC,2,ALLEGRO_SUGGEST);

    display = al_create_display(disp_data.width, disp_data.height);

    printer("Trabalhando com telas e pintando a base...");
    if(!display){
        printer("Falha ao carregar o jogo: Falha ao carregar tela do jogo");
        exit(-1);
        return -1;
    }
    printer("Beautifulificando as coisas...");
    icon=al_load_bitmap(datapath_icon);   ///| ICON! |///
    al_set_display_icon(display,icon); ///| ICON! |///

    ///| Eventos |///

    event_queue = al_create_event_queue();

    printer("Pensando nas coisas que terei que pensar futuramente...");
    if(!event_queue)
    {
        printer("Falha ao carregar o jogo: Falha ao carregar eventos do jogo");
        exit_app(display,"Falha ao carregar eventos do jogo");
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));

    al_register_event_source(event_queue, al_get_keyboard_event_source());

    ///| Fim deles |///

    printer("Nomeando-me alguém com algum nome interessante e útil...");
    al_set_window_title(display,"Maze Game by Erfra");
    al_set_exe_name("Maze_App.exe");

    printer("Chamando Seeker para monitorar as coisas e FIM!");
    seeker(display,disp_data,event_queue,times,chars,render_x,render_y);
    return 0;
}
