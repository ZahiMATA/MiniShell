/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:53:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 19:06:24 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_tokens(t_minishell *m)
{
	if (DEBUG_LEX)
	{
		while (m->token_list)
		{
			printf("Token/Val[%d][%s]\n",
				m->token_list->token, m->token_list->val);
			m->token_list = m->token_list->next;
		}
	}
}