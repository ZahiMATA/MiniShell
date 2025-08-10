/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:25:52 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 15:56:52 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*prs_lstnew_redir(t_redir redir)
{
	t_redir	*list;

	list = ft_calloc(1, sizeof(t_redir));
	if (list == NULL)
		return (NULL);
	list->type = redir.type;
	if (redir.file)
	{
		list->file = ft_strdup(redir.file);
		if (list->file == NULL)
			return (free(list), NULL);
	}
	list-> next = NULL;
	return (list);
}
