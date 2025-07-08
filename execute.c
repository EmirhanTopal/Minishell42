#include "minishell.h"

void	execute_not_builtin_command(t_command *cmd, char **envp)
{
	pid_t pid;
	char *path;

	pid = fork();
	path = find_path(envp, cmd->argv);
	if (path == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 21);
		exit(127);
	}
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0) // child process
	{
		execve(path, cmd->argv, envp);
		perror("execve");
		exit(127);
	}
	else
		get_signal(pid);
}

int	ft_is_builtin(char *cmd)
{
	if (!cmd)
        return 0;
	return (!ft_strcmp(cmd, "cd") ||
            !ft_strcmp(cmd, "echo") ||
            !ft_strcmp(cmd, "exit") ||
            !ft_strcmp(cmd, "pwd") ||
            !ft_strcmp(cmd, "env") ||
            !ft_strcmp(cmd, "export") ||
            !ft_strcmp(cmd, "unset"));
}

void	execute_builtin_command(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		builtin_echo(cmd->argv);
    else if (!ft_strcmp(cmd->argv[0], "pwd"))
		builtin_pwd();
	else if (!ft_strcmp(cmd->argv[0], "exit"))
        builtin_exit(cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		builtin_cd(cmd);
	// else if (!strcmp(cmd->argv[0], "env"))
	// 	builtin_env(cmd->argv);
	// else if (!strcmp(cmd->argv[0], "export"))
	// 	builtin_export(cmd->argv);
	// else if (!strcmp(cmd->argv[0], "unset"))
	// 	builtin_unset(cmd->argv);
}

void	get_signal(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_last_exit_status = 128 + WTERMSIG(status); 
	else
		g_last_exit_status = 1; // bilinmeyen durum
}