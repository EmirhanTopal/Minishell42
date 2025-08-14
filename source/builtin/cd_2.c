/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:16:44 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 13:17:40 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cd_err(char *msg)
{
	write(2, "cd: ", 4);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	ft_update_pwd_vars(char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		setenv("OLDPWD", oldpwd, 1);
		setenv("PWD", cwd, 1);
	}
}

void	ft_cd_go_env(char *var, t_shell *shell)
{
	char	*path;

	path = ft_get_env(var, shell);
	if (!path)
	{
		ft_print_cd_err("environment variable not set");
		ft_last_exit(1);
	}
	else if (chdir(path) == -1)
	{
		perror("cd");
		ft_last_exit(1);
	}
	else
		ft_update_pwd_vars(ft_get_env("PWD", shell));
}
