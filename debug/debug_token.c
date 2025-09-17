/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:53:47 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:41:53 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_tokens(t_minishell *m)
{
	t_token_list	*l;

	l = m->token_list;
	if (DEBUG_LEX)
	{
		ft_putstr_nl("\033[0;31mToken\033[0m");
		while (l)
		{
			printf("Token/Val[%d][%s]\n",
				l->token, l->val);
			l = l->next;
		}
		printf("Last Status=[%d]\n", m->last_status);
	}
}

void	debug_serial_token(t_minishell *m, char *buffer, size_t size)
{
	t_token_list	*l;
	char			*n;

	buffer[0] = '\0';
	l = m->token_list;
	while (l)
	{
		ft_strlcat(buffer, "[", size);
		n = ft_itoa(l->token);
		if (n == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		ft_strlcat(buffer, n, size);
		ft_strlcat(buffer, "][", size);
		ft_strlcat(buffer, l->val, size);
		ft_strlcat(buffer, "]", size);
		free(n);
		l = l-> next;
	}
	ft_strlcat(buffer, "\n", size);
}
