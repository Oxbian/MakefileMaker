#include "MakefileMaker.h"

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    GtkBuilder* builder = gtk_builder_new_from_file ("assets/glade/MakefileMaker.glade");

    GtkWidget* window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
    g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    make_t make;
    make.compilator = 0; //Init the computer to default: 0 GCC

    /*Getting the gtkWidget from the builder file*/
    make.filesname_entry = GTK_WIDGET(gtk_builder_get_object (builder, "mk_files_name_entry"));
    make.srcdir_entry = GTK_WIDGET(gtk_builder_get_object (builder, "mk_srcdir_entry"));
    make.incdir_entry = GTK_WIDGET(gtk_builder_get_object (builder, "mk_incdir_entry"));
    make.flag_entry = GTK_WIDGET(gtk_builder_get_object (builder, "mk_flag_entry"));
    make.progname_entry = GTK_WIDGET(gtk_builder_get_object (builder, "mk_progname_entry"));

    /*Getting all the other gtkWidget we need*/
    GtkWidget* mk_gcc_radio_btn = GTK_WIDGET(gtk_builder_get_object (builder, "mk_gcc_radio_btn"));
    GtkWidget* mk_gplus_radio_btn =GTK_WIDGET(gtk_builder_get_object (builder, "mk_g++_radio_btn"));
    GtkWidget* mk_clang_radio_btn = GTK_WIDGET(gtk_builder_get_object (builder, "mk_clang_radio_btn"));
    GtkWidget* mk_generate_btn = GTK_WIDGET(gtk_builder_get_object (builder, "mk_generate_btn"));

    /*Connection all signals to the builder*/
    g_signal_connect (mk_gcc_radio_btn, "toggled", G_CALLBACK (on_mk_gcc_radio_btn_toggled), &make);
    g_signal_connect (mk_gplus_radio_btn, "toggled", G_CALLBACK (on_mk_gplus_radio_btn_toggled), &make);
    g_signal_connect (mk_clang_radio_btn, "toggled", G_CALLBACK (on_mk_clang_radio_btn_toggled), &make);
    g_signal_connect (mk_generate_btn, "clicked", G_CALLBACK (on_mk_generate_btn_clicked), &make);

    gtk_widget_show_all(window);
    gtk_main();
    return EXIT_SUCCESS;
}

void on_mk_gcc_radio_btn_toggled (GtkButton* btn, gpointer user_data)
{
    make_t* data = (make_t*) user_data;
    data->compilator = 0;
}

void on_mk_gplus_radio_btn_toggled (GtkButton* btn, gpointer user_data)
{
    make_t* data = (make_t*) user_data;
    data->compilator = 1;
}

void on_mk_clang_radio_btn_toggled (GtkButton* btn, gpointer user_data)
{
    make_t* data = (make_t*) user_data;
    data->compilator = 2;
}

/* Function to allow the copy paste with the opening box */
static void _set_label_selectable(gpointer data, gpointer user_data)
{
    GtkWidget* widget = GTK_WIDGET(data);

    if (GTK_IS_LABEL(widget)) {
        gtk_label_set_selectable(GTK_LABEL(widget), TRUE);
    }
}

static void _set_lables_selectable(GtkWidget* dialog)
{
    GtkWidget* area = gtk_message_dialog_get_message_area(GTK_MESSAGE_DIALOG(dialog));
    GtkContainer* box = (GtkContainer* ) area;

    GList* children = gtk_container_get_children(box);
    g_list_foreach(children, _set_label_selectable, NULL);
    g_list_free(children);
}

void on_mk_generate_btn_clicked (GtkButton* btn, gpointer user_data)
{
    make_t* data = (make_t*) user_data;

    /*Copying data into more readable strings*/
    char compilator[6], filesname[gtk_entry_get_text_length (GTK_ENTRY(data->filesname_entry))+1], 
    srcdir[gtk_entry_get_text_length (GTK_ENTRY(data->srcdir_entry))+1], incdir[gtk_entry_get_text_length (GTK_ENTRY(data->incdir_entry))+1],
    flag[gtk_entry_get_text_length (GTK_ENTRY(data->flag_entry))+1], progname[gtk_entry_get_text_length (GTK_ENTRY(data->progname_entry))+1];

    switch (data->compilator)
    {
        case 0:
            strncpy(compilator, "gcc", 6);
            break;
        case 1:
            strncpy(compilator, "g++", 6);
            break;
        case 2:
            strncpy(compilator, "clang", 6);
            break;
    }
    strcpy(filesname, gtk_entry_get_text(GTK_ENTRY(data->filesname_entry)));
    strcpy(srcdir, gtk_entry_get_text(GTK_ENTRY(data->srcdir_entry)));
    strcpy(incdir, gtk_entry_get_text(GTK_ENTRY(data->incdir_entry)));
    strcpy(flag, gtk_entry_get_text(GTK_ENTRY(data->flag_entry)));
    strcpy(progname, gtk_entry_get_text(GTK_ENTRY(data->progname_entry)));

    GtkWidget* dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"NAME := %s\n#------------------------------------------------#\n#   INGREDIENTS                                  #\n#------------------------------------------------#\n# SRC_DIR   source directory\n# OBJ_DIR   object directory\n# SRCS      source files\n# OBJS      object files\n#\n# CC        compiler\n# CFLAGS    compiler flags\n# CPPFLAGS  preprocessor flags\n\nSRC_DIR := %s\nOBJ_DIR := obj\nSRCS := %s\nSRCS := $(SRCS:%%=$(SRC_DIR)/%%)\nOBJS := $(SRCS:$(SRC_DIR)/%%.c=$(OBJ_DIR)/%%.o)\n\nCC := %s\nCFLAGS := %s\nCPPFLAGS := -I %s\n#------------------------------------------------#\n#   UTENSILS                                     #\n#------------------------------------------------#\n# RM        force remove\n# MAKEFLAGS make flags\n# DIR_DUP   duplicate directory tree\n\nRM := rm -f\nMAKEFLAGS += --no-print-directory\nDIR_DUP = mkdir -p $(@D)\n#------------------------------------------------#\n#   RECIPES                                      #\n#------------------------------------------------#\n# all       default goal\n# $(NAME)   linking .o -> binary\n# %%.o       compilation .c -> .o\n# clean     remove .o\n# fclean    remove .o + binary\n# re        remake default goal\n\nall: $(NAME)\n\n$(NAME): $(OBJS)\n\t$(CC) $(OBJS) -o $(NAME)\n\t$(info CREATED $(NAME))\n\n$(OBJ_DIR)/%%.o: $(SRC_DIR)/%%.c\n\t$(DIR_DUP)\n\t$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<\n\t$(info CREATED $@)\n\nclean:\n\t$(RM) $(OBJS)\n\nfclean: clean\n\t$(RM) $(NAME)\n\nre:\n\t$(MAKE) fclean\n\t$(MAKE) all\n#------------------------------------------------#\n#   SPEC                                         #\n#------------------------------------------------#\n\n.PHONY: clean fclean re\n.SILENT:",
    progname, srcdir, filesname, compilator, flag, incdir);
    _set_lables_selectable(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
}