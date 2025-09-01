/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_getcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:44:16 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/01 18:20:37 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tr a A -> tr
char	*prs_getcmd(t_minishell *m, char *s)
{
	char	**split;
	char	*ret;

	if (s == NULL)
		return (NULL);
	split = ft_split(s, ' ');
	if (split == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	if (split[0])
	{
		ret = ft_strdup(split[0]);
		if (ret == NULL)
		{
			mem_free_array(&split, "prs_getcmd.split");
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		}
	}
	else
		ret = NULL;
	mem_free_array(&split, "prs_getcmd.split");
	return ret;
}

// [tr] [a] [A] -> tr
char	*prs_getcmd_from_args(t_minishell *m, char **args)
{
	(void)m;
	if (args == NULL /*|| args[0] == NULL*/)
		return (NULL);
	return (args[0]);
}
