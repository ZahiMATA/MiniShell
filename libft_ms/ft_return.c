/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:46:27 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/27 11:07:31 by ybouroga         ###   ########.fr       */
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

void	ft_return_error(t_minishell *m, char *mes1, char *mes2, int status)
{
	if (mes1)
		ft_print_error(mes1, mes2);
	else
		ft_putstr_nl(MINISHELL); // TODO Voir si utile
	m -> last_status = status;
}
