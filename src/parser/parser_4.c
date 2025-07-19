/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:35:33 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 16:27:04 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

static t_parse	*ft_create_parse_node(void)
{
	t_parse	*node;

	node = malloc(sizeof(t_parse));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
	node->type = 0;
	node->next = NULL;
	return (node);
}

static void	ft_process_redirections(t_parse *node, t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == LESS || tokens->type == GREAT
			|| tokens->type == DOUBLE_GREAT || tokens->type == DOUBLE_LESS)
			ft_handle_redirection(node, tokens);
		tokens = tokens->next;
	}
}

static t_token	*ft_advance_to_next_cmd(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens && tokens->type == PIPE)
		tokens = tokens->next;
	return (tokens);
}

t_parse	*ft_parser(t_token *tokens)
{
	t_parse	*head;
	t_parse	*current;
	t_parse	*node;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		node = ft_create_parse_node();
		if (!node)
			return (NULL);
		ft_process_redirections(node, tokens);
		node->args = ft_collect_args(tokens);
		if (node->args && node->args[0] && ft_is_builtin(node->args[0]))
			node->is_builtin = 1;
		else
			node->is_builtin = 0;
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
		tokens = ft_advance_to_next_cmd(tokens);
	}
	return (head);
}
