/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:16:20 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 18:52:12 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_list(void *s1, void *s2)
{
	if (DEBUG)
		printf("Env.key=%s val=%s\n", (char *) s1, (char *) s2);
}
/*
void	debug_show_args(t_minishell *m)
{
	int	i;

	if (DEBUG)
	{
		ft_putstr("DEBUG:");
		ft_putstr("CMDS:");
		i = 0;
		while (m->cmds && m->cmds[i].args)
		{
			printf("cmd%d=%s\n", i, m->cmds[i].path);
			ft_print_array(m->cmds[i].args);
			i++;
		}
		ft_lstiter_env(m->env_list, ft_print_list);
	}
}*/

static char	*debug_get_args(char **tab)
{
	char	*buffer;
	int		i;

	buffer = malloc(BUFFER_LOG);
	if (buffer == NULL)
		return NULL;
	buffer[0] = '\0';
	i = 0;
	while (tab && tab[i])
	{
		ft_strlcat(buffer, tab[i++], BUFFER_LOG);
		ft_strlcat(buffer, " ", BUFFER_LOG);
	}
	return buffer;
}

void	debug_show_processes(t_minishell *m, char *message)
{
	t_cmd	*l;
	int		i;
	char	*args;

	if (DEBUG)
	{
		l = m->cmds;
		ft_putstr(message);
		i = 0;
		while (l)
		{
			args = debug_get_args(l->args);
			if (args == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
			printf("{PID%d=[%d], CMD=[%s]}", i, l->pid, args);
			free(args);
			i++;
			l = l->next;
		}
	}
}

void	debug_show_error(char *message)
{
	if (DEBUG)
	{
		perror("debug");
		ft_putstr(message);
	}
}
