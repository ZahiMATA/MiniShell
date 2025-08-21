/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:33:16 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/21 13:26:07 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define DOT2_SPACE ": "

void	ft_print_error(char *message, char *pmessage)
{
	write(STDERR_FILENO, MINISHELL, ft_strlen(MINISHELL));
	write(STDERR_FILENO, DOT2_SPACE, ft_strlen(DOT2_SPACE));
	write(STDERR_FILENO, message, ft_strlen(message));
	if (pmessage)
	{
		write(STDERR_FILENO, DOT2_SPACE, ft_strlen(DOT2_SPACE));
		perror("");
	}
	else
		write(STDERR_FILENO, "\n", 1);
}
