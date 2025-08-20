#include "minishell.h"
#include <limits.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
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
}*/
/*
    -path_max : C’est une constante définie par le système, qui indique la longueur maximale autorisée pour un chemin absolu (genre /home/zahi/monprojet/minishell).

    -diff perror , sterror :
            perror() = message avec un préfixe automatique
            strerror(errno) = message sans préfixe, que tu dois afficher toi-même

    -getpwd : permet de récupérer le chemin du répertoire de travail courant
*/
int ft_pwd(void)
{
    char    len_max_repertoire[PATH_MAX];
    char *p_rep;

    p_rep = getcwd(len_max_repertoire, PATH_MAX);
    if(p_rep == NULL)
    {
        perror("pwd"); //TODO verifier
        return(1);
    }
    else
        ft_putstr_fd(p_rep, 1);
    write(1, "\n", 1);
    return(0);
}
/*
int main(void)
{
    ft_pwd();
}*/
