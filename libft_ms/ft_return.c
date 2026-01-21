/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:46:27 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 19:04:05 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_return_perror(t_minishell *m, char *message, int status)
{
	if (message)
		perror(message);
	else
		perror(MINISHELL);
	m ->last_status = status;
}

void	ft_return_error(t_minishell *m, char *mes1, char *mes2, int status)
{
	if (mes1)
		ft_perror(mes1, mes2, NULL);
	else
		ft_putstr_nl(MINISHELL);
	m -> last_status = status;
}

void	ft_return_err(t_minishell *m, int status, void *nop)
{
	(void)nop;
	m -> last_status = status;
}
