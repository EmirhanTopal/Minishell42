#include "minishell.h"

static	void	pipeline_child_process(t_command *tmp, int *fd, int prev_fd)
{
	pipeline_in_out_app_hrdc(tmp);
	if (prev_fd != -1) // örneğin ls grep wc komutları arasında 2. komuttaysak prev_fd = fd[0] olur. 
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (!tmp->outfile && tmp->next) // eğer tek komut değilse birden fazla komut varsa
	{
		close(fd[0]); // pipe okuma ucunu kapat çünkü yazma yapacağım pipe ın read ucu ile işim yok.
		dup2(fd[1], STDOUT_FILENO); // fd[1] artık stdout un bir kopyası yani bundan sonra stdout a yönlendirilenler fd[1] e yönlendirilecek.
		close(fd[1]); // pipe yazma ucunu kapat
	}
}

static	void	pipeline_parent_process(t_command *tmp, int *fd, int *prev_fd)
{
	if ((*prev_fd) != -1) // eğer parent da kapatma işlemi yapılmazsa ve bir sonraki komut yok ise. fd[0] açık kalacağı için read bekler, eğer zaten bir sonraki komut var ise tekrardan pref_fd yi güncelleriz.
		close((*prev_fd));
	if (!tmp->outfile && tmp->next)
	{
		(*prev_fd) = fd[0];
		close(fd[1]);
	}
}

static	void	pipeline_error()
{
	perror("fork");
	exit(1);
}

static	void	pipeline_execute(t_command *tmp, t_shell *shell, char **envp)
{
	if (tmp->is_builtin)
		execute_builtin_command(tmp, shell);
	else
		execute_not_builtin_command(tmp, envp);
}

void	execute_pipeline(t_command *cmd, t_shell *shell, char **envp)
{
    int			fd[2];
    pid_t		pid;
	int			prev_fd;
    t_command	*tmp;

	tmp = cmd;
	prev_fd = -1;
	while (tmp)
	{
		if (!tmp->outfile && tmp->next)
        	pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			pipeline_child_process(tmp, fd, prev_fd);
			pipeline_execute(tmp, shell, envp);
			exit(g_last_exit_status);
		}
		else if (pid < 0)
			pipeline_error();
		pipeline_parent_process(tmp, fd, &prev_fd);
		tmp = tmp->next;
	}
	while (wait(NULL) > 0); // wait() çağrısı, bir child process bitince onun PID’sini döner. Eğer bekleyecek child kalmadıysa -1 döner.
}
