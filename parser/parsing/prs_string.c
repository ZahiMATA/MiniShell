/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouroga <ybouroga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:46:06 by ybouroga          #+#    #+#             */
/*   Updated: 2025/08/10 13:30:54 by ybouroga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// IN
// < Makefile tr a A | tr b B > ficout
// [1][<][6][Makefile]
// [6][tr][6][a][6][A]
// [0][|]
// [6][tr][6][b][6][B]
// [2][>]
// [6][ficout]
// OUT
// PIPE(
//  CMD(redir_in="Makefile", args=["tr", "a", "A"]),
//  CMD(args=["tr", "b", "B"],
//  redir_out="ficout"))

char	**prs_realloc_args(t_minishell *m, char **tab, int size, char *insert)
{
	char	**ret;
	char	*dup;
	int		i;

	ret = malloc(sizeof(char *) * (size + 2));
	if (ret == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	i = 0;
	while (tab && tab[i])
	{
		ret[i] = tab[i];
		i++;
	}
	free(tab);
	dup = ft_strdup(insert);
	if (dup == NULL)
		ft_exit_fail_status(m, NULL, EXIT_ALLOC_ERROR);
	ret[i] = dup;
	ret[i + 1] = NULL;
	return (ret);
}



