/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:20:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 18:20:18 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_lexer_quote(t_param *_);

static void	lexer_subquote(t_param *_)
{
	_->i++;
	while (_->m->line[_->i] && _->m->line[_->i] != '\'')
	{
		if (ft_strncmp(_->m->line + _->i, "\\\"", 2) == 0)
			_->i++;
		_->i++;
	}
}

void	lexer_quote(t_param *_)
{
	char	*s;

	_->open_q = 0;
	_->open_s = 0;
	_->start = _->i;
	do_lexer_quote(_);
	s = ft_substring(_->m->line, _->start, (_->i - _->start));
	if (s == NULL)
		ft_exit_fail_status(_->m, NULL, EXIT_ALLOC_ERROR);
	add_token(_, T_WORD, s, 0);
	mem_free(s, "lexer_string.s", s);
}

void	do_lexer_quote(t_param *_)
{
	while (_->m->line[_->i])
	{
		lexer_subquote(_);
		if (_->m->line[_->i] == '\0')
		{
			ft_return_error(_->m, ERROR_SYNTAX, ERROR_QUOTE, EXIT_FAILURE);
			lex_lstclear(&_->m->token_list);
			return ;
		}
		if (_->m->line[_->i + 1] == 0)
		{
			_->i++;
			break ;
		}
		_->i++;
		lexer_subword(_);
		if (ft_issublexer(_->m->line[_->i]))
		{
			if (ft_isspace(_->m->line[_->i] - 1) != 0)
				_->i--;
			break ;
		}
	}
}
