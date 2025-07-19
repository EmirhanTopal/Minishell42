/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:30:39 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 18:35:16 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_parse *cmd, t_shell *shell)
{
	if (cmd->args[1] && !is_numeric(cmd->args[1]))
	{
		write(2, "exit: ", 6);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, ": numeric argument required\n", 28);
		free_env(shell->shell_env);
		free(cmd);
		free(shell);
		exit(256);
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		write(2, "exit: too many arguments\n", 26);
		g_last_exit_status = 1;
		return ;
	}
	if (cmd->args[1])
		g_last_exit_status = ft_atoi(cmd->args[1]) % 256;
	write(1, "exit\n", 5);
	free_env(shell->shell_env);
	free(cmd);
	free(shell);
	exit((unsigned char)g_last_exit_status);
}
