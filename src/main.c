/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:38:16 by elduran           #+#    #+#             */
/*   Updated: 2025/07/20 17:45:07 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_parse	*cmds;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	shell->shell_env = init_env(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = ft_lexer(input);
		if (!tokens)
			continue ;
		ft_expand_tokens(tokens);
		cmds = ft_parser(tokens);
		execute_pipeline(cmds, shell, envp);
		ft_free_tokens(tokens);
		ft_free_parse(cmds);
		free(input);
	}
	return (g_last_exit_status);
}
