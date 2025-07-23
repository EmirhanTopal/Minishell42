/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:35:23 by elduran           #+#    #+#             */
/*   Updated: 2025/07/23 23:50:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

		if (tokens->type == WORD && tokens->value[0] != '\0' && (!prev || (prev->type
					!= LESS && prev->type != GREAT && prev->type
					!= DOUBLE_LESS && prev->type != DOUBLE_GREAT)))
			args[i++] = tokens->value;
		prev = tokens;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}
