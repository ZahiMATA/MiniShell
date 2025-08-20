/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:16:14 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/20 19:02:58 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	debug_show_cmd(t_cmd *c, int n)
{
	int i ;

	printf("\033[0;31mCmd\033[0m\n");

	printf("Cmd_abs=[%s]\n#n=[%d]\nN=[%d]\n",
		c->cmd_abs, c->n, n);
	i = 0;
	if (c->redirs && c->redirs->file)
		printf("file=[%s]\ntype=[%d]\n", c->redirs->file, c->redirs->type);
	else
		printf("no redir or file\n");
	while (c->args && c->args[i])
		printf("args=[%s]\n", c->args[i++]);
}

void	debug_show_cmds(t_minishell *m, int n)
{
	t_cmd	*l;
	int		i;

	l = m->cmds;

	//if (DEBUG_LEX)
	{
		ft_putstr_nl("\033[0;31mCmds\033[0m");
		i = 0;
		while (i < n && l)
		{
			i++;
			l = l->next;
		}
		if (l)
		{
			printf("Cmd_abs=[%s]\n#n=[%d]\nN=[%d]\nf=[%s]\nt=[%d]\n", l->cmd_abs, l->n, n, l->redirs->file, l->redirs->type);
			i = 0;
			while (l->args && l->args[i])
				printf("args=[%s]\n", l->args[i++]);
//			l = l->next;
		}
	}
}

static void	debug_args(t_cmd *l, char*buffer, size_t size)
{
	int	i;

	i = 0;
	while (l->args && l->args[i])
	{
		if (i == 0)
			ft_strlcat(buffer, "ARGS=[", size);
		ft_strlcat(buffer, l->args[i], size);
		if (l->args[i + 1])
			ft_strlcat(buffer, ",", size);
		else
			ft_strlcat(buffer, "]", size);
		i++;
	}
}

static void	debug_redirs(t_minishell *m, t_cmd *l, char*buffer, size_t size)
{
	int		i;
	char	*n;

	i = 0;
	while (l->redirs && l->redirs->file)
	{
		ft_strlcat(buffer, "[", size);
		ft_strlcat(buffer, l->redirs->file, size);
		ft_strlcat(buffer, "]", size);
		ft_strlcat(buffer, "[", size);
		n = ft_itoa(l->redirs->type);
		if (n == NULL)
			ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
		ft_strlcat(buffer, n, size);
		ft_strlcat(buffer, "]", size);
		/*if (l->args[i + 1])
			ft_strlcat(buffer, ",", size);*/
		free(n);
		i++;
		l->redirs = l->redirs->next;
	}
	//ft_strlcat(buffer, "]", size);
}

void	debug_serial_parser(t_minishell *m, char *buffer, size_t size)
{
	t_cmd	*l;

	buffer[0] = '\0';
	l = m->cmds;
	while (l)
	{
		ft_strlcat(buffer, "CMD(", size);
		debug_args(l, buffer, size);
		debug_redirs(m, l, buffer, size);
		ft_strlcat(buffer, ")", size);
		if (l->next)
			ft_strlcat(buffer, ",", size);
		l = l-> next;
	}
	ft_strlcat(buffer, "\n", size);
}
