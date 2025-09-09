/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/09 19:45:31 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void ms_launch_read(t_minishell *m, int fd[2], char *limiter, int nop)
{
	(void)nop;
	int	dup_tmp;
		dup_tmp = dup(STDOUT_FILENO);
	if ( dup_tmp == -1)
		ft_exit_fail(m, ERROR_DUP);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	while (1)
	{
		//m->line = readline(PROMPT_HEREDOC);
		m->line = read_input(m, PROMPT_HEREDOC);

		{
			if (m->line == NULL)
			{
				ft_printf_fd( STDERR_FILENO, WARNING_HEREDOC, limiter);
				break;
			}
			if ( m->line && ft_strcmp(m->line, limiter) == 0)
				break;
			ft_putstr_fd( ms_expand_word(m, m->line), fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	if (dup2(dup_tmp, STDOUT_FILENO) == -1)
		ft_exit_fail(m, ERROR_DUP2);
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
}

int	ms_heredoc(t_minishell *m, char *limiter, int nop)
{
	int		fd[2];

	if (pipe(fd) == -1)
		ft_exit_fail(m, ERROR_PIPE);
	ms_launch_read(m, fd, limiter, nop);
	return fd[0];
}
