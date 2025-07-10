# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>

extern int g_last_exit_status;

typedef struct s_command 
{
    char **argv;               // Komut ve argümanlar ["ls", "-l", NULL]
    char *infile;              // "< input.txt" varsa burada tutulur
    char *outfile;             // "> output.txt" veya ">> append.txt"
    int append;                // >> varsa 1, > varsa 0
    char *heredoc_delim;       // << varsa burada delimiter saklanır
    int is_builtin;              // Built-in komut mu? (1 = evet, 0 = hayır)
    struct s_command *next;    // Pipe varsa sonraki komutu gösterir
} t_command;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_shell
{
    t_env *shell_env;
} t_shell;



void	execute_not_builtin_command(t_command *cmd, char **envp);
void	execute_builtin_command(t_command *cmd, t_shell *shell);
int     ft_strcmp(char *s1, char *s2);
void	get_signal(pid_t pid);
char	*check_path(char **paths, char *cmd);
char	*find_path(char **env, char **cmd);
void	ft_db_free(char **double_pointer);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
int     ft_is_builtin(char *cmd);
void    builtin_echo(char **argv);
void    builtin_pwd();
void    builtin_exit(t_command *cmd);
void    builtin_cd(t_command *cmd);
void    builtin_env(t_command *cmd, t_shell *shell);
void    builtin_export(t_command *cmd, t_shell *shell);
t_env	*init_env(char **envp);
void	add_env_node_back(t_env **head, t_env *node);
void	free_env(t_env *env);
int     is_numeric(char *str);
int     ft_atoi(char *str);
char	*ft_strchr(const char *s, int c);
char    *ft_strndup(const char *s, size_t n);
char	*ft_strdup(const char *s1);