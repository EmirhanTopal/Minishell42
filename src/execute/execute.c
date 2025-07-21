/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:41:43 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/22 00:14:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exc_null_path(t_parse *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	execute_not_builtin_command(t_parse *cmd, char **envp)
{
	char	*path;

	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		g_last_exit_status = 1;
		exit(g_last_exit_status);
	}
	if (cmd->args[0][0] == '/')
		path = ft_strdup(cmd->args[0]);
	else
		path = find_path(envp, cmd->args);
	if (path == NULL)
		exc_null_path(cmd);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		exit(0);
	if (execve(path, cmd->args, envp) == -1)
	{
		if (access(path, X_OK) != 0 && access(path, F_OK) == 0)
		{
			exit(0);
		}
		else if (access(path, F_OK) != 0)
		{
			exit(127);
		}
	}
}

void	execute_builtin_command(t_parse *cmd, t_shell *shell, char **envp)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		builtin_echo(cmd->args, envp);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd->args[0], "exit"))
		builtin_exit(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		builtin_cd(cmd);
	else if (!ft_strcmp(cmd->args[0], "env"))
		builtin_env(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "export"))
		builtin_export(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		builtin_unset(cmd, shell);
}
