#include "minishell.h"

t_env	*init_env(char **envp)
{
    t_env   *head = NULL;
	t_env	*node;
	char	*equal_ptr;
	int		key_len;
    int		i;

	key_len = 0;
	i = 0;
	while (envp[i])
	{
		node = malloc(sizeof(t_env));
		node->next = NULL;
		equal_ptr = ft_strchr(envp[i], '=');
		key_len = equal_ptr - envp[i];
		node->key = ft_strndup(envp[i], key_len);
		node->value = ft_strdup(equal_ptr + 1);
		add_env_node_back(&head, node);
		i++;
	}
	return (head);
}

void	add_env_node_back(t_env **head, t_env *node)
{
	t_env *temp = *head;
	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	else 
	{
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = node;
	}
}

void	free_env(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void    builtin_env(t_command *cmd, t_shell *shell)
{
    t_env *env;

	env = shell->shell_env;
    if (cmd->argv[1] != NULL)
    {
        write(2, "env: ", 5);
        write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
        write(2, ": No such file or directory", 27);
        return ;
    }
    while (env)
    {
        if (env->value != NULL)
        {
            write(1, env->key, ft_strlen(env->key));
            write(1, "=", 1);
            write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
        env = env->next;
    }
}
// void    builtin_export(t_command *cmd)
// {

// }
// void    builtin_unset(t_command *cmd)
// {

// }