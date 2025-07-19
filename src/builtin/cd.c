/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:29:28 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 18:29:01 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_parse *cmd)
{
	char	*oldpwd;

	oldpwd = getenv("PWD");
	if (cmd->args[1] && cmd->args[2])
	{
		print_cd_err("too many arguments");
		g_last_exit_status = 1;
	}
	else if (!cmd->args[1])
		cd_go_env("HOME");
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		cd_go_env("OLDPWD");
		if (getenv("OLDPWD"))
		{
			write(1, getenv("OLDPWD"), ft_strlen(getenv("OLDPWD")));
			write(1, "\n", 1);
		}
	}
	else if (chdir(cmd->args[1]) == -1)
	{
		print_cd_err("No such file or directory");
		g_last_exit_status = 1;
	}
	else
		update_pwd_vars(oldpwd);
}
