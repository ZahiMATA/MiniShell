/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:20:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 14:24:11 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int		is_valid_export_key(const char *str);
void	add_or_update_env_var(t_env **env_list, const char *key,
			const char *value);

int	handle_export_arg(char *arg, t_env **env_list)
{
	char	*eq;

	if (!is_valid_export_key(arg))
	{
		ft_printf_fd(2,
			"minishell: export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	eq = strchr(arg, '=');
	if (eq)
	{
		*eq = '\0';
		add_or_update_env_var(env_list, arg, eq + 1);
		*eq = '=';
	}
	else
		add_or_update_env_var(env_list, arg, NULL);
	return (0);
}
