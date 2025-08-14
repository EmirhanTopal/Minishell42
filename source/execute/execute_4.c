/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:44:56 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:11:36 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_preflight_and_resolve_path(t_shell *shl,
	t_parse *cmd, t_token *tkns, t_parse *hd)
{
	char	*path;

	if (cmd->infile == -1 || cmd->outfile == -1)
	{
		ft_last_exit(1);
		ft_free_helper(cmd, shl, tkns);
		exit(ft_last_exit(-1));
	}
	if (!cmd->args || !cmd->args[0] || cmd->args[0][0] == '\0')
	{
		ft_free_helper(cmd, shl, tkns);
		exit(127);
	}
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		path = ft_strdup(cmd->args[0]);
	else
		path = ft_find_path(shl, cmd->args);
	if (!path)
		ft_exc_null_path(cmd, shl, tkns, hd);
	return (path);
}

static void	ft_check_path_or_die(char *path,
	t_shell *shl, t_parse *cmd, t_token *tkns)
{
	if (access(path, F_OK) == -1)
	{
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		free(path);
		ft_free_helper(cmd, shl, tkns);
		exit(127);
	}
}

static void	ft_exec_or_report(char *path,
	t_shell *shl, t_parse *cmd, t_token *tkns)
{
	if (execve(path, cmd->args, shl->envp) == -1)
	{
		if (errno == EISDIR)
		{
			write(2, path, ft_strlen(path));
			write(2, ": Is a directory\n", 18);
			free(path);
			ft_free_helper(cmd, shl, tkns);
			exit(126);
		}
		else if (errno == EACCES)
		{
			write(2, path, ft_strlen(path));
			write(2, ": Permission denied\n", 21);
			free(path);
			ft_free_helper(cmd, shl, tkns);
			exit(126);
		}
		else if (errno == ENOEXEC)
		{
			free(path);
			ft_free_helper(cmd, shl, tkns);
			exit(127);
		}
	}
}

static void	ft_exc_not_bt_cd(t_shell *shl,
	t_parse *cmd, t_token *tkns, t_parse *hd)
{
	char	*path;

	path = ft_preflight_and_resolve_path(shl, cmd, tkns, hd);
	ft_check_path_or_die(path, shl, cmd, tkns);
	ft_exec_or_report(path, shl, cmd, tkns);
	free(path);
}

void	ft_pipeline_execute(t_parse *tmp,
	t_shell *shell, t_token *tokens, t_parse *head)
{
	if (tmp->is_builtin)
		ft_execute_builtin_command(tmp, shell, tokens);
	else
		ft_exc_not_bt_cd(shell, tmp, tokens, head);
}
