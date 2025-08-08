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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
    if(!s)
        return;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int ft_env(char **arg, t_env *env_list)
{
    t_env *tmp = env_list;

    if (arg[1])
    {
        write(2, "env: No such file or directory\n", 31);
        return (127);
    }

    while (tmp)
    {
        if (tmp->value != NULL)
        {
            ft_putstr_fd(tmp->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(tmp->value, 1);
            ft_putstr_fd("\n", 1);
        }
        tmp = tmp->next;
    }
    return (0);
}

