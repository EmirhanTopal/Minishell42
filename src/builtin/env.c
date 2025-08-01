/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:30:22 by elduran           #+#    #+#             */
/*   Updated: 2025/07/25 00:11:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_env(t_parse *cmd, t_shell *shell)
{
    t_env *env;

    env = shell->shell_env;
    if (cmd->args[1] != NULL)
    {
        write(2, "env: ", 5);
        write(2, cmd->args[1], ft_strlen(cmd->args[1]));
        write(2, ": No such file or directory\n", 28);
        return;
    }
    while (env)
    {
        if (env->key == NULL)
            write(2, "Warning: env->key is NULL\n", 26);
        else
            printf("Key: '%s'\n", env->key);
        
        if (env->value == NULL)
            write(2, "Value: (null)\n", 14);
        else
            printf("Value: '%s'\n", env->value);

        if (env->value != NULL)
        {
            write(1, env->key, ft_strlen(env->key));
            write(1, "=", 1);
            write(1, env->value, ft_strlen(env->value));
            write(1, "\n", 1);
        }
        env = env->next;
    }
}

