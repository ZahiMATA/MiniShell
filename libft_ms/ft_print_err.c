/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:33:16 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 19:11:38 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_perror(char *mes1, char *mes2, char *mes3)
{
	if (mes1 == NULL)
		return (NULL);
	if (mes2 == NULL)
		ft_printf_fd(STDERR_FILENO, "%s\n", mes1);
	else if (mes3 == NULL)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", mes1, mes2);
	else if (ft_strcmp(mes3, PERROR) == 0)
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", mes1, mes2, strerror(errno));
	else
		ft_printf_fd(STDERR_FILENO, "%s: %s: %s\n", mes1, mes2, mes3);
	return (NULL);
}
