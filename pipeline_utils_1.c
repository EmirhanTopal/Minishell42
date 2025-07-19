/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:12:31 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 15:00:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_infile(t_command *tmp)
{
	if (tmp->infile)
	{
		tmp->fd_in = open(tmp->infile, O_RDONLY);
		if (tmp->fd_in != -1)
		{
			dup2(tmp->fd_in, STDIN_FILENO);
			close(tmp->fd_in);
		}
		else
		{
			perror(tmp->infile);
			g_last_exit_status = 1;
		}
	}
}

void	pipeline_out_app(t_command *tmp)
{
	if (tmp->outfile)
	{
		if (tmp->append)
			tmp->fd_out = open(tmp->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			tmp->fd_out = open(tmp->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (tmp->fd_out != -1)
		{
			dup2(tmp->fd_out, STDOUT_FILENO);
			close(tmp->fd_out);
		}
		else
		{
			perror(tmp->outfile);
			g_last_exit_status = 1;
		}
	}
}

static	int	heredoc_help(t_command *cmd, char *line, int hrdc_fd)
{
	if (line)
		free(line);
	line = readline("heredoc> ");
	if (line == NULL)
		return (1);
	if (!ft_strcmp(line, cmd->heredoc_delim))
		return (1);
	write(hrdc_fd, line, ft_strlen(line));
	write(hrdc_fd, "\n", 1);
	return (0);
}

void	pipeline_heredoc(t_command *cmd)
{
	char	*line;
	int		hrdc_fd;

	line = NULL;
	hrdc_fd = -1;
	if (cmd->heredoc_delim)
	{
		hrdc_fd = open("heredoc_test.txt", O_WRONLY | O_TRUNC | O_CREAT);
		while (1)
		{
			if (heredoc_help(cmd, line, hrdc_fd))
				break ;
		}
		close(hrdc_fd);
		hrdc_fd = open("heredoc_test.txt", O_RDONLY);
		if (hrdc_fd != -1)
		{
			dup2(hrdc_fd, STDIN_FILENO);
			close(hrdc_fd);
		}
	}
}

void	pipeline_in_out_app_hrdc(t_command *tmp)
{
	pipeline_heredoc(tmp);
	pipeline_infile(tmp);
	pipeline_out_app(tmp);
}
