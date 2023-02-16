#include "gtkwrap.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

static gboolean render (GtkGLArea *area, GdkGLContext *context) {

    glClearColor (0, 0, 0, 0);
    glClear (GL_COLOR_BUFFER_BIT);

}


void activate(GtkApplication* app, gpointer user_data){
    bool done = false;
    GtkWidget *window;
    GtkWidget *canvas;

    gtk_init ();

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Test Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    canvas = gtk_gl_area_new ();

    g_signal_connect (canvas, "render", G_CALLBACK (render), NULL);

    gtk_window_set_child (GTK_WINDOW (window), canvas);

    gtk_widget_show (window);
}

