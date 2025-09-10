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
		line = read_input(m, PROMPT/*, STDIN_FILENO*/);
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

	m = NULL;
	setup_signals();
	exec_init_minishell(&m);
	g_signal = SIG_N_ZERO;
	while (1)
	{
		m->line = read_input(m, PROMPT);
		ft_g_signal(m);
		lexer(m);
		debug_show_tokens(m);
		parser(m);
		if (m->line == NULL)
			ft_exit(m, NULL);
		if (m->last_status == 0)
		{
			m->last_status = m->status_echo;
			exec_feed_minishell(&m, env);
			dispatch(m);
			debug_show_args(m);
		}
		// debug_show_args(m);
		mem_reset_m(m);
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
		ft_putstr_nl(ERROR_WRONGARGS);
}