#include "headers.h"

void register_file(char *username, char *password, char *email, char *category)
{
    FILE *fd = fopen("resources/usercredential.xls", "a");
    if (fd == NULL)
    {
        perror("Error opening file");
        return;
    }
    fprintf(fd, "%s\t%s\t%s\t%s\n", username, password, email, category);
    fclose(fd);
}

int check_credentials(const char *username, const char *password)
{
    FILE *fd = fopen("resources/usercredential.xls", "r");
    if (fd == NULL)
    {
        perror("Error opening file");
        return -1;
    }
    char line[256];
    while (fgets(line, sizeof(line), fd))
    {
        char *file_username = strtok(line, "\t");
        if (!file_username)
            continue;
        char *file_password = strtok(NULL, "\t");
        if (!file_password)
            continue;
        char *file_email = strtok(NULL, "\t");
        if (!file_email)
            continue;
        char *file_category = strtok(NULL, "\t");
        if (!file_category)
            continue;

        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
        {
            extern User *current_user;
            current_user = (User *)malloc(sizeof(User));
            current_user->username = strdup(file_username);
            current_user->category = strdup(file_category);
            fclose(fd);
            return 1;
        }
    }
    fclose(fd);
    return 0;
}