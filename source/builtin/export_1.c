/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:19:52 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:22:02 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_helper_2(t_parse *cmd, int i)
{
	write(2, "export: '", 10);
	write(2, cmd->args[i], ft_strlen(cmd->args[i]));
	write(2, "': not a valid identifier\n", 27);
	ft_last_exit(1);
}

void	builtin_export(t_parse *cmd, t_shell *shell)
{
	char	*arg_v;
	char	*arg_key;
	int		key_len;
	int		i;

	key_len = 0;
	i = 1;
	if (ft_export_helper_1(cmd, shell))
		return ;
	while (cmd->args[i])
	{
		if (!ft_is_valid_identifier(cmd->args[i]))
		{
			ft_export_helper_2(cmd, i);
			i++;
			continue ;
		}
		ft_exp_eql_ptr_ctrl(cmd, &key_len, i, &arg_v);
		arg_key = ft_strndup(cmd->args[i], key_len);
		ft_export_add_env(shell, arg_v, arg_key);
		i++;
		ft_last_exit(0);
	}
}
