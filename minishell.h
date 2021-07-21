#ifndef MINISHELL_H
#define MINISHELL_H

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./libft/libft.h"
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

int	g_flag;
int	g_flag2;
int error_file;
int test;


typedef struct	s_glob
{
	int flag;
}				t_glob;

typedef struct	s_command
{
	char 		**arg;
	int 		fd_in;
	int			fd_out;
	int			file_error;
	int 		flag; //shell flag
}				t_command;

typedef struct 	s_minishell
{
	t_command 	**commands;
	char 		**envp;
	int 		n_cmd;
	int 		status;
	int			flag;
}				t_minishell;

typedef struct	s_index
{
	int 		start;
	int 		end;
}				t_index;

t_glob glob;

//parser
int		parse(char *line, t_minishell *minishell);
int		ft_isspace(char c);
t_index	get_index(t_minishell *minishell, char *line, int i);
int		get_n_commands(char *line);
int		get_cmd_n_rdr(t_minishell *minishell, char *line, t_index index, int i);
char	*cjoin(char *line, char c);
int		is_quoted(char *str, int j);
int 	save_arg(t_list **head, char **arg);
int		parse_and_create_command(t_minishell *minishell, char *arg, char *redir,
									int i);
int		handle_redir(t_command *command, char *redir, char **envo);
int		handle_single_quote(char *line, int *i, char **current);
int		handle_double_quote(char *line, int *i, char **current, char **envp);
int		handle_rest(char *line, int *i, char **current);
int		get_dollar2(char **str, int *i, char **envp);
int		handle_dollar_with_quotes(char **str, char **envp);
int		get_dollar(char **str, int *i, char **envp);
int		handle_dollar(char *arg, char **current, int *i, char **envp);
int		handle_exec(t_minishell *minishell);
int		binarize(t_minishell *minishell, t_command *command);
void	free_minishell(t_minishell *minishell);
void	free_list(t_list *head);
void	free_arr(char **arr);
void	handle_sig2(int signo);
void	handle_sig3(int sig);
int		ft_strcmp(char *arg, char *builtin);

void	handle_signals(int signo);
void	update_env(t_minishell *minishell, char *new_value);

//builtin
int		handle_builtin(char **args, t_minishell *minishell);
char	*minimize_arg(char *arg);
int		builtin_env(char **args);
void	builtin_exit(void);
int		builtin_pwd(char **env);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_minishell *minishell);
int		builtin_export(char **args);
int		builtin_unset(char **args);



#endif
