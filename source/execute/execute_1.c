/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:57:16 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:01:31 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_single_parent_builtin(t_parse *cmd)
{
	if (!cmd || cmd->next || !cmd->is_builtin || !cmd->args || !cmd->args[0])
		return (0);
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "export"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (1);
	return (0);
}

void	ft_execute_builtin_command(t_parse *cmd, t_shell *shell, t_token *tkns)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
	{
		builtin_echo(cmd->args);
		ft_free_helper(cmd, shell, tkns);
	}
	else if (!ft_strcmp(cmd->args[0], "pwd"))
	{
		builtin_pwd();
		ft_free_helper(cmd, shell, tkns);
	}
	else if (!ft_strcmp(cmd->args[0], "exit"))
		builtin_exit(cmd, shell, tkns);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		builtin_cd(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "env"))
	{
		builtin_env(cmd, shell);
		ft_free_helper(cmd, shell, tkns);
	}
	else if (!ft_strcmp(cmd->args[0], "export"))
		builtin_export(cmd, shell);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		builtin_unset(cmd, shell);
}

static void	ft_update_exit_status_from_wait(int wstatus)
{
	int	sig;

	if (WIFEXITED(wstatus))
	{
		ft_last_exit(WEXITSTATUS(wstatus));
	}
	else if (WIFSIGNALED(wstatus))
	{
		sig = WTERMSIG(wstatus);
		ft_last_exit(128 + sig);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 20);
	}
}

static void	ft_wait_and_update(pid_t last_pid)
{
	int		status;
	pid_t	wpid;

	if (ft_last_exit(-1) == 130)
		write(1, "\n", 1);
	while (1)
	{
		wpid = wait(&status);
		if (wpid == -1)
		{
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (wpid == last_pid)
			ft_update_exit_status_from_wait(status);
	}
}

void	ft_execute_pipeline(t_parse *cmd, t_shell *shell, t_token *tokens)
{
	t_helper	h;
	t_parse		*tmp;
	pid_t		last_pid;
	int			prev_fd;

	h.shell = shell;
	h.tokens = tokens;
	h.head = cmd;
	tmp = cmd;
	prev_fd = -1;
	if (ft_is_single_parent_builtin(cmd))
	{
		ft_execute_builtin_command(cmd, shell, tokens);
		return ;
	}
	while (tmp)
		ft_one_step(&tmp, &prev_fd, &h, &last_pid);
	if (prev_fd != -1)
		close(prev_fd);
	ft_wait_and_update(last_pid);
}
