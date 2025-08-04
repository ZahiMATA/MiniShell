/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:37:41 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/04 19:37:07 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_string(char *key, char *val)
{
	char	*s;
	if (key == NULL || val == NULL)
		return (NULL);
	s = ft_strjoin_with_char(key, '=', val);
	return (s);
}

int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

char	**env_list_to_tab(t_minishell *m, t_env *env)
{
	char	**env_tab;
	int		i;
	int		n;

	n = env_size(env);
	env_tab = malloc(sizeof(char *) * (n + 1));
	if (env_tab == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	i = 0;
	while (i < n)
	{
		env_tab[i] = get_env_string(env->key, env->val);
		if (env_tab[i] == NULL)
		{
			while (i > 0)
				free(env_tab[--i]);
			free(env_tab);
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		}
		env = env->next;
		i++;
	}
	env_tab[i] = NULL;
	return env_tab;
}
