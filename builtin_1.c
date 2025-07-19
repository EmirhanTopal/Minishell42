#include "minishell.h"

void    builtin_echo(char **argv, char **envp)
{
    int i;
	int ctrl;
    
    i = 1;
	ctrl = ft_strcmp(argv[i], "-n");
    if (argv[i] && !ctrl)
        i++;
    while (argv[i])
    {
		if (argv[i][0] == '$')
			dolar_sign_echo(argv[i], envp);
        else
			write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
        i++;
    }
    if (ctrl)
        write(1, "\n", 1);
}
void    builtin_pwd()
{
	char buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX) == NULL)
	{
		perror("pwd");
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
}
void	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	if (cmd->argv[1] && !is_numeric(cmd->argv[1]))
	{
		write(2, "exit: ", 6);
		write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(2, ": numeric argument required\n", 28);
		free_env(shell->shell_env);
		free(cmd);
		free(shell);
		exit(255);
	}
	else if (cmd->argv[1] && cmd->argv[2])
	{
		write(2, "exit: too many arguments\n", 26);
		return ;
	}
	if (cmd->argv[1])
		exit_status = ft_atoi(cmd->argv[1]) % 256;
	write(1, "exit\n", 5);
	free_env(shell->shell_env);
	free(cmd);
	free(shell);
	exit(exit_status);
}

void	builtin_cd(t_command *cmd)
{
	char	*oldpwd;

	oldpwd = getenv("PWD");
	if (cmd->argv[1] && cmd->argv[2])
		print_cd_err("too many arguments");
	else if (!cmd->argv[1])
		cd_go_env("HOME");
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		cd_go_env("OLDPWD");
		if (getenv("OLDPWD"))
		{
			write(1, getenv("OLDPWD"), ft_strlen(getenv("OLDPWD")));
			write(1, "\n", 1);
		}
	}
	else if (chdir(cmd->argv[1]) == -1)
		print_cd_err(cmd->argv[1]);
	else
		update_pwd_vars(oldpwd);
}
