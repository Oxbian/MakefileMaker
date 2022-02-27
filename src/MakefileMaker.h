#ifndef DEF_MAKEFILEMAKER_H
#define DEF_MAKEFILEMAKER_H

#include <gtk/gtk.h>

typedef struct _MakeS MakeS;
struct _MakeS
{
    gint8 compilator; //Compilator type choose (0: GCC, 1: G++, 2: CLANG)
    GtkWidget *functionEntry; //Entry of the function header name
    GtkWidget *librairieEntry; //Entry of the librairie header name
    GtkWidget *flagsEntry; //Entry of the list of compiling
};

void on_MkS_gcc_radioBtn_toggled (GtkButton *btn, gpointer user_data);
void on_MkS_gplus_radioBtn_toggled (GtkButton *btn, gpointer user_data);
void on_MkS_clang_radioBtn_toggled (GtkButton *btn, gpointer user_data);
void on_MkS_generateBtn_clicked (GtkButton *btn, gpointer user_data);

typedef struct _MakeA MakeA;
struct _MakeA
{
    gint8 compilator; //Compilator type choose (0: GCC, 1: G++, 2: CLANG)
    GtkWidget *functionEntry; //Entry of the function header name
    GtkWidget *librairieEntry; //Entry of the librairie header name
    GtkWidget *flagsEntry; //Entry of the list of compiling
    GtkWidget *sourceDir; //Directory of the source files
    GtkWidget *objectDir; //Directory where to put the object files
};

void on_MkA_gcc_radioBtn_toggled (GtkButton *btn, gpointer user_data);
void on_MkA_gplus_radioBtnn_toggled (GtkButton *btn, gpointer user_data);
void on_MkA_clang_radioBtn_toggled (GtkButton *btn, gpointer user_data);
void on_MkA_generateBtn_clicked (GtkButton *btn, gpointer user_data);

#endif