/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:12:31 by emtopal           #+#    #+#             */
/*   Updated: 2025/07/21 22:02:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_infile(t_parse *tmp)
{
    if (tmp->infile == -1)
    {
        g_last_exit_status = 1;
        exit(g_last_exit_status);
    }
	if (tmp->infile != STDIN_FILENO && tmp->infile != -1)
	{
		dup2(tmp->infile, STDIN_FILENO);
		close(tmp->infile);
        g_last_exit_status = 0;
	}
}

void	pipeline_out_app(t_parse *tmp)
{
    if (tmp->outfile == -1)
    {
        g_last_exit_status = 1;
        exit(g_last_exit_status);
    }
	if (tmp->outfile != STDOUT_FILENO) 
	{
		dup2(tmp->outfile, STDOUT_FILENO);
		close(tmp->outfile);
        g_last_exit_status = 0;
	}
}
