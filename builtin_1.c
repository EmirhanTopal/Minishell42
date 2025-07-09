#include "minishell.h"

void    builtin_echo(char **argv)
{
    int i;
	int ctrl;
    
    i = 1;
	ctrl = ft_strcmp(argv[i], "-n");
    if (argv[i] && !ctrl)
        i++;
    while (argv[i])
    {
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
void    builtin_exit(t_command *cmd)
{
    int n;

    n = 0;
    if (!is_numeric(cmd->argv[1]) && cmd->argv[1])
    {
        write(2, "exit: ", 6);
        write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
        write(2, ": numeric argument required\n", 28);
        exit(255);
    }
    else if(cmd->argv[2] && cmd->argv[1])
    {
        write(2, "exit: ", 6);
        write(2, ": too many arguments\n", 21);
    }
    else if(cmd->argv[1] != NULL)
    {
        n = ft_atoi(cmd->argv[1]);
        write(2, "exit\n", 5);
        exit(n % 256);
    }
    else
       exit(0);
}

static  void cd_help(char *env_str, char *oldpwd, char *cwd)
{
	char *get_env;

	get_env = getenv(env_str);
	if (!get_env)
	{
		write(2, "cd: ", 4);
		write(2, env_str, ft_strlen(env_str));
		write(2, " not set\n", 9);
		g_last_exit_status = 1;
		return ;
	}
    chdir(get_env);
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("cd");
        return ;
    }
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", cwd, 1);
	g_last_exit_status = 0;
}
void    builtin_cd(t_command *cmd)
{
    char *oldpwd = getenv("PWD");
    char cwd[PATH_MAX];
    if (cmd->argv[2] != NULL && cmd->argv[1])
    {
        write(2, "cd: too many arguments", 23);
		g_last_exit_status = 1;
    }
    else if (cmd->argv[1] == NULL)
        cd_help("HOME", oldpwd, cwd);
    else if (ft_strcmp(cmd->argv[1], "-") == 0 && cmd->argv[1] != NULL)
    {
        cd_help("OLDPWD", oldpwd, cwd);
        write(1, cwd, ft_strlen(cwd));
        write(1, "\n", 1);
    }
    else if (cmd->argv[1] != NULL)
    {
        if (chdir(cmd->argv[1]) == -1)
        {
            write(2, "cd: ", 4);
            write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
            write(2, ": No such file or directory", 27);
			g_last_exit_status = 1;
        }
    }
}
