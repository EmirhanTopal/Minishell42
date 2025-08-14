/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:37:26 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 13:37:27 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s1);
	i = 0;
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == 0)
	{
		return (0);
	}
	while (i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[len] = '\0';
	return (copy);
}
