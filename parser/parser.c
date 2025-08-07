/*
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
	while (m->token_list && m->token_list->token != T_PIPE)
	{
		if(m->token_list->token == T_STRING || m->token_list->token == T_WORD)
		{
			m->cmds2->cmd = ft_strdup(m->token_list->val);
			if (m->cmds2->cmd == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		}
		else if(m->token_list->token == T_REDIRECT_LEFT)
		{
			m->token_list = m->token_list->next;
			m->cmds2->file_in = ft_strdup(m->token_list->val);
			if (m->cmds2->file_in  == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		}
		else if(m->token_list->token == T_REDIRECT_RIGHT)
		{
			m->token_list = m->token_list->next;
			m->cmds2->file_out = ft_strdup(m->token_list->val);
			if (m->cmds2->file_out == NULL)
				ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		}
		m->token_list = m->token_list->next;
	}
}

void	parser(t_minishell *m)
{
	t_cmd2	*head;
	t_cmd2	*current;

	head = NULL;
	current = NULL;
	while (m->token_list)
	{
		m->cmds2 = ft_calloc(1, sizeof(t_cmd2));
		if (m->cmds2 == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		check_token(m);
		if (m->token_list && m->token_list->token == T_PIPE)
			m->token_list = m->token_list->next;
		if (head == NULL)
			head = m->cmds2;
		else
			current->next = m->cmds2;
		current = m->cmds2;
	}
	m->cmds2 = head;
}

