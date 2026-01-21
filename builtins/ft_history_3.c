/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:45:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 14:44:09 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	history_is_meta(const char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "|") == 0)
		return (1);
	if (ft_strcmp(s, "<") == 0)
		return (1);
	if (ft_strcmp(s, ">") == 0)
		return (1);
	if (ft_strcmp(s, "<<") == 0)
		return (1);
	if (ft_strcmp(s, ">>") == 0)
		return (1);
	return (0);
}

void	history_usage(void)
{
	ft_putstr_fd("history: usage: history [-c] [-d offset] [n]\n", 2);
	ft_putstr_fd("   or: history -anrw [filename]\n", 2);
	ft_putstr_fd("   or: history -ps arg [arg...]\n", 2);
}

int	history_scan_argc(char **tok)
{
	int	i;

	i = 1;
	while (tok[i] && !history_is_meta(tok[i]))
		i++;
	return (i);
}

int	history_check_flags(t_minishell *m, char **tok, int argc, int *n)
{
	if (tok[1][0] == '-' && tok[1][1] != '\0')
	{
		ft_putstr_fd("minishell: history: ", 2);
		ft_putstr_fd(tok[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		history_usage();
		m->last_status = 2;
		return (1);
	}
	if (argc > 2)
	{
		ft_putstr_fd("minishell: history: too many arguments\n", 2);
		m->last_status = 2;
		return (1);
	}
	(void)n;
	return (0);
}
