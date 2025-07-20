/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:30:03 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/20 18:27:47 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void pipeline_child_process(t_parse *tmp, int *fd, int prev_fd)
{
    pipeline_infile(tmp);
    pipeline_out_app(tmp);
    if (prev_fd != -1 && tmp->infile == STDIN_FILENO)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
        g_last_exit_status = 0;
    }
    if (tmp->next && tmp->outfile == STDOUT_FILENO)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
}


static	void	pipeline_parent_process(t_parse *tmp, int *fd, int *prev_fd)
{
	if ((*prev_fd) != -1)
		close((*prev_fd));
	if ((tmp->outfile != -1) && tmp->next)
	{
		(*prev_fd) = fd[0];
		close(fd[1]);
	}
}

static	void	pipeline_error(void)
{
	perror("fork");
	exit(1);
}

static	void	pipeline_execute(t_parse *tmp, t_shell *shell, char **envp)
{
	if (tmp->is_builtin)
		execute_builtin_command(tmp, shell, envp);
	else
		execute_not_builtin_command(tmp, envp);
}

void	execute_pipeline(t_parse *cmd, t_shell *shell, char **envp)
{
	int			fd[2];
	pid_t		pid;
	int			prev_fd;
	t_parse		*tmp;
	int			status;

	tmp = cmd;
	prev_fd = -1;
	while (tmp)
	{
		if (tmp->next)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			pipeline_child_process(tmp, fd, prev_fd);
			pipeline_execute(tmp, shell, envp);
			exit(g_last_exit_status);
		}
		else if (pid < 0)
			pipeline_error();
        else
		    pipeline_parent_process(tmp, fd, &prev_fd);
		tmp = tmp->next;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			g_last_exit_status = WEXITSTATUS(status);	
	}
}
