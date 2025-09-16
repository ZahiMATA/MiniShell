/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:50:18 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/16 14:47:02 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void ms_launch_read(t_minishell *m, int fd[2], char *limiter, int expand)
{
	char	*s;

	while (1)
	{
		//m->line = readline(PROMPT_HEREDOC);
		m->line = read_input(m, PROMPT_HEREDOC);
		////ft_putstr("test2\n");
		{
			if (m->line == NULL)
			{
				ft_printf_fd( STDOUT_FILENO, WARNING_HEREDOC, limiter);
				break;
			}
			if ( (m->line && ft_strcmp(m->line, limiter) == 0) || (g_signal & SIG_FLAG))
			{
				////ft_putstr("test\n");
				break;
			}
			if (expand)
			{
				s = ms_expand_word(m, m->line);
				ft_putstr_fd(s, fd[1]);
				mem_free_null(&s, "ms_launch_read");
			}
			else
				ft_putstr_fd(m->line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			mem_free_null(&m->line, "ms_launch_child.line");
		}
	}
	close(fd[1]);
	mem_free_null(&m->line, "ms_launch_child.line");

}

char *ms_unquote(char *s)
{
	char	*ret;

	if (ft_strchr(s, '\"'))
		ret = ft_strtrim_all(s, "\"");
	else if (ft_strchr(s, '\''))
		ret = ft_strtrim_all(s, "'");
	else
		ret =  ft_strdup(s);
	return (ret);
}

int	ms_heredoc(t_minishell *m, char *limiter, int nop)
{
	int		fd[2];
	int		expand;
	char	*new_limiter;

	(void)nop;
	// sig on
	setup_signals_for_heredoc();
	g_signal |= HEREDOC_FLAG;
	expand = 1;
	if (ft_strchr(limiter, '\'') || ft_strchr(limiter, '"'))
		expand = 0;
	new_limiter = ms_unquote(limiter);
	if (pipe(fd) == -1)
		ft_exit_fail(m, ERROR_PIPE);
	ms_launch_read(m, fd, new_limiter, expand);
	mem_free(new_limiter, "ms_heredoc", new_limiter);
	// sig off
	setup_signals();
	g_signal &= ~HEREDOC_FLAG;
	/*if (g_signal & SIG_FLAG)
	{
		g_signal &= ~SIG_FLAG;
		close(fd[0]);
		return (-1);
	}*/
	return (fd[0]);
}
