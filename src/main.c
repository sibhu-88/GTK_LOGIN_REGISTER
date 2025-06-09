#include "headers.h"

User *current_user = NULL;

void cleanup_user(gpointer data)
{
    User *user = (User *)data;
    free(user->username);
    free(user->category);
    free(user);
}

void load_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen,
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, "resources/style.css", &error);
    if (error)
    {
        g_printerr("Error loading CSS: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *stack;
    GtkWidget *stack_switcher;
    GtkWidget *main_box;
    GtkWidget *register_page;
    GtkWidget *login_page;

    gtk_init(&argc, &argv);
    load_css();

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login/Register");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 700);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(main_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(main_box, GTK_ALIGN_CENTER);

    stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 500);
    gtk_widget_set_halign(stack, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(stack, GTK_ALIGN_CENTER);

    stack_switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(stack));
    gtk_widget_set_halign(stack_switcher, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(stack_switcher, GTK_ALIGN_CENTER);

    register_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    login_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(register_page, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(login_page, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(register_page, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(login_page, GTK_ALIGN_CENTER);
    gtk_style_context_add_class(gtk_widget_get_style_context(login_page), "toplevel");
    gtk_style_context_add_class(gtk_widget_get_style_context(register_page), "toplevel");

    create_register_page(register_page);
    create_login_page(login_page);

    gtk_stack_add_titled(GTK_STACK(stack), login_page, "login", "Login");
    gtk_stack_add_titled(GTK_STACK(stack), register_page, "register", "Register");

    gtk_box_pack_start(GTK_BOX(main_box), stack_switcher, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(main_box), stack, TRUE, TRUE, 5);

    gtk_container_add(GTK_CONTAINER(window), main_box);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(cleanup_user), NULL);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}