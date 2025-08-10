/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:29:42 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 14:20:57 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_islexer(int c)
{
	return (ft_isspace(c) || (c == '|') || (c == '<') || (c == '>')
		|| (c == '"') || (c == '\''));
}

int ft_is_stringword(t_minishell *m)
{
	return ( m->token_list->token == T_STRING || m->token_list->token == T_WORD);
}

int	ft_is_redir(t_minishell *m)
{
	return (
		m->token_list->token == T_REDIRECT_LEFT ||
		m->token_list->token == T_REDIRECT_RIGHT ||
		m->token_list->token == T_DOUBLE_REDIRECT_LEFT ||
		m->token_list->token == T_DOUBLE_REDIRECT_RIGHT
	);
}
