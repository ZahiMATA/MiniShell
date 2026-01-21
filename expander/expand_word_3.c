/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:20:00 by zmata             #+#    #+#             */
/*   Updated: 2025/09/18 10:58:43 by zmata            ###   ########.fr       */
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

static int	handle_dollar_core(t_exp *e)
{
	int		j;
	char	*name;
	char	*val;

	if (e->s[e->i + 1] == '0')
		return (e->out = ew_append_str(e->out, MINISHELL), e->i += 2, 1);
	if (ew_is_name_start(e->s[e->i + 1]))
	{
		j = e->i + 1;
		while (ew_is_name_char(e->s[j]))
			j++;
		name = ft_substring(e->s, e->i + 1, j - (e->i + 1));
		val = ms_env_get(e->m->env_list, name);
		e->out = ew_append_str(e->out, val);
		free(name);
		e->i = j;
		return (1);
	}
	e->out = ew_append_char(e->out, '$');
	e->i += 1;
	return (1);
}

int	ew_handle_dollar(void *ctx)
{
	t_exp	*e;
	char	*num;

	e = (t_exp *)ctx;
	if (!(e->s[e->i] == '$') || e->in_s)
		return (0);
	if (e->s[e->i + 1] == '?')
	{
		num = ft_itoa(e->m->last_status);
		e->out = ew_append_str(e->out, num);
		free(num);
		e->i += 2;
		return (1);
	}
	return (handle_dollar_core(e));
}
