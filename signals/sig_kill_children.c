/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_kill_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:57:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/27 12:09:51 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_kill_children(t_minishell *m)
{
	t_cmd	*c;

	if (g_signal)
	{
		g_signal = 0;
		if (m && m->cmds)
		{
			c = m->cmds;
			while (c)
			{
				if (c->pid > 0)
					kill(c->pid, SIGINT);
				c = c->next;
			}
		}
		return GOT_SIGNAL;
	}
	return GOT_NO_SIGNAL;
}
