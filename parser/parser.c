/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:26:51 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/02 19:59:42 by ybouroga         ###   ########.fr       */
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

static void	check_token(t_minishell *m, t_token_list **token_list)
{
	t_cmd cmd;
	t_cmd *pcmd;
	t_red_t type;
	t_redir *redir;

	ft_bzero(&cmd, sizeof(t_cmd));
	pcmd = NULL;
	while (*token_list && (*token_list)->token != T_PIPE)
	{
		if(ft_is_stringword(*token_list))
			cmd.args = prs_realloc_args(m, cmd.args, cmd.n++, (*token_list)->val);
		else if(ft_is_redir(*token_list))
		{
			type = prs_get_redir((*token_list)->token);
			*token_list = (*token_list)->next;
			if (*token_list == NULL || ft_is_stringword(*token_list) == 0)
				return (ft_return_error(m, MINISHELL, ERROR_NL, RETURN_NL)); // TODO ajouter free cmd
			redir = prs_lstnew_redir(type, (*token_list)->val);
			if(redir == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);

			prs_lstadd_back_redir(&cmd.redirs, redir);
		}
		*token_list = (*token_list)->next;
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
	t_token_list	*token_list;
	//printf("tl=[%p]\n",  m->token_list);

	token_list = m->token_list;
	while (token_list)
	{
		check_token(m, &token_list);
		if (m->cmds && m->cmds->args && m->cmds->args[0])
			if (m->last_status)
				return ;
		if (token_list && token_list->token == T_PIPE)
			token_list = token_list->next;
	}
	//printf("tl=[%p]\n",  m->token_list);
	//printf("apres\n");
	//debug_show_cmds(m);
}


