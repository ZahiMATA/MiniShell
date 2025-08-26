/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:27:44 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/26 19:07:41 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "libft.h"
# include "ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef DEBUG_ENV
#  define DEBUG_ENV 0
# endif
# define BUFFER_SIZE 1024
# define BUFFER_LOG 1024
# define KO 0
# define OK 1
# define MINISHELL "minishell"
# define PROMPT "minishell$ "
# define CTRL_C "^C"
# define PROMPT_HEREDOC "> "
# define WARNING_HEREDOC "minishell: warning: here-document delimited by end-of-file (wanted `%s')"
// # define EXIT_FAILURE 1
# define EXIT_ALLOC_ERROR 2
# define EXIT_PERMISSION_DENIED 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_SYNTAX_ERROR 258
# define EXIT "exit"
# define ERROR "Error"
# define ERROR_WRONGARGS "Error: Wrong arguments"
# define ERROR_NOENV "Error: No environment"
# define ERROR_NOPATH "Error: No PATH"
# define ERROR_NOCOMS "Error: No commands"
# define ERROR_MALLOC "Error: Malloc failed"
# define ERROR_NOFILE "Error: Source file does not exist"
# define ERROR_EXECVE "Error: Execve"
# define ERROR_ACCESS "Error: Access"
# define ERROR_FORK "Error: Fork"
# define ERROR_DUP2 "Error: Dup2"
# define ERROR_PIPE "Error: Pipe"
# define ERROR_COM "Command not found"
# define ERROR_NOSUCH "No such file or directory"
# define PATH "PATH="
# define S_EMPTY ""
# define OFST_FIRST_CMD 2
# define NB_NOT_ARG 3
# define OW O_WRONLY
# define OC O_CREAT
# define OT O_TRUNC
# define FLAG_FIC 0644
// # define EXIT_CMDNOEXISTS 1

extern volatile sig_atomic_t g_signal;

// TODO implementer init et l access et le free et le update data
typedef struct s_env
{
	char			*key;
	char			*val;
	struct	s_env	*next;
} t_env;

// **env is the system env (envp)
// *env_list is our modifiable env
typedef struct s_minishell
{
	int				fd_in;
	int				fd_out;
	t_cmd			*cmds;
	t_token_list	*token_list;
	int				nb_cmd;
	int				is_here_doc;
	char			*limiter;
	char			**path;
	t_env			*env_list; //gere le free
	char			*line;
	char			*error; // a nettoyer
	int				last_status; // pour echo $?
}	t_minishell;

void	mem_free_all(t_minishell *m);
void	mem_free_array(char	***tab);
void 	exec_init_minishell(t_minishell **m);
void	exec_feed_minishell(t_minishell **m, char **env);
void	exec_init_path(t_minishell **p, char **env);
void	exec_init_cmds_and_cmd_args(t_minishell **p, char **cmd, int nbcom);
void	exec_init_cmd_path(t_minishell **p/*, int nbcom*/);
char	*exec_find_command(t_minishell *m, char *cmd);
void	exec_execve(t_minishell *m);
void	debug_show_args(t_minishell *m);
void	debug_show_processes(t_minishell *m, char *message);
void	debug_show_error(char *message);
void	mem_free_null(char	**ptr);
void	mem_close_fds(t_minishell *m);
int		exec_get_last_status(t_minishell *m);
void	ft_print_array(char **tab);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_gerer_zone(char **split, char *zone, int *n);
char	*ft_strchr(const char *s, int c);
t_env	*ft_lstnew_env(void *key, void *val);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
void	ft_lstiter_env(t_env *lst, void (*f)(void *, void *));
void	del_env_content(void *ptr);
void	ft_return_error(t_minishell *m, char *mes, char *pmes, int status);
void	ft_return_perror(t_minishell *m, char *message, int status);
void	ft_exit_fail(t_minishell *m, char *message);
void	ft_exit_fail_status(t_minishell *m, char *message, int status);
void	ft_exit_perror(t_minishell *m, char *message);
void	ft_exit_error(t_minishell *m, char *mes1, char *mes2, int status);
void	ft_exit_with_status(t_minishell *m, char *message, int status);
char 	*ft_substring(const char *s, int start, int len);
char	*read_input(t_minishell *m, int fd);
char	**env_list_to_tab(t_minishell *m, t_env *env);
void	 debug_pointer(void *p);
void	debug_var(char *s);
void	dispatch(t_minishell *m);
int		ft_cd(char **argv, t_env *env_list);
int		ft_echo(char **argv);
int		ft_env(char **arg, t_env *env_list);
int		ft_exit(t_minishell *m);
int		ft_export(char **args, t_env **env_list);
int		ft_pwd(void);
int		ft_unset(char **arg, t_env **env_list);
void	ft_print_perror(char *message, char *pmessage);
void	ft_print_error(char *mes1, char *mes2);
int		ms_heredoc(t_minishell *m, char *limiter, int expand);
void	sig_kill_children(t_minishell *m);
void	setup_signals(void);


#endif