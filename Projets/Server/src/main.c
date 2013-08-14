/*#include <stdio.h>
#include <Ecore.h>
#include <Ecore_Con.h>
*/
#include<Elementary.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# define __UNUSED__
#endif

void main(void)
{
   Ecore_Con_Server *svr;

   ecore_init();
   ecore_con_init();

   if (!(svr = ecore_con_server_add(ECORE_CON_REMOTE_TCP, "127.0.0.1", 1234, NULL)))
            exit(1);

printf("Server done !\n") ;

    ecore_con_server_timeout_set(svr, 10);
    ecore_con_server_client_limit_set(svr, 3, 0);

    ecore_main_loop_begin();



     }
