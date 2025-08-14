/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:26:37 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:53:37 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_process_redirections(t_parse *node,
	t_token *tokens, t_shell *shell)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == DOUBLE_LESS || tokens->type == DOUBLE_GREAT
			|| tokens->type == LESS || tokens->type == GREAT)
			ft_handle_redirection(node, tokens, shell);
		tokens = tokens->next;
	}
}

static int	ft_process_node(t_parse *node, t_token *tokens, t_shell *shell)
{
	ft_process_redirections(node, tokens, shell);
	node->args = ft_collect_args(tokens);
	if (!node->args)
		return (0);
	node->is_builtin = (node->args[0] && ft_is_builtin(node->args[0]));
	return (1);
}

static t_token	*ft_advance_to_next_cmd(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens && tokens->type == PIPE)
		tokens = tokens->next;
	return (tokens);
}

t_parse	*ft_parser(t_token *tokens, t_shell *shell)
{
	t_parse	*head;
	t_parse	*current;
	t_parse	*node;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		node = ft_create_parse_node();
		if (!node || !ft_process_node(node, tokens, shell))
		{
			ft_free_parse(head);
			free(node);
			return (NULL);
		}
		if (!head)
			head = node;
		else
			current->next = node;
		current = node;
		tokens = ft_advance_to_next_cmd(tokens);
	}
	return (head);
}
