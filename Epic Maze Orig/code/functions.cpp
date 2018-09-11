#include "functions.h"

bool moved(int *labirinto, posicao atual, int d_x, int d_y, int tamx, int tamy)
{
    if (atual.x + d_x < 0 || atual.y + d_y == tamy ||
        atual.y + d_y < 0 || atual.x + d_x == tamx)
    {
        return false;
    }
    if (*(labirinto + (atual.x + d_x) + (atual.y + d_y)*tamx) == LIVRE)
    {
        *(labirinto + (atual.x + d_x) + (atual.y + d_y)*tamx) = VISITADO;
        return true;
    }
    return false;
}

void load_gif_bitmaps (int amount, pauses_anim *to_anims, const char *first_name_43)
{
    int helpi;
    char final_result[50];
    helpi=-1;

    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_00 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_01 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_02 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_03 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_04 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_05 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_06 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_07 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_08 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_09 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_10 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_11 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_12 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_13 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_14 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_15 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_16 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_17 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_18 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_19 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_20 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_21 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_22 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_23 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_24 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_25 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_26 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_27 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_28 = al_load_bitmap(final_result);}
    helpi++; if (helpi<amount) {sprintf_s(final_result,"%s_%02d.png",first_name_43,helpi); to_anims->anim_29 = al_load_bitmap(final_result);}
}

void background_menu_animation (complete_things *__things)
{
    double calc = ((sqrt(al_get_bitmap_width(__things->images->buffer)*al_get_bitmap_height(__things->images->buffer)))/1440);
    ALLEGRO_BITMAP *buf, *blk;
    int basex, basey;
    buf   = __things->images->buffer;
    blk   = __things->images->apoio_04;

    al_set_target_bitmap(buf);
    __things->posxy = 1 + __things->posxy;
    if (__things->posxy>=0) __things->posxy = -63;
    for (basex=__things->posxy;calc*basex*1.0<al_get_bitmap_width(buf);basex+=64)
    {
        for (basey=__things->posxy;calc*basey*1.0<al_get_bitmap_height(buf);basey+=64)
        {
            draw_bitmap_to_buff(blk,buf,0,0,basex,basey,0);
        }
    }
    al_set_target_backbuffer(__things->display);
}

void clear_memory(data_type filetype, void *file)
{
    pauses_anim *images;
    FILE *other;
    char *example;
    int helpar;
    /// ANALLEGROBITMAP, ACHAR, APAUSESANIMCOMPLETE

    switch (filetype){
    case ONER_BITMAPR:
        al_destroy_bitmap((ALLEGRO_BITMAP*)file);
        break;
    case CHAR_POINTER:
        example=(char*)file;
        free(file);
        break;
    case FILE_POINTER:
        other=(FILE*)file;
        free(other);
        break;
    case ANIMATION_KO:
        images=(pauses_anim*)file; ///30 bitmaps actually (effect)
        for (helpar=0;helpar<30;helpar++)
        {
            switch (helpar){
            case 0:  al_destroy_bitmap(images->anim_00); break;
            case 1:  al_destroy_bitmap(images->anim_01); break;
            case 2:  al_destroy_bitmap(images->anim_02); break;
            case 3:  al_destroy_bitmap(images->anim_03); break;
            case 4:  al_destroy_bitmap(images->anim_04); break;
            case 5:  al_destroy_bitmap(images->anim_05); break;
            case 6:  al_destroy_bitmap(images->anim_06); break;
            case 7:  al_destroy_bitmap(images->anim_07); break;
            case 8:  al_destroy_bitmap(images->anim_08); break;
            case 9:  al_destroy_bitmap(images->anim_09); break;
            case 10: al_destroy_bitmap(images->anim_10); break;
            case 11: al_destroy_bitmap(images->anim_11); break;
            case 12: al_destroy_bitmap(images->anim_12); break;
            case 13: al_destroy_bitmap(images->anim_13); break;
            case 14: al_destroy_bitmap(images->anim_14); break;
            case 15: al_destroy_bitmap(images->anim_15); break;
            case 16: al_destroy_bitmap(images->anim_16); break;
            case 17: al_destroy_bitmap(images->anim_17); break;
            case 18: al_destroy_bitmap(images->anim_18); break;
            case 19: al_destroy_bitmap(images->anim_19); break;
            case 20: al_destroy_bitmap(images->anim_20); break;
            case 21: al_destroy_bitmap(images->anim_21); break;
            case 22: al_destroy_bitmap(images->anim_22); break;
            case 23: al_destroy_bitmap(images->anim_23); break;
            case 24: al_destroy_bitmap(images->anim_24); break;
            case 25: al_destroy_bitmap(images->anim_25); break;
            case 26: al_destroy_bitmap(images->anim_26); break;
            case 27: al_destroy_bitmap(images->anim_27); break;
            case 28: al_destroy_bitmap(images->anim_28); break;
            case 29: al_destroy_bitmap(images->anim_29); break;
            }
        }
        images->anim_00    = NULL;
        images->anim_01    = NULL;
        images->anim_02    = NULL;
        images->anim_03    = NULL;
        images->anim_04    = NULL;
        images->anim_05    = NULL;
        images->anim_06    = NULL;
        images->anim_07    = NULL;
        images->anim_08    = NULL;
        images->anim_09    = NULL;
        images->anim_10    = NULL;
        images->anim_11    = NULL;
        images->anim_12    = NULL;
        images->anim_13    = NULL;
        images->anim_14    = NULL;
        images->anim_15    = NULL;
        images->anim_16    = NULL;
        images->anim_17    = NULL;
        images->anim_18    = NULL;
        images->anim_19    = NULL;
        images->anim_20    = NULL;
        images->anim_21    = NULL;
        images->anim_22    = NULL;
        images->anim_23    = NULL;
        images->anim_24    = NULL;
        images->anim_25    = NULL;
        images->anim_26    = NULL;
        images->anim_27    = NULL;
        images->anim_28    = NULL;
        images->anim_29    = NULL;
        break;
    case APOIO_THINGS:
        images=(pauses_anim*)file;
        for (helpar=0;helpar<13;helpar++)
        {
            switch (helpar){
            case  0: al_destroy_bitmap(images->apoio_01); break;
            case  1: al_destroy_bitmap(images->apoio_02); break;
            case  2: al_destroy_bitmap(images->apoio_03); break;
            case  3: al_destroy_bitmap(images->apoio_04); break;
            case  4: al_destroy_bitmap(images->apoio_05); break;
            case  5: al_destroy_bitmap(images->apoio_06); break;
            case  6: al_destroy_bitmap(images->apoio_07); break;
            case  7: al_destroy_bitmap(images->apoio_08); break;
            case  8: al_destroy_bitmap(images->apoio_09); break;
            case  9: al_destroy_bitmap(images->apoio_10); break;
            case 10: al_destroy_bitmap(images->apoio_11); break;
            case 11: al_destroy_bitmap(images->apoio_12); break;
            case 12: al_destroy_bitmap(images->apoio_13); break;
            }
        images->apoio_01   = NULL;
        images->apoio_02   = NULL;
        images->apoio_03   = NULL;
        images->apoio_04   = NULL;
        images->apoio_05   = NULL;
        images->apoio_06   = NULL;
        images->apoio_07   = NULL;
        images->apoio_08   = NULL;
        images->apoio_09   = NULL;
        images->apoio_10   = NULL;
        images->apoio_11   = NULL;
        images->apoio_12   = NULL;
        images->apoio_13   = NULL;
        }
        break;
    case KILL_ALL_GOD:
        images=(pauses_anim*)file; ///46-3 bitmaps actually (won't destroy base images like buffer, logo and vignette)
        for (helpar=0;helpar<43;helpar++)
        {
            switch (helpar){
            case 0:  al_destroy_bitmap(images->anim_00); break;
            case 1:  al_destroy_bitmap(images->anim_01); break;
            case 2:  al_destroy_bitmap(images->anim_02); break;
            case 3:  al_destroy_bitmap(images->anim_03); break;
            case 4:  al_destroy_bitmap(images->anim_04); break;
            case 5:  al_destroy_bitmap(images->anim_05); break;
            case 6:  al_destroy_bitmap(images->anim_06); break;
            case 7:  al_destroy_bitmap(images->anim_07); break;
            case 8:  al_destroy_bitmap(images->anim_08); break;
            case 9:  al_destroy_bitmap(images->anim_09); break;
            case 10: al_destroy_bitmap(images->anim_10); break;
            case 11: al_destroy_bitmap(images->anim_11); break;
            case 12: al_destroy_bitmap(images->anim_12); break;
            case 13: al_destroy_bitmap(images->anim_13); break;
            case 14: al_destroy_bitmap(images->anim_14); break;
            case 15: al_destroy_bitmap(images->anim_15); break;
            case 16: al_destroy_bitmap(images->anim_16); break;
            case 17: al_destroy_bitmap(images->anim_17); break;
            case 18: al_destroy_bitmap(images->anim_18); break;
            case 19: al_destroy_bitmap(images->anim_19); break;
            case 20: al_destroy_bitmap(images->anim_20); break;
            case 21: al_destroy_bitmap(images->anim_21); break;
            case 22: al_destroy_bitmap(images->anim_22); break;
            case 23: al_destroy_bitmap(images->anim_23); break;
            case 24: al_destroy_bitmap(images->anim_24); break;
            case 25: al_destroy_bitmap(images->anim_25); break;
            case 26: al_destroy_bitmap(images->anim_26); break;
            case 27: al_destroy_bitmap(images->anim_27); break;
            case 28: al_destroy_bitmap(images->anim_28); break;
            case 29: al_destroy_bitmap(images->anim_29); break;
            case 30: al_destroy_bitmap(images->apoio_01); break;
            case 31: al_destroy_bitmap(images->apoio_02); break;
            case 32: al_destroy_bitmap(images->apoio_03); break;
            case 33: al_destroy_bitmap(images->apoio_04); break;
            case 34: al_destroy_bitmap(images->apoio_05); break;
            case 35: al_destroy_bitmap(images->apoio_06); break;
            case 36: al_destroy_bitmap(images->apoio_07); break;
            case 37: al_destroy_bitmap(images->apoio_08); break;
            case 38: al_destroy_bitmap(images->apoio_09); break;
            case 39: al_destroy_bitmap(images->apoio_10); break;
            case 40: al_destroy_bitmap(images->apoio_11); break;
            case 41: al_destroy_bitmap(images->apoio_12); break;
            case 42: al_destroy_bitmap(images->apoio_13); break;
            }
        }
        images->anim_00    = NULL;
        images->anim_01    = NULL;
        images->anim_02    = NULL;
        images->anim_03    = NULL;
        images->anim_04    = NULL;
        images->anim_05    = NULL;
        images->anim_06    = NULL;
        images->anim_07    = NULL;
        images->anim_08    = NULL;
        images->anim_09    = NULL;
        images->anim_10    = NULL;
        images->anim_11    = NULL;
        images->anim_12    = NULL;
        images->anim_13    = NULL;
        images->anim_14    = NULL;
        images->anim_15    = NULL;
        images->anim_16    = NULL;
        images->anim_17    = NULL;
        images->anim_18    = NULL;
        images->anim_19    = NULL;
        images->anim_20    = NULL;
        images->anim_21    = NULL;
        images->anim_22    = NULL;
        images->anim_23    = NULL;
        images->anim_24    = NULL;
        images->anim_25    = NULL;
        images->anim_26    = NULL;
        images->anim_27    = NULL;
        images->anim_28    = NULL;
        images->anim_29    = NULL;
        images->apoio_01   = NULL;
        images->apoio_02   = NULL;
        images->apoio_03   = NULL;
        images->apoio_04   = NULL;
        images->apoio_05   = NULL;
        images->apoio_06   = NULL;
        images->apoio_07   = NULL;
        images->apoio_08   = NULL;
        images->apoio_09   = NULL;
        images->apoio_10   = NULL;
        images->apoio_11   = NULL;
        images->apoio_12   = NULL;
        images->apoio_13   = NULL;
        break;
    }
}

int rec_reader(const char *arquivo, defaultrecords manobonito[10])
{
    int i,tempsc,j,k;
    char temp[30];

	FILE *recs = NULL;
	fopen_s(&recs, arquivo, "r");

    if (recs==NULL)
		fopen_s(&recs, arquivo, "w+");

    if (recs!=NULL){
        fseek(recs,0,SEEK_SET);
        for (i=0;i<10;i++)
        {
            strcpy_s(manobonito[i].nick,"NONENONE");
            manobonito[i].score=-1;
        }
        while (!feof(recs))
        {
            fscanf_s(recs,"%s %d\n",&temp, 30,&tempsc);
            for (j=0;j<10;j++)
            {
                if (tempsc>manobonito[j].score)
                {
                    for (k=9;k>j;k--)
                    {
                        strcpy_s(manobonito[k].nick,manobonito[k-1].nick);
                        manobonito[k].score=manobonito[k-1].score;
                    }
                    strcpy_s(manobonito[k].nick,temp);
                    manobonito[k].score=tempsc;
                    j=10;
                }
            }
        }
    }
    else
    {
        fclose(recs);
        return -1;
    }
    fclose(recs);
    return 0;
}

///Chama o load correto!
bool load_correct (complete_things *__things)
{
    bool returno = false;
    //while (__things->is_unloading || __things->is_loading);

    switch (__things->chosen)
    {
    case BASIC:
        __things->what_to_load = BASICS_DEFAULT_LOAD;
        __things->is_loading = true;
        returno = true;
        break;
    case MENU:
        __things->what_to_load = MENU_DEFAULT_LOAD;
        __things->is_loading = true;
        returno = true;
        break;
    case START:
        __things->what_to_load = MENU_START_LOAD;
        __things->is_loading = true;
        returno = true;
        break;
    case INSTRUCTIONS:
        __things->what_to_load = MENU_INSTRUCTIONS_LOAD;
        __things->is_loading = true;
        returno = true;
        break;
    case RECORDS:
        __things->what_to_load = MENU_RECORDS_LOAD;
        __things->is_loading = true;
        returno = true;
        break;
    case GAME_EASY:
    case GAME_MEDIUM:
    case GAME_INSANE:
        __things->what_to_load = GAME_LOAD;
        __things->is_loading = true;
        returno = true;
        break;
    case CONFIG_OCULT:
        __things->what_to_load = MENU_CONFIG_OCULT;
        __things->is_loading = true;
        returno = true;
        break;
    default:
        exit_app(__things->display,"{{LOAD_CORRECT}} FAIL BOOL SWITCH IMPOSSIBLE");
    }
    //while (!__things->is_loading) {}
	not_dynamic_loader(__things);
    return returno;
}

void end_of_func (complete_things *__things, int what_to_erase_CODE)
{
    __things->what_to_unload = what_to_erase_CODE;
    while (!load_correct(__things)){
        draw_effect(true,__things);
    }
}


///desenha animações épicas
void draw_effect(bool esq_p_meio, complete_things *__things)
{
    float t;
    bool exite=false;

    if (esq_p_meio)
         t = 418;
    else t = 2;

    while (__things->is_loading || __things->is_unloading)
    {
        background_menu_animation(__things);
    }

    while (!exite)
    {
        if (esq_p_meio) t-=(t/3.0);
        else            t+=(t/3.0);

        background_menu_animation(__things);

        if (esq_p_meio)
        {
            draw_bitmap_to_buff(__things->images->logo,__things->images->buffer,0,0,418-t,133,0);
            switch (__things->option){
            case 1:
                draw_bitmap_to_buff(__things->images->apoio_01,__things->images->buffer,0,0,-t,0,0);
                break;
            case 2:
                draw_bitmap_to_buff(__things->images->apoio_02,__things->images->buffer,0,0,-t,0,0);
                break;
            case 3:
                draw_bitmap_to_buff(__things->images->apoio_03,__things->images->buffer,0,0,-t,0,0);
                break;
            case 4:
                draw_bitmap_to_buff(__things->images->apoio_04,__things->images->buffer,0,0,-t,0,0);
                break;
            case 5:
                draw_bitmap_to_buff(__things->images->apoio_05,__things->images->buffer,0,0,-t,0,0);
                break;
            case 6:
                draw_bitmap_to_buff(__things->images->apoio_06,__things->images->buffer,0,0,-t,0,0);
                break;
            case 7:
                draw_bitmap_to_buff(__things->images->apoio_07,__things->images->buffer,0,0,-t,0,0);
                break;
            case 8:
                draw_bitmap_to_buff(__things->images->apoio_08,__things->images->buffer,0,0,-t,0,0);
                break;
            case 9:
                draw_bitmap_to_buff(__things->images->apoio_09,__things->images->buffer,0,0,-t,0,0);
                break;
            case 10:
                draw_bitmap_to_buff(__things->images->apoio_10,__things->images->buffer,0,0,-t,0,0);
                break;
            case 11:
                draw_bitmap_to_buff(__things->images->apoio_11,__things->images->buffer,0,0,-t,0,0);
                break;
            case 12:
                draw_bitmap_to_buff(__things->images->apoio_12,__things->images->buffer,0,0,-t,0,0);
                break;
            case 13:
                draw_bitmap_to_buff(__things->images->apoio_13,__things->images->buffer,0,0,-t,0,0);
                break;
            }
        }
        else
        {
            draw_bitmap_to_buff(__things->images->logo,__things->images->buffer,0,0,418+t,133,0);
            switch (__things->option){
            case 1:
                draw_bitmap_to_buff(__things->images->apoio_01,__things->images->buffer,0,0, t,0,0);
                break;
            case 2:
                draw_bitmap_to_buff(__things->images->apoio_02,__things->images->buffer,0,0, t,0,0);
                break;
            case 3:
                draw_bitmap_to_buff(__things->images->apoio_03,__things->images->buffer,0,0, t,0,0);
                break;
            case 4:
                draw_bitmap_to_buff(__things->images->apoio_04,__things->images->buffer,0,0, t,0,0);
                break;
            case 5:
                draw_bitmap_to_buff(__things->images->apoio_05,__things->images->buffer,0,0, t,0,0);
                break;
            case 6:
                draw_bitmap_to_buff(__things->images->apoio_06,__things->images->buffer,0,0, t,0,0);
                break;
            case 7:
                draw_bitmap_to_buff(__things->images->apoio_07,__things->images->buffer,0,0, t,0,0);
                break;
            case 8:
                draw_bitmap_to_buff(__things->images->apoio_08,__things->images->buffer,0,0, t,0,0);
                break;
            case 9:
                draw_bitmap_to_buff(__things->images->apoio_09,__things->images->buffer,0,0, t,0,0);
                break;
            case 10:
                draw_bitmap_to_buff(__things->images->apoio_10,__things->images->buffer,0,0, t,0,0);
                break;
            case 11:
                draw_bitmap_to_buff(__things->images->apoio_11,__things->images->buffer,0,0, t,0,0);
                break;
            case 12:
                draw_bitmap_to_buff(__things->images->apoio_12,__things->images->buffer,0,0, t,0,0);
                break;
            case 13:
                draw_bitmap_to_buff(__things->images->apoio_13,__things->images->buffer,0,0, t,0,0);
                break;
            }
        }

        draw_bitmap_to_buff(__things->images->vignette,__things->images->buffer,0,0,0,0,0);

        frame_maker(__things);

        if (t<2 || t>418)
            exite=true;
    }
}

///recebe FILE e texto e salva no LOG e mostra na tela. Se debug enabled, mostra informações mais detalhadas. Fazer (a,...)

int printer(const char *text)
{
	FILE *log = NULL;
	fopen_s(&log, "log.txt", "r+");
    if (text!=NULL){
        printf("%s\n",text);
        if (log!=NULL)
        {
            fseek(log,0,SEEK_END);
            fprintf(log,"%s\n",text);
            fclose(log);
        }
        else {
            printf("[Printer-E00] ERRO AO TENTAR ESCREVER NO LOG\n");
        }
        return 0;
    }
    else {
        fclose(log);
        printf("[Printer-E01] ERRO CARREGANDO TEXTO DE ENTRADA. IMPOSSÍVEL ESCREVER!\n");
        return -1;
    }
}

///carrega os txt necessários pro jogo
int prepare_txts(bool *is_fullscreen, int *width, int *height, int *refx, int *refy)
{
    int loadtime, tempx, tempy;
	FILE *outro = NULL;

    /// LOG FILE LOAD ///
    fopen_s(&outro, "log.txt","r+");
    if (outro!=NULL)
    {
        fseek(outro,13,SEEK_SET);
        fscanf_s(outro,"%d",&loadtime);
        loadtime++;
        printf_s("Time: %d\n",loadtime);
        fseek(outro,0,SEEK_SET);
        fprintf_s(outro,"# Log file > %d ",loadtime);
        fseek(outro,0,SEEK_END);
        fprintf_s(outro,"\n------------------\nSTARTED UP %d TIME\n------------------\n",loadtime);
        printf_s("~log carregado\n");
    }
    else{
		fopen_s(&outro, "log.txt", "w+");
		if (!outro) exit(0);
        fprintf(outro,"# Log file > 0000000000000000000000\n");
        loadtime=0;
        fprintf(outro,"|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
                      "| Informations from this game (maybe useful)|\n"
                      "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
                      "|> Game made by: Ernesto Luis & Franco Luiz!|\n"
                      "|> ERFRA Games 2016 - Idk any type of rights|\n"
                      "|> Thanks for playing this game! See u soon!|\n"
                      "|-------------------------------------------|\n\n\n");
        printf("~log gerado\n");
    }
    fclose(outro);

    /// RECORDS FILE LOAD ///

	fopen_s(&outro, "records.txt", "r+");
    if (outro==NULL)
		fopen_s(&outro, "records.txt", "a+");
    printf("~recs carregado/gerado\n");
    fclose(outro);

    /// CONFIG FILE LOAD ///

	fopen_s(&outro, "config.txt", "r+");

    if (outro==NULL)
    {
		fopen_s(&outro, "config.txt", "w+");

        fprintf(outro,"#Configuration_file\nfullscreen= true\nscreensize= %dx%d\n",*width,*height);
        *is_fullscreen=true;
        fclose(outro);
		fopen_s(&outro, "config.txt", "r+");
        if (outro==NULL)
        {
            printf("FAIL CONFIG LOAD!\n");
            exit(-1);
        }
        else printf("~config gerado\n");
    }

    if (outro!=NULL) {
        printf("~config carregando");
        int times=0;
        while (!feof(outro))
        {
            times++;
            char shuffled[128];
            char config_cblho[]="#Configuration_file";
            char fullscreen[]="fullscreen=";
            char truer[] ="true";
            char screen_size[]="screensize=";

            fscanf_s(outro,"%s ",&shuffled, 128);


            if (strcmp(shuffled,fullscreen) == 0)
            {
                fscanf_s(outro,"%s ",&shuffled, 128);
                if (strcmp(shuffled,truer) == 0)
                    *is_fullscreen=true;
                else *is_fullscreen=false;
            }

            else if (strcmp(shuffled,screen_size) == 0)
            {
                fscanf_s(outro,"%dx%d\n",&tempx,&tempy);
            }
            else if (strcmp(shuffled,config_cblho) == 0)
            {
                times=1;
            }
            printf(".");
        }

		/*
        if (tempx>1920)
        {
            printer("Configuração de tela maior que a base do jogo! Redimensionado pra 1920x**");
            tempx=1920;
        }
        if (tempy>1080)
        {
            printer("Configuração de tela maior que a base do jogo! Redimensionado pra **x1080");
            tempy=1080;
        }*/

        if (*is_fullscreen==false)
        {
            *width=tempx;
            *height=tempy;
        }
        *refx=tempx;
        *refy=tempy;
        printf("\n~config carregada!\n");
    }
    fclose(outro);

    return loadtime;
}

///retorna o valor da tecla somente quando pressionada, sem problemas de segurar.
int func_key_get(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display)
{
    int mykey=0;

    ALLEGRO_EVENT ev;

    al_get_next_event(event_queue,&ev);
    ///al_wait_for_event(event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        exit_app(display,"[KeyGet-E00] Jogo fechado [X]");
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP)
    {
        mykey=-9999;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        switch(ev.keyboard.keycode)
        {
        case ALLEGRO_KEY_DOWN:
            if (KEY_RET) printer("[Key > Down ]");
            mykey+=1;
            break;

        case ALLEGRO_KEY_UP:
            if (KEY_RET) printer("[Key > Up   ]");
            mykey+=2;
            break;

        case ALLEGRO_KEY_LEFT:
            if (KEY_RET) printer("[Key > Left ]");
            mykey+=4;
            break;

        case ALLEGRO_KEY_RIGHT:
            if (KEY_RET) printer("[Key > Right]");
            mykey+=8;
            break;

        case ALLEGRO_KEY_S:
            if (KEY_RET) printer("[Key > S    ]");
            mykey+=1;
            break;

        case ALLEGRO_KEY_W:
            if (KEY_RET) printer("[Key > W    ]");
            mykey+=2;
            break;

        case ALLEGRO_KEY_A:
            if (KEY_RET) printer("[Key > A    ]");
            mykey+=4;
            break;

        case ALLEGRO_KEY_D:
            if (KEY_RET) printer("[Key > D    ]");
            mykey+=8;
            break;

        case ALLEGRO_KEY_ENTER:
            if (KEY_RET) printer("[Key > Enter]");
            mykey+=16;
            break;

        case ALLEGRO_KEY_PAD_ENTER:
            if (KEY_RET) printer("[Key > PdEnt]");
            mykey+=16;
            break;

        case ALLEGRO_KEY_SPACE:
            if (KEY_RET) printer("[Key > Space]");
            mykey+=16;
            break;

        case ALLEGRO_KEY_ESCAPE:
            if (KEY_RET) printer("[Key > ESC  ]");
            mykey+=32;
            break;

        case ALLEGRO_KEY_C:
            if (KEY_RET) printer("[Key > C    ]");
            mykey+=64;
            break;

        case ALLEGRO_KEY_F3:
            if (KEY_RET) printer("[Key > F3   ]");
            mykey+=128;
            break;

        case ALLEGRO_KEY_1:
            if (KEY_RET) printer("[Key > 1    ]");
            mykey=-1;
            break;

        case ALLEGRO_KEY_2:
            if (KEY_RET) printer("[Key > 2    ]");
            mykey=-2;
            break;

        case ALLEGRO_KEY_3:
            if (KEY_RET) printer("[Key > 3    ]");
            mykey=-3;
            break;

        case ALLEGRO_KEY_4:
            if (KEY_RET) printer("[Key > 4    ]");
            mykey=-4;
            break;

        case ALLEGRO_KEY_F1:
            if (KEY_RET) printer("[Key > F1   ]");
            mykey=-11;
            break;

        default:
            mykey=0;
        }
    }
    return mykey;
}

char raw_key_get(ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_DISPLAY *display)
{
    char ch = 0;
    ALLEGRO_EVENT ev;

    if (al_get_next_event(event_queue,&ev))
    {
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            exit_app(display,"Jogo fechado [X]");
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            ch=0;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_A:
                ch='A';
                break;
            case ALLEGRO_KEY_B:
                ch='B';
                break;
            case ALLEGRO_KEY_C:
                ch='C';
                break;
            case ALLEGRO_KEY_D:
                ch='D';
                break;
            case ALLEGRO_KEY_E:
                ch='E';
                break;
            case ALLEGRO_KEY_F:
                ch='F';
                break;
            case ALLEGRO_KEY_G:
                ch='G';
                break;
            case ALLEGRO_KEY_H:
                ch='H';
                break;
            case ALLEGRO_KEY_I:
                ch='I';
                break;
            case ALLEGRO_KEY_J:
                ch='J';
                break;
            case ALLEGRO_KEY_K:
                ch='K';
                break;
            case ALLEGRO_KEY_L:
                ch='L';
                break;
            case ALLEGRO_KEY_M:
                ch='M';
                break;
            case ALLEGRO_KEY_N:
                ch='N';
                break;
            case ALLEGRO_KEY_O:
                ch='O';
                break;
            case ALLEGRO_KEY_P:
                ch='P';
                break;
            case ALLEGRO_KEY_Q:
                ch='Q';
                break;
            case ALLEGRO_KEY_R:
                ch='R';
                break;
            case ALLEGRO_KEY_S:
                ch='S';
                break;
            case ALLEGRO_KEY_T:
                ch='T';
                break;
            case ALLEGRO_KEY_U:
                ch='U';
                break;
            case ALLEGRO_KEY_V:
                ch='V';
                break;
            case ALLEGRO_KEY_W:
                ch='W';
                break;
            case ALLEGRO_KEY_X:
                ch='X';
                break;
            case ALLEGRO_KEY_Y:
                ch='Y';
                break;
            case ALLEGRO_KEY_Z:
                ch='Z';
                break;
            case ALLEGRO_KEY_0:
                ch='0';
                break;
            case ALLEGRO_KEY_1:
                ch='1';
                break;
            case ALLEGRO_KEY_2:
                ch='2';
                break;
            case ALLEGRO_KEY_3:
                ch='3';
                break;
            case ALLEGRO_KEY_4:
                ch='4';
                break;
            case ALLEGRO_KEY_5:
                ch='5';
                break;
            case ALLEGRO_KEY_6:
                ch='6';
                break;
            case ALLEGRO_KEY_7:
                ch='7';
                break;
            case ALLEGRO_KEY_8:
                ch='8';
                break;
            case ALLEGRO_KEY_9:
                ch='9';
                break;
            case ALLEGRO_KEY_SPACE:
                ch='_';
                break;
            case ALLEGRO_KEY_BACKSPACE:
                ch=-1;
                break;
            case ALLEGRO_KEY_ENTER:
                ch=-2;
                break;
            case ALLEGRO_KEY_PAD_ENTER:
                ch=-2;
                break;
            case ALLEGRO_KEY_ESCAPE:
                ch=-10;
                break;
            case ALLEGRO_KEY_UP:
                ch=-50;
                break;
            case ALLEGRO_KEY_DOWN:
                ch=-51;
                break;
            case ALLEGRO_KEY_LEFT:
                ch=-52;
                break;
            case ALLEGRO_KEY_RIGHT:
                ch=-53;
                break;
            case ALLEGRO_KEY_F1:
                ch=-11;
                break;
            case ALLEGRO_KEY_F3:
                ch=-128;
                break;
            default:
                ch=0;
                break;
            }
        }
    }
    else ch = 0;
    return ch;
}

void frame_maker(complete_things *all)
{
    double old = all->timer;
    ALLEGRO_DISPLAY *display;
    int tamxb, tamyb;

    display = all->display;
    ALLEGRO_BITMAP *buf, *bufchang;

    buf = all->images->buffer;

    tamxb = al_get_bitmap_width (buf);
    tamyb = al_get_bitmap_height(buf);

    all->timer=al_get_time();

    all->fps_real=(1.0/(all->timer - old));

    ///| Caso FPS baixo, resize do buffer pra melhorar ;P |///

    if (all->fps_real < 55 && tamxb>176 && tamyb>146 && CONTROLARFRAMES)
    {
        tamxb-=2;
        tamyb-=2;

        bufchang = al_create_bitmap(al_get_bitmap_width(buf),al_get_bitmap_height(buf));

        al_set_target_bitmap(bufchang);
        al_draw_scaled_bitmap(buf,0,0,al_get_bitmap_width(buf),al_get_bitmap_height(buf),0,0,al_get_bitmap_width(bufchang),al_get_bitmap_height(bufchang),0);
        al_destroy_bitmap(buf);

        buf = al_create_bitmap(tamxb,tamyb);

        al_set_target_bitmap(buf);
        al_draw_scaled_bitmap(bufchang,0,0,al_get_bitmap_width(bufchang),al_get_bitmap_height(bufchang),0,0,al_get_bitmap_width(buf),al_get_bitmap_height(buf),0);
        al_destroy_bitmap(bufchang);
    }

    ///| //////////////////////////////////////////////// |///

    al_set_target_backbuffer(display);

    al_draw_scaled_bitmap(buf,0,0,al_get_bitmap_width(buf),al_get_bitmap_height(buf),0,0,al_get_display_width(display),al_get_display_height(display),0);
    if (SHOW_FPS)
    {
        al_draw_textf(all->font,al_map_rgb(255,255,0),0,0,0,"%.0f",all->fps_real);
    }

    al_flip_display();

    all->timer=al_get_time();

    controla_frame(old,all->timer,60);
    al_set_target_bitmap(buf);

    buf      = NULL;
    bufchang = NULL;
}

void controla_frame (double antes, double agora, int fps_max)
{
    if (agora-antes < 1.0 / fps_max && ((1.0 / fps_max) - (agora-antes))>0)
    {
        al_rest((1.0 / fps_max) - (agora-antes));
    }
}

void min_e_seg(double *mins, double *segs)
{
    (*segs)=(*mins)*60+(*segs);
    (*mins)=0;

    while ((*segs)/60>=1)
    {
        *mins=(*mins)+1;
        *segs=(*segs)-60;
    }
}

int pauser_time (complete_things *__things)
{
    __things->what_to_load = PAUSE_MENU_LOAD;
    int i, frame;
    bool pause_b=true;
    printer("[Game-Play] PAUSE!");
    ALLEGRO_BITMAP *buf, *pse, *p_ef;
    ALLEGRO_DISPLAY *display;
    i=0; frame=0;

    buf              = __things->images->buffer;
    pse              = __things->images->apoio_10;
    display          = __things->display;


    al_set_target_bitmap(buf);
    al_clear_to_color(al_map_rgb(0,0,0));
    draw_bitmap_to_buff(pse,buf,0,0,0,0,0);
    frame_maker(__things);

    /// load_gif_bitmaps(30,images,"pause");

    while (__things->key_get_write_push) {}

    while (pause_b==true)
    {
        frame++;
        if (frame>120)
            frame=0;
        al_set_target_bitmap(buf);
        al_clear_to_color(al_map_rgb(0,0,0));

        switch(__things->key_get_write){
        case UP_KEY:
            i++;
            break;
        case DOWN_KEY:
            i--;
            break;
        case ENTER_KEY:
            if (i==0) pause_b=false;
            else frame=-10;
            break;
        case ESC_KEY:
            pause_b=false;
        }

        if (frame==-10)
        {
            __things->what_to_unload = ANIMATION_KO;
            return 10;
        }

        if (i>1)
            i=0;
        else if (i<0)
            i=1;

        switch (frame/2){
        case 0:  p_ef=__things->images->anim_00; break;
        case 1:  p_ef=__things->images->anim_01; break;
        case 2:  p_ef=__things->images->anim_02; break;
        case 3:  p_ef=__things->images->anim_03; break;
        case 4:  p_ef=__things->images->anim_04; break;
        case 5:  p_ef=__things->images->anim_05; break;
        case 6:  p_ef=__things->images->anim_06; break;
        case 7:  p_ef=__things->images->anim_07; break;
        case 8:  p_ef=__things->images->anim_08; break;
        case 9:  p_ef=__things->images->anim_09; break;
        case 10: p_ef=__things->images->anim_10; break;
        case 11: p_ef=__things->images->anim_11; break;
        case 12: p_ef=__things->images->anim_12; break;
        case 13: p_ef=__things->images->anim_13; break;
        case 14: p_ef=__things->images->anim_14; break;
        case 15: p_ef=__things->images->anim_15; break;
        case 16: p_ef=__things->images->anim_16; break;
        case 17: p_ef=__things->images->anim_17; break;
        case 18: p_ef=__things->images->anim_18; break;
        case 19: p_ef=__things->images->anim_19; break;
        case 20: p_ef=__things->images->anim_20; break;
        case 21: p_ef=__things->images->anim_21; break;
        case 22: p_ef=__things->images->anim_22; break;
        case 23: p_ef=__things->images->anim_23; break;
        case 24: p_ef=__things->images->anim_24; break;
        case 25: p_ef=__things->images->anim_25; break;
        case 26: p_ef=__things->images->anim_26; break;
        case 27: p_ef=__things->images->anim_27; break;
        case 28: p_ef=__things->images->anim_28; break;
        case 29: p_ef=__things->images->anim_29; break;
        default: p_ef=__things->images->anim_00;
        }

        draw_bitmap_to_buff(p_ef,buf,0,0,548,132,0);

        if (i==0) pse = __things->images->apoio_10;
        else      pse = __things->images->apoio_11;

        frame_maker(__things);
    }
    __things->what_to_unload = ANIMATION_KO;

    while (__things->is_unloading) {}

    printer("[Game-Play] UNPAUSED!");
    return 0;
}

void draw_bitmap_to_buff (ALLEGRO_BITMAP *bitmap, ALLEGRO_BITMAP *buf, float pos_center_bitmap_x, float pos_center_bitmap_y, double pos_related_x, double pos_related_y, double rotation)
{
    if (bitmap!=NULL && buf!=NULL)
    {
        al_set_target_bitmap(buf);
        al_draw_scaled_rotated_bitmap(bitmap,
                                      pos_center_bitmap_x,
                                      pos_center_bitmap_y,
                                      1.0*al_get_bitmap_width(buf)*pos_related_x/1920.0,
                                      1.0*al_get_bitmap_height(buf)*pos_related_y/1080.0,
                                      1.0*al_get_bitmap_width(bitmap)*(al_get_bitmap_width(buf)/1920.0),
                                      al_get_bitmap_height(bitmap)*(al_get_bitmap_height(buf)/1080.0),
                                      (rotation/180)*ALLEGRO_PI,
                                      0);
    }
}

void all_null(complete_things *_things)
{
    _things->images->buffer     = NULL;
    _things->images->vignette   = NULL;
    _things->images->logo       = NULL;
    _things->images->apoio_01   = NULL;
    _things->images->apoio_02   = NULL;
    _things->images->apoio_03   = NULL;
    _things->images->apoio_04   = NULL;
    _things->images->apoio_05   = NULL;
    _things->images->apoio_06   = NULL;
    _things->images->apoio_07   = NULL;
    _things->images->apoio_08   = NULL;
    _things->images->apoio_09   = NULL;
    _things->images->apoio_10   = NULL;
    _things->images->apoio_11   = NULL;
    _things->images->apoio_12   = NULL;
    _things->images->apoio_13   = NULL;
    _things->images->anim_00    = NULL;
    _things->images->anim_01    = NULL;
    _things->images->anim_02    = NULL;
    _things->images->anim_03    = NULL;
    _things->images->anim_04    = NULL;
    _things->images->anim_05    = NULL;
    _things->images->anim_06    = NULL;
    _things->images->anim_07    = NULL;
    _things->images->anim_08    = NULL;
    _things->images->anim_09    = NULL;
    _things->images->anim_10    = NULL;
    _things->images->anim_11    = NULL;
    _things->images->anim_12    = NULL;
    _things->images->anim_13    = NULL;
    _things->images->anim_14    = NULL;
    _things->images->anim_15    = NULL;
    _things->images->anim_16    = NULL;
    _things->images->anim_17    = NULL;
    _things->images->anim_18    = NULL;
    _things->images->anim_19    = NULL;
    _things->images->anim_20    = NULL;
    _things->images->anim_21    = NULL;
    _things->images->anim_22    = NULL;
    _things->images->anim_23    = NULL;
    _things->images->anim_24    = NULL;
    _things->images->anim_25    = NULL;
    _things->images->anim_26    = NULL;
    _things->images->anim_27    = NULL;
    _things->images->anim_28    = NULL;
    _things->images->anim_29    = NULL;
}


