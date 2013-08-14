#include <Elementary.h>
#include <stdio.h>
#include "main.h"




typedef struct Fenetre Fenetre ;
struct Fenetre
{

Evas_Object *win ;
Evas_Object *btn ;
Evas_Object *bg ;
Evas_Object *ent ;


};

static void
btn_clicked(void *data, Evas_Object *obj, void *event)
{


Fenetre *a = data ;

printf ("%s\n", elm_object_text_get(a->ent)) ;

Ecore_Con_Server *svr ;
int port = 8080 ;

const char *address = elm_object_text_get(a->ent) ;

if (!(svr = ecore_con_server_connect(ECORE_CON_REMOTE_TCP, address, port, NULL)))
     {
        printf("could not connect to the server: %s, port %d.\n",
               address, port);
        exit(2);
     }


}


static void
Construire_Fenetre ()
{

Fenetre *Fen_Principale  = malloc(sizeof(Fenetre)) ;


    //Create windows

#ifdef DEBUG

    printf("Create windows\n") ;

#endif

    Fen_Principale->win = elm_win_add(NULL, "main_window", ELM_WIN_BASIC);
    evas_object_smart_callback_add(Fen_Principale->win, "delete,request", win_del, Fen_Principale);
    elm_win_title_set(Fen_Principale->win, "MyTest") ;
    evas_object_resize(Fen_Principale->win, 500, 500) ;
    evas_object_show(Fen_Principale->win);


    //Create background
    printf("Create background\n") ;
    Fen_Principale->bg = elm_bg_add(Fen_Principale->win);
    elm_win_resize_object_add(Fen_Principale->win, Fen_Principale->bg) ;
    elm_bg_color_set(Fen_Principale->bg, 10, 90, 200) ;
    evas_object_size_hint_weight_set(Fen_Principale->bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND) ;
    evas_object_show(Fen_Principale->bg);


    //Create Button
    printf("Create Button\n") ;
    Fen_Principale->btn = elm_button_add(Fen_Principale->win) ;
    evas_object_move(Fen_Principale->btn, 100, 100) ;
    evas_object_resize(Fen_Principale->btn, 100, 50) ;
    elm_object_text_set(Fen_Principale->btn, "ClickMe") ;
    evas_object_show(Fen_Principale->btn) ;


    //Create Entry
    printf("Create entry\n") ;
    Fen_Principale->ent = elm_entry_add(Fen_Principale->win) ;
    evas_object_move(Fen_Principale->ent, 300, 200) ;
    evas_object_resize(Fen_Principale->ent, 100, 30) ;
    elm_object_text_set (Fen_Principale->ent, "127.0.0.1") ;
    elm_entry_scrollable_set(Fen_Principale->ent, EINA_TRUE) ;
    elm_object_tooltip_text_set(Fen_Principale->ent, "Coucou") ;
    evas_object_show(Fen_Principale->ent) ;



evas_object_smart_callback_add(Fen_Principale->btn, "clicked", btn_clicked, Fen_Principale) ;


}

static void
win_del(void *data, Evas_Object *obj, void *event_info)
{

    free(data) ;
    elm_exit();
}


int
main(int argc, char *argv[])
{
    elm_init(argc, argv) ;
    Construire_Fenetre () ;
    elm_run();
    elm_shutdown();

    return EXIT_SUCCESS;
}

