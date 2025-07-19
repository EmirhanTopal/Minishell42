/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:38:43 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 14:28:32 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd_err(char *msg)
{
	write(2, "cd: ", 4);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_last_exit_status = 1;
}

void	update_pwd_vars(char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		setenv("OLDPWD", oldpwd, 1);
		setenv("PWD", cwd, 1);
	}
}

void	cd_go_env(char *var)
{
	char	*path;

	path = getenv(var);
	if (!path)
		print_cd_err("environment variable not set");
	else if (chdir(path) == -1)
		perror("cd");
	else
		update_pwd_vars(getenv("PWD"));
}
