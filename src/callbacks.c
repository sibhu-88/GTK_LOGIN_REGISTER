#include "headers.h"

// login page callback
void on_login_clicked(GtkButton *button, gpointer user_data)
{
    // Handle login button click
    g_print("Login button clicked\n");
    GtkWidget **data = (GtkWidget **)user_data;
    char *username = strdup(gtk_entry_get_text(GTK_ENTRY(data[0])));
    char *password = strdup(gtk_entry_get_text(GTK_ENTRY(data[1])));
    GtkWidget *status_label = data[2];
    if (strlen(username) == 0 || strlen(password) == 0)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Username and password cannot be empty.");
        return;
    }
    int status = check_credentials(username, password);
    if (status == 1)
    {
        extern User *current_user;
        gtk_label_set_text(GTK_LABEL(status_label), "Login successful.");
        printf("Login successful.\n");
        printf("Username: %s Category: %s\n", current_user->username, current_user->category);
        // Proceed to the next page or perform further actions
    }
    else if (status == 0)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Invalid username or password.");
        printf("Invalid username or password.\n");
    }
    gtk_entry_set_text(GTK_ENTRY(data[0]), "");
    gtk_entry_set_text(GTK_ENTRY(data[1]), "");
}

// Register page callback
void on_register_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Register button clicked in register page\n");
    GtkWidget **data = (GtkWidget **)user_data;
    char *username = strdup(gtk_entry_get_text(GTK_ENTRY(data[0])));
    char *password = strdup(gtk_entry_get_text(GTK_ENTRY(data[1])));
    char *conform_password = strdup(gtk_entry_get_text(GTK_ENTRY(data[2])));
    char *email = strdup(gtk_entry_get_text(GTK_ENTRY(data[3])));
    char *category = strdup(gtk_combo_box_get_active(GTK_COMBO_BOX(data[4])) == 0 ? "User" : "Admin");
    GtkWidget *status_label = data[5];

    if (strlen(username) == 0 || strlen(password) == 0 || strlen(conform_password) == 0 || strlen(email) == 0)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "All fields are required.");
        return;
    }

    int status = check_register(username, password, conform_password, email, category);
    if (status == 0)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Registration successful.");
        printf("Registration successful.\n");
        printf("Username: %s Password: %s ConfirmPassword: %s Email: %s Category: %s\n", username, password, conform_password, email, category);
        register_file(username, password, email, category);
    }
    else if (status == 1)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Username must be more than 3 characters and less than 20 characters.");
        printf("Username must be more than 3 characters and less than 20 characters.\n");
    }
    else if (status == 2)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Password must be more than 4 characters and less than 20 characters.");
        printf("Password must be more than 4 characters and less than 20 characters.\n");
    }
    else if (status == 3)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Passwords do not match.");
        printf("Passwords do not match.\n");
    }
    else if (status == 4)
    {
        gtk_label_set_text(GTK_LABEL(status_label), "Invalid email format.");
        printf("Invalid email format.\n");
    }
    else
    {
        gtk_label_set_text(GTK_LABEL(status_label), "An unknown error occurred.");
        printf("An unknown error occurred.\n");
    }

    gtk_entry_set_text(GTK_ENTRY(data[0]), "");
    gtk_entry_set_text(GTK_ENTRY(data[1]), "");
    gtk_entry_set_text(GTK_ENTRY(data[2]), "");
    gtk_entry_set_text(GTK_ENTRY(data[3]), "");
}

int check_register(const char *username, const char *password, const char *conform_password, const char *email, const char *category)
{
    if (strcmp(password, conform_password) != 0)
    {
        return 3;
    }
    if (strlen(username) < 3 || strlen(username) > 20)
    {
        return 1;
    }
    if (strlen(password) < 4 || strlen(password) > 20)
    {
        return 2;
    }
    // Enhanced email validation
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    if (!at || !dot || at > dot || at == email || dot == email + strlen(email) - 1)
    {
        return 4;
    }
    return 0;
}