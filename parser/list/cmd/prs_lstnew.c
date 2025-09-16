/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:41:06 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/16 14:18:16 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

/*static void	ft_free(t_cmd2 *list)
{
	if (list->cmd)
		free(list->cmd);
	if (list->file_in)
		free(list->file_in);
	if (list->file_out)
		free(list->file_out);
	free(list);
}*/

t_cmd	*prs_lstnew(t_cmd cmd)
{
	t_cmd	*list;

	list = ft_calloc(1, sizeof(t_cmd));
	if (list == NULL)
		return (NULL);
	if (cmd.args)
		list->args = cmd.args;
	list->n = cmd.n;
	list->redirs = cmd.redirs;
	list->fd_in = -1;
	list->fd_out = -1;
	list-> next = NULL;
	return (list);
}

