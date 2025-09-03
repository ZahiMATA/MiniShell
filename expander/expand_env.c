#include "minishell.h"

char	*ms_env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, (char *)key) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}
