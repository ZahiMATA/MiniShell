/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:16:20 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/04 16:15:38 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_args(t_minishell *m)
{
	int	i;

	if (DEBUG)
	{
		i = 0;
		while (m->cmds[i].args)
		{
			ft_putstr(m->cmds[i].path);
			ft_print_array(m->cmds[i].args);
			i++;
		}
	}
}

void	debug_show_processes(t_minishell *m, char *message, char *cmd, int i)
{
	if (DEBUG)
	{
		ft_putstr(message);
		ft_putstr_fd("PID0=", STDOUT_FILENO);
		ft_putnbr_fd(m->cmds[0].pid, STDOUT_FILENO);
		ft_putstr(":END-PID0");
		ft_putstr_fd("PID1=", STDOUT_FILENO);
		ft_putnbr_fd(m->cmds[1].pid, STDOUT_FILENO);
		ft_putstr(":END-PID1");
		ft_putstr(":CMD=");
		ft_putstr(cmd);
		ft_putstr(":END-CMD");
		ft_putstr(":#=");
		ft_putnbr_fd(i, STDOUT_FILENO);
		ft_putstr(":END-#");
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
