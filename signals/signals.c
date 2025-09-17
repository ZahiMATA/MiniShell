/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:53:40 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:53:40 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal;

static void sigint_handler(int sig)
{
	(void)sig;
	g_signal |= SIG_FLAG;
	write(STDOUT_FILENO, "\n", 1);
	if (g_signal & RDL_FLAG)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
#include <sys/ioctl.h>
static void sigint_handler_hd(int sig)
{
	(void)sig;
	//write(STDOUT_FILENO, "ok\n", 3);
	/*
	g_signal |= SIG_FLAG;

	write(STDOUT_FILENO, "\n", 1);
	int i = g_signal + '0';
	write(1, &i, 1);

	rl_done = 1;
	ioctl(STDOUT_FILENO, TIOCSTI, "\n");
	        ioctl(STDOUT_FILENO, TIOCSTI, "\n");
        rl_on_new_line();
        rl_replace_line("", 0);*/
}

/*static* / void sigquit_handler(int sig)
{
	(void)sig;

	debug_var("test\n");
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}*/

void setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void setup_signals_off(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void setup_signals_for_children(void)
{
	signal(SIGINT,  SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void setup_signals_for_heredoc(void)
{
/*	signal(SIGINT,  sigint_handler_hd);
	signal(SIGQUIT, SIG_IGN);*/

    struct sigaction sa;
    sa.sa_handler = sigint_handler_hd;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0*SA_RESTART;//0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
