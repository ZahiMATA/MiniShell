/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 12:13:41 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int	verif_arg(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (1);
	i = 1;
	if (arg[i] == '\0')
		return (1);
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (0);
	return (1);
}

int	ft_echo(t_minishell *m, t_cmd *cmd)
{
	int	yes_backslash_n;
	int	i;

	(void)m;
	i = 1;
	yes_backslash_n = 0;
	while (cmd->args[i] && verif_arg(cmd->args[i]) == 0)
	{
		yes_backslash_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (yes_backslash_n == 0)
		write(1, "\n", 1);
	return (0);
}
