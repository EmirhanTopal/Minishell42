/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:34:08 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 13:18:54 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_env_node_back(t_env **head, t_env *node)
{
	t_env	*temp;

	temp = *head;
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

static	t_env	*ft_create_env_node(char *env_str)
{
	t_env	*node;
	char	*equal_ptr;
	int		key_len;

	equal_ptr = ft_strchr(env_str, '=');
	if (!equal_ptr)
		return (NULL);
	key_len = equal_ptr - env_str;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strndup(env_str, key_len);
	node->value = ft_strdup(equal_ptr + 1);
	node->next = NULL;
	return (node);
}

t_env	*ft_init_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		node = ft_create_env_node(envp[i]);
		if (node)
			ft_add_env_node_back(&head, node);
		i++;
	}
	return (head);
}

void	builtin_env(t_parse *cmd, t_shell *shell)
{
	t_env	*env;

	env = shell->shell_env;
	if (cmd->args[1] != NULL)
	{
		write(2, "env: ", 5);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": No such file or directory\n", 28);
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
