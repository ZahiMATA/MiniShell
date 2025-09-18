/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/18 11:31:56 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

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

static void	echo_put_arg(t_minishell *m, char *s)
{
	char	*home;

	if (s && s[0] == '~')
	{
		home = get_env_value("HOME", m->env_list);
		if (home)
		{
			if (s[1] == '\0')
				return ((void)ft_putstr_fd(home, 1));
			if (s[1] == '/')
			{
				ft_putstr_fd(home, 1);
				return ((void)ft_putstr_fd(s + 1, 1));
			}
		}
	}
	ft_putstr_fd(s, 1);
}

static int	echo_skip_opts(t_cmd *cmd, int *no_nl)
{
	int	i;

	*no_nl = 0;
	i = 1;
	while (cmd->args[i] && verif_arg(cmd->args[i]) == 0)
	{
		*no_nl = 1;
		i++;
	}
	return (i);
}

int	ft_echo(t_minishell *m, t_cmd *cmd)
{
	int	no_nl;
	int	i;

	i = echo_skip_opts(cmd, &no_nl);
	while (cmd->args[i])
	{
		echo_put_arg(m, cmd->args[i]);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_nl)
		write(1, "\n", 1);
	return (0);
}
