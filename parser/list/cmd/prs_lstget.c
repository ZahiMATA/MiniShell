/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:31:20 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 15:43:26 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For example : /usr/bin/tr a A
t_cmd2	*prs_lstget(t_minishell *m, int n)

{
	t_cmd2	*l;
	int		i;

	l = m->cmds2;
	i = 0;
	while (l && i < n)
	{
		i++;
		l = l->next;
	}
	return (l);
}

int	prs_lstget_nb(t_minishell *m)

{
	t_cmd2	*l;
	int		i;

	l = m->cmds2;
	i = 0;
	while (l)
	{
		i++;
		l = l->next;
	}
	return (i);
}
