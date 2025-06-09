#include "headers.h"

static void free_data(gpointer data)
{
    free(data);
}

void create_login_page(GtkWidget *page_box)
{
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *login_button;
    GtkWidget *status_label;

    grid = gtk_grid_new();
    gtk_widget_set_margin_top(grid, 20);
    gtk_widget_set_margin_bottom(grid, 20);
    gtk_widget_set_margin_start(grid, 20);
    gtk_widget_set_margin_end(grid, 20);

    username_label = gtk_label_new("Username:");
    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Enter your username");
    gtk_entry_set_max_length(GTK_ENTRY(username_entry), 20);

    password_label = gtk_label_new("Password:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Enter your password");
    gtk_entry_set_max_length(GTK_ENTRY(password_entry), 20);
    gtk_entry_set_invisible_char(GTK_ENTRY(password_entry), '*');

    login_button = gtk_button_new_with_label("Login");
    gtk_widget_set_halign(login_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(login_button, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(login_button, 100, 30);
    gtk_widget_set_can_default(login_button, TRUE);
    gtk_widget_grab_default(login_button);

    status_label = gtk_label_new("");
    gtk_widget_set_halign(status_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(status_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(status_label, "status_label");

    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), status_label, 0, 3, 2, 1);

    gtk_widget_set_margin_top(username_label, 5);
    gtk_widget_set_margin_bottom(username_label, 5);
    gtk_widget_set_margin_top(username_entry, 5);
    gtk_widget_set_margin_bottom(username_entry, 5);
    gtk_widget_set_margin_top(password_label, 5);
    gtk_widget_set_margin_bottom(password_label, 5);
    gtk_widget_set_margin_top(password_entry, 5);
    gtk_widget_set_margin_bottom(password_entry, 5);
    gtk_widget_set_margin_top(login_button, 5);
    gtk_widget_set_margin_bottom(login_button, 5);

    GtkWidget **data = (GtkWidget **)malloc(sizeof(GtkWidget *) * 3);
    data[0] = username_entry;
    data[1] = password_entry;
    data[2] = status_label;

    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), data);
    g_signal_connect(page_box, "destroy", G_CALLBACK(free_data), data);

    gtk_container_add(GTK_CONTAINER(page_box), grid);
    gtk_widget_show_all(page_box);
}

void create_register_page(GtkWidget *page_box)
{
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *confirm_password_label;
    GtkWidget *confirm_password_entry;
    GtkWidget *email_label;
    GtkWidget *email_entry;
    GtkWidget *category_label;
    GtkWidget *category_combobox;
    GtkWidget *register_button;
    GtkWidget *status_label;

    grid = gtk_grid_new();
    gtk_widget_set_margin_top(grid, 20);
    gtk_widget_set_margin_bottom(grid, 20);
    gtk_widget_set_margin_start(grid, 20);
    gtk_widget_set_margin_end(grid, 20);

    username_label = gtk_label_new("Username:");
    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Enter your username");
    gtk_entry_set_max_length(GTK_ENTRY(username_entry), 20);

    password_label = gtk_label_new("Password:");
    password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Enter your password");
    gtk_entry_set_max_length(GTK_ENTRY(password_entry), 20);
    gtk_entry_set_invisible_char(GTK_ENTRY(password_entry), '*');

    confirm_password_label = gtk_label_new("Confirm Password:");
    confirm_password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(confirm_password_entry), FALSE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(confirm_password_entry), "Re-enter your password");
    gtk_entry_set_max_length(GTK_ENTRY(confirm_password_entry), 20);
    gtk_entry_set_invisible_char(GTK_ENTRY(confirm_password_entry), '*');

    email_label = gtk_label_new("Email:");
    email_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(email_entry), "Enter your email");
    gtk_entry_set_max_length(GTK_ENTRY(email_entry), 50);

    category_label = gtk_label_new("Category:");
    category_combobox = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(category_combobox), "User");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(category_combobox), "Admin");
    gtk_combo_box_set_active(GTK_COMBO_BOX(category_combobox), 0);
    gtk_widget_set_size_request(category_combobox, 150, -1);
    gtk_widget_set_halign(category_combobox, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(category_combobox, GTK_ALIGN_CENTER);

    register_button = gtk_button_new_with_label("Register");
    gtk_widget_set_halign(register_button, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(register_button, GTK_ALIGN_CENTER);
    gtk_widget_set_size_request(register_button, 100, 30);
    gtk_widget_set_can_default(register_button, TRUE);
    gtk_widget_grab_default(register_button);

    status_label = gtk_label_new("");
    gtk_widget_set_halign(status_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(status_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(status_label, "status_label");

    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), confirm_password_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), confirm_password_entry, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_label, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), email_entry, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), category_label, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), category_combobox, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), register_button, 0, 5, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), status_label, 0, 6, 2, 1);

    gtk_widget_set_margin_top(username_label, 5);
    gtk_widget_set_margin_bottom(username_label, 5);
    gtk_widget_set_margin_top(username_entry, 5);
    gtk_widget_set_margin_bottom(username_entry, 5);
    gtk_widget_set_margin_top(password_label, 5);
    gtk_widget_set_margin_bottom(password_label, 5);
    gtk_widget_set_margin_top(password_entry, 5);
    gtk_widget_set_margin_bottom(password_entry, 5);
    gtk_widget_set_margin_top(confirm_password_label, 5);
    gtk_widget_set_margin_bottom(confirm_password_label, 5);
    gtk_widget_set_margin_top(confirm_password_entry, 5);
    gtk_widget_set_margin_bottom(confirm_password_entry, 5);
    gtk_widget_set_margin_top(email_label, 5);
    gtk_widget_set_margin_bottom(email_label, 5);
    gtk_widget_set_margin_top(email_entry, 5);
    gtk_widget_set_margin_bottom(email_entry, 5);
    gtk_widget_set_margin_top(category_label, 5);
    gtk_widget_set_margin_bottom(category_label, 5);
    gtk_widget_set_margin_top(category_combobox, 5);
    gtk_widget_set_margin_bottom(category_combobox, 5);
    gtk_widget_set_margin_top(register_button, 5);
    gtk_widget_set_margin_bottom(register_button, 5);

    GtkWidget **data = (GtkWidget **)malloc(sizeof(GtkWidget *) * 6);
    data[0] = username_entry;
    data[1] = password_entry;
    data[2] = confirm_password_entry;
    data[3] = email_entry;
    data[4] = category_combobox;
    data[5] = status_label;

    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_clicked), data);
    g_signal_connect(page_box, "destroy", G_CALLBACK(free_data), data);

    gtk_container_add(GTK_CONTAINER(page_box), grid);
    gtk_widget_show_all(page_box);
}