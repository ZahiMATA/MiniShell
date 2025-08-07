/*
tests1: < Makefile  grep a | wc

test2.0
< Makefile cat > ficout -> OK
< Makefile cat | wc > ficout -> KO


cat < Makefile << FIN > outfile >> ficout

test2:
< Makefile tr a A | tr b B > ficout
->
[<][makefile][tr a A][|][tr b B][>][ficout]
->
typedef struct _s_cmd
{
	char	**args; = [tr][a][b]
	char	*file_in; = "makefile"
	char	*file_out; NULL
	int		append_mode;
	int		heredoc_mode;
	struct	s_cmd	*next;
}	t_cmd;


typedef struct _s_cmd
{
	char	**args; = [tr][b][B]
	char	*file_in; = -1
	char	*file_out; = ficout
	int		append_mode; > -> 0 : >> -> 1
	int		heredoc_mode;
	struct	s_cmd	*next; ->NULL
}	t_cmd;
*/

#include "minishell.h"

static void	check_token(t_minishell *m)
{
	t_cmd2 cmd;
	t_cmd2 *cmd2;

	cmd.cmd = NULL;
	cmd.file_in  = NULL;
	cmd.file_out  = NULL;
	cmd.mode_in = T_NONE;
	cmd.mode_out = T_NONE;
	cmd.next = NULL;
	while (m->token_list && m->token_list->token != T_PIPE)
	{

		if(ft_is_stringword(m))
			cmd.cmd = m->token_list->val;
		else if(m->token_list->token == T_REDIRECT_LEFT)
		{
			m->token_list = m->token_list->next;
			if (m->token_list == NULL || ft_is_stringword(m) == 0)
				return (ft_return_error(m, ERROR_NL, RETURN_NL));
			cmd.file_in = m->token_list->val;
			cmd.mode_in = T_INPUT;
		}
		else if(m->token_list->token == T_REDIRECT_RIGHT)
		{
			m->token_list = m->token_list->next;
			if (m->token_list == NULL || ft_is_stringword(m) == 0)
				return (ft_return_error(m, ERROR_NL, RETURN_NL));
			cmd.file_out = m->token_list->val;
			cmd.mode_out = T_OUTPUT;
		}
		m->token_list = m->token_list->next;
	}
	cmd2 = prs_lstnew(cmd);
	if (cmd2 == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	prs_lstadd_back(&m->cmds2, cmd2);
}

void	parser(t_minishell *m)
{
	printf("t=%d\n", m->token_list->token);
	while (m->token_list)
	{
		check_token(m);
		if (m->last_status)
			return ;
		if (m->token_list && m->token_list->token == T_PIPE)
			m->token_list = m->token_list->next;
	}
}

