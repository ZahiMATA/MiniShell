/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:55:44 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 16:55:44 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char **env)
{
	t_minishell	*m;

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
		mem_reset_m(m);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	(void) argv;
	if (argc == 1)
		minishell(env);
	else
		ft_putstr_nl(ERROR_WRONGARGS);
}
