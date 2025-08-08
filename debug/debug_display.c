/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:16:20 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/08 10:58:31 by ybouroga         ###   ########.fr       */
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

void	debug_show_processes(t_minishell *m, char *message)
{
	t_cmd2	*l;
	int		i;

	if (DEBUG)
	{
		// ft_putstr(message);
		// ft_putstr_fd("PID0=", STDOUT_FILENO);
		// ft_putnbr_fd(m->cmds[0].pid, STDOUT_FILENO);
		// ft_putstr(":END-PID0");
		// ft_putstr_fd("PID1=", STDOUT_FILENO);
		// ft_putnbr_fd(m->cmds[1].pid, STDOUT_FILENO);
		// ft_putstr(":END-PID1");
		// ft_putstr(":CMD=");
		// ft_putstr(cmd);
		// ft_putstr(":END-CMD");
		// ft_putstr(":#=");
		// ft_putnbr_fd(i, STDOUT_FILENO);
		// ft_putstr(":END-#");

		l = m->cmds2;
		ft_putstr(message);
		i = 0;
		while (l)
		{
			printf("{PID%d=[%d], CMD=[%s]}", i, l->pid, l->cmd);
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
