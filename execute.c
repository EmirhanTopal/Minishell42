/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:41:43 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 13:53:36 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	exc_child(t_command *cmd, char **envp, char *path)
{
	execve(path, cmd->argv, envp);
	perror("execve");
	free(path);
	exit(127);
}

static	void	exc_null_path(t_command *cmd)
{
	write(2, "minishell: ", 11);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	execute_not_builtin_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	if (cmd->argv[0][0] == '/')
		path = ft_strdup(cmd->argv[0]);
	else
		path = find_path(envp, cmd->argv);
	if (path == NULL)
		exc_null_path(cmd);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		exit(1);
	}
	else if (pid == 0)
		exc_child(cmd, envp, path);
	else
	{
		free(path);
		get_signal(pid);
	}
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
}

void	execute_builtin_command(t_command *cmd, t_shell *shell, char **envp)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		builtin_echo(cmd->argv, envp);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		builtin_exit(cmd, shell);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		builtin_cd(cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		builtin_env(cmd, shell);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		builtin_export(cmd, shell);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		builtin_unset(cmd, shell);
}
