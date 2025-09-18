/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:25:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/18 11:20:20 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_exp
{
	t_minishell	*m;
	const char	*s;
	int			x;
	int			i;
	int			in_s;
	int			in_d;
	char		*out;
}	t_exp;

char	*ms_expand_word(t_minishell *m, const char *s, int x)
{
	t_exp	e;
	int		h;

	e.m = m;
	e.s = s;
	e.x = x;
	e.i = 0;
	e.in_s = 0;
	e.in_d = 0;
	e.out = ft_strdup("");
	if (!s || !e.out)
		return (NULL);
	while (s[e.i])
	{
		h = 0;
		if (!h && ew_handle_backslash(&e))
			h = 1;
		if (!h && ew_handle_quote_toggles(&e))
			h = 1;
		if (!h && ew_handle_dollar(&e))
			h = 1;
		if (!h)
			e.out = ew_append_char(e.out, s[e.i++]);
	}
	return (e.out);
}
