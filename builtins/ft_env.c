/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 12:15:18 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
typedef struct s_env { //TODO supp
    char *key;
    char *value;
    struct s_env *next;
} t_env;*/
/*
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if(!s)
		return;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}*/

int	ft_env(t_minishell *m, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = m->env_list;
	if (cmd->args[1])
	{
		write(2, "env: No such file or directory\n", 31);
		return (127);
	}
	while (tmp)
	{
		if (tmp->val != NULL)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->val, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}
