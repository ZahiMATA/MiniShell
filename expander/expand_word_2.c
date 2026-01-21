/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:00:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/18 10:58:52 by zmata            ###   ########.fr       */
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

int	ew_handle_backslash(void *ctx)
{
	t_exp	*e;

	e = (t_exp *)ctx;
	if (!(e->s[e->i] == '\\' && e->x))
		return (0);
	if (!e->in_s && e->s[e->i + 1])
	{
		if (e->in_d && (e->s[e->i + 1] == '$'
				|| (e->s[e->i + 1] == '\"' && e->x)
				|| (e->s[e->i + 1] == '\\' && e->x)
				|| e->s[e->i + 1] == '`'))
			return (e->out = ew_append_char(e->out, e->s[e->i + 1]),
				e->i += 2, 1);
		if (!e->in_d)
			return (e->out = ew_append_char(e->out, e->s[e->i + 1]),
				e->i += 2, 1);
	}
	e->out = ew_append_char(e->out, e->s[e->i]);
	e->i += 1;
	return (1);
}

int	ew_handle_quote_toggles(void *ctx)
{
	t_exp	*e;

	e = (t_exp *)ctx;
	if (e->s[e->i] == '$' && (e->s[e->i + 1] == '\"' && e->x)
		&& !e->in_s && !e->in_d)
		return (e->in_d = 1, e->i += 2, 1);
	if (e->s[e->i] == '$' && (e->s[e->i + 1] == '\"' && e->x)
		&& !e->in_s && e->in_d)
		return (e->out = ew_append_char(e->out, '$'), e->i += 1, 1);
	if (e->s[e->i] == '$' && (e->s[e->i + 1] == '\'' && e->x)
		&& !e->in_s && !e->in_d)
		return (e->in_s = 1, e->i += 2, 1);
	if ((e->s[e->i] == '\'' && e->x) && !e->in_d)
		return (e->in_s = !e->in_s, e->i += 1, 1);
	if ((e->s[e->i] == '\"' && e->x) && !e->in_s)
		return (e->in_d = !e->in_d, e->i += 1, 1);
	return (0);
}
