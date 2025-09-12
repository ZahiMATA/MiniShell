#include "minishell.h"
#include <stdlib.h>

static int	has_dollar(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	has_any_quote(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static int	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static char	*dup_range(const char *s, int a, int b)
{
	char	*res;
	int		k;

	if (b <= a)
		return (ft_strdup(""));
	res = (char *)malloc((b - a + 1) * sizeof(char));
	if (!res)
		return (NULL);
	k = 0;
	while (a < b)
		res[k++] = s[a++];
	res[k] = '\0';
	return (res);
}

static char	**split_ifs_words(const char *s)
{
	char	**tab;
	int		count;
	int		i;
	int		start;
	int		idx;

	if (!s)
		return (NULL);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && is_ifs(s[i]))
			i++;
		if (s[i])
			count++;
		while (s[i] && !is_ifs(s[i]))
			i++;
	}
	if (count <= 1)
		return (NULL);
	tab = (char **)malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] && is_ifs(s[i]))
			i++;
		start = i;
		while (s[i] && !is_ifs(s[i]))
			i++;
		if (i > start)
		{
			tab[idx] = dup_range(s, start, i);
			if (!tab[idx])
			{
				int	j;

				j = 0;
				while (j < idx)
				{
					free(tab[j]);
					j++;
				}
				free(tab);
				return (NULL);
			}
			idx++;
		}
	}
	tab[idx] = NULL;
	return (tab);
}

static void	free_strtab_container_only(char **t)
{
	if (t)
		free(t);
}

static int	inject_tokens(t_cmd *cmd, int i, char **tok)
{
	char	**old;
	char	**newv;
	int		argc;
	int		tk;
	int		j;
	int		k;
	int		out;

	argc = 0;
	while (cmd->args[argc])
		argc++;
	tk = 0;
	while (tok[tk])
		tk++;
	newv = (char **)malloc(sizeof(char *) * (argc - 1 + tk + 1));
	if (!newv)
		return (0);
	j = 0;
	while (j < i)
	{
		newv[j] = cmd->args[j];
		j++;
	}
	k = 0;
	while (k < tk)
	{
		newv[j + k] = tok[k];
		k++;
	}
	out = j + tk;
	k = i + 1;
	while (k < argc)
	{
		newv[out] = cmd->args[k];
		out++;
		k++;
	}
	newv[out] = NULL;
	old = cmd->args;
	free(old[i]);
	free(old);
	cmd->args = newv;
	return (1);
}

static void	ms_expand_argv_of_cmd(t_minishell *m, t_cmd *cmd)
{
	int		i;
	char	*orig;
	char	*neww;
	char	**split;
	int		did_inject;

	if (!cmd || !cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		orig = cmd->args[i];
		neww = ms_expand_word(m, orig);
		did_inject = 0;
		if (neww)
		{
			if (has_dollar(orig) && !has_any_quote(orig))
			{
				split = split_ifs_words(neww);
				if (split)
				{
					if (inject_tokens(cmd, i, split))
						did_inject = 1;
					free_strtab_container_only(split);
					free(neww);
				}
			}
			if (!did_inject)
			{
				free(cmd->args[i]);
				cmd->args[i] = neww;
			}
		}
		if (!did_inject)
			i++;
	}
}


void	ms_expand_all_cmds(t_minishell *m)
{
	t_cmd	*cur;

	cur = m->cmds;
	while (cur)
	{
		ms_expand_argv_of_cmd(m, cur);
		cur = cur->next;
	}
}
