/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 13:18:47 by elduran           #+#    #+#             */
/*   Updated: 2025/07/21 22:02:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD			0
# define PIPE			1
# define GREAT			2
# define LESS			3
# define DOUBLE_GREAT	4
# define DOUBLE_LESS	5

extern int	g_last_exit_status;

typedef enum e_quote
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote;

typedef struct s_token
{
	int				type;
	char			*value;
	t_quote			quote;
	struct s_token	*next;
}	t_token;

typedef struct s_parse
{
	char			**args;
	int				infile;
	int				outfile;
	int				type;
	int				is_builtin;
	int				error_printed;
	struct s_parse	*next;
}	t_parse;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*shell_env;
}	t_shell;

// buildin && builtin_util
void	builtin_cd(t_parse *cmd);
void	print_cd_err(char *msg);
void	update_pwd_vars(char *oldpwd);
void	cd_go_env(char *var);

void	builtin_echo(char **args, char **envp);
char	*get_env_value(char **env, char *key);
void	dolar_sign_echo(char *args, char **envp);

void	builtin_env(t_parse *cmd, t_shell *shell);
t_env	*init_env(char **envp);
void	add_env_node_back(t_env **head, t_env *node);
void	free_env(t_env *env);

void	builtin_exit(t_parse *cmd, t_shell *shell);

void	builtin_export(t_parse *cmd, t_shell *shell);
t_env	*copy_env_lst(t_env *orj_env);
t_env	*sort_env_lst(t_env *orj_env);
void	print_env_export(t_env *env);
void	export_help(t_env *new_copy_env);
int		export_help_2(t_shell *shell, char *arg_key, char *arg_value);
void	export_without_argument(t_parse *cmd, t_shell *shell);
void	export_add_env(t_shell *shell, char *arg_value, char *arg_key);
void	exp_eql_ptr_ctrl(t_parse *cmd, int *key_len, int i, char **arg_value);

void	builtin_pwd(void);

void	builtin_unset(t_parse *cmd, t_shell *shell);
void	unset_key_free(t_env *tmp_env);

// execute
char	*check_path(char **paths, char *cmd);
char	*find_path(char **env, char **cmd);
void	execute_not_builtin_command(t_parse *cmd, char **envp);
void	execute_builtin_command(t_parse *cmd, t_shell *shell, char **envp);

// free
char	*ft_strjoin_free(char *s1, const char *s2);
void	ft_db_free(char **double_pointer);
void	ft_free_tokens(t_token *tokens);
void	ft_free_parse(t_parse *cmd);

// lexer
void	ft_skip_whitespace(char *input, int *i);
int		ft_handle_operator(char *input, int *i);
char	*ft_operator_value(int type);
void	ft_add_token(t_token **head, t_token *new);
t_token	*ft_create_token(int type, char *value, t_quote quote);
int		ft_handle_quote(char *line, int *i, t_token **tokens);
char	*ft_handle_word(char *input, int *i, t_quote *out_quote);
t_token	*ft_lexer(char *input);

// parser
char	**ft_collect_args(t_token *tokens);
void	ft_handle_redirection(t_parse *node, t_token *token);
void	ft_expand_tokens(t_token *tokens);
int		ft_is_builtin(const char *cmd);
t_parse	*ft_parser(t_token *tokens);

// pipeline && redirections
void	execute_pipeline(t_parse *cmd, t_shell *shell, char **envp);
void	pipeline_infile(t_parse *tmp);
void	pipeline_out_app(t_parse *tmp);
void	pipeline_heredoc(t_parse *cmd);
void	pipeline_in_out_app_hrdc(t_parse *tmp);

// signal
void	get_signal(pid_t pid);

// util
long	ft_atoi(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		is_numeric(char *str);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
