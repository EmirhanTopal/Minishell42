/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:38:02 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:11:47 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipeline_error(void)
{
	perror("fork");
	exit(1);
}

static void	ft_pipeline_parent_process(t_parse *tmp, int *fd, int *prev_fd)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (tmp->next)
	{
		*prev_fd = fd[0];
		close(fd[1]);
	}
}

void	ft_one_step(t_parse **tmp, int *prev_fd, t_helper *h, pid_t *last_pid)
{
	int		fd[2];
	pid_t	pid;

	if ((*tmp)->next && pipe(fd) == -1)
	{
		ft_pipeline_error();
		return ;
	}
	pid = fork();
	if ((*tmp)->next == NULL)
		*last_pid = pid;
	if (pid == 0)
		ft_child_exec(*tmp, fd, *prev_fd, h);
	else if (pid < 0)
		ft_pipeline_error();
	else
		ft_pipeline_parent_process(*tmp, fd, prev_fd);
	*tmp = (*tmp)->next;
}
