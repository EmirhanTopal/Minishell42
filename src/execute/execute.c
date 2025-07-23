/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:41:43 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/23 23:52:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exc_null_path(t_parse *cmd)
{
	write(2, "bash: ", 6);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, ": command not found\n", 20);
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
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		path = ft_strdup(cmd->args[0]);
	else
		path = find_path(envp, cmd->args);
	if (!path)
		exc_null_path(cmd);
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
		exit(0);
	if (access(path, F_OK) == -1)
	{
		write(2, "bash: ", 6);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 27);
		exit(127);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		if (errno == EISDIR)
		{
			write(2, "bash: ", 6);
			write(2, path, ft_strlen(path));
			write(2, ": Is a directory\n", 17);
			exit(126);
		}
		else if (errno == EACCES)
		{
			write(2, "bash: ", 6);
			write(2, path, ft_strlen(path));
			write(2, ": Permission denied\n", 20);
			exit(126);
		}
		else if (errno == ENOEXEC)
		{
			exit(0);
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
