/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:13:22 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/01 17:55:54 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *mem_malloc(size_t size, const char *mes)
{
	void *p;

	p = malloc(size);
	if (p == NULL)
		return (NULL);
	if (DEBUG_MALLOC)
		ft_printf_fd(STDERR_FILENO, "MALLOC[%d][%s]\n", p, mes);
	return (p);
}
