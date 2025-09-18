/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:10:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/18 10:38:57 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, (char *)key) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
