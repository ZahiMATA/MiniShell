/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:16:14 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 21:08:42 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_cmds(t_minishell *m)
{
	t_cmd	*l;

	l = m->cmds;

	if (DEBUG_LEX)
	{
		ft_putstr("\033[0;31mCmd[]\033[0m");
		while (l)
		{
			printf("cmd=[%s]\n",
				l->cmd_abs);
				l = l->next;
		}
	}
}

// TODO
void	debug_serial_parser(t_minishell *m, char *buffer, size_t size)
{
	(void)m;
	(void)buffer;
	(void)size;
}