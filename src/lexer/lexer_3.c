/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:34:15 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 20:12:36 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lexer_process_token(char *input, int *i, t_token **head)
{
	int		type;
	char	*value;

	if (input[*i] == '\'' || input[*i] == '"')
		return (ft_handle_quote(input, i, head));
	if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
	{
		type = ft_handle_operator(input, i);
		value = ft_operator_value(type);
		if (!value)
			return (0);
		ft_add_token(head, ft_create_token(type, value, QUOTE_NONE));
		return (1);
	}
	value = ft_handle_word(input, i);
	if (!value)
		return (0);
	ft_add_token(head, ft_create_token(WORD, value, QUOTE_NONE));
	return (1);
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
