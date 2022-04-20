#include "../include/gtkwrap.h"
#include "../include/import_file.h"
#include "../include/transform.h"




int main (int argc, char** argv) {
    GtkApplication *app;
    int status;
    int sz;

    unsigned char* file = import(argv[1]);
    sz = size_of_file(file);

    for (int i=0; i< sz; i++){
        printf("%c",file[i]);
    }

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    free(file);
    return status;
}