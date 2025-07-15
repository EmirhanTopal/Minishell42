#include "minishell.h"

void	pipeline_infile(t_command *tmp)
{
	if (tmp->infile)
	{
		tmp->fd_in = open(tmp->infile, O_RDONLY);
		if (tmp->fd_in != -1)
		{
			dup2(tmp->fd_in, STDIN_FILENO);
			close(tmp->fd_in);
		}
		else
		{
			perror(tmp->infile);
			g_last_exit_status = 1;
		}
	}
}

void	pipeline_out_app(t_command *tmp)
{
	if (tmp->outfile)
	{
		if (tmp->append)
			tmp->fd_out = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			tmp->fd_out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (tmp->fd_out != -1)
		{
			dup2(tmp->fd_out, STDOUT_FILENO);
			close(tmp->fd_out);
		}
		else
		{
			perror(tmp->outfile);
			g_last_exit_status = 1;
		}
	}
}

void    pipeline_heredoc(t_command *cmd)
{
    char    *line = NULL;
    int     hrdc_fd;

    hrdc_fd = -1;
    if (cmd->heredoc_delim)
    {
        hrdc_fd = open("heredoc_test.txt", O_WRONLY | O_TRUNC | O_CREAT);
        while (1)
        {
            if (line)
                free(line);
            line = readline("heredoc> ");
            if (line == NULL) // ctrl + D
                break;
            if (!ft_strcmp(line, cmd->heredoc_delim))
                break;
            write(hrdc_fd, line, ft_strlen(line));
            write(hrdc_fd, "\n", 1);
        }
        close(hrdc_fd);
        hrdc_fd = open("heredoc_test.txt", O_RDONLY); // kapatıp tekrar açıyoruz, sadece RDONLY için.
        if (hrdc_fd != -1)
        {
            dup2(hrdc_fd, STDIN_FILENO);
            close(hrdc_fd);
        }
    }
}
void	pipeline_in_out_app_hrdc(t_command *tmp)
{
    pipeline_heredoc(tmp);
	pipeline_infile(tmp);
	pipeline_out_app(tmp);
}