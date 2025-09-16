/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:33:16 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/16 17:14:13 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define DOT2_SPACE ": "

void	ft_print_perror(char *message, char *pmessage)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s", MINISHELL, message);

	/*write(STDERR_FILENO, MINISHELL, ft_strlen(MINISHELL));
	write(STDERR_FILENO, DOT2_SPACE, ft_strlen(DOT2_SPACE));
	write(STDERR_FILENO, message, ft_strlen(message));*/
	if (pmessage)
	{
		//write(STDERR_FILENO, DOT2_SPACE, ft_strlen(DOT2_SPACE));
		ft_printf_fd(STDERR_FILENO, ": ");
		perror("");
	}
	else
		//write(STDERR_FILENO, "\n", 1);
		ft_printf_fd(STDERR_FILENO, "\n");
}

void	*ft_perror(char *mes1, char *mes2, char * mes3)
{
	if (mes1 == NULL /*|| *mes1 == 0*/)
		return (NULL);
	if (mes2 == NULL /*|| *mes2 == 0*/)
		ft_printf_fd(STDERR_FILENO, "%s\n", mes1);
	else if (mes3 == NULL /*|| *mes3 == 0*/)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", mes1, mes2);
	else if(ft_strcmp(mes3, PERROR) == 0)
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", mes1, mes2, strerror(errno));
	else
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", mes1, mes2, mes3);

	/*write(STDERR_FILENO, mes1, ft_strlen(mes1));
	write(STDERR_FILENO, DOT2_SPACE, ft_strlen(DOT2_SPACE));
	write(STDERR_FILENO, mes2, ft_strlen(mes2));
	write(STDERR_FILENO, "\n", 1);*/
	return (NULL);
}
