/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:41 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:25:20 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_tokens(t_token *tokens, t_shell *shell)
{
	char	*expanded;
	int		exit_status;

	exit_status = shell->exit_code;
	while (tokens)
	{
		if (tokens->type == WORD
			&& tokens->value
			&& (tokens->quote == QUOTE_NONE || tokens->quote == QUOTE_DOUBLE)
			&& ft_strchr(tokens->value, '$'))
		{
			expanded = ft_expand_var(tokens->value, exit_status, shell);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
