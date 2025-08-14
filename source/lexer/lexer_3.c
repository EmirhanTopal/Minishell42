/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:56:01 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:02:51 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_quoted_piece(const char *input,
	int *i, t_quote *current_quote)
{
	int		start;
	char	quote;
	char	*piece;

	quote = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	piece = ft_substr(input, start, *i - start);
	if (input[*i] == quote)
		(*i)++;
	if (quote == '\'')
		*current_quote = QUOTE_SINGLE;
	else
		*current_quote = QUOTE_DOUBLE;
	return (piece);
}

static char	*read_plain_piece(const char *input, int *i)
{
	int		start;
	char	*piece;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '|' && input[*i] != '<'
		&& input[*i] != '>')
		(*i)++;
	piece = ft_substr(input, start, *i - start);
	return (piece);
}

char	*ft_handle_word(char *input, int *i, t_quote *out_quote)
{
	char	*full;
	char	*piece;
	t_quote	current_quote;

	full = ft_calloc(1, 1);
	*out_quote = QUOTE_NONE;
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|'
		&& input[*i] != '<' && input[*i] != '>')
	{
		piece = NULL;
		current_quote = QUOTE_NONE;
		if (input[*i] == '\'' || input[*i] == '"')
			piece = read_quoted_piece(input, i, &current_quote);
		else
			piece = read_plain_piece(input, i);
		if (*out_quote == QUOTE_NONE)
			*out_quote = current_quote;
		else if (*out_quote == QUOTE_DOUBLE && current_quote == QUOTE_SINGLE)
			*out_quote = QUOTE_SINGLE;
		full = ft_strjoin_free(full, piece);
		free(piece);
	}
	return (full);
}
