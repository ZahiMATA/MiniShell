#include "minishell.h"

/* Expand un tableau argv */
static void	ms_expand_argv_of_cmd(t_minishell *m, char **argv)
{
	int		i;
	char	*neww;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		neww = ms_expand_word(m, argv[i]);
		if (neww)
		{
			free(argv[i]);
			argv[i] = neww;
		}
		i++;
	}
}

void	ms_expand_all_cmds(t_minishell *m)
{
	t_cmd	*cur;

	cur = m->cmds;
	while (cur)
	{
		ms_expand_argv_of_cmd(m, cur->args);
		cur = cur->next;
	}
}
