/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:33:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 13:33:47 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	args_count(char **av)
{
	int	i;

	i = 0;
	while (av && av[i])
		i++;
	return (i);
}

static int	cd_get_road(t_minishell *m, t_cmd *cmd, char **road)
{
	if (cmd->args[1] == NULL)
		return (cd_get_road_home(m, road));
	if (cmd->args[1][0] == '~')
		return (cd_get_road_tilde(m, cmd, road));
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
		return (cd_get_road_oldpwd(m, road));
	*road = ft_strdup(cmd->args[1]);
	if (!*road)
		return (1);
	return (0);
}

int	ft_cd(t_minishell *m, t_cmd *cmd)
{
	char	old_pwd[PATH_MAX];
	char	*road;
	t_env	**penv;
	int		ac;

	penv = &m->env_list;
	ac = args_count(cmd->args);
	if (ac > 2)
	{
		ft_printf_fd(2, "%s: %s: too many arguments\n", MINISHELL, "cd");
		return (1);
	}
	if (!getcwd(old_pwd, PATH_MAX))
		return (1);
	road = NULL;
	if (cd_get_road(m, cmd, &road))
		return (1);
	if (!road)
	{
		ft_printf_fd(2, "cd: target path not set\n");
		return (1);
	}
	return (cd_apply_chdir_update(road, old_pwd, penv));
}
