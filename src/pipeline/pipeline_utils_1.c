/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:12:31 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 17:50:26 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_infile(t_parse *tmp)
{
	if (tmp->infile != -1)
	{
		dup2(tmp->infile, STDIN_FILENO);
		close(tmp->infile);
	}
	else
	{
		g_last_exit_status = 1;
	}
}

void	pipeline_out_app(t_parse *tmp)
{
	if (tmp->outfile != -1)
	{
		dup2(tmp->outfile, STDOUT_FILENO);
		close(tmp->outfile);
	}
	else
	{
		g_last_exit_status = 1;
	}
}

static	int	heredoc_help(t_parse *cmd, char *line, int hrdc_fd)
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

void	pipeline_heredoc(t_parse *cmd)
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

void	pipeline_in_out_app_hrdc(t_parse *tmp)
{
	if (tmp->infile != -1)
		pipeline_infile(tmp);
	else if (tmp->outfile != -1)
		pipeline_out_app(tmp);
	else if (tmp->heredoc_delim != NULL)
		pipeline_heredoc(tmp);
	return ;
}
