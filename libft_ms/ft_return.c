/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:46:27 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/21 11:46:49 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	ft_return_success(t_minishell *m, char *message)
{
	if (message)
		ft_putstr(message);
	else
		ft_putstr(MINISHELL);
	mem_free_all(m);
}

void	ft_return_error(t_minishell *m, char *message)
{
	if (message)
		ft_putstr(message);
	else
		perror(MINISHELL);
	mem_free_all(m);
}*/

void	ft_return_perror(t_minishell *m, char *message, int status)
{
	if (message)
		perror(message);
	else
		perror(MINISHELL);
	m -> last_status = status;
}

void	ft_return_error(t_minishell *m, char *message, int status)
{
	if (message)
		ft_print_error(message);
	else
		ft_putstr_nl(MINISHELL);
	m -> last_status = status;
}
