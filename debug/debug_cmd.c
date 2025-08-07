/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:16:14 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/07 11:29:11 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_cmds(t_minishell *m)
{
	if (DEBUG_LEX){
		ft_putstr("\033[0;31mCmd\033[0m");
		while (m->cmds2)
		{
			printf("cmd/in/out=[%s][%s][%s]",
				m->cmds2->file_in,m->cmds2->file_out, m->cmds2->cmd);
		}
	}
}