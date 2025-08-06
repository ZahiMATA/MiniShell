/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:23:17 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/06 14:25:21 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  < makefile "tr a A" | "tr b B" > ficout
// -> **token  [<][makefile][tr a A][|][tr b B][>][ficout]

#include "lexer.h"
#include "minishell.h"

static void add_token(t_param *_, t_token token, char *val, int n)
{
	t_token_list	*tmp;

	tmp = lex_lstnew(token, val);
	lex_lstadd_back(&_->token_list, tmp);
	_->i += n;
}
t_token_list *lexer(char *line)
{
	t_param	_;

	_.token_list = NULL;
	_.i = 0;
	while (line && line[_.i])
	{
		while (ft_isspace(line[_.i]))
			_.i++;
		if (line[_.i] == '\0')
			break;
		else if (line[_.i] == '|')
			add_token(&_, T_PIPE, "|", 1);
		/*else if (line[i] == '<')
			add_token(t, &i);
		else if (line[i] == '>')
			add_token(t, &i);
		else if (line[i] == '<' && line[i + 1] == '<')
			add_token(t, &i);
		else if (line[i] == '>' && line[i + 1] == '>')
			add_token(t, &i);
		else
			add_token(t, &i);*/
	}
	return (NULL);

}
