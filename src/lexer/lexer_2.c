/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:23:51 by elduran           #+#    #+#             */
/*   Updated: 2025/07/21 21:45:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	ft_handle_quote(char *line, int *i, t_token **tokens)
{
	char	quote_char;
	int		start;
	char	*value;
	t_token	*new;
	t_quote	quote_type;

	quote_char = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (line[*i])
		(*i)++;
	if (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		while (line[*i] && !ft_isspace(line[*i])
			&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
			(*i)++;
	}
	value = ft_substr(line, start, *i - start - 1);
	if (!value)
		return (0);
	if (quote_char == '\'')
		quote_type = QUOTE_SINGLE;
	else
		quote_type = QUOTE_DOUBLE;
	new = ft_create_token(WORD, value, quote_type);
	if (!new)
		return (free(value), 0);
	ft_add_token(tokens, new);
	return (1);
}

char	*ft_handle_word(char *input, int *i, t_quote *out_quote)
{
	char	*full;
	char	*piece;
	int		start;
	char	quote;
	t_quote	current_quote;

	full = ft_calloc(1, 1);
	*out_quote = QUOTE_NONE;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		piece = NULL;
		current_quote = QUOTE_NONE;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			(*i)++;
			start = *i;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			piece = ft_substr(input, start, *i - start);
			if (input[*i] == quote)
				(*i)++;
			current_quote = (quote == '\'') ? QUOTE_SINGLE : QUOTE_DOUBLE;
		}
		else
		{
			start = *i;
			while (input[*i] && !ft_isspace(input[*i])
				&& input[*i] != '\'' && input[*i] != '"'
				&& input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
				(*i)++;
			piece = ft_substr(input, start, *i - start);
		}
		if (*out_quote == QUOTE_NONE)
			*out_quote = current_quote;
		else if (*out_quote == QUOTE_DOUBLE && current_quote == QUOTE_SINGLE)
			*out_quote = QUOTE_SINGLE;
		char *tmp = full;
		full = ft_strjoin(full, piece);
		free(tmp);
		free(piece);
	}
	return (full);
}



