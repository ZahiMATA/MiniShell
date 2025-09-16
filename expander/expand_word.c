#include "minishell.h"

static int	is_name_start(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

static int	is_name_char(char c)
{
	return (is_name_start(c) || (c >= '0' && c <= '9'));
}

static char	*append_char(char *dst, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = dst;
	dst = ft_strjoin(dst, buf);
	free(tmp);
	return (dst);
}

static char	*append_str(char *dst, const char *s)
{
	char	*tmp;

	if (!s)
		return (dst);
	tmp = dst;
	dst = ft_strjoin(dst, (char *)s);
	free(tmp);
	return (dst);
}

char	*ms_expand_word(t_minishell *m, const char *s, int x)
{
	int		in_s;
	int		in_d;
	int		i;
	int		handled;
	char	*out;

	in_s = 0;
	in_d = 0;
	i = 0;
	out = ft_strdup("");
	if (!s || !out)
		return (NULL);
	while (s[i])
	{
		handled = 0;
		if ((s[i] == '\\'  && x))
		{
			if (!in_s && s[i + 1])
			{
				if (in_d && (s[i + 1] == '$' || (s[i + 1] == '\"' && x)
						|| (s[i + 1] == '\\' && x) || s[i + 1] == '`'))
				{
					out = append_char(out, s[i + 1]);
					i += 2;
					handled = 1;
				}
				else if (!in_d)
				{
					out = append_char(out, s[i + 1]);
					i += 2;
					handled = 1;
				}
			}
			if (!handled)
			{
				out = append_char(out, s[i]);
				i++;
				handled = 1;
			}
		}
		else if (s[i] == '$' && (s[i + 1] == '\"' && x) && !in_s && !in_d)
		{
			in_d = 1;
			i += 2;
			handled = 1;
		}
		else if (s[i] == '$' && (s[i + 1] == '\"' && x) && !in_s && in_d)
		{
			out = append_char(out, '$');
			i += 1;
			handled = 1;
		}
		else if (s[i] == '$' && (s[i + 1] == '\'' && x) && !in_s && !in_d)
		{
			in_s = 1;
			i += 2;
			handled = 1;
		}
		else if ((s[i] == '\'' && x) && !in_d)
		{
			in_s = !in_s;
			i++;
			handled = 1;
		}
		else if ((s[i] == '\"' && x) && !in_s)
		{
			in_d = !in_d;
			i++;
			handled = 1;
		}
		else if (s[i] == '$' && !in_s)
		{
			if (s[i + 1] == '?')
			{
				char	*num;

				num = ft_itoa(m->last_status);
				out = append_str(out, num);
				free(num);
				i += 2;
				handled = 1;
			}
			else if (s[i + 1] == '0')
			{
				out = append_str(out, MINISHELL);
				i += 2;
				handled = 1;
			}
			else if (is_name_start(s[i + 1]))
			{
				int		j;
				char	*name;
				char	*val;

				j = i + 1;
				while (is_name_char(s[j]))
					j++;
				name = ft_substring(s, i + 1, j - (i + 1));
				val = ms_env_get(m->env_list, name);
				out = append_str(out, val);
				free(name);
				i = j;
				handled = 1;
			}
			else
			{
				out = append_char(out, '$');
				i++;
				handled = 1;
			}
		}
		if (!handled)
		{
			out = append_char(out, s[i]);
			i++;
		}
	}
	return (out);
}
