/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:20:43 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/20 17:17:03 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# ifndef DEBUG_PRS
#  define DEBUG_PRS 0
# endif

typedef struct s_minishell	t_minishell;
//typedef struct s_cmd2		t_cmd2;

typedef enum e_red_t
{
	N_REDIR_LEFT,
	N_REDIR_RIGHT,
	N_DOUBLE_REDIR_LEFT,
	N_DOUBLE_REDIR_RIGHT,
} t_red_t;

typedef struct	s_redir
{
	t_red_t			type;
	char			*file;
	struct s_redir	*next;
} t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_abs;
	int				n;
	t_redir			*redirs;
	int				status;
	int				pid;
	struct s_cmd 	*next;
} t_cmd;

void	prs_lstadd_back(t_cmd  **lst, t_cmd *new_lst);
void	prs_lstclear(t_cmd **lst);
t_cmd	*prs_lstnew(t_cmd cmd);
t_cmd	*prs_lstget(t_minishell *m, int n);
void	prs_lstadd_back_redir(t_redir  **lst, t_redir *new_lst);
void	prs_lstclear_redir(t_redir **lst);
t_redir	*prs_lstnew_redir(t_red_t type, char *file);
char	*prs_getcmd(t_minishell *m, char *s);
char	*prs_getcmd_from_args(t_minishell *m, char **args);
int		prs_lstget_nb(t_minishell *m);
char	**prs_realloc_args(t_minishell *m, char **tab, int size, char *insert);
t_red_t	prs_get_redir(t_token t);
void	debug_serial_parser(t_minishell *m, char *buffer, size_t size);

#endif