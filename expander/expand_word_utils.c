/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:15:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/18 11:08:29 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ew_is_name_start(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

int	ew_is_name_char(char c)
{
	return (ew_is_name_start(c) || (c >= '0' && c <= '9'));
}

char	*ew_append_char(char *dst, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = dst;
	dst = ft_strjoin(dst, buf);
	free(tmp);
	return (dst);
}

char	*ew_append_str(char *dst, const char *s)
{
	char	*tmp;

	if (!s)
		return (dst);
	tmp = dst;
	dst = ft_strjoin(dst, (char *)s);
	free(tmp);
	return (dst);
}
