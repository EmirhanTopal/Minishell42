/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:53:42 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 13:54:19 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*copy_env_lst(t_env *orj_env)
{
	t_env	*copy;
	t_env	*node;

	copy = NULL;
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

t_env	*sort_env_lst(t_env *orj_env)
{
	t_env	*tmp_head;
	t_env	*new_copy_env;
	int		flag;

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
				export_help(new_copy_env);
				flag = 1;
			}
			new_copy_env = new_copy_env->next;
		}
	}
	return (tmp_head);
}

void	print_env_export(t_env *env)
{
	while (env)
	{
		write(1, "declare -x ", 11);
		write(1, env->key, ft_strlen(env->key));
		if (env->value != NULL)
		{
			write(1, "=\"", 2);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\"", 2);
			write(1, "\n", 1);
		}		
		env = env->next;
	}
}
