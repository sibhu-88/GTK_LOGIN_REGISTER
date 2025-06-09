#ifndef HEADERS_H
#define HEADERS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    char *category;
} User;

extern User *current_user;

void create_login_page(GtkWidget *page_box);
void create_register_page(GtkWidget *page_box);
void on_login_clicked(GtkButton *button, gpointer user_data);
void on_register_clicked(GtkButton *button, gpointer user_data);
int check_credentials(const char *username, const char *password);
int check_register(const char *username, const char *password, const char *confirm_password, const char *email, const char *category);
void register_file(char *username, char *password, char *email, char *category);

#endif