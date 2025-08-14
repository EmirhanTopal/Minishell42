/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:25:04 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 12:25:10 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_append_exit_status(char **result, int *i, int exit_status)
{
	char	*status;

	(*i) += 2;
	status = ft_itoa(exit_status);
	if (!status)
		return ;
	*result = ft_strjoin_free(*result, status);
	free(status);
}

static char	*ft_env_get(t_env *env, const char *key)
{
	t_env	*cur;
	size_t	klen;

	if (!env || !key)
		return (NULL);
	klen = ft_strlen(key);
	cur = env;
	while (cur)
	{
		if (cur->key && ft_strlen(cur->key) == klen
			&& ft_strncmp(cur->key, key, klen) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

static void	ft_append_env_value(char **result, const char *str,
	int *i, t_shell *shell)
{
	int		start;
	char	*var;
	char	*val;
	t_env	*tmp_env;

	start = ++(*i);
	tmp_env = shell->shell_env;
	val = NULL;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	if (start == *i)
	{
		*result = ft_strjoin_free(*result, "$");
		return ;
	}
	var = ft_substr(str, start, *i - start);
	if (!var)
		return ;
	val = ft_env_get(shell->shell_env, var);
	if (val != NULL)
		*result = ft_strjoin_free(*result, val);
	free(var);
}

static void	ft_append_char(char **result, const char *str, int *i)
{
	char	buf[2];

	buf[0] = str[(*i)++];
	buf[1] = '\0';
	*result = ft_strjoin_free(*result, buf);
}

char	*ft_expand_var(const char *str, int exit_status, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_calloc(1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				ft_append_exit_status(&result, &i, exit_status);
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				ft_append_env_value(&result, str, &i, shell);
			else
				ft_append_char(&result, str, &i);
		}
		else
			ft_append_char(&result, str, &i);
	}
	return (result);
}
