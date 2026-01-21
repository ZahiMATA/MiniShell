/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:26:51 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 18:53:23 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/*
test:
< Makefile tr a A | tr b B > ficout
->
[<][makefile][tr a A][|][tr b B][>][ficout]
->
(CMD(redir_in="Makefile", args=["tr", "a", "A"]),
 CMD(args=["tr", "b", "B"], redir_out="ficout"))
*/

static void	do_ct(t_minishell *m, t_token_list **tl, t_cmd	*cmd, t_redir *r);

static void	check_token(t_minishell *m, t_token_list **tl)
{
	t_cmd	cmd;
	t_cmd	*pcmd;
	t_redir	*redir;

	ft_bzero(&cmd, sizeof(t_cmd));
	pcmd = NULL;
	redir = NULL;
	do_ct(m, tl, &cmd, redir);
	if (m->last_status != 0)
		return ;
	pcmd = prs_lstnew(cmd);
	if (pcmd == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	prs_lstadd_back(&m->cmds, pcmd);
}

static void	do_ct(t_minishell *m, t_token_list **tl, t_cmd	*cmd, t_redir *r)
{
	t_red_t	type;

	while (*tl && (*tl)->token != T_PIPE)
	{
		if (ft_is_stringword(*tl))
			cmd->args = prs_realloc_args(m, cmd->args, cmd->n++, (*tl)->val);
		else if (ft_is_redir(*tl))
		{
			type = prs_get_redir((*tl)->token);
			*tl = (*tl)->next;
			if (*tl == NULL || ft_is_stringword(*tl) == 0)
			{
				ft_printf_fd(STDERR_FILENO, "%s: %s %s\n", \
					MINISHELL, ERROR_SENUT, ft_get_token(*tl));
				mem_free_array(&cmd->args, "check_token");
				prs_lstclear_redir(&cmd->redirs);
				return (ft_return_err(m, RETURN_NL, NULL));
			}
			r = prs_lstnew_redir(type, (*tl)->val);
			if (r == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
			prs_lstadd_back_redir(&cmd->redirs, r);
		}
		*tl = (*tl)->next;
	}
}

void	parser(t_minishell *m)
{
	t_token_list	*token_list;

	token_list = m->token_list;
	while (token_list)
	{
		check_token(m, &token_list);
		if (m->last_status)
			return ;
		if (token_list && token_list->token == T_PIPE)
			token_list = token_list->next;
	}
}
