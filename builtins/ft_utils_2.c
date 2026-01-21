/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:47:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 15:00:14 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*dup_or_null(const char *val)
{
	if (val)
		return (ft_strdup(val));
	return (NULL);
}

int	env_insert_front(t_env **lst, const char *key, const char *val)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	if (!tmp)
		return (1);
	tmp->key = ft_strdup(key);
	tmp->val = dup_or_null(val);
	if (!tmp->key || (val && !tmp->val))
	{
		free(tmp->key);
		free(tmp->val);
		free(tmp);
		return (1);
	}
	tmp->next = *lst;
	*lst = tmp;
	return (0);
}
