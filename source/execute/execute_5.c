/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:48:18 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:11:22 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_path(char **paths, char *cmd)
{
	int		j;
	char	*full_path;
	char	*temp_path;

	j = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[j])
	{
		temp_path = ft_strjoin(paths[j], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!access(full_path, X_OK | F_OK))
			return (full_path);
		free(full_path);
		j++;
	}
	return (NULL);
}

char	*ft_find_path(t_shell *shell, char **cmd)
{
	char	**paths;
	char	*full_path;
	t_env	*tmp_env;

	tmp_env = shell->shell_env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "PATH"))
		{
			paths = ft_split(tmp_env->value, ':');
			full_path = ft_check_path(paths, cmd[0]);
			ft_db_free(paths);
			if (!full_path)
				return (NULL);
			return (full_path);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	ft_exc_null_path(t_parse *cmd,
	t_shell *shell, t_token *tokens, t_parse *head)
{
	if (cmd->args && cmd->args[0])
	{
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 21);
	}
	ft_free_env(shell->shell_env);
	ft_free_tokens(tokens);
	ft_free_parse(head);
	free(shell->input);
	free(shell);
	exit(127);
}
