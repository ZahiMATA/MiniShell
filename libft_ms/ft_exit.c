/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:30:19 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/02 16:02:39 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_with_status(t_minishell *m, char *message, int status)
{
	if (message)
		ft_putstr_nl(message);
	else
		ft_putstr_nl(MINISHELL);
	mem_free_all(m);
	exit(status);
}

void	ft_exit_fail(t_minishell *m, char *message)
{
	ft_exit_fail_status(m, message, EXIT_FAILURE);
}

void	ft_exit_fail_status(t_minishell *m, char *message, int status)
{
	if (message)
		perror(message);
	else
		perror(MINISHELL);
	mem_free_all(m);
	exit(status);
}

void	ft_exit_perror(t_minishell *m, char *message)
{
	int status;

	if (message)
		perror(message);
	else
		perror(MINISHELL);
	status = EXIT_FAILURE;
	if (errno == ENOENT)
		status = EXIT_COMMAND_NOT_FOUND;
	else if (errno == EACCES)
		status = EXIT_PERMISSION_DENIED;
	mem_free_all(m);
	//printf("[%d]\n", status); // TODO a supprimer
	exit(status);
}

void	ft_exit_error(t_minishell *m, char *mes1, char *mes2, int status)
{

	ft_perror(mes1, mes2, NULL);
	//exit(EXIT_COMMAND_NOT_FOUND);
	mem_free_all(m);
	//printf("[%d]\n", status); // TODO a supprimer
	exit(status);
}

void	ft_exit_err(t_minishell *m, int status, void *nop)
{
	(void)nop;
	//ft_print_error(err.mes1, err.mes2, err.mes3);
	//exit(EXIT_COMMAND_NOT_FOUND);
	mem_free_all(m);
	exit(status);
}
