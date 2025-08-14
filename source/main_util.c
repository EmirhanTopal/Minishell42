/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:15:15 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:15:44 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_syntax_error(const char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	ft_last_exit(2);
	return (1);
}

static	int	ft_syntax_check_help(t_token *next)
{
	if (!next)
		return (ft_syntax_error("newline"));
	if (next->type == PIPE)
		return (ft_syntax_error("|"));
	if (next->type == GREAT)
		return (ft_syntax_error(">"));
	if (next->type == DOUBLE_GREAT)
		return (ft_syntax_error(">>"));
	if (next->type == LESS)
		return (ft_syntax_error("<"));
	if (next->type == DOUBLE_LESS)
		return (ft_syntax_error("<<"));
	return (0);
}

int	ft_syntax_check(t_token *t)
{
	t_token	*next;

	if (!t)
		return (0);
	if (t->type == PIPE)
		return (ft_syntax_error("|"));
	while (t)
	{
		next = t->next;
		if (t->type == PIPE && next && next->type == PIPE)
			return (ft_syntax_error("|"));
		if (t->type == GREAT || t->type == DOUBLE_GREAT
			|| t->type == LESS || t->type == DOUBLE_LESS)
		{
			if (ft_syntax_check_help(next))
				return (1);
		}
		t = next;
	}
	return (0);
}
