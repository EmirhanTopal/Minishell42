#include "minishell.h"

void	unset_key_free(t_env *tmp_env)
{
	free(tmp_env->key);
	if (tmp_env->value != NULL)
		free(tmp_env->value);
	free(tmp_env);
}