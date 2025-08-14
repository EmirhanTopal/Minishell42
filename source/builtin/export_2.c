/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:30:41 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:21:41 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_helper_1(t_parse *cmd, t_shell *shell)
{
	if (cmd->args[1] == NULL)
	{
		ft_export_without_argument(cmd, shell);
		return (1);
	}
	return (0);
}

int	ft_is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exp_eql_ptr_ctrl(t_parse *cmd, int *key_len, int i, char **arg_value)
{
	char	*arg_eql_ptr;

	arg_eql_ptr = ft_strchr(cmd->args[i], '=');
	if (arg_eql_ptr != NULL)
	{
		(*key_len) = arg_eql_ptr - cmd->args[i];
		(*arg_value) = ft_strdup(arg_eql_ptr + 1);
	}
	else
	{
		(*arg_value) = NULL;
		(*key_len) = ft_strlen(cmd->args[i]);
	}
}

static int	ft_export_help_2(t_shell *shell, char *arg_key, char *arg_value)
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
				tmp_head->value = ft_strdup(arg_value);
			}
			return (1);
		}
		tmp_head = tmp_head->next;
	}
	return (0);
}

void	ft_export_add_env(t_shell *shell, char *arg_value, char *arg_key)
{
	t_env	*node;

	if (!ft_export_help_2(shell, arg_key, arg_value))
	{
		node = malloc(sizeof(t_env));
		node->key = arg_key;
		node->value = arg_value;
		node->next = NULL;
		ft_add_env_node_back(&shell->shell_env, node);
	}
	else
		free(arg_key);
}
