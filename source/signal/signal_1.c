/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:43:14 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 11:45:08 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_signal_cmd(int sig)
{
	(void)sig;
	ft_last_exit(130);
	exit(130);
}

static void	ft_signal_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ft_last_exit(130);
	exit(130);
}

static void	ft_handle_interrupt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	ft_last_exit(130);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_handler(int mode)
{
	signal(SIGQUIT, SIG_IGN);
	if (mode == 0)
	{
		signal(SIGINT, ft_handle_interrupt);
	}
	else if (mode == 1)
	{
		signal(SIGINT, ft_signal_heredoc);
	}
	else if (mode == 2)
	{
		signal(SIGQUIT, ft_signal_cmd);
		signal(SIGINT, ft_signal_cmd);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
	}
}
