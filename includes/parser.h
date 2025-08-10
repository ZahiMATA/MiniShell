/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:20:43 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 15:00:54 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# ifndef DEBUG_PRS
#  define DEBUG_PRS 0
# endif

typedef struct s_minishell	t_minishell;
typedef struct s_cmd2		t_cmd2;

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
	int				n;
	t_redir			*redirs;
	struct s_cmd 	*next;
} t_cmd;

void	prs_lstadd_back(t_cmd2  **lst, t_cmd2 *new_lst);
void	prs_lstclear(t_cmd2 **lst);
t_cmd2	*prs_lstnew(t_cmd2 cmd);
t_cmd2	*prs_lstget(t_minishell *m, int n);
char	*prs_getcmd(t_minishell *m, char *s);
int		prs_lstget_nb(t_minishell *m);
char	**prs_realloc_args(t_minishell *m, char **tab, int size, char *insert);
t_redir	prs_get_redir(t_token t);

#endif