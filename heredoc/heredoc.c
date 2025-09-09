/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmata <zmata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/09 15:43:40 by zmata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	void ms_launch_read(t_minishell *m, int fd[2], char *limiter, int nop)
{
	(void)nop;
	while (1)
	{
		ft_printf_fd(STDERR_FILENO, "%s", PROMPT_HEREDOC);
		m->line = read_line(m, STDERR_FILENO);
		if (m->line && ft_strlen(m->line) >= 1)
			m->line[ft_strlen(m->line) - 1] = 0;
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
