/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:33:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/02 10:42:17 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char *key, t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->val);
		env_list = env_list->next;
	}
	return (NULL);
}

static void	set_env_kv(t_env **lst, const char *key, const char *val)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->val);
			tmp->val = (val) ? ft_strdup(val) : NULL;
			return ;
		}
		tmp = tmp->next;
	}
	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return ;
	tmp->key = ft_strdup(key);
	tmp->val = (val) ? ft_strdup(val) : NULL;
	if (!tmp->key || (val && !tmp->val))
	{
		free(tmp->key);
		free(tmp->val);
		free(tmp);
		return ;
	}
	tmp->next = *lst;
	*lst = tmp;
}

static char	*expand_tilde(char *arg, t_env *env_list)
{
	char	*home;
	char	*rest;
	char	*joined;

	if (!arg)
		return (NULL);
	if (arg[0] != '~')
		return (ft_strdup(arg));
	home = get_env_value("HOME", env_list);
	if (!home)
		return (NULL);
	if (arg[1] == '\0')
		return (ft_strdup(home));
	rest = ft_strdup(arg + 1);
	if (!rest)
		return (NULL);
	joined = ft_strjoin(home, rest);
	free(rest);
	return (joined);
}

static void	update_pwd_and_oldpwd(char *old_pwd, char *new_pwd, t_env **env_list)
{
	set_env_kv(env_list, "OLDPWD", old_pwd);
	set_env_kv(env_list, "PWD", new_pwd);
}


int	ft_cd(t_minishell *m, t_cmd *cmd)
{
	char		old_pwd[PATH_MAX];
	char		*new_pwd;
	char		*road;
	t_env		**penv;

	(void)m;
	penv =  &m->env_list;
	if (!getcwd(old_pwd, PATH_MAX))
		return (1);
	road = NULL;
	if (!cmd->args[1])
	{
		road = get_env_value("HOME", m->env_list);
		if (!road)
			return (ft_printf_fd(2, "cd: HOME not set\n"), 1);
		road = ft_strdup(road);
	}
	else if (cmd->args[1][0] == '~')
	{
		road = expand_tilde(cmd->args[1], m->env_list);
		if (!road)
			return (ft_printf_fd(2, "cd: HOME not set\n"), 1);
	}
	else if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
	{
		road = get_env_value("OLDPWD", m->env_list);
		if (!road)
			return (ft_printf_fd(2, "cd: OLDPWD not set\n"), 1);
		ft_printf_fd(1, "%s\n", road);
		road = ft_strdup(road);
	}
	else
		road = ft_strdup(cmd->args[1]);
	if (!road)
		return (ft_printf_fd(2, "cd: target path not set\n"), 1);
	if (chdir(road) == -1)
	{
		ft_printf_fd(2, "%s: %s: %s: %s\n", MINISHELL, "cd", road, ERROR_NOSUCH);
		free(road);
		return (1);
	}
	free(road);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	update_pwd_and_oldpwd(old_pwd, new_pwd, penv);
	free(new_pwd);
	return (0);
}

