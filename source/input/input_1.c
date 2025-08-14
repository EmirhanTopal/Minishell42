/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:10:32 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:18:23 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_has_unclosed_quote(const char *s)
{
	int	sq;
	int	dq;
	int	i;

	sq = 0;
	dq = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' && dq == 0)
			sq = !sq;
		else if (s[i] == '\"' && sq == 0)
			dq = !dq;
		i++;
	}
	return (sq || dq);
}

static int	ft_pipeline_ends_with_pipe(t_token *t)
{
	t_token	*last;

	last = NULL;
	while (t)
	{
		last = t;
		t = t->next;
	}
	return (last && last->type == PIPE);
}

static int	ft_free_and_return(char **input, t_token **tokens, int ret)
{
	ft_free_tokens(*tokens);
	*tokens = NULL;
	free(*input);
	*input = NULL;
	return (ret);
}

static char	*ft_join_with_newline(char *input, const char *more)
{
	char	*tmp;
	char	*out;

	tmp = ft_strjoin_free(input, "\n");
	if (!tmp)
		return (NULL);
	out = ft_strjoin_free(tmp, (char *)more);
	return (out);
}

int	ft_handle_incomplete_input(char **input, t_token **tokens)
{
	char	*more;
	char	*joined;

	if (!input || !*input || !tokens)
		return (-1);
	while (ft_has_unclosed_quote(*input)
		|| (*tokens && ft_pipeline_ends_with_pipe(*tokens)))
	{
		more = readline("> ");
		if (!more)
			return (ft_free_and_return(input, tokens, 0));
		joined = ft_join_with_newline(*input, more);
		free(more);
		if (!joined)
			return (ft_free_and_return(input, tokens, -1));
		ft_free_tokens(*tokens);
		*tokens = NULL;
		*input = joined;
		*tokens = ft_lexer(*input);
		if (!*tokens)
			return (ft_free_and_return(input, tokens, -1));
	}
	return (1);
}
