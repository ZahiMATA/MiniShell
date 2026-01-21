/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:00:00 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/20 13:08:52 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

void	ft_putstr(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}

void	ft_putstr_nl(char *s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_print_array(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_putstr_nl(tab[i++]);
}
