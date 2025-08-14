/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:40:43 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 13:48:49 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_exit(int flag)
{
	static int	exit = 0;

	if (flag == -1)
		return (exit);
	exit = flag;
	return (exit);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

void	ft_free_helper(t_parse *cmd, t_shell *shell, t_token *tokens)
{
	ft_free_all(shell, tokens, cmd);
	free(shell->input);
	free(shell);
}

void	ft_db_free(char **double_pointer)
{
	int	i;

	i = 0;
	while (double_pointer[i])
	{
		free(double_pointer[i]);
		i++;
	}
	free(double_pointer);
}
