/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:23:51 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 20:14:12 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_create_quoted_token(char quote_char, char *value)
{
	if (quote_char == '\'')
		return (ft_create_token(WORD, value, QUOTE_SINGLE));
	return (ft_create_token(WORD, value, QUOTE_DOUBLE));
}

int	ft_handle_quote(char *line, int *i, t_token **tokens)
{
	char	quote_char;
	int		start;
	char	*value;
	t_token	*new;

	quote_char = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	value = ft_substr(line, start, *i - start);
	if (!value)
		return (0);
	new = ft_create_quoted_token(quote_char, value);
	if (!new)
		return (free(value), 0);
	ft_add_token(tokens, new);
	if (line[*i])
		(*i)++;
	return (1);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*ft_handle_word(char *input, int *i)
{
	char	*full;
	char	*piece;
	int		start;
	char	quote;

	full = ft_calloc(1, 1);
	while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
	{
		piece = NULL;
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
		}
		else
		{
			start = *i;
			while (input[*i] && !ft_isspace(input[*i]) && input[*i] != '\'' && input[*i] != '"' && input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
				(*i)++;
			piece = ft_substr(input, start, *i - start);
		}
		full = ft_strjoin_free(full, piece);
		free(piece);
	}
	return (full);
}
