#include "minishell.h"

int g_last_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
    t_command *cmd1;
    t_command *cmd2;
    t_shell *shell;
    cmd1 = malloc(sizeof(t_command));
    cmd2 = malloc(sizeof(t_command));
    shell = malloc(sizeof(t_shell));
    if (!cmd1)
        return(1);

    char *end_cmd1[] = {"ls", NULL};
    cmd1->argv = end_cmd1;
    cmd1->is_builtin = ft_is_builtin(cmd1->argv[0]);
    cmd1->next = cmd2;
    char *end_cmd2[] = {"grep", "a", NULL};
    cmd2->argv = end_cmd2;
    cmd2->is_builtin = ft_is_builtin(cmd1->argv[0]);
    cmd2->next = NULL;
    (void)argc;
    (void)argv;

    t_command *cmd = cmd1;
    shell->shell_env = init_env(envp);
    execute_pipeline(cmd, shell, envp);
	free(cmd1);
    free_env(shell->shell_env);
    free(shell);
	return (0);
}
