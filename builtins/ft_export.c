/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/18 16:37:31 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	is_valid_export_key(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!((str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z')
			|| str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

t_env	*find_env_var(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	add_or_update_env_var(t_env **env_list, const char *key
	, const char *value)
{
	t_env	*var;
	t_env	*new_node;

	var = find_env_var(*env_list, key);
	if (var)
	{
		free(var->val);
		if (value)
			var->val = strdup(value);
		else
			var->val = NULL;
	}
	else
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		new_node->key = strdup(key);
		if (value)
			new_node->val = strdup(value);
		else
			new_node->val = NULL;
		new_node->next = *env_list;
		*env_list = new_node;
	}
}

void	print_export_env(t_env *env_list)
{
	while (env_list)
	{
		ft_putstr("declare -x ");
		ft_putstr(env_list->key);
		ft_putstr("=\"");
		if (env_list->val)
			ft_putstr(env_list->val);
		ft_putstr("\"");
		ft_putstr("\n");
		env_list = env_list->next;
	}
}

int	ft_export(char **args, t_env **env_list)
{
	int		i;
	int		had_error;

	i = 1;
	had_error = 0;
	if (!args[1])
	{
		print_export_env(*env_list);
		return (0);
	}
	while (args[i])
	{
		had_error |= handle_export_arg(args[i], env_list);
		i++;
	}
	return (had_error);
}
