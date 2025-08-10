/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:41:06 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 15:46:58 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

static void	ft_free(t_cmd2 *list)
{
	if (list->cmd)
		free(list->cmd);
	if (list->file_in)
		free(list->file_in);
	if (list->file_out)
		free(list->file_out);
	free(list);
}

t_cmd2	*prs_lstnew(t_cmd2 cmd)
{
	t_cmd2	*list;

	list = ft_calloc(1, sizeof(t_cmd2));
	if (list == NULL)
		return (NULL);
	if (cmd.cmd)
	{
		list->cmd = ft_strdup(cmd.cmd);
		if (list->cmd == NULL)
			return (ft_free(list), NULL);
	}
	if (cmd.file_in)
	{
		list->file_in = ft_strdup(cmd.file_in);
		if (list->file_in == NULL)
			return (ft_free(list), NULL);
	}
	if (cmd.file_out)
	{
		list->file_out = ft_strdup(cmd.file_out);
		if (list->file_out == NULL)
			return (ft_free(list), NULL);
	}
	list->mode_in = cmd.mode_in;
	list->mode_out = cmd.mode_out;
	list-> next = NULL;
	return (list);
}
