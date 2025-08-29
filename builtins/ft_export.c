#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_valid_export_key(const char *str)
{
	int i = 0;

	if (!str || (!((str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z') || str[0] == '_')))
		return 0;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') ||
				(str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
			return 0;
		i++;
	}
	return 1;
}

t_env *find_env_var(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
			return env_list;
		env_list = env_list->next;
	}
	return NULL;
}

void add_or_update_env_var(t_env **env_list, const char *key, const char *value)
{
	t_env *var = find_env_var(*env_list, key);

	if (var)
	{
		free(var->val);
		if (value)
			var->val = strdup(value);
		else
			var->val = NULL;
	}
	else
	{
		t_env *new_node = malloc(sizeof(t_env));
		if (!new_node)
			return; // tu peux aussi gérer une erreur ici
		new_node->key = strdup(key);
		if (value)
			new_node->val = strdup(value);
		else
			new_node->val = NULL;
		new_node->next = *env_list;
		debug_var(key);
		debug_var(value);
		*env_list = new_node;
	}
}

//affiche si pas arg
void print_export_env(t_env *env_list)
{
	while (env_list) {
		ft_putstr("declare -x ");
		ft_putstr(env_list->key);
		if (env_list->val)
		{
			ft_putstr("=\"");
			ft_putstr(env_list->val);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		env_list = env_list->next;
	}
}

int ft_export(char **args, t_env **env_list)
{
	int i = 1;

	if (!args[1])
	{
		print_export_env(*env_list);
		return 0;
	}

	while (args[i])
	{
		if (!is_valid_export_key(args[i]))
		{
			ft_putstr("export: not a valid identifier: ");
			ft_putstr(args[i]);
			ft_putstr("\n");
		} else
		{
			char *equal_sign = strchr(args[i], '=');
			if (equal_sign)
			{
				*equal_sign = '\0';
				add_or_update_env_var(env_list, args[i], equal_sign + 1);
				*equal_sign = '=';
			} else
			{
				add_or_update_env_var(env_list, args[i], NULL);
			}
		}
		i++;
	}
	return 0;
}
