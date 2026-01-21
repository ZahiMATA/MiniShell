/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:01:50 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 14:47:10 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_pointer(void *p)
{
	printf("debug_pointer : begin\n");
	if (p == NULL)
		printf("p is null\n");
	else
	{
		printf("p is not null[%p]\n", p);
	}
	printf("debug_pointer : end\n");
}

void	debug_var(const char *s)
{
	ft_printf_fd(STDIN_FILENO, "[%s]\n", s);
}

void	debug_var_i(int i)
{
	ft_printf_fd(STDIN_FILENO, "[%d]\n", i);
}
