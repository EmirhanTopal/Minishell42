/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:35:27 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 13:35:28 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redir_infile(t_parse *node, t_token *token)
{
	int	fd;

	fd = open(token->next->value, O_RDONLY);
	if (fd == -1)
	{
		perror(token->next->value);
		node->infile = -1;
	}
	else
	{
		if (node->infile != STDIN_FILENO)
			close(node->infile);
		node->infile = fd;
	}
}

static void	ft_redir_outfile_trunc(t_parse *node, t_token *token)
{
	int	fd;

	fd = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(token->next->value);
	else
	{
		if (node->outfile != STDOUT_FILENO)
			close(node->outfile);
		node->outfile = fd;
	}
}

static void	ft_redir_outfile_append(t_parse *node, t_token *token)
{
	int	fd;

	fd = open(token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		perror(token->next->value);
	else
	{
		if (node->outfile != STDOUT_FILENO)
			close(node->outfile);
		node->outfile = fd;
	}
}

static void	ft_handle_heredoc(t_parse *node, char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	node->infile = pipe_fd[0];
}

void	ft_handle_redirection(t_parse *node, t_token *token)
{
	if (!token || !token->next)
		return ;
	if (token->type == LESS)
		ft_redir_infile(node, token);
	else if (token->type == GREAT)
		ft_redir_outfile_trunc(node, token);
	else if (token->type == DOUBLE_GREAT)
		ft_redir_outfile_append(node, token);
	else if (token->type == DOUBLE_LESS && token->next)
		ft_handle_heredoc(node, token->next->value);
}
