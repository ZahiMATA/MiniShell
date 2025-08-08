/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:32:59 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/08 18:27:53 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	prs_lstadd_back(t_cmd2  **lst, t_cmd2 *new_lst)
{
	t_cmd2	*p;

	if (lst == NULL || new_lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_lst;
		return ;
	}
	p = *lst;
	while (p && p -> next)
		p = p -> next;
	p -> next = new_lst;
}