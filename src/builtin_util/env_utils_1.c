/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:39:30 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 14:28:46 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node_back(t_env **head, t_env *node)
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

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	char	*equal_ptr;
	int		key_len;
	int		i;

	key_len = 0;
	i = 0;
	head = NULL;
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

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}
