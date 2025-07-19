/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:36:32 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 13:55:46 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_command *cmd, t_shell *shell)
{
	t_env	*env;

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

void	builtin_export(t_command *cmd, t_shell *shell)
{
	char	*arg_value;
	char	*arg_key;
	int		key_len;
	int		i;

	key_len = 0;
	i = 1;
	export_without_argument(cmd, shell);
	while (cmd->argv[i])
	{
		exp_eql_ptr_ctrl(cmd, &key_len, i, &arg_value);
		arg_key = ft_strndup(cmd->argv[i], key_len);
		export_add_env(shell, arg_value, arg_key);
		i++;
	}
	print_env_export(shell->shell_env);
}

void	builtin_unset(t_command *cmd, t_shell *shell)
{
	t_env	*tmp_env;
	t_env	*node;
	int		i;

	i = 1;
	node = NULL;
	tmp_env = shell->shell_env;
	while (cmd->argv[i])
	{
		while (tmp_env)
		{
			if (!ft_strcmp(cmd->argv[i], tmp_env->key))
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
