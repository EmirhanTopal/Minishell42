/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:42:00 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:54:31 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_helper_1(t_parse *node,
	t_token *tokens, t_shell *shell, int pipe_fd[2])
{
	perror("fork");
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_free_all(shell, tokens, node);
	free(shell);
}

void	ft_heredoc_child(char *delimiter, int pipe_fd[2], t_helper *h)
{
	char	*line;

	line = NULL;
	ft_signal_handler(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	if (h->head->infile != STDIN_FILENO && h->head->infile != -1)
		close(h->head->infile);
	h->head->infile = pipe_fd[0];
	ft_free_all(h->shell, h->tokens, h->head);
	free(h->shell);
	exit(0);
}

void	ft_heredoc_helper_2(t_parse *node, int pipe_fd[2])
{
	close(pipe_fd[1]);
	if (node->infile != STDIN_FILENO)
		close(node->infile);
	node->infile = pipe_fd[0];
}
