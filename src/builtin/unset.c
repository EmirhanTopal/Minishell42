/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:31:29 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 16:17:48 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_parse *cmd, t_shell *shell)
{
	t_env	*tmp_env;
	t_env	*node;
	int		i;

	i = 1;
	node = NULL;
	tmp_env = shell->shell_env;
	while (cmd->args[i])
	{
		while (tmp_env)
		{
			if (!ft_strcmp(cmd->args[i], tmp_env->key))
			{
				if (node == NULL)
					shell->shell_env = tmp_env->next;
				else
					node->next = tmp_env->next;
				unset_key_free(tmp_env);
				break ;
			}
			node = tmp_env;
			tmp_env = tmp_env->next;
		}
		i++;
	}
}
