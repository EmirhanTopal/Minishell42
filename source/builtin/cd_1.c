/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:10:05 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:18:16 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char *var, t_shell *shell)
{
	t_env	*tmp_env;
	char	*val;

	val = NULL;
	tmp_env = shell->shell_env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, var) == 0)
		{
			val = tmp_env->value;
		}
		tmp_env = tmp_env->next;
	}
	return (val);
}

static	void	ft_cd_help(t_parse *cmd)
{
	write(2, "cd: ", 4);
	write(2, cmd->args[1], ft_strlen(cmd->args[1]));
	write(2, ": No such file or directory\n", 29);
	ft_last_exit(1);
}

void	builtin_cd(t_parse *cmd, t_shell *shell)
{
	char	*oldpwd;

	oldpwd = NULL;
	oldpwd = ft_get_env("OLDPWD", shell);
	if (cmd->args[1] && cmd->args[2])
	{
		ft_print_cd_err("too many arguments");
		ft_last_exit(1);
	}
	else if (!cmd->args[1] || !ft_strcmp(cmd->args[1], "~"))
		ft_cd_go_env("HOME", shell);
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		ft_cd_go_env("OLDPWD", shell);
		if (oldpwd)
		{
			write(1, oldpwd, ft_strlen(oldpwd));
			write(1, "\n", 1);
		}
	}
	else if (chdir(cmd->args[1]) == -1)
		ft_cd_help(cmd);
	else
		ft_update_pwd_vars(oldpwd);
}
