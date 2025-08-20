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

char *get_env_value(char *key, t_env *env_list)
{
    while (env_list)
    {
        if (strcmp(env_list->key, key) == 0)
            return env_list->value;
        env_list = env_list->next;
    }
    return NULL;
}

void update_pwd_and_oldpwd(char *old_pwd, char *new_pwd, t_env *env_list)
{
    t_env *tmp = env_list;
    t_env *last = NULL;
    int found_pwd = 0;
    int found_oldpwd = 0;

    while (tmp)
    {
        if (strcmp(tmp->key, "OLDPWD") == 0)
        {
            free(tmp->value);
            tmp->value = strdup(old_pwd);
            found_oldpwd = 1;
        }
        else if (strcmp(tmp->key, "PWD") == 0)
        {
            free(tmp->value);
            tmp->value = strdup(new_pwd);
            found_pwd = 1;
        }
        last = tmp;
        tmp = tmp->next;
    }

    if (!found_oldpwd)
    {
        t_env *new_oldpwd = malloc(sizeof(t_env));
        new_oldpwd->key = strdup("OLDPWD");
        new_oldpwd->value = strdup(old_pwd);
        new_oldpwd->next = NULL;
        if (last)
            last->next = new_oldpwd;
        else
            env_list = new_oldpwd;
        last = new_oldpwd;
    }

    if (!found_pwd)
    {
        t_env *new_pwd_env = malloc(sizeof(t_env)); //TODO protec
        new_pwd_env->key = strdup("PWD");
        new_pwd_env->value = strdup(new_pwd);
        new_pwd_env->next = NULL;
        if (last)
            last->next = new_pwd_env;
        else
            env_list = new_pwd_env;
    }
}

int ft_cd(char **argv, t_env *env_list)
{
    char old_pwd[PATH_MAX];
    char *new_pwd;
    char    *road;

    road = NULL;
    getcwd(old_pwd, PATH_MAX); //save old pwd

    if(!argv[1])
        road = get_env_value("HOME", env_list);
    else if(argv[1][0] == '-' && argv[1][1] == '\0')
    {
        road = get_env_value("OLDPWD", env_list);
         if (!road)
        {
            write(2, "cd: OLDPWD not set\n", 20); //TODO changer les write
            return (1);
        }
        printf("%s\n", road); //TODO changer les write
    }
    else
        road = (argv[1]);
    if (!road)
    {
        write(2, "cd: target path not set\n", 25);
        return (1);
    }
    if(chdir(road) == -1) //se deplace et verifie si le cd reussi
    {
        perror("cd");
        return(1);
    }
    new_pwd = getcwd(NULL, 0); // danger
    if (!new_pwd)
        return (1);
    update_pwd_and_oldpwd(old_pwd, new_pwd, env_list);
    free(new_pwd);
    return(0);
}
/*
int main()
{

}*/
/*
     -get_env_value(nom) : récupère une variable de ton environnement (ta liste chaînée)
    -chdir() : changer de dossier courant (cd)
    -getcwd : permet de récupérer le chemin du répertoire de travail courant
*/

//TODO rajjoutter cd til