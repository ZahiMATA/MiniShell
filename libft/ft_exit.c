/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:30:19 by ybouroga          #+#    #+#             */
/*   Updated: 2025/07/10 16:01:17 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>

void	ft_return(char *message, t_pipex *p)
{
	ft_putstr(message);
	px_free_all(p);
}

void	ft_exit(char *message, t_pipex *p)
{
	ft_exit_status(message, p, EXIT_FAILURE);
}

void	ft_exit_status(char *message, t_pipex *p, int status)
{
	ft_return(message, p);
	exit(status);
}
