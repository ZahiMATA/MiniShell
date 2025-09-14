/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:27:44 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/14 15:20:42 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "parser.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/stat.h>

# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef DEBUG_ENV
#  define DEBUG_ENV 0
# endif
# ifndef DEBUG_MALLOC
#  define DEBUG_MALLOC 0
# endif
# ifndef DEBUG_TEST
#  define DEBUG_TEST 1
# endif
# define BUFFER_SIZE 1024
# define BUFFER_LOG 1024
# define KO 0
# define OK 1
# define MINISHELL "minishell"
# define PROMPT "minishell$ "
# define CTRL_C "^C"
# define PROMPT_HEREDOC "> "
# define WARNING_HEREDOC "\nminishell: warning: here-document delimited by end-of-file (wanted `%s')\n"
// # define EXIT_FAILURE 1
# define EXIT_ALLOC_ERROR 2
# define EXIT_PERMISSION_DENIED 126
# define EXIT_IS_A_DIRECTORY 126
# define EXIT_IS_NOT_A_DIRECTORY 126
# define EXIT_PERMISSION 126
# define EXIT_COMMAND_NOT_FOUND 127
# define EXIT_NO_SUCH_FILE 127
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
# define ERROR_ACCESS "Error: Acsetup_signals_for_childrencess"
# define ERROR_FORK "Error: Fork"
# define ERROR_DUP "Error: Dup"
# define ERROR_DUP2 "Error: Dup2"
# define ERROR_TTY "Cannot open /dev/tty"
# define ERROR_PIPE "Error: Pipe"
# define ERROR_PERMISSION "Permission denied"
# define ERROR_COM "Command not found"
# define ERROR_NO_COM "No command"
# define ERROR_DIR "Is a directory"
# define ERROR_NOT_DIR "Not a directory"
# define ERROR_NOSUCH "No such file or directory"
# define S_QUIT "Quit (core dumped)"
//# define PATH "PATH="
# define S_PATH "PATH"
# define S_EMPTY ""
# define OFST_FIRST_CMD 2
# define NB_NOT_ARG 3
# define OW O_WRONLY
# define OC O_CREAT
# define OT O_TRUNC
# define OA O_APPEND
# define FLAG_FIC 0644
 # define SIG_N_ZERO 0
// # define GOT_SIGNAL 1
// # define GOT_CHILD_SIG 2
// # define EXIT_CMDNOEXISTS 1
#define SIG_FLAG 0x1
#define RDL_FLAG 0x2

extern volatile sig_atomic_t g_signal;
//extern volatile sig_atomic_t g_readline_active;

// TODO implementer init et l access et le free et le update data

typedef struct s_err
{
	char	*mes1;
	char	*mes2;
	char	*mes3;
	//int		status;

} t_err;

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
	char			*error;
	int				status_echo;
	int				last_status;
	t_list			*history;
}	t_minishell;

void	mem_free_all(t_minishell *m);
void	mem_reset_m(t_minishell *m);
void	mem_free_array(char	***tab, char *mes);
void	mem_free_null(char	**p, char *mes);
void	mem_free(void *p, const char *key, const char *val);
void	mem_close_fds(t_minishell *m);
void	*mem_malloc(size_t size, const char *key, const char *val);
void 	exec_init_minishell(t_minishell **m/*, t_env *last_env_list*/);
void	exec_feed_minishell(t_minishell **m, char **env);
void	exec_init_path(t_minishell **p);
void	exec_init_cmds_and_cmd_args(t_minishell **p, char **cmd, int nbcom);
void	exec_init_cmd_path(t_minishell **p/*, int nbcom*/);
char	*exec_find_command(t_minishell *m, char *cmd);
void	exec_execve(t_minishell *m);
void	debug_show_args(t_minishell *m);
void	debug_show_processes(t_minishell *m, char *message);
void	debug_show_error(char *message);
void	ft_print_list(void *s1, void *s2);
int		set_last_status(t_minishell *m);
void	ft_print_array(char **tab);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strchr(const char *s, int c);
t_env	*ft_lstnew_env(void *key, void *val);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
void	ft_lstiter_env(t_env *lst, void (*f)(void *, void *));
void	ft_del_env_content(void *ptr);
void	ft_return_error(t_minishell *m, char *mes1, char *mes2, int status);
void	ft_return_err(t_minishell *m, int status, void *nop);
void	ft_return_perror(t_minishell *m, char *message, int status);
void	ft_exit_fail(t_minishell *m, char *message);
void	ft_exit_fail_status(t_minishell *m, char *message, int status);
void	ft_exit_perror(t_minishell *m, char *message);
void	ft_exit_error(t_minishell *m, char *mes1, char *mes2, int status);
void	ft_exit_err(t_minishell *m, int status, void *nop);
void	ft_exit_with_status(t_minishell *m, char *message, int status);
char 	*ft_substring(const char *s, int start, int len);
char	*read_input(t_minishell *m, char * prompt);
char	*get_input(void);
char	**env_list_to_tab(t_minishell *m, t_env *env);
void	 debug_pointer(void *p);
void	debug_var(const char *s);
void	debug_var_i(int i);
void	dispatch(t_minishell *m);
int		ft_history(t_minishell *m);
void	ft_add_history(t_minishell *m, char *s);
int		ft_cd(t_minishell *m, t_cmd *cmd);
int		ft_echo(t_minishell *m, t_cmd *cmd);
int		ft_env(t_minishell *m, t_cmd *cmd);
int		ft_exit(t_minishell *m, t_cmd *cmd);
int		ft_export(char **args, t_env **env_list);
int		ft_pwd(void);
int		ft_unset(char **arg, t_env **env_list);
int		ft_colon(t_minishell *m);
char	*ms_env_get(t_env *env, const char *key);
void	ms_expand_all_cmds(t_minishell *m);
char	*ms_expand_word(t_minishell *m, const char *s);
void	ft_print_perror(char *message, char *pmessage);
void	*ft_perror(char *mes1, char *mes2, char * mes3);
int		ft_stat(const char *path);
int		ft_is_dir(const char *path);
int		ft_not_dir_but_file(char *path);
int		ft_same_edges(char *s, int c);
int		ms_heredoc(t_minishell *m, char *limiter, int expand);
int		ft_g_signal(t_minishell *m);
void	setup_signals(void);
void	setup_signals_for_children(void);
int		exec_builtin(t_minishell *m, t_cmd *cmd);
int		is_builin_parent(char *s);
int		is_builin_child(char *s);
void	redir_in(t_minishell *m, t_cmd *cmd);
void	redir_out(t_minishell *m, t_cmd *cmd);

#endif