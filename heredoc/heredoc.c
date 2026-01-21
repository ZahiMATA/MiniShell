/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 20:28:11 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_launch_read(t_minishell *m, int fd[2], char *limiter, int expand)
{
	while (1)
	{
		m->line = read_input(m, PROMPT_HEREDOC);
		{
			if (m->status_heredoc != 0)
				break ;
			else if (m->line == NULL)
			{
				ft_printf_fd(STDOUT_FILENO, WARNING_HEREDOC, limiter);
				break ;
			}
			if ((m->line && ft_strcmp(m->line, limiter) == 0))
				break ;
			if (expand)
			{
				m->dummy = ms_expand_word(m, m->line, WITHOUT_QUOTES);
				ft_putstr_fd_nl(m->dummy, fd[1]);
				mem_free_null(&m->dummy, "ms_launch_read");
			}
			else
				ft_putstr_fd_nl(m->line, fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
}

char	*ms_unquote(char *s)
{
	char	*ret;

	if (ft_strchr(s, '\"'))
		ret = ft_strtrim_all(s, "\"");
	else if (ft_strchr(s, '\''))
		ret = ft_strtrim_all(s, "'");
	else
		ret = ft_strdup(s);
	return (ret);
}

int	ms_heredoc(t_minishell *m, char *limiter, int nop)
{
	int				fd[2];
	int				expand;
	char			*new_limiter;
	struct termios	config;

	(void)nop;
	setup_signals_for_heredoc();
	expand = 1;
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '"'))
		expand = 0;
	new_limiter = ms_unquote(limiter);
	if (pipe(fd) == -1)
		ft_exit_fail(m, ERROR_PIPE);
	tcgetattr(STDIN_FILENO, &config);
	disable_ctr_backslash();
	ms_launch_read(m, fd, new_limiter, expand);
	enable_ctr_backslash(&config);
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");
	mem_free(new_limiter, "ms_heredoc", new_limiter);
	setup_signals();
	return (fd[0]);
}
