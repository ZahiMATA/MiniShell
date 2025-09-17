/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:09:44 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int	ft_is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	exit_maybe_print(void)
{
	if (!DEBUG_TEST)
		ft_printf_fd(STDERR_FILENO, "exit\n");
}

int	ft_exit(t_minishell *m, t_cmd *cmd)
{
	long long	ll;

	ll = 0;
	if (!cmd || !cmd->args || !cmd->args[1])
	{
		exit_maybe_print();
		mem_free_all(m);
		exit((unsigned char)m->last_status);
	}
	if (cmd->args[2])
	{
		ft_printf_fd(STDERR_FILENO, "%s: exit: too many arguments\n", MINISHELL);
		return (1);
	}
	if (!ft_is_numeric(cmd->args[1]) || atoll_overflow(cmd->args[1], &ll))
	{
		ft_printf_fd(STDERR_FILENO, "%s: exit: %s: numeric argument required\n",
			MINISHELL, cmd->args[1]);
		exit_maybe_print();
		mem_free_all(m);
		exit(2);
	}
	exit_maybe_print();
	mem_free_all(m);
	exit((int)(unsigned char)ll);
}
