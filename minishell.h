/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:27:44 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/05 15:44:33 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# ifndef DEBUG
#  define DEBUG 1
# endif
# define BUFFER_SIZE 1024
# define KO 0
# define OK 1
# define MINISHELL "minishell"
# define PROMPT "minishell$ "
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
# define ERROR_NOT_FOUND "minishell: Command not found"
# define PATH "PATH="
# define OFST_FIRST_CMD 2
# define NB_NOT_ARG 3
# define OW O_WRONLY
# define OC O_CREAT
# define OT O_TRUNC
# define FLAG_FIC 0644
// # define EXIT_CMDNOEXISTS 1

typedef struct s_cmd
{
	char	**args;
	char	*path;
	char	*file_in; // gerer le free
	char	*file_out; // gerer le free
	int		status;
	//int		fd_pipe[2];
	int		pid;
}	t_cmd;

// TODO QUI remplacera s_cmd qui est une liste chainee
// le tableau sera plus simple car on connait le nb de commandes
typedef struct _s_cmd
{
	char	**args;
	char	*file_in; // gerer le free
	char	*file_out; // gerer le free
	int		append_mode;
	int		heredoc_mode;
	struct	s_cmd	*next;
}	_t_cmd;

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
	int		fd_in;
	int		fd_out;
	t_cmd	*cmds;
	char	**token;
	int		nb_cmd;
	int		is_here_doc;
	char	*limiter;
	char	**path;
	//char	**env; // a eventuellent enlever car sera dans envlist
	t_env	*env_list; //gere le free
	int		last_status; // pour echo $?
}	t_minishell;

void	mem_free_all(t_minishell *m);
void	mem_free_array(char	**tab);
void 	exec_init_minishell(t_minishell **m);
void	exec_feed_minishell(t_minishell **m, char **args, int nbcom, char **env);
void	exec_init_path(t_minishell **p, char **env);
void	exec_init_cmds_and_cmd_args(t_minishell **p, char **cmd, int nbcom);
void	exec_init_cmd_path(t_minishell **p, int nbcom);
char	*exec_find_command(t_minishell *m, char *cmd);
void	exec_execve(t_minishell *m);
void	debug_show_args(t_minishell *m);
void	debug_show_processes(t_minishell *m, char *message, char *cmd, int i);
void	debug_show_error(char *message);
void	mem_free_null(char	**ptr);
void	mem_close_fds(t_minishell *m);
int		exec_get_last_status(t_minishell *m);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd( char *s, int fd);
void	ft_putstr(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_print_array(char **tab);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split_multi(char const *s, char c[2]);
char	**ft_split(char const *s, char c);
int		ft_gerer_zone(char **split, char *zone, int *n);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *str);
t_env	*ft_lstnew(void *key, void *val);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	ft_lstclear(t_env **lst, void (*del)(void *));
void	ft_lstiter(t_env *lst, void (*f)(void *, void *));
void	del_env_content(void *ptr);
void	ft_return_error(t_minishell *m, char *message, int status);
void	ft_exit_fail(t_minishell *m, char *message);
void	ft_exit_fail_status(t_minishell *m, char *message, int status);
void	ft_exit_error(t_minishell *m, char *message);
void	ft_exit_with_status(t_minishell *m, char *message, int status);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_with_char(char const *s1, char c, char const *s2);
char	*read_input(t_minishell *m, int fd);
char	**env_list_to_tab(t_minishell *m, t_env *env);

#endif