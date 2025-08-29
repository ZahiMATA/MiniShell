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
	//char 		*line;
	int			last_status;
	//t_env		*last_env_list;
	int			got_signal;

	m = NULL;
	setup_signals();
	last_status = 0;
	//last_env_list = NULL;
	got_signal = 0;
	exec_init_minishell(&m/*, last_env_list*/);
	while (1)
	{
		//if(got_signal == GOT_NO_SIGNAL) ft_putstr(PROMPT);
		m->line = read_input(m, got_signal);
		//debug_var(m->line);
		lexer(m);
		debug_show_tokens(m);
		parser(m);
		if (m->line == NULL)
			ft_exit(m);
		if (m->last_status == 0)
		{
			m->last_status = last_status;
			exec_feed_minishell(&m, env);
			dispatch(m);
			got_signal = sig_kill_children(m);
			//ft_printf_fd(1,"[%c]", got_signal + '0');
			set_last_status(m);
			debug_show_args(m);
		}
		last_status = m->last_status;
		mem_reset_m(m);
		m->last_status = 0;
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