/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:26:51 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/14 10:42:54 by ybouroga         ###   ########.fr       */
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

static void	check_token(t_minishell *m)
{
	t_cmd cmd;
	t_cmd *pcmd;
	t_red_t type;
	t_redir *redir;

	ft_bzero(&cmd, sizeof(t_cmd));
	pcmd = NULL;
	while (m->token_list && m->token_list->token != T_PIPE)
	{
		if(ft_is_stringword(m))
			cmd.args = prs_realloc_args(m, cmd.args, cmd.n++, m->token_list->val);
		else if(ft_is_redir(m))
		{
			type = prs_get_redir(m->token_list->token);
			m->token_list = m->token_list->next;
			if (m->token_list == NULL || ft_is_stringword(m) == 0)
				return (ft_return_error(m, ERROR_NL, RETURN_NL)); // TODO ajouter free cmd
			redir = prs_lstnew_redir(type, m->token_list->val);
			if(redir == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);

			prs_lstadd_back_redir(&cmd.redirs, redir);
		}
		m->token_list = m->token_list->next;
	}
	pcmd = prs_lstnew(cmd);
	if (pcmd == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	prs_lstadd_back(&m->cmds, pcmd);
}

void	parser(t_minishell *m)
{
	//printf("avant\n");
	//debug_show_cmds(m);
	while (m->token_list)
	{
		check_token(m);
		if (m->cmds->args && m->cmds->args[0])
		if (m->last_status)
			return ;
		if (m->token_list && m->token_list->token == T_PIPE)
			m->token_list = m->token_list->next;
	}
	//printf("apres\n");
	//debug_show_cmds(m);
}

