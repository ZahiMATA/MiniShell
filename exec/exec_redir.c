/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:35:12 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:29:52 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in(t_minishell *m, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == N_REDIR_LEFT)
		{
			m->fd_in = open(redir->file, O_RDONLY);
			if (m->fd_in == -1)
				ft_exit_err(m, EXIT_FAILURE, \
					ft_perror(MINISHELL, redir->file, PERROR));
			else if (dup2(m->fd_in, STDIN_FILENO) == -1)
				ft_exit_fail(m, ERROR_DUP2);
			close(m->fd_in);
		}
		else if (redir->type == N_DOUBLE_REDIR_LEFT)
		{
			if (cmd->fd_in == -1)
				ft_exit_err(m, EXIT_FAILURE, \
					ft_perror(MINISHELL, redir->file, PERROR));
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				ft_exit_fail(m, ERROR_DUP2);
		}
		redir = redir->next;
	}
}

void	redir_out(t_minishell *m, t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == N_REDIR_RIGHT)
		{
			m->fd_out = open(r->file, OW | OC | OT, FLAG_FIC);
			if (m->fd_out == -1)
				ft_exit_err(m, EXIT_1, ft_perror(MINISHELL, r->file, PERROR));
			else if (dup2(m->fd_out, STDOUT_FILENO) == -1)
				ft_exit_fail(m, ERROR_DUP2);
			close(m->fd_out);
		}
		else if (r->type == N_DOUBLE_REDIR_RIGHT)
		{
			m->fd_out = open(r->file, OW | OC | OA, FLAG_FIC);
			if (m->fd_out == -1)
				ft_exit_err(m, EXIT_1, ft_perror(MINISHELL, r->file, PERROR));
			else if (dup2(m->fd_out, STDOUT_FILENO) == -1)
				ft_exit_fail(m, ERROR_DUP2);
			close(m->fd_out);
		}
		r = r->next;
	}
}

void	redir_heredoc(t_minishell *m, t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == N_DOUBLE_REDIR_LEFT)
		{
			mem_close_fd(cmd->fd_in);
			cmd->fd_in = ms_heredoc(m, redir->file, 0);
			if (cmd->fd_in == -1)
				ft_exit_err(m, EXIT_FAILURE, \
					ft_perror(MINISHELL, redir->file, PERROR));
			if (m->status_heredoc != 0)
				return ;
		}
		redir = redir->next;
	}
}
