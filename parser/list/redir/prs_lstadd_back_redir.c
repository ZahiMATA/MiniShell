/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstadd_back_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:26:00 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 18:56:42 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_lstadd_back_redir(t_redir **lst, t_redir *new_lst)
{
	t_redir	*p;

	if (lst == NULL || new_lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_lst;
		return ;
	}
	p = *lst;
	while (p && p -> next)
		p = p->next;
	p->next = new_lst;
}
