/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:10:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/19 10:53:03 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		ea_has_dollar(const char *s);
int		ea_has_any_quote(const char *s);
char	**ea_split_ifs_words(const char *s);
int		ea_inject_tokens(t_cmd *cmd, int i, char **tok);
void	ea_free_container_only(char **t);

static int	ea_try_split_inject(t_cmd *cmd, int i, char *expanded)
{
	char	**split;

	split = ea_split_ifs_words(expanded);
	if (!split)
		return (0);
	if (ea_inject_tokens(cmd, i, split))
	{
		ea_free_container_only(split);
		free(expanded);
		return (1);
	}
	ea_free_container_only(split);
	free(expanded);
	return (0);
}

static void	ea_assign_replacement(t_cmd *cmd, int i, char *neww)
{
	free(cmd->args[i]);
	cmd->args[i] = neww;
}

static int	ea_process_one(t_minishell *m, t_cmd *cmd, int i, int x)
{
	char	*orig;
	char	*neww;

	orig = cmd->args[i];
	neww = ms_expand_word(m, orig, x);
	if (!neww)
		return (1);
	if (ea_has_dollar(orig) && !ea_has_any_quote(orig))
	{
		if (ea_try_split_inject(cmd, i, neww))
			return (1);
	}
	ea_assign_replacement(cmd, i, neww);
	return (1);
}

static void	ms_expand_argv_of_cmd(t_minishell *m, t_cmd *cmd, int x)
{
	int	i;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
		if (ea_process_one(m, cmd, i, x))
			i++;
}

void	ms_expand_all_cmds(t_minishell *m)
{
	t_cmd	*cur;

	cur = m->cmds;
	while (cur)
	{
		ms_expand_argv_of_cmd(m, cur, WITH_QUOTES);
		cur = cur->next;
	}
}
