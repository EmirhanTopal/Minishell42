/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:48:07 by elduran           #+#    #+#             */
/*   Updated: 2025/07/19 13:48:08 by elduran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char	c_char;

	c_char = (char)c;
	while (*s != '\0')
	{
		if (*s == c_char)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c_char == '\0')
	{
		return ((char *)s);
	}
	return (0);
}
