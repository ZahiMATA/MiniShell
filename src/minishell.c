/*
	TODO
		revoir doc et verif la correction
		finir built in
		parsing relire sujet et lexer
		finir exec
		dispatcheur built in ou exec et redirection
		faire historique commande
		signaux

*/
#include "minishell.h"

void	test0(char **env)
{
	t_minishell *m;
	char *line;

	m = NULL;
	(void)env;
	while (1)
	{
		exec_init_minishell(&m);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		line = read_input(m, STDIN_FILENO);
		if (line == NULL)
			continue;
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		ft_putstr_fd("Texte entré : ", STDOUT_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
		free(line);
	}
}

void	test1(char **env)
{
	t_minishell *m;
	char 		*line;
	int			last_status;

	m = NULL;
	last_status = 0;
	(void)env;
	while (1)
	{
		exec_init_minishell(&m);
		ft_putstr_fd(PROMPT, STDOUT_FILENO);
		line = read_input(m, STDIN_FILENO);
		if (line == NULL)
			continue;
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		ft_putstr_fd("Texte entré[1] : ", STDOUT_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
		//char *args[] = { ".a.out", "Makefile", "tr ac AC", "tr b B", "tr xy XY", "ficout", NULL };
		//exec_feed_minishell(&m, /*args, 3,*/ env);
		//debug_show_args(m);
		//exec_execve(m);

		lexer(m, line);
		debug_show_tokens(m);

		parser(m);
		debug_show_cmds(m);

		exec_feed_minishell(&m, env);
		//exec_execve(m);

		last_status = m->last_status;
		free(line);
		mem_free_all(m);
	}
}


void	minishell(char **env)
{
	int i = 1;
	if (i ==0) test0(env);
	if (i ==1) test1(env);
}

int	main(int argc, char *argv[], char *env[])
{
	(void) argv;
	if (argc == 1)
		minishell(env);
	else
		ft_putstr(ERROR_WRONGARGS);
}