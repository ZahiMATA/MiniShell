/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:24:57 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 20:27:10 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_ctr_backslash(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_ctr_backslash(struct termios *config)
{
	tcsetattr(STDIN_FILENO, TCSANOW, config);
}

static void	sigint_handler_hd(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, CTRL_C, strlen(CTRL_C));
}

void	setup_signals_for_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_hd;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0 * SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
