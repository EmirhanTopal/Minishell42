#include "minishell.h"

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
		key_len = equal_ptr - envp[i]; // aynı char* içerisinde byte farkını bularak uzunluk hesaplaması yapılabilir.
		node->key = ft_strndup(envp[i], key_len);
		node->value = ft_strdup(equal_ptr + 1);
		add_env_node_back(&head, node);
		i++;
	}
	return (head);
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

t_env	*copy_env_lst(t_env *orj_env)
{
	t_env *copy = NULL;
	t_env *node;

	while (orj_env)
	{
		node = malloc(sizeof(t_env));
		node->key = ft_strdup(orj_env->key);
		if (orj_env->value == NULL)
			node->value = NULL;
		else
			node->value = ft_strdup(orj_env->value);
		node->next = NULL;
		add_env_node_back(&copy, node);
		orj_env = orj_env->next;
	}
	return (copy);
}

static	t_env	*sort_env_lst(t_env *orj_env)
{
	t_env	*tmp_head;
	t_env	*new_copy_env;
	int		flag;
	char	*tmp_key;
	char	*tmp_value;

	tmp_head = copy_env_lst(orj_env);
	flag = 1;
	if (tmp_head == NULL)
		return (NULL);
	while (flag)
	{
		flag = 0;
		new_copy_env = tmp_head;
		while (new_copy_env && new_copy_env->next)
		{
			if (ft_strcmp(new_copy_env->key, new_copy_env->next->key) > 0)
			{
				tmp_key = new_copy_env->key;
				new_copy_env->key = new_copy_env->next->key;
				new_copy_env->next->key = tmp_key;
				
				tmp_value = new_copy_env->value;
				new_copy_env->value = new_copy_env->next->value;
				new_copy_env->next->value = tmp_value;
				flag = 1;
			}
			new_copy_env = new_copy_env->next;
		}	
	}
	return (tmp_head);
}

static	void	print_env_export(t_env *env)
{
	while (env)
	{
		write(1, "declare -x ", 11);
		write(1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\n", 1);
		env = env->next;
	}
}

void    builtin_export(t_command *cmd, t_shell *shell)
{
	if (cmd->argv[1] == NULL)
	{
		t_env *sorted = sort_env_lst(shell->shell_env);
		print_env_export(sorted);
	}
	
}
// void    builtin_unset(t_command *cmd)
// {

// }