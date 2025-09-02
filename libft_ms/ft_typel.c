/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:29:42 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/02 19:40:30 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_islexer(int c)
{
	return (ft_isspace(c) || (c == '|') || (c == '<') || (c == '>')
		|| (c == '"') || (c == '\''));
}

int ft_is_stringword(t_token_list *t)
{
	return ( t->token == T_STRING || t->token == T_WORD);
}

int	ft_is_redir(t_token_list *t)
{
	return (
		t->token == T_REDIRECT_LEFT ||
		t->token == T_REDIRECT_RIGHT ||
		t->token == T_DOUBLE_REDIRECT_LEFT ||
		t->token == T_DOUBLE_REDIRECT_RIGHT
	);
}
