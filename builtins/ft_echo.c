#include "minishell.h"
#include <limits.h>
# include <stdio.h>
# include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h> //TODO supp include
// TODO FAIRE lexpand ???
/*
void	ft_putstr_fd(char *s, int fd) //TODO supp
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
*/
int verif_arg(char *argv)
{
	int i;

	i = 0;

	if(argv[i] == '-')
		i++;
	while(argv[i] == 'n')
		i++;
	if(argv[i] == '\0')
		return(0); //-n
	else
		return(1); // pas de -n
}
int ft_echo(t_minishell *m, char **argv)
{
	int yes_backslash_n;
	int i;

	i = 1;
	yes_backslash_n = 0;

	while(argv[i])
	{
		if(verif_arg(argv[i]) == 0)
		{
			yes_backslash_n = 1;
			i++;
		}
		else
			break;
	}
	while(argv[i])
	{
		if (ft_strcmp(argv[i], "$?") == 0)
		{
			ft_printf_fd(1, "%d", m->last_status);
		}
		else
			ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (yes_backslash_n == 1)
		return(0);
	write(1, "\n", 1);
	m->last_status = 0; // TODO a vour ou le placer de facon generale
	return(0);
}
/*
int main(void)
{
    // Cas 1 : echo seul
    char *test1[] = {"echo", NULL};
    ft_echo(test1);

    // Cas 2 : echo bonjour
    char *test2[] = {"echo", "bonjour", NULL};
    ft_echo(test2);

    // Cas 3 : echo -n bonjour
    char *test3[] = {"echo", "-n", "bonjour", NULL};
    ft_echo(test3);

    // Cas 4 : echo -nnn bonjour
    char *test4[] = {"echo", "-nnn", "bonjour", NULL};
    ft_echo(test4);

    // Cas 5 : echo -n -n -n hello
    char *test5[] = {"echo", "-n", "-n", "-n", "hello", NULL};
    ft_echo(test5);

    // Cas 6 : echo -n -p test
    char *test6[] = {"echo", "-n", "-p", "test", NULL};
    ft_echo(test6);

    return 0;
}*/
