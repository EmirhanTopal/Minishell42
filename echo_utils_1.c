#include "minishell.h"

char	*get_env_value(char **env, char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len) && env[i][len] == '=')
			return (env[i] + len + 1); // "USER=emtopal" → "emtopal"
		i++;
	}
	return (NULL);
}

void    dolar_sign_echo(char *argv, char **envp)
{
    char    *value;

    if (!ft_strcmp(argv, "$?"))
        write(1, ft_itoa(g_last_exit_status), 3);
    value = get_env_value(envp, argv + 1);
    if (value)
        write(1, value, ft_strlen(value));
    else
        write(1, "", ft_strlen(""));
}