#include "minishell.h"

char	*check_path(char **paths, char *cmd)
{
	int		j;
	char	*full_path;
	char	*temp_path;

	j = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[j])
	{
		temp_path = ft_strjoin(paths[j], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!access(full_path, X_OK | F_OK))
			return (full_path);
		free(full_path);
		j++;
	}
	return (NULL);
}

char	*find_path(char **env, char **cmd)
{
	int		i;
	char	**paths;
	char	*full_path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			full_path = check_path(paths, cmd[0]);
			ft_db_free(paths);
			if (!full_path)
				return (NULL);
			return (full_path);
		}
		i++;
	}
	return (NULL);
}