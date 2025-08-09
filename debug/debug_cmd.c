/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:16:14 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/09 15:22:16 by ybouroga         ###   ########.fr       */
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
			printf("cmd/in/out/mode=[%s][%s][%s][%d][%d]\n",
				l->cmd, l->file_in, l->file_out, l->mode_in, l->mode_out);
				l = l->next;
		}
	}
}

