/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:01:50 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/29 12:10:33 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void debug_pointer(void *p)
{
	printf("debug_pointer : begin\n");
	if (p == NULL)
			printf("p is null\n");
	else
	{
		printf("p is not null[%p]\n", p);
		/*if (*p == NULL)
			printf("*p is null[%p]\n", *p);
		else
			printf("*p is not null[%p]\n", *p);*/
	}
	printf("debug_pointer : end\n");
}

void debug_var(const char *s)
{
	ft_printf_fd(STDIN_FILENO, "[%s]\n", s);
}