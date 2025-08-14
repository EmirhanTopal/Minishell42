/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elduran <elduran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:17:53 by elduran           #+#    #+#             */
/*   Updated: 2025/08/10 14:22:13 by elduran          ###   ########.fr       */
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
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WORD			0
# define PIPE			1
# define GREAT			2
# define LESS			3
# define DOUBLE_GREAT	4
# define DOUBLE_LESS	5

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
	t_env			*shell_env;
	char			*input;
	char			**envp;
	int				exit_code;
}	t_shell;

typedef struct s_helper
{
	t_shell			*shell;
	t_token			*tokens;
	t_parse			*head;
}	t_helper;

// cd_1.c
char	*ft_get_env(char *var, t_shell *shell);
void	builtin_cd(t_parse *cmd, t_shell *shell);

// cd_2.c
void	ft_print_cd_err(char *msg);
void	ft_update_pwd_vars(char *oldpwd);
void	ft_cd_go_env(char *var, t_shell *shell);

// echo_1.c
void	builtin_echo(char **args);

// env_1.c
void	ft_add_env_node_back(t_env **head, t_env *node);
t_env	*ft_init_env(char **envp);
void	builtin_env(t_parse *cmd, t_shell *shell);

// exit_1.c
void	builtin_exit(t_parse *cmd, t_shell *shell, t_token *tokens);

// export_1.c
void	builtin_export(t_parse *cmd, t_shell *shell);

// export_2.c
int		ft_export_helper_1(t_parse *cmd, t_shell *shell);
int		ft_is_valid_identifier(const char *str);
void	ft_exp_eql_ptr_ctrl(t_parse *cmd,
			int *key_len, int i, char **arg_value);
void	ft_export_add_env(t_shell *shell, char *arg_value, char *arg_key);

// export_3.c
void	ft_export_without_argument(t_parse *cmd, t_shell *shell);

// pwd_1.c
void	builtin_pwd(void);

// unset_1.c
void	builtin_unset(t_parse *cmd, t_shell *shell);

// execute_1.c
void	ft_execute_pipeline(t_parse *cmd, t_shell *shell, t_token *tokens);
void	ft_execute_builtin_command(t_parse *cmd, t_shell *shell, t_token *tkns);

// execute_2.c
void	ft_one_step(t_parse **tmp, int *prev_fd, t_helper *h, pid_t *last_pid);

// execute_3.c
void	ft_child_exec(t_parse *tmp, int fd[2], int prev_fd, t_helper *h);

// execute_4.c
void	ft_pipeline_execute(t_parse *tmp,
			t_shell *shell, t_token *tokens, t_parse *head);

// execute_5.c
char	*ft_check_path(char **paths, char *cmd);
char	*ft_find_path(t_shell *shell, char **cmd);
void	ft_exc_null_path(t_parse *cmd,
			t_shell *shell, t_token *tokens, t_parse *head);

// expand_1.c
void	ft_expand_tokens(t_token *tokens, t_shell *shell);

// expand_2.c
char	*ft_expand_var(const char *str, int exit_status, t_shell *shell);

// free_1.c
int		ft_last_exit(int flag);
char	*ft_strjoin_free(char *s1, const char *s2);
void	ft_free_helper(t_parse *cmd, t_shell *shell, t_token *tokens);
void	ft_db_free(char **double_pointer);

// free_2.c
void	ft_free_env(t_env *shell_env);
void	ft_free_tokens(t_token *tokens);
void	ft_free_parse(t_parse *parse);
void	ft_free_all(t_shell *shell, t_token *tokens, t_parse *cmd);

// input_1.c
int		ft_handle_incomplete_input(char **input, t_token **tokens);

// lexer_1.c
t_token	*ft_lexer(char *input);

// lexer_2.c
int		ft_handle_operator(char *input, int *i);
char	*ft_operator_value(int type);
void	ft_add_token(t_token **head, t_token *new);
t_token	*ft_create_token(int type, char *value, t_quote quote);
int		ft_isspace(char c);

// lexer_3.c
char	*ft_handle_word(char *input, int *i, t_quote *out_quote);

// parser_1.c
t_parse	*ft_parser(t_token *tokens, t_shell *shell);

// parser_2.c
void	ft_handle_redirection(t_parse *node, t_token *token, t_shell *shell);

// parser_3.c
void	ft_heredoc_helper_1(t_parse *node,
			t_token *tokens, t_shell *shell, int pipe_fd[2]);
void	ft_heredoc_child(char *delimiter, int pipe_fd[2], t_helper *h);
void	ft_heredoc_helper_2(t_parse *node, int pipe_fd[2]);

// parser_4.c
char	**ft_collect_args(t_token *tokens);
int		ft_is_builtin(const char *cmd);

// signal_1.c
void	ft_signal_handler(int mode);

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

int		ft_syntax_check(t_token *t);

#endif