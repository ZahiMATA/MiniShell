#include <limits.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


typedef struct s_env { //TODO supp
    char *key;
    char *value;
    struct s_env *next;
} t_env;

void remove_env_var(t_env **env_list, const char *key)
{
    t_env *current = *env_list;
    t_env *prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env_list = current->next;

            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int is_valid_identifier(const char *str)
{
    if (!str || !str[0])
        return (0);
    if (!(str[0] == '_' || (str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')))
        return (0);
    for (int i = 1; str[i]; i++)
    {
        if (!(str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')))
            return (0);
    }
    return (1);
}

int ft_unset(char **arg, t_env **env_list)
{
    int i = 1;
    int error = 0;

    while (arg[i])
    {
        if (is_valid_identifier(arg[i]))
            remove_env_var(env_list, arg[i]);
        else
        {
            dprintf(2, "unset: `%s': not a valid identifier\n", arg[i]);
            error = 1;
        }
        i++;
    }
    return (error);
}

