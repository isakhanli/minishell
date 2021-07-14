#ifndef NINISHELL_H
#define NINISHELL_H

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

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct	s_command
{
	char 		**arg;
	int 		fd_in;
	int			fd_out;
	int 		pipe[2];
}				t_command;

typedef struct 	s_minishell
{
	t_command 	**commands;
	char 		**envp;
	int 		n_cmd;
	int 		status;
}				t_minishell;

typedef struct	s_index
{
	int 		start;
	int 		end;
}				t_index;




//parser
int parse(char *line, t_minishell *minishell, char **envp);
int ft_isspace(char c);
t_index get_index(t_minishell *minishell, char *line, int i);
int	get_n_commands(char *line);
int	add_command(t_minishell *minishell, char *line, t_index index, int i);
char *cjoin(char *line, char c);
int is_quoted(char *str, int j);
int 	save_arg(t_list **head, char **arg);
int	parse_and_create_command(t_minishell *minishell, char *arg, char *redir,
								int i);
int handle_redir(t_command *command, char *redir, char **envo);

int	handle_single_quote(char *line, int *i, char **current);
int	handle_double_quote(char *line, int *i, char **current, char **envp);
int handle_other(char *line, int *i, char **current);
int get_dollar2(char **str, int *i, char **envp);

int handle_dollar_with_quotes(char **str, char **envp);
int		get_dollar(char **str, int *i, char **envp);
int 	handle_dollar(char *arg, char **current, int *i, char **envp);

//list
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);


//exec
int		handle_exec(t_minishell *minishell, t_command *command, int odd[],
					   int even[], int i);
int binarize(t_minishell *minishell, t_command *command);

#endif
