/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:29:59 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 20:19:42 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **args, char **envp)
{
	int	i;
	int	ctrl;

	i = 1;
	(void)envp;
	ctrl = ft_strcmp(args[i], "-n");
	if (args[i] && !ctrl)
		i++;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (ctrl)
		write(1, "\n", 1);
}
