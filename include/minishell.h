#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "./libft/libft.h"
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_glob
{
	int			sig_flag;
	int			status;
	int			heredoc_index;
	int			file_error;
}				t_glob;

typedef struct s_command
{
	char		**arg;
	char		*cmd;
	int			fd_in;
	int			fd_out;
	char		*heredoc;
	int			file_error;
}				t_command;

typedef struct s_minishell
{
	t_command	*commands[1024];
	char		**envp;
	int			n_cmd;
}				t_minishell;

typedef struct s_index
{
	int			start;
	int			end;
}				t_index;

t_glob	g_glob;

int				parse(char *line, t_minishell *minishell);
int				ft_isspace(char c);
t_index			get_index(t_minishell *minishell, char *line, int i);
int				get_n_commands(char *line);
int				get_cmd_n_rdr(t_minishell *minishell, char *line,
					t_index index, int i);
char			*cjoin(char *line, char c, int flag);
int				is_quoted(char *str, int j);
int				save_arg(t_list **head, char **arg);
int				parse_n_create_cmd(t_minishell *minishell,
					char *arg, char *redir, int i);
int				handle_redir(t_command *command, char *redir, char **envo);
int				handle_single_quote(char *line, int *i, char **current);
int				handle_double_quote(char *line, int *i, char **current,
					char **envp);
int				handle_rest(char *line, int *i, char **current);
int				get_dollar2(char **str, int *i, char **envp);
int				handle_dollar_with_quotes(char **str, char **envp);
int				handle_dollar(char *arg, char **current, int *i, char **envp);
int				handle_exec(t_minishell *minishell);
int				binarize(t_minishell *minishell, t_command *command);
void			free_minishell(t_minishell *minishell);
void			free_list(t_list *head);
void			free_arr(char **arr);
void			handle_ctrl_c(int signo);
int				ft_strcmp(char *arg, char *builtin);
int				is_builtin(char *str);
int				check_input(char *arg);
int				just_space(char *line);
int				count_array_lines(char **arr);
char			**define_env(char **envp);
int				parse_cmd_n_rdr(char *line, char **redir, char **cmd);
int				get_start(char *line, int i);
int				get_end(t_minishell *minishell, char *line, int i);
int				is_redir(char *cmd, int i);
int				get_file(char *redir, char **file, int *i, int k);
int				is_redir_sym(char *red, int i);
int				handle_heredoc(t_command *command, char **file, char **envp);
int				get_var(char **var, char *str, int k);
int				get_var_value(char **value, char *var, char **envp);
int				handle_status_code(char **current, int *i);
int				has_dollar(char *input);
int				handle_read_and_write(t_command *command, char **file,
					char **envp);
int				create_pipe(int size, int fd[][2]);
int				close_pipes(int size, int fd[][2]);
void			handle_pipes_redirs(t_minishell *minishell, int i, int fd[][2]);
void			handle_exit(t_command *command, char **envp);
int				is_builtin(char *str);
char			*ft_strjoin2(char **s1, char **s2);
int				handle_unlink(t_minishell *minishell);
int				handle_file_error(int ret, char **file);
int				free_n_return(int ret, char **str);
int				check_bin(char *str);
int				error_message(char *msg, char *cmd, int ret);
int				execute_builtin2(t_minishell *minishell, int i);
void			handle_signals(int signo);
int				count_array_lines(char **arr);
int				count_arguments(char **args);
int				update_env(char **env, char *new_value, char *arg, int size);
int				get_env_id(char **env, char *env_param, int len_param);
char			*get_env_value(char **env, char *env_param);
char			*get_env_param(char **env, char *env_param);
int				env_param_update(char *args, int len, t_minishell *minishell);
int				sort_env(char **arr);
char			**realloc_env(t_minishell *minishell, char *param, char *value);
void			handle_cd_error(char *path, int err);
void			handle_builtin_error(char *path, char *func_name);
int				wrong_export_arg(char *arg, char *func_name);
int				wrong_unset_arg(char *arg, char *func_name);
int				handle_builtin(char **args, t_minishell *minishell, int len);
char			*minimize_arg(char *arg);
int				builtin_env(char **args);
int				builtin_exit(char **args);
int				builtin_pwd(int i);
int				builtin_echo(char **args, int i, int flag_n);
int				builtin_cd(char **args, t_minishell *minishell);
int				builtin_export(char **args, t_minishell *minishell, int i);
int				builtin_unset(char **args, t_minishell *minishell);
int				check_path(char **envp);
long long int	ft_atoi2(const char *str);

#endif
