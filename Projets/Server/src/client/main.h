#include <Elementary.h>

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

static void Build_Window () ;

static void win_del(void *data, Evas_Object *obj, void *event_info) ;

static void btn_connect(void *data, Evas_Object *obj, void *event) ;
static void btn_del(void *data, Evas_Object *obj, void *event) ;


//Struct window
typedef struct Window Window ;
struct Window
{

//Objects window
    Evas_Object         *win ;
    Evas_Object         *btn_con ;
    Evas_Object         *btn_disc ;
    Evas_Object         *bg ;
    Evas_Object         *ip ;

//Our server
    Ecore_Con_Server    *svr ;

};



#endif // MAIN_H_INCLUDED
