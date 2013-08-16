#include <Elementary.h>
#include <stdio.h>
#include "main.h"
//#include <pthread.h>



Eina_Bool
_add(void *data , int type, Ecore_Con_Event_Client_Add *ev)
{

printf("New client !\n") ;

printf("Server connected %d, \n", ecore_con_server_connected_get(ev->client));

Window *a = data ;


// Button Connection Disabled and Disconnect Enabled
    elm_object_disabled_set(a->btn_disc, EINA_FALSE) ;
    elm_object_disabled_set(a->btn_con, EINA_TRUE) ;

  /* char welcome[] = "hello! - sent from the server";
   Ecore_Con_Server *srv;
   Ecore_Con_Client *cl;
   const Eina_List *clients, *l;

   struct _Client *client = malloc(sizeof(*client));
   client->sdata = 0;

   printf("Client with ip %s, port %d, connected = %d!\n",
          ecore_con_client_ip_get(ev->client),
          ecore_con_client_port_get(ev->client),
          ecore_con_client_connected_get(ev->client));

   ecore_con_client_send(ev->client, welcome, sizeof(welcome));
   ecore_con_client_flush(ev->client);

   ecore_con_client_timeout_set(ev->client, 6);

   ecore_con_client_data_set(ev->client, client);

   srv = ecore_con_client_server_get(ev->client);
   printf("Clients connected to this server:\n");
   clients = ecore_con_server_clients_get(srv);
   EINA_LIST_FOREACH(clients, l, cl)
     printf("%s\n", ecore_con_client_ip_get(cl));

   return ECORE_CALLBACK_RENEW;*/
}

Eina_Bool
_del(void *data , int type, Ecore_Con_Event_Client_Add *ev)
{

Window *a = data ;

printf("Client disconected !\n") ;

// Button Connection Enabled and Disconnect Disabled
    elm_object_disabled_set(a->btn_disc, EINA_TRUE) ;
    elm_object_disabled_set(a->btn_con, EINA_FALSE) ;


}


Eina_Bool
_data(void *data, int type, Ecore_Con_Event_Server_Data *ev)
{
   char fmt[128];


    snprintf(fmt, sizeof(fmt), "Received %i bytes from server:\n" ">>>>>\n"  "%s\n" ">>>>>\n", ev->size, ev->data);

   printf(fmt);


  return ECORE_CALLBACK_RENEW;
}


// Button connect pressed
static void
btn_connect(void *data, Evas_Object *obj, void *event)
{

Window *a = data ;


int port = 1234 ;

// Get ip from user
    const char *address = elm_object_text_get(a->ip) ;


// Get port from user
//    int port = atoi(elm_object_text_get(a->port)) ;


// Create connection
    if (!(a->svr = ecore_con_server_connect(ECORE_CON_REMOTE_TCP, address, port, NULL)))
        {
            printf("could not connect to the server: %s, port %d.\n", address, port) ;
            exit(2);
        }


   /* set event handler for server connect */
   ecore_event_handler_add(ECORE_CON_EVENT_SERVER_ADD, (Ecore_Event_Handler_Cb)_add, a);
   /* set event handler for server disconnect */
   ecore_event_handler_add(ECORE_CON_EVENT_SERVER_DEL, (Ecore_Event_Handler_Cb)_del, a);
   /* set event handler for receiving server data */
   ecore_event_handler_add(ECORE_CON_EVENT_SERVER_DATA, (Ecore_Event_Handler_Cb)_data, a);


char welcome[] = "Connection" ;

ecore_con_server_send(a->svr, welcome, sizeof(welcome)) ;

}




// Button disconnect pressed
static void
btn_disconnect(void *data, Evas_Object *obj, void *event)
{

Window *a = data ;



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

