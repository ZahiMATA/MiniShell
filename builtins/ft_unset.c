/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:55:46 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <stdlib.h>

static void	remove_env_var(t_env **env_list, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env_list;
	prev = NULL;
	while (cur)
	{
		if (strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env_list = cur->next;
			free(cur->key);
			free(cur->val);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static int	is_valid_identifier(const char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!(s[0] == '_' || (s[0] >= 'A' && s[0] <= 'Z')
			|| (s[0] >= 'a' && s[0] <= 'z')))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(s[i] == '_' || (s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(char **arg, t_env **env_list)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (arg[i])
	{
		if (is_valid_identifier(arg[i]))
			remove_env_var(env_list, arg[i]);
		else
		{
			ft_printf_fd(2, "unset: `%s': not a valid identifier\n", arg[i]);
			error = 1;
		}
		i++;
	}
	return (error);
}
