#include <Elementary.h>
#include <stdio.h>
#include "main.h"


// Button connect pressed
static void
btn_connect(void *data, Evas_Object *obj, void *event)
{

Window *a = data ;

//printf ("%s\n", elm_object_text_get(a->ip)) ;

int port = 1234 ;

// Get ip from user
    const char *address = elm_object_text_get(a->ip) ;

// Create connection
    if (!(a->svr = ecore_con_server_connect(ECORE_CON_REMOTE_TCP, address, port, NULL)))
        {
            printf("could not connect to the server: %s, port %d.\n", address, port) ;
            exit(2);
        }
// Button Connection Disabled and Disconnect Enabled
    elm_object_disabled_set(a->btn_disc, EINA_FALSE) ;
    elm_object_disabled_set(a->btn_con, EINA_TRUE) ;
}

// Button disconnect pressed
static void
btn_disconnect(void *data, Evas_Object *obj, void *event)
{

Window *a = data ;

// Button Connection Enabled and Disconnect Disabled
    elm_object_disabled_set(a->btn_disc, EINA_TRUE) ;
    elm_object_disabled_set(a->btn_con, EINA_FALSE) ;

// Stop connection
    ecore_con_server_del(a->svr) ;

}


// Create Window
static void
Build_Window ()
{

// Create window named Main_Win
    Window *Main_Win  = malloc(sizeof(Window)) ;

//Create window
    printf("Create window\n") ;
    Main_Win->win = elm_win_add(NULL, "main_window", ELM_WIN_BASIC);
    evas_object_smart_callback_add(Main_Win->win, "delete,request", win_del, Main_Win);
    elm_win_title_set(Main_Win->win, "MyTest") ;
    evas_object_resize(Main_Win->win, 500, 500) ;
    evas_object_show(Main_Win->win);

//Create background
    printf("Create background\n") ;
    Main_Win->bg = elm_bg_add(Main_Win->win);
    elm_win_resize_object_add(Main_Win->win, Main_Win->bg) ;
    elm_bg_color_set(Main_Win->bg, 10, 90, 200) ;
    evas_object_size_hint_weight_set(Main_Win->bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND) ;
    evas_object_show(Main_Win->bg);

//Create Buttons
    printf("Create Button\n") ;
    Main_Win->btn_con = elm_button_add(Main_Win->win) ;
    evas_object_move(Main_Win->btn_con, 10, 10) ;
    evas_object_resize(Main_Win->btn_con, 100, 30) ;
    elm_object_text_set(Main_Win->btn_con, "Connect") ;
    evas_object_show(Main_Win->btn_con) ;


    Main_Win->btn_disc = elm_button_add(Main_Win->win) ;
    evas_object_move(Main_Win->btn_disc, 10, 50) ;
    evas_object_resize(Main_Win->btn_disc, 100, 30) ;
    elm_object_text_set(Main_Win->btn_disc, "Disconnect") ;
    evas_object_show(Main_Win->btn_disc) ;
    elm_object_disabled_set(Main_Win->btn_disc, EINA_TRUE) ;

//Create Entrys
    printf("Create entry\n") ;
    Main_Win->ip = elm_entry_add(Main_Win->win) ;
    evas_object_move(Main_Win->ip, 120, 12) ;
    evas_object_resize(Main_Win->ip, 60, 20) ;
    elm_object_text_set (Main_Win->ip, "127.0.0.1") ;
    elm_entry_scrollable_set(Main_Win->ip, EINA_TRUE) ;
    elm_object_tooltip_text_set(Main_Win->ip, "Coucou") ;
    evas_object_show(Main_Win->ip) ;

// Link Buttons Functions
    evas_object_smart_callback_add(Main_Win->btn_con, "clicked", btn_connect, Main_Win) ;
    evas_object_smart_callback_add(Main_Win->btn_disc, "clicked", btn_disconnect, Main_Win) ;
}

// Close window
static void
win_del(void *data, Evas_Object *obj, void *event_info)
{

//Clear memory allowed to struct Fenetre
    free(data) ;

//Exit elementary loop
    elm_exit();
}

//main function
int
main(int argc, char *argv[])
{

//Init elm
    elm_init(argc, argv) ;

//Start create window
    Build_Window () ;

//Start elementary loop
    elm_run();

//Close elementary
    elm_shutdown();

    return EXIT_SUCCESS;
}

