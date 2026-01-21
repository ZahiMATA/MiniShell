/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:53:46 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/03 14:54:37 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_lstclear(t_cmd **lst)
{
	t_cmd	*p;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		mem_free_array(&(*lst)->args, "prs_lstclear");
		free((*lst)->cmd_abs);
		prs_lstclear_redir(&(*lst)->redirs);
		mem_free(*lst, "prs_lstclear", NULL);
		*lst = p;
	}
}
