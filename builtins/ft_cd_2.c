/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:05:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 15:40:38 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	cd_print_err(const char *path)
{
	if (errno == ENOTDIR)
		ft_printf_fd(2, "%s: %s: %s: Not a directory\n",
			MINISHELL, "cd", path);
	else if (errno == ENOENT)
		ft_printf_fd(2, "%s: %s: %s: No such file or directory\n",
			MINISHELL, "cd", path);
	else if (errno == EACCES)
		ft_printf_fd(2, "%s: %s: %s: Permission denied\n",
			MINISHELL, "cd", path);
	else
		ft_printf_fd(2, "%s: %s: %s: %s\n",
			MINISHELL, "cd", path, strerror(errno));
	return (1);
}

int	cd_get_road_home(t_minishell *m, char **road)
{
	*road = get_env_value("HOME", m->env_list);
	if (!*road)
	{
		ft_printf_fd(2, "cd: HOME not set\n");
		return (1);
	}
	*road = ft_strdup(*road);
	if (!*road)
		return (1);
	return (0);
}

int	cd_get_road_tilde(t_minishell *m, t_cmd *cmd, char **road)
{
	*road = expand_tilde(cmd->args[1], m->env_list);
	if (!*road)
	{
		ft_printf_fd(2, "cd: HOME not set\n");
		return (1);
	}
	return (0);
}

int	cd_get_road_oldpwd(t_minishell *m, char **road)
{
	*road = get_env_value("OLDPWD", m->env_list);
	if (!*road)
	{
		ft_printf_fd(2, "cd: OLDPWD not set\n");
		return (1);
	}
	ft_printf_fd(1, "%s\n", *road);
	*road = ft_strdup(*road);
	if (!*road)
		return (1);
	return (0);
}

int	cd_apply_chdir_update(char *road, char old_pwd[],
	t_env **penv)
{
	char	*new_pwd;

	if (chdir(road) == -1)
	{
		(void)cd_print_err(road);
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
