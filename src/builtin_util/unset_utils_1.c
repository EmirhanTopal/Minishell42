/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:22:51 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/19 14:22:54 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_key_free(t_env *tmp_env)
{
	free(tmp_env->key);
	if (tmp_env->value != NULL)
		free(tmp_env->value);
	free(tmp_env);
}
