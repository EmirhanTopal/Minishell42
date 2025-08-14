/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:16:57 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 11:46:26 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parse_execute_clean(t_shell *shell, t_token *tokens)
{
	t_parse	*cmds;

	ft_expand_tokens(tokens, shell);
	cmds = ft_parser(tokens, shell);
	ft_execute_pipeline(cmds, shell, tokens);
	ft_free_tokens(tokens);
	ft_free_parse(cmds);
	free(shell->input);
}

static int	ft_incomplete_input_check(t_shell *shell, t_token **tokens)
{
	int	rc;

	rc = ft_handle_incomplete_input(&shell->input, tokens);
	if (rc <= 0)
		return (0);
	return (1);
}

static int	ft_lexer_and_validate(t_shell *shell, t_token **tokens)
{
	*tokens = ft_lexer(shell->input);
	if (!*tokens)
		return (0);
	if (ft_syntax_check(*tokens))
	{
		ft_free_tokens(*tokens);
		free(shell->input);
		return (0);
	}
	return (1);
}

static int	ft_read_line_step(t_shell *shell)
{
	shell->exit_code = ft_last_exit(-1);
	ft_signal_handler(0);
	shell->input = readline("minishell$ ");
	ft_signal_handler(4);
	if (!shell->input)
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (*shell->input)
		add_history(shell->input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_token	*tokens;

	(void)argc;
	(void)argv;
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	shell->shell_env = ft_init_env(envp);
	shell->envp = envp;
	while (1)
	{
		if (!ft_read_line_step(shell))
			break ;
		if (!ft_lexer_and_validate(shell, &tokens))
			continue ;
		if (!ft_incomplete_input_check(shell, &tokens))
			continue ;
		ft_parse_execute_clean(shell, tokens);
	}
	ft_free_env(shell->shell_env);
	free(shell);
	return (ft_last_exit(-1));
}
