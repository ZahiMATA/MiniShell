/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:25:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 15:00:05 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*get_env_value(char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->val);
		env_list = env_list->next;
	}
	return (NULL);
}

static char	*join_home_rest(const char *home, const char *rest)
{
	char	*tmp;
	char	*joined;

	tmp = ft_strdup(rest);
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(home, tmp);
	free(tmp);
	return (joined);
}

void	set_env_kv(t_env **lst, const char *key, const char *val)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->val);
			tmp->val = dup_or_null(val);
			return ;
		}
		tmp = tmp->next;
	}
	(void)env_insert_front(lst, key, val);
}

char	*expand_tilde(char *arg, t_env *env_list)
{
	char	*home;

	if (!arg)
		return (NULL);
	if (arg[0] != '~')
		return (ft_strdup(arg));
	home = get_env_value("HOME", env_list);
	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		return (ft_strdup(home));
	return (join_home_rest(home, arg + 1));
}

void	update_pwd_and_oldpwd(char *old_pwd, char *new_pwd, t_env **env_list)
{
	set_env_kv(env_list, "OLDPWD", old_pwd);
	set_env_kv(env_list, "PWD", new_pwd);
}
