#include "MakefileMaker.h"

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new_from_file ("src/MakefileMaker.glade");

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (builder, "window"));
    g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    MakeS makeS;
    makeS.compilator = 0; //Init the computer int to 0: GCC

    /*Getting the gtkWidget from the builder file*/
    makeS.functionEntry = GTK_WIDGET(gtk_builder_get_object (builder, "MkS_functionEntry"));
    makeS.librairieEntry = GTK_WIDGET(gtk_builder_get_object (builder, "MkS_librairieEntry"));
    makeS.flagsEntry = GTK_WIDGET(gtk_builder_get_object (builder, "MkS_flagsEntry"));

    MakeA makeA;
    makeA.compilator = 0; //Init the computer int to 0: GCC

    /*Getting the gtkWidget from the builder file*/
    makeA.functionEntry = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_functionEntry"));
    makeA.librairieEntry = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_librairieEntry"));
    makeA.flagsEntry = GTK_WIDGET(gtk_builder_get_object (builder , "MkA_flagsEntry"));
    makeA.objectDir = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_objectFile"));
    makeA.sourceDir = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_sourceFile"));

    /*Getting all the other gtkWidget we need*/
    GtkWidget *MkS_gcc_radioBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkS_gcc_radioBtn"));
    GtkWidget *MkS_gplus_radioBtn =GTK_WIDGET(gtk_builder_get_object (builder, "MkS_g++_radioBtn"));
    GtkWidget *MkS_clang_radioBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkS_clang_radioBtn"));
    GtkWidget *MkS_generateBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkS_generateBtn"));

    GtkWidget *MkA_gcc_radioBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_gcc_radioBtn"));
    GtkWidget *MkA_gplus_radioBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_g++_radioBtn"));
    GtkWidget *MkA_clang_radioBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_clang_radioBtn"));
    GtkWidget *MkA_generateBtn = GTK_WIDGET(gtk_builder_get_object (builder, "MkA_generateBtn"));

    /*Connection all signals to the builder*/
    g_signal_connect (MkS_gcc_radioBtn, "toggled", G_CALLBACK (on_MkS_gcc_radioBtn_toggled), &makeS);
    g_signal_connect (MkS_gplus_radioBtn, "toggled", G_CALLBACK (on_MkS_gplus_radioBtn_toggled), &makeS);
    g_signal_connect (MkS_clang_radioBtn, "toggled", G_CALLBACK (on_MkS_clang_radioBtn_toggled), &makeS);
    g_signal_connect (MkS_generateBtn, "clicked", G_CALLBACK (on_MkS_generateBtn_clicked), &makeS);

    g_signal_connect (MkA_gcc_radioBtn, "toggled", G_CALLBACK (on_MkA_gcc_radioBtn_toggled), &makeA);
    g_signal_connect (MkA_gplus_radioBtn, "toggled", G_CALLBACK (on_MkA_gplus_radioBtnn_toggled), &makeA);
    g_signal_connect (MkA_clang_radioBtn, "toggled", G_CALLBACK (on_MkA_clang_radioBtn_toggled), &makeA);
    g_signal_connect (MkA_generateBtn, "clicked", G_CALLBACK (on_MkA_generateBtn_clicked), &makeA);

    gtk_widget_show_all(window);
    gtk_main();
    return EXIT_SUCCESS;
}

void on_MkS_gcc_radioBtn_toggled (GtkButton *btn, gpointer user_data)
{
    MakeS *data = (MakeS*) user_data;
    data->compilator = 0;
}

void on_MkS_gplus_radioBtn_toggled (GtkButton *btn, gpointer user_data)
{
    MakeS *data = (MakeS*) user_data;
    data->compilator = 1;
}

void on_MkS_clang_radioBtn_toggled (GtkButton *btn, gpointer user_data)
{
    MakeS *data = (MakeS*) user_data;
    data->compilator = 2;
}

static void _set_label_selectable(gpointer data, gpointer user_data)
{
    GtkWidget *widget = GTK_WIDGET(data);

    if (GTK_IS_LABEL(widget))
    {
        gtk_label_set_selectable(GTK_LABEL(widget), TRUE);
    }
}

static void _set_lables_selectable(GtkWidget *dialog)
{
    GtkWidget *area = gtk_message_dialog_get_message_area(
        GTK_MESSAGE_DIALOG(dialog));
    GtkContainer *box = (GtkContainer *) area;

    GList *children = gtk_container_get_children(box);
    g_list_foreach(children, _set_label_selectable, NULL);
    g_list_free(children);
}

void on_MkS_generateBtn_clicked (GtkButton *btn, gpointer user_data)
{
    MakeS *data = (MakeS*) user_data;

    /*Copying data into more readable strings*/
    char compilator[6], function[gtk_entry_get_text_length (GTK_ENTRY(data->functionEntry))+1], librairie[gtk_entry_get_text_length (GTK_ENTRY(data->librairieEntry))+1], cflags[gtk_entry_get_text_length (GTK_ENTRY(data->flagsEntry))+1];
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
    strcpy(function, gtk_entry_get_text(GTK_ENTRY(data->functionEntry)));
    strcpy(librairie, gtk_entry_get_text(GTK_ENTRY(data->librairieEntry)));
    strcpy(cflags, gtk_entry_get_text(GTK_ENTRY(data->flagsEntry)));

    /*We check if the function entry has a text with more than 3 characters else we just assume the users wants to use a librarie only*/
    if (strlen(function) >= 3)
    {
        //Sorry if it looks like some garbage :(
        if (strlen(librairie) >= 3)
        {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"prog: main.o %s.o %s.o\n\t%s main.o %s.o %s.o -o prog.exe %s\nmain.o: main.c %s.h %s.h\n\t%s %s -c main.c\n%s.o: %s.c %s.h %s.h\n\t%s %s -c %s.c\n%s.o: %s.c %s.h\n\t%s %s -c %s.c\n.PHONY : clean\nclean:\n\trm *.o",
            function, librairie, compilator, function, librairie, cflags, function, librairie, compilator, cflags, function, function, function, librairie, compilator, cflags, function, librairie, librairie, librairie, compilator, cflags, librairie);
            _set_lables_selectable(dialog);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy (dialog);
        }
        else
        {
            GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"prog: main.o %s.o\n\t%s main.o %s.o -o prog.exe %s\nmain.o: main.c %s.h\n\t%s %s -c main.c\n%s.o: %s.c %s.h\n\t%s %s -c %s.c\n.PHONY : clean\nclean:\n\trm *.o",
            function, compilator, function, cflags, function, compilator, cflags, function, function, function, compilator, cflags, function);
            _set_lables_selectable(dialog);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy (dialog);
        }
    }
    else if (gtk_entry_get_text_length (GTK_ENTRY(data->librairieEntry)) >= 3)
    {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"prog: main.o %s.o\n\t%s main.o %s.o -o prog.exe %s\nmain.o: main.c %s.h\n\t%s %s -c main.c\n%s.o: %s.c %s.h\n\t%s %s -c %s.c\n.PHONY : clean\nclean:\n\trm *.o",
        librairie, compilator, librairie, cflags, librairie ,compilator, cflags, librairie, librairie, librairie, compilator, cflags, librairie);
        _set_lables_selectable(dialog);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy (dialog);
    }

}

void on_MkA_gcc_radioBtn_toggled (GtkButton *btn, gpointer user_data)
{
    MakeA *data = (MakeA*) user_data;
    data->compilator = 0;
}

void on_MkA_gplus_radioBtnn_toggled (GtkButton *btn, gpointer user_data)
{
    MakeA *data = (MakeA*) user_data;
    data->compilator = 1;
}

void on_MkA_clang_radioBtn_toggled (GtkButton *btn, gpointer user_data)
{
    MakeA *data = (MakeA*) user_data;
    data->compilator = 2;
}

void on_MkA_generateBtn_clicked (GtkButton *btn, gpointer user_data)
{
    MakeA *data = (MakeA*) user_data;
    char compilator[6], function[gtk_entry_get_text_length (GTK_ENTRY(data->functionEntry))+1], librairie[gtk_entry_get_text_length (GTK_ENTRY(data->librairieEntry))+1], cflags[gtk_entry_get_text_length (GTK_ENTRY(data->flagsEntry))+1], srcDir[strlen(gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(data->sourceDir))) +1], objDir[strlen(gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(data->objectDir))) +1];
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
    strcpy(function, gtk_entry_get_text(GTK_ENTRY(data->functionEntry)));
    strcpy(librairie, gtk_entry_get_text(GTK_ENTRY(data->librairieEntry)));
    strcpy(cflags, gtk_entry_get_text(GTK_ENTRY(data->flagsEntry)));
    strcpy(srcDir, gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(data->sourceDir)));
    strcpy(objDir, gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(data->objectDir)));

    /*We check if the srcDirectory isn't null else we just assume the files are in the same dir than the makefile*/
    if (strlen(srcDir) >= 1)
    {
        //Checking if there is a objDir too
        if (strlen(objDir) >= 1)
        {
            if (strlen(function) >= 3)
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nvpath %%.c %s\nsources := %s.c %s.c main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, srcDir, function, librairie, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nvpath %%.c %s\nsources := %s.c main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, srcDir, function, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
            else
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nvpath %%.c %s\nsources := %s.c main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, srcDir, librairie, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nvpath %%.c %s\nsources := main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, srcDir, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
        }
        else
        {
            if (strlen(function) >= 3)
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nvpath %%.c %s\nvpath %.h %s\nvpath %%.o %s\n\nsources := %s.c %s.c main.c\nobjects := $(addprefix %s/,$(sources:.c=.o))\nCFLAGS := %s\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): %s.h %s.h\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, srcDir, srcDir, srcDir, function, librairie, srcDir, cflags, function, librairie);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nvpath %%.c %s\nvpath %.h %s\nvpath %%.o %s\n\nsources := %s.c main.c\nobjects := $(addprefix %s/,$(sources:.c=.o))\nCFLAGS := %s\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): %s.h\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, srcDir, srcDir, srcDir, function, srcDir, cflags, function);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
            else
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nvpath %%.c %s\nvpath %.h %s\nvpath %%.o %s\n\nsources := %s.c main.c\nobjects := $(addprefix %s/,$(sources:.c=.o))\nCFLAGS := %s\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): %s.h\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, srcDir, srcDir, srcDir, librairie, srcDir, cflags, librairie);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"Veuillez remplir les cases function et/ou librairie");
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
        }
    }
    else
    {
        //Checking if there is a objDir too
        if (strlen(objDir) >= 1)
        {
            if (strlen(function) >= 3)
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nsources := %s.c %s.c main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, function, librairie, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nsources := %s.c main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, function, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
            else
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nsources := %s.c main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, librairie, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\nOBJDIR := %s\nsources := main.c\nobjects := $(addprefix $(OBJDIR)/,$(sources:.c=.o))\nCFLAGS := %s\n\n$(OBJDIR)/%%.o : %%.c\n\t$(COMPILE.c) $(OUTPUT_OPTION) $<\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): | $(OBJDIR)\n\n$(OBJDIR):\n\tmkdir $(OBJDIR)\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, objDir, cflags);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
        }
        else
        {
            if (strlen(function) >= 3)
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\n\nsources := %s.c %s.c main.c\nobjects := $(sources:.c=.o)\nCFLAGS := %s\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): %s.h %s.h\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, function, librairie, cflags, function, librairie);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\n\nsources := %s.c main.c\nobjects := $(sources:.c=.o)\nCFLAGS := %s\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): %s.h\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, function, cflags, function);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
            else
            {
                if (strlen(librairie) >= 3)
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"CC:= %s\n\nsources := %s.c main.c\nobjects := $(sources:.c=.o)\nCFLAGS := %s\n\nprog: $(objects)\n\t$(CC) -o prog $(objects) $(CFLAGS)\n\n$(objects): %s.h\n\n.PHONY : clean\nclean:\n\trm prog $(objects)\n\n.SECONDARY: $(objects)",
                    compilator, librairie,cflags, librairie);
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
                else
                {
                    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,"Veuillez remplir les cases function et/ou librairie");
                    _set_lables_selectable(dialog);
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy (dialog);
                }
            }
        }
    }

}