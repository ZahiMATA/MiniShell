/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:53:46 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 15:41:46 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prs_lstclear(t_cmd2 **lst)
{
	t_cmd2	*p;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		p = (*lst)->next;
		free((*lst)->cmd);
		free((*lst)->cmd_abs);
		free((*lst)->file_in);
		free((*lst)->file_out);
		free(*lst);
		*lst = p;
	}
}
