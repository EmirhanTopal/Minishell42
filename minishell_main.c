#include "minishell.h"

int g_last_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
    t_command *cmd1;
    t_command *cmd2;

    cmd1 = malloc(sizeof(t_command));
    cmd2 = malloc(sizeof(t_command));
    if (!cmd1)
        return(1);

    char *end_cmd1[] = {"cd" ,NULL};
    cmd1->argv = end_cmd1;
    cmd1->is_builtin = ft_is_builtin(cmd1->argv[0]);
    cmd1->next = cmd2;

    char *end_cmd2[] = {"pwd", NULL};
    if (!cmd2)
        return(1);
    cmd2->argv = end_cmd2;
    cmd2->is_builtin = ft_is_builtin(cmd2->argv[0]);
    cmd2->next = NULL;
    (void)argc;
    (void)argv;

    t_command *cmd = cmd1;
    while (cmd)
    {
        if (cmd->is_builtin)
			execute_builtin_command(cmd);
        else
			execute_not_builtin_command(cmd, envp);
        cmd = cmd->next;
    }
	free(cmd);
	return (0);
}
