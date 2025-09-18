/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_g_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:35:53 by ybouroga          #+#    #+#             */
/*   Updated: 2025/09/17 19:16:21 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_g_signal(t_minishell *m)
{
	if (g_signal)
	{
		g_signal &= ~SIG_FLAG;
		m->status_echo = 128 + SIGINT;
	}
	return (0);
}
