#include<Elementary.h>


Eina_Bool
_add(void *data , int type, Ecore_Con_Event_Client_Add *ev)
{
//teste
printf("New client !\n") ;

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

printf("Client disconected !\n") ;


}


Eina_Bool
_data(void *data, int type, Ecore_Con_Event_Server_Data *ev)
{
   char fmt[128];


 snprintf(fmt, sizeof(fmt), "Received %i bytes from server:\n" ">>>>>\n"  "%s\n" ">>>>>\n", ev->size, ev->data);

   printf(fmt);


  return ECORE_CALLBACK_RENEW;
}


void main(void)
{
// Our server
    Ecore_Con_Server *svr ;

// Init Ecore
    ecore_init();
    ecore_con_init();

// Start Server
    if (!(svr = ecore_con_server_add(ECORE_CON_REMOTE_TCP, "127.0.0.1", 1234, NULL)))
            exit(1);

// Set timeout and client limit
    ecore_con_server_timeout_set(svr, 10);
    ecore_con_server_client_limit_set(svr, 3, 0);

    printf("Server done !\n") ;

// What it doing when new client, client quit, or data received
    ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_ADD, (Ecore_Event_Handler_Cb)_add, NULL);
    ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_DEL, (Ecore_Event_Handler_Cb)_del, NULL);
    ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_DATA, (Ecore_Event_Handler_Cb)_data, NULL);

// Start ecore loop
    ecore_main_loop_begin();



     }
