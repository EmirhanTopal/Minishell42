/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:52:12 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 13:26:05 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env *shell_env)
{
	t_env	*tmp_env;

	while (shell_env)
	{
		tmp_env = shell_env->next;
		free(shell_env->key);
		free(shell_env->value);
		free(shell_env);
		shell_env = tmp_env;
	}
}

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		free(tokens->value);
		tokens = tokens->next;
		free(tmp);
	}
}

static void	ft_free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_free_parse(t_parse *parse)
{
	t_parse	*tmp;

	while (parse)
	{
		tmp = parse->next;
		if (parse->infile != STDIN_FILENO && parse->infile != -1)
			close(parse->infile);
		if (parse->outfile != STDOUT_FILENO && parse->outfile != -1)
			close(parse->outfile);
		ft_free_args(parse->args);
		free(parse);
		parse = tmp;
	}
}

void	ft_free_all(t_shell *shell, t_token *tokens, t_parse *cmd)
{
	ft_free_env(shell->shell_env);
	ft_free_tokens(tokens);
	ft_free_parse(cmd);
}
