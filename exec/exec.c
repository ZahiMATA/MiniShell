/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:27:33 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/10 16:01:38 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @CDOCS pipex
 * @DESC ./pipex file1 cmd1 cmd2 file2 simulates < file1 cmd1 | cmd2 >
 * @PARAMS file cmd1 cmd2 files
 * RETURNS < file1 cmd1 | cmd2 >
 * @IN f_in "grep Jun" "tr Jun May" f_out
 * @OUT Put in f_out the text Jun turn in May
 *
 *
 */

#include "pipex.h"
#include <unistd.h>

int	exec(char **args, int nbcom, char **env)
{
	t_pipex	*p;
	int		ret;

	px_init_pipex(&p, args, nbcom, env);
	px_execve(p);
	ret = px_get_last_status(p);
	px_free_all(p);
	return (ret);
}
/*
int	main(int argc, char *argv[], char *env[])
{
	if (argc == 5)
		return (pipex(argv, argc - NB_NOT_ARG, env));
	else
		return (ft_return(ERROR_WRONGARGS, NULL), EXIT_FAILURE);
}
*/
