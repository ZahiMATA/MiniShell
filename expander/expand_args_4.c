/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:40:20 by zmata             #+#    #+#             */
/*   Updated: 2025/09/17 16:37:08 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	ea_count(char **v)
{
	int	n;

	n = 0;
	while (v[n])
		n++;
	return (n);
}

static void	ea_copy_before(char **dst, char **src, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		dst[j] = src[j];
		j++;
	}
}

static void	ea_insert(char **dst, char **tok, int pos)
{
	int	k;

	k = 0;
	while (tok[k])
	{
		dst[pos + k] = tok[k];
		k++;
	}
}

int	ea_inject_tokens(t_cmd *cmd, int i, char **tok)
{
	char	**newv;
	int		argc;
	int		tk;
	int		out;
	int		k;

	argc = ea_count(cmd->args);
	tk = ea_count(tok);
	newv = (char **)malloc(sizeof(char *) * (argc - 1 + tk + 1));
	if (!newv)
		return (0);
	ea_copy_before(newv, cmd->args, i);
	ea_insert(newv, tok, i);
	out = i + tk;
	k = i + 1;
	while (k < argc)
		newv[out++] = cmd->args[k++];
	newv[out] = NULL;
	free(cmd->args[i]);
	free(cmd->args);
	cmd->args = newv;
	return (1);
}
