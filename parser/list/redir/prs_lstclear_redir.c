/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstclear_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:25:57 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 15:47:31 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_lstclear_redir(t_redir **lst)
{
	t_redir	*p;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		free((*lst)->file);
		free(*lst);
		*lst = p;
	}
}
