#ifndef DEF_MAKEFILEMAKER_H
#define DEF_MAKEFILEMAKER_H

#include <gtk/gtk.h>
#include <string.h>

typedef struct _make
{
    gint8 compilator; // Compilator type choose (0: GCC, 1: G++, 2: CLANG)
    GtkWidget* filesname_entry; // Entry for the files names 
    GtkWidget* srcdir_entry; // Entry for the source dir path
    GtkWidget* incdir_entry; // Entry for the include dir path
    GtkWidget* flag_entry; // Entry for the compilations flags
    GtkWidget* progname_entry; // Entry for the libs flags
} make_t;

#define BUFFER 4096

void on_mk_gcc_radio_btn_toggled (GtkButton* btn, gpointer user_data);
void on_mk_gplus_radio_btn_toggled (GtkButton* btn, gpointer user_data);
void on_mk_clang_radio_btn_toggled (GtkButton* btn, gpointer user_data);
void on_mk_generate_btn_clicked (GtkButton* btn, gpointer user_data);

#endif 