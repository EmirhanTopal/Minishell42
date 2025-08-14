/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:30:25 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:12:09 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_copy_env_lst(t_env *orj_env)
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
		ft_add_env_node_back(&copy, node);
		orj_env = orj_env->next;
	}
	return (copy);
}

static void	ft_export_help_1(t_env *new_copy_env)
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

static t_env	*ft_sort_env_lst(t_env *orj_env)
{
	t_env	*tmp_head;
	t_env	*new_copy_env;
	int		flag;

	tmp_head = ft_copy_env_lst(orj_env);
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
				ft_export_help_1(new_copy_env);
				flag = 1;
			}
			new_copy_env = new_copy_env->next;
		}
	}
	return (tmp_head);
}

static void	ft_print_env_export(t_env *env)
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
		}
		write(1, "\n", 1);
		env = env->next;
	}
}

void	ft_export_without_argument(t_parse *cmd, t_shell *shell)
{
	t_env	*sorted;

	if (cmd->args[1] == NULL)
	{
		sorted = ft_sort_env_lst(shell->shell_env);
		ft_print_env_export(sorted);
		ft_free_env(sorted);
		ft_last_exit(0);
	}
}
