/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:07:19 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 13:09:35 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	builtin_exit(t_parse *cmd, t_shell *shell, t_token *tokens)
{
	if (cmd->args[1] && cmd->args[2])
	{
		write(2, "exit: too many arguments\n", 31);
		ft_last_exit(1);
		ft_free_all(shell, tokens, cmd);
		exit(ft_last_exit(-1));
	}
	else if (cmd->args[1] && !ft_is_numeric(cmd->args[1]))
	{
		write(2, "exit: \n", 7);
		write(2, cmd->args[1], ft_strlen(cmd->args[1]));
		write(2, " exit: numeric argument required\n", 32);
		ft_free_all(shell, tokens, cmd);
		exit(2);
	}
	else if (cmd->args[1])
		ft_last_exit(ft_atoi(cmd->args[1]) % 256);
	write(1, "exit\n", 5);
	ft_free_all(shell, tokens, cmd);
	free(shell);
	exit(ft_last_exit(-1));
}
