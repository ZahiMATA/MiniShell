/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:25:29 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/20 15:07:36 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red_t	prs_get_redir(t_token t)
{
	if (t == T_REDIRECT_LEFT)
		return (N_REDIR_LEFT);
	else if (t == T_REDIRECT_RIGHT)
		return (N_REDIR_RIGHT);
	else if (t == T_DOUBLE_REDIRECT_LEFT)
		return (N_DOUBLE_REDIR_LEFT);
	else
		return (N_DOUBLE_REDIR_RIGHT);
}