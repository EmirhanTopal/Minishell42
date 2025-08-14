/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:36:34 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:41:23 by elduran          ###   ########.fr       */
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
		node->error_printed = 1;
		node->infile = -1;
		ft_last_exit(1);
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

	fd = open(token->next->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(token->next->value);
		node->outfile = -1;
		ft_last_exit(1);
	}
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
	{
		perror(token->next->value);
		node->outfile = -1;
		ft_last_exit(1);
	}
	else
	{
		if (node->outfile != STDOUT_FILENO)
			close(node->outfile);
		node->outfile = fd;
	}
}

static void	ft_handle_heredoc(t_parse *node, char *delimiter,
		t_token *tokens, t_shell *shell)
{
	int			pipe_fd[2];
	pid_t		pid;
	t_helper	h;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	h = (t_helper){shell, tokens, node};
	pid = fork();
	if (pid == -1)
	{
		ft_heredoc_helper_1(node, tokens, shell, pipe_fd);
		return ;
	}
	if (pid == 0)
		ft_heredoc_child(delimiter, pipe_fd, &h);
	waitpid(pid, NULL, 0);
	ft_heredoc_helper_2(node, pipe_fd);
}

void	ft_handle_redirection(t_parse *node, t_token *token, t_shell *shell)
{
	if (!token || !token->next)
		return ;
	if (node->infile == -1 || node->outfile == -1)
		return ;
	if (token->type == LESS)
	{
		ft_redir_infile(node, token);
	}
	else if (token->type == GREAT)
	{
		ft_redir_outfile_trunc(node, token);
	}
	else if (token->type == DOUBLE_GREAT)
	{
		ft_redir_outfile_append(node, token);
	}
	else if (token->type == DOUBLE_LESS && token->next)
	{
		ft_handle_heredoc(node, token->next->value, token, shell);
	}
}
