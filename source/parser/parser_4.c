/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:47:22 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:49:01 by elduran          ###   ########.fr       */
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

static int	ft_count_args(t_token *tokens)
{
	int		count;
	t_token	*prev;

	count = 0;
	prev = NULL;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD && (!prev || (prev->type
					!= LESS && prev->type != GREAT && prev->type
					!= DOUBLE_LESS && prev->type != DOUBLE_GREAT)))
			count++;
		prev = tokens;
		tokens = tokens->next;
	}
	return (count);
}

char	**ft_collect_args(t_token *tokens)
{
	int		count;
	char	**args;
	int		i;
	t_token	*prev;

	i = 0;
	prev = NULL;
	count = ft_count_args(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD
			&& (tokens->value[0] != '\0' || tokens->quote != QUOTE_NONE)
			&& (!prev || (prev->type != LESS && prev->type != GREAT
					&& prev->type != DOUBLE_LESS
					&& prev->type != DOUBLE_GREAT)))
			args[i++] = ft_strdup(tokens->value);
		prev = tokens;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}
