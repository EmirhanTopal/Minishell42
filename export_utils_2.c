#include "minishell.h"

void	export_help(t_env *new_copy_env)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = new_copy_env->key;
	new_copy_env->key = new_copy_env->next->key;
	new_copy_env->next->key = tmp_key;
	tmp_value = new_copy_env->value;
	new_copy_env->value = new_copy_env->next->value;
	new_copy_env->next->value = tmp_value;
}

int	export_help_2(t_shell *shell, char *arg_key, char *arg_value)
{
	t_env	*tmp_head;

	tmp_head = shell->shell_env;
	while (tmp_head)
	{
		if (!ft_strcmp(tmp_head->key, arg_key))
		{
			if (arg_value != NULL)
			{
				free(tmp_head->value);
				tmp_head->value = arg_value;
			}
			return (1);
		}
		tmp_head = tmp_head->next;
	}
	return (0);
}

void	export_without_argument(t_command *cmd, t_shell *shell)
{
	if (cmd->argv[1] == NULL)
	{
		t_env *sorted = sort_env_lst(shell->shell_env);
		print_env_export(sorted);
		free_env(sorted);
	}
}

void	export_add_env(t_shell *shell, char *arg_value, char *arg_key)
{
	t_env	*node;

	if (!export_help_2(shell, arg_key, arg_value))
	{
		node = malloc(sizeof(t_env));
		node->key = arg_key;
		node->value = arg_value;
		node->next = NULL;
		add_env_node_back(&shell->shell_env, node);
	}
	else
		free(arg_key);
}

void	export_eql_ptr_ctrl(t_command *cmd, int *key_len, int i, char **arg_value)
{
	char	*arg_eql_ptr;

	arg_eql_ptr = ft_strchr(cmd->argv[i], '=');
	if (arg_eql_ptr != NULL)
	{
		(*key_len) = arg_eql_ptr - cmd->argv[i];
		(*arg_value) = ft_strdup(arg_eql_ptr + 1);
	}
	else
	{
		(*arg_value) = NULL;
		(*key_len) = ft_strlen(cmd->argv[i]);
	}
}
