/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:41:19 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 13:55:31 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipeline_infile(t_parse *tmp, t_shell *shell, t_token *tokens)
{
	if (tmp->infile == -1)
	{
		ft_last_exit(1);
		ft_free_all(shell, tokens, tmp);
		free(shell);
		exit(ft_last_exit(-1));
	}
	if (tmp->infile != STDIN_FILENO && tmp->infile != -1)
	{
		dup2(tmp->infile, STDIN_FILENO);
		close(tmp->infile);
		ft_last_exit(0);
	}
}

static void	ft_pipeline_out_app(t_parse *tmp, t_shell *shell, t_token *tokens)
{
	if (tmp->outfile == -1)
	{
		ft_last_exit(1);
		ft_free_all(shell, tokens, tmp);
		free(shell);
		exit(ft_last_exit(-1));
	}
	if (tmp->outfile != STDOUT_FILENO)
	{
		dup2(tmp->outfile, STDOUT_FILENO);
		close(tmp->outfile);
		ft_last_exit(0);
	}
}

static void	ft_pipeline_child_process(t_parse *tmp,
	t_shell *shell, t_token *tokens)
{
	ft_pipeline_infile(tmp, shell, tokens);
	ft_pipeline_out_app(tmp, shell, tokens);
}

static void	ft_pipeline_child_process_help(t_parse *tmp, int *fd, int prev_fd)
{
	if (prev_fd != -1 && tmp->infile == STDIN_FILENO)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
		ft_last_exit(0);
	}
	if (tmp->next)
	{
		if (tmp->outfile == STDOUT_FILENO)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

void	ft_child_exec(t_parse *tmp, int fd[2], int prev_fd, t_helper *h)
{
	if (!tmp->args || !tmp->args[0])
	{
		ft_free_all(h->shell, h->tokens, h->head);
		free(h->shell);
		exit(0);
	}
	ft_signal_handler(2);
	ft_pipeline_child_process(tmp, h->shell, h->tokens);
	ft_pipeline_child_process_help(tmp, fd, prev_fd);
	ft_pipeline_execute(tmp, h->shell, h->tokens, h->head);
	exit(ft_last_exit(-1));
}
