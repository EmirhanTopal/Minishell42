/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:30:58 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 21:25:26 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  int is_valid_identifier(const char *str)
{
	int	i = 0;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


void	builtin_export(t_parse *cmd, t_shell *shell)
{
	char	*arg_value;
	char	*arg_key;
	int		key_len;
	int		i;

	key_len = 0;
	i = 1;
    if (cmd->args[1] && cmd->args[2])
    {
        g_last_exit_status = 0;
        return ;
    }
	export_without_argument(cmd, shell);
	while (cmd->args[i])
	{
        if (!is_valid_identifier(cmd->args[i]))
        {
            write(2, " not a valid identifier", 23);
            g_last_exit_status = 1;
            i++;
            continue;
        }
		exp_eql_ptr_ctrl(cmd, &key_len, i, &arg_value);
		arg_key = ft_strndup(cmd->args[i], key_len);
		export_add_env(shell, arg_value, arg_key);
        free(arg_key);
		i++;
        g_last_exit_status = 0;
	}
}



