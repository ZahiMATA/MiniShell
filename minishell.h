/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:27:44 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/04 11:20:23 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>


# ifndef DEBUG
#  define DEBUG 0
# endif
# define BUFFER_SIZE 1024
# define KO 0
# define OK 1
# define ERROR "Error"
# define ERROR_NOENV "Error : No environment"
# define ERROR_NOPATH "Error : No PATH"
# define ERROR_NOCOMS "Error : No commands"
# define ERROR_MALLOC "Error : Malloc failed"
# define ERROR_WRONGARGS "Error : Wrong arguments"
# define ERROR_NOFILE "Error : Source file does not exist"
# define ERROR_EXECVE "Error : Execve"
# define ERROR_ACCESS "Error : Access"
# define ERROR_FORK "Error : Fork"
# define ERROR_DUP2 "Error : Dup2"
# define ERROR_PIPE "Error : Pipe"
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
	int		status;
	int		fd_pipe[2];
	int		pid;
}	t_cmd;

// TODO QUI remplacera s_cmd qui est une liste chainee
typedef struct _s_cmd
{
	char	**args;
	char	*file_in; // gerer le free
	char	*file_out; // gerer le free
	int		append_mode;
	int		heredoc_mode;
	struct	s_cmd	*next;
}	t_cmd;

// TODO implementer init et l access et le free
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
	char	**path;
	//char	**env; // a eventuellent enlever car sera dans envlist
	t_env	*env_list;
	int		last_status; // pour echo $?
}	t_minishell;

void	px_free_all(t_pipex *p);
void	px_init_pipex(t_pipex **p, char **args, int nbcom, char **env);
void	px_execve(t_pipex *p);
void	px_show_args(t_pipex *p);
void	px_free_null(char	**ptr);
void	px_show_processes(t_pipex *p, char *message, char *cmd, int i);
void	px_show_error(char *message);
void	px_close_fds(t_pipex *p);
int		px_get_last_status(t_pipex*p);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd( char *s, int fd);
void	ft_putstr(char *s);
void	ft_putnbr_fd(int n, int fd);
void	ft_print_array(char **tab);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	**ft_split_multi(char const *s, char c[2]);
int		ft_gerer_zone(char **split, char *zone, int *n);
int		ft_strlen(const char *str);
void	ft_exit(char *message, t_pipex *p);
void	ft_exit_status(char *message, t_pipex *p, int status);
void	ft_return(char *message, t_pipex *p);
char	*ft_strdup(const char *s);
char	*ft_strjoin_with_char(char const *s1, char c, char const *s2);

#endif