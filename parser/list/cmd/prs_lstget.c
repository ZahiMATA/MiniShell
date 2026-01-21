/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstget.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:31:20 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 19:42:33 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// For example : /usr/bin/tr a A
t_cmd	*prs_lstget(t_minishell *m, int n)

{
	t_cmd	*l;
	int		i;

	l = m->cmds;
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
	t_cmd	*l;
	int		i;

	l = m->cmds;
	i = 0;
	while (l)
	{
		i++;
		l = l->next;
	}
	return (i);
}
