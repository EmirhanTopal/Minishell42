/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:51:42 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:03:03 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_token(int type, char *value, t_quote quote)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->quote = quote;
	token->next = NULL;
	return (token);
}

void	ft_add_token(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*ft_operator_value(int type)
{
	if (type == PIPE)
		return (ft_strdup("|"));
	if (type == GREAT)
		return (ft_strdup(">"));
	if (type == LESS)
		return (ft_strdup("<"));
	if (type == DOUBLE_GREAT)
		return (ft_strdup(">>"));
	if (type == DOUBLE_LESS)
		return (ft_strdup("<<"));
	return (NULL);
}

int	ft_handle_operator(char *input, int *i)
{
	if (input[*i] == '|' )
		return ((*i)++, PIPE);
	if (input[*i] == '>' && input[*i + 1] == '>')
		return ((*i += 2), DOUBLE_GREAT);
	if (input[*i] == '<' && input[*i + 1] == '<')
		return ((*i += 2), DOUBLE_LESS);
	if (input[*i] == '>')
		return ((*i)++, GREAT);
	if (input[*i] == '<')
		return ((*i)++, LESS);
	return (-1);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
