/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:35:44 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:12:13 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_key_free(t_env *tmp_env)
{
	free(tmp_env->key);
	if (tmp_env->value != NULL)
		free(tmp_env->value);
	free(tmp_env);
}

void	builtin_unset(t_parse *cmd, t_shell *shell)
{
	t_env	*tmp_env;
	t_env	*node;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		node = NULL;
		tmp_env = shell->shell_env;
		while (tmp_env)
		{
			if (!ft_strcmp(cmd->args[i], tmp_env->key))
			{
				if (node == NULL)
					shell->shell_env = tmp_env->next;
				else
					node->next = tmp_env->next;
				ft_unset_key_free(tmp_env);
				break ;
			}
			node = tmp_env;
			tmp_env = tmp_env->next;
		}
		i++;
	}
}
