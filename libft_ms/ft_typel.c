/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_typel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:29:42 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/07 12:59:04 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_islexer(int c)
{
	return (ft_isspace(c) || (c == '|') || (c == '<') || (c == '>')
		|| (c == '"') || (c == '\''));
}

int ft_is_not_stringword(t_minishell *m)
{
	return (m->token_list == NULL ||
		(m->token_list->token != T_STRING && m->token_list->token != T_WORD));
}