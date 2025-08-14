/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:47:12 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 11:50:37 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lexer_process_token(char *input, int *i, t_token **head)
{
	int		type;
	char	*value;
	t_quote	quote_type;

	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		type = ft_handle_operator(input, i);
		value = ft_operator_value(type);
		if (!value)
			return (0);
		ft_add_token(head, ft_create_token(type, value, QUOTE_NONE));
		return (1);
	}
	value = ft_handle_word(input, i, &quote_type);
	if (!value)
		return (0);
	ft_add_token(head, ft_create_token(WORD, value, quote_type));
	return (1);
}

static void	ft_skip_whitespace(char *input, int *i)
{
	while (input[*i] && (
			input[*i] == ' '
			|| input[*i] == '\t'
			|| input[*i] == '\n'
			|| input[*i] == '\v'
			|| input[*i] == '\f'
			|| input[*i] == '\r'))
	{
		(*i)++;
	}
}

t_token	*ft_lexer(char *input)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (input[i])
	{
		ft_skip_whitespace(input, &i);
		if (!input[i])
			break ;
		if (!ft_lexer_process_token(input, &i, &head))
			return (NULL);
	}
	return (head);
}
