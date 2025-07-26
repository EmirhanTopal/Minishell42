/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:35:39 by elduran           #+#    #+#             */
/*   Updated: 2025/07/24 22:52:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_append_exit_status(char **result, int *i, int exit_status)
{
	char	*status;

	(*i) += 2;
	status = ft_itoa(exit_status);
	if (!status)
		return ;
	*result = ft_strjoin_free(*result, status);
	free(status);
}

static void	ft_append_env_value(char **result, const char *str, int *i)
{
	int		start;
	char	*var;
	char	*val;

	start = ++(*i);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	if (start == *i)
	{
		*result = ft_strjoin_free(*result, "$");
		return ;
	}
	var = ft_substr(str, start, *i - start);
	if (!var)
		return ;
	val = getenv(var);
	if (val != NULL)
		*result = ft_strjoin_free(*result, val);
	free(var);
}

static void	ft_append_char(char **result, const char *str, int *i)
{
	char	buf[2];

	buf[0] = str[(*i)++];
	buf[1] = '\0';
	*result = ft_strjoin_free(*result, buf);
}

static char	*ft_expand_var(const char *str, int exit_status)
{
	char	*result;
	int		i;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				ft_append_exit_status(&result, &i, exit_status);
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				ft_append_env_value(&result, str, &i);
			else
				ft_append_char(&result, str, &i);
		}
		else
			ft_append_char(&result, str, &i);
	}
	return (result);
}

void	ft_expand_tokens(t_token *tokens)
{
	char	*expanded;
	int		exit_status;

	exit_status = g_last_exit_status;
	while (tokens)
	{
		if (tokens->type == WORD
			&& tokens->value
			&& (tokens->quote == QUOTE_NONE || tokens->quote == QUOTE_DOUBLE)
			&& ft_strchr(tokens->value, '$'))
		{
			expanded = ft_expand_var(tokens->value, exit_status);
			free(tokens->value);
			tokens->value = expanded;
		}
		tokens = tokens->next;
	}
}
