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

void	 builtin_echo(char **args)
{
    int i = 1;
    int newline;

    newline = 1;
    if (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write(1, args[i], strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
}
