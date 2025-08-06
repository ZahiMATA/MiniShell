/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:53:46 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 17:57:18 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	lex_lstclear(t_token_list **lst)
{
	t_token_list	*p;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		free((*lst)->val);
		free(*lst);
		*lst = p;
	}
	*lst = NULL;
}
