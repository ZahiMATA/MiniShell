/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:53:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/07 12:00:35 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_tokens(t_minishell *m)
{
	t_token_list	*l;

	l = m->token_list;
	if (DEBUG_LEX)
	{
		ft_putstr("\033[0;31mToken\033[0m");
		while (l)
		{
			printf("Token/Val[%d][%s]\n",
				l->token, l->val);
			l = l->next;
		}
		printf("Last Status=[%d]\n", m->last_status);
	}
}