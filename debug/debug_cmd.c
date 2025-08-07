/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:16:14 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/07 13:03:22 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_cmds(t_minishell *m)
{
	t_cmd2	*l;

	l = m->cmds2;
	if (DEBUG_LEX)
	{
		ft_putstr("\033[0;31mCmd\033[0m");
		while (l)
		{
			printf("cmd/in/out=[%s][%s][%s]\n",
				l->file_in, l->file_out, l->cmd);
				l = l->next;
		}
	}
}
